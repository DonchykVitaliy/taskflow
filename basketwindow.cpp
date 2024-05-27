#include "basketwindow.h"
#include "ui_basketwindow.h"
#include <QPixmap>
#include <QWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QTimer>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QFont>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

BasketWindow::BasketWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BasketWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500,650)); //вимкнення зміни розміру вікна

    QDir dir("delete");
    if (!dir.exists())
        dir.mkpath(".");
    QStringList filters;
    filters << "*.txt"; // Фільтр для текстових файлів

    QStringList curFiles = dir.entryList(filters, QDir::Files);

    if (curFiles.isEmpty()) {
        ui->EmptyLine->setVisible(true);
        ui->EmptyText->setVisible(true);
        ui->clearButton->setVisible(false);

        qDebug() << "Директорія не містить файлів";
    } else {
        ui->EmptyLine->setVisible(false);
        ui->EmptyText->setVisible(false);
        ui->clearButton->setVisible(true);
    }


    QVBoxLayout *layout = new QVBoxLayout;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {


        QStringList currentFiles = dir.entryList(filters, QDir::Files);


        if (currentFiles.isEmpty()) {
            ui->EmptyLine->setVisible(true);
            ui->EmptyText->setVisible(true);
            ui->clearButton->setVisible(false);

            qDebug() << "Директорія не містить файлів";
        } else {
            ui->EmptyLine->setVisible(false);
            ui->EmptyText->setVisible(false);
            ui->clearButton->setVisible(true);
        }


        // Визначення видалених файлів
        QStringList deletedFiles;
        for (const QString &fileName : addedFiles) {
            if (!currentFiles.contains(fileName)) {
                deletedFiles << fileName;
            }
        }

        // Видалення віджетів відповідних видаленим файлам
        QList<QWidget*> widgetsToRemove;
        for (const QString &deletedFile : deletedFiles) {
            for (int i = 0; i < layout->count(); ++i) {
                QLayoutItem *layoutItem = layout->itemAt(i);
                QWidget *widget = layoutItem->widget();
                if (widget && widget->property("FileName").toString() == deletedFile) {
                    qDebug() << "Deleting widget for file:" << deletedFile;

                    // Знаходимо віджети QLabel, QTextBrowser та QPushButton
                    QLabel *labelFileName = widget->findChild<QLabel *>();
                    QTextBrowser *textBrowser = widget->findChild<QTextBrowser *>();
                    QPushButton *deleteButton = widget->findChild<QPushButton *>();
                    QPushButton *completeButton = widget->findChild<QPushButton *>();

                    if (labelFileName) {
                        addedFiles.remove(labelFileName->property("FileName").toString());
                        labelFileName->deleteLater();
                    }

                    if (textBrowser) {
                        addedFiles.remove(textBrowser->property("FileName").toString());
                        widgetsToRemove << textBrowser;
                    }

                    if (deleteButton) {
                        deleteButton->deleteLater();
                    }

                    if (completeButton) {
                        completeButton->deleteLater();
                    }

                    // Оновлення множини доданих файлів
                    addedFiles.remove(deletedFile);

                    // Додаємо видаляємий віджет до списку для подальшого видалення
                    widgetsToRemove << widget;
                }
            }
        }

        // Видаляємо віджети зі списку layout
        for (QWidget *widget : widgetsToRemove) {
            layout->removeWidget(widget);
            widget->deleteLater();
        }

        // Додаємо нові файли та оновлюємо множину доданих файлів
        for (const QString &fileName : currentFiles) {
                // Перевірка, чи файл вже був доданий
                if (addedFiles.contains(fileName)) {
                    continue;  // Пропустити цикл для цього файлу
                }
    QFile file(dir.filePath(fileName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContent = in.readAll();

        QLabel *labelFileName = new QLabel(this);
        QString TitleFile = fileName;
        TitleFile.chop(4);
        labelFileName->setText("Назва нотатки: " + TitleFile);
        QFont fontTitle = labelFileName->font();
        fontTitle.setPointSize(14);
        labelFileName->setFont(fontTitle);
        labelFileName->setStyleSheet("color: dark_gray;");
        labelFileName->setProperty("FileName", fileName);

        QTextBrowser *textBrowser = new QTextBrowser(this);
        textBrowser->setPlainText(fileContent + "\n");
        QFont fontText = textBrowser->currentFont();
        fontText.setPointSize(14);
        textBrowser->setCurrentFont(fontText);
        textBrowser->setStyleSheet("border-radius: 10px;border: none;color:rgb(85, 85, 85);font: 9pt;background-color: rgb(223, 223, 223);");
        textBrowser->setProperty("FileName", fileName);

        QPushButton *deleteButton = new QPushButton("Видалити нотатку", this);
        deleteButton->setProperty("FileName", fileName);
        connect(deleteButton, &QPushButton::clicked, this, &BasketWindow::deleteFile);
        deleteButton->setStyleSheet(
            "QPushButton {"
            "   background-color: rgb(235, 94, 0);"
            "   color: white;"
            "   font: 11pt 'Britannic Bold';"
            "   border-radius: 6px;"
            "}"

            "QPushButton:hover {"
            "   background-color: rgb(200, 60, 0);"
            "}"
        );

        QPushButton *backButton = new QPushButton("Відновити", this);
        backButton->setProperty("FileName", fileName);
        connect(backButton, &QPushButton::clicked, this, &BasketWindow::backFile);
        backButton->setStyleSheet(
            "QPushButton {"
            "   background-color: rgb(235, 94, 0);"
            "   color: white;"
            "   font: 11pt 'Britannic Bold';"
            "   border-radius: 6px;"
            "}"

            "QPushButton:hover {"
            "   background-color: rgb(200, 60, 0);"
            "}"
            );

        layout->addWidget(labelFileName);
        layout->addWidget(textBrowser);
        layout->addWidget(deleteButton);
        layout->addWidget(backButton);

        // Оновлення множини доданих файлів
        addedFiles.insert(fileName);

        file.close();
    } else {
        qDebug() << "Помилка відкриття файлу:" << fileName;
        }
    }
});

    timer->start(1000);  // Таймер викликає цикл кожну секунду

    // Створення QWidget для використання QVBoxLayout
    QWidget *widget = new QWidget(this);
    widget->setGeometry(50, 100, 400, 520);
    widget->setLayout(layout);
}

void BasketWindow::backFile()
{
    QPushButton *backButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (backButton) {
    QString fileName = backButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
    QString noteDirectory = "note";
    QString deleteDirectory = "delete";
    QString filePathNote = QDir(noteDirectory).filePath(fileName);
    QString filePathDelete = QDir(deleteDirectory).filePath(fileName);

    // Переміщення файлу до директорії "delete"
    if (QFile::rename(filePathDelete, filePathNote)) {
        qDebug() << "Файл успішно переміщено в директорію 'delete':" << fileName;
    } else {
        qDebug() << "Помилка переміщення файлу в директорію 'delete':" << fileName;
        QMessageBox::critical(this, "Помилка", "Не вдалося перемістити файл.");
        return; // Вихід з функції у випадку помилки переміщення
    }
    }
}


void BasketWindow::deleteFile()
{
    QPushButton *deleteButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (deleteButton) {
    QString fileName = deleteButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
    QString deleteDirectory = "delete";
    QString filePath = QDir(deleteDirectory).filePath(fileName);

    // Видалення файлу
    if (QFile::remove(filePath)) {
        qDebug() << "Файл успішно видалено:" << fileName;
    } else {
        qDebug() << "Помилка видалення файлу:" << fileName;
        QMessageBox::critical(this, "Помилка", "Не вдалося видалити файл.");
    }
    }
}


BasketWindow::~BasketWindow()
{
    delete ui;
}

void BasketWindow::on_clearButton_clicked()
{
    QDir dirDelete("delete");
    QStringList files = dirDelete.entryList(QDir::Files);

    // Видалення кожного файлу
    foreach (const QString &file, files) {
    QString filePath = dirDelete.filePath(file);
    if (QFile::remove(filePath)) {
        qDebug() << "Файл видалено:" << filePath;
    } else {
        qDebug() << "Помилка видалення файлу:" << filePath;
    }
    }
}

