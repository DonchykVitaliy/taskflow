#include "folderwindow.h"
#include "ui_folderwindow.h"
#include "creatfolderwindow.h"
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
#include <QLabel>
#include <QLineEdit>

FolderWindow::FolderWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(800,600)); //вимкнення зміни розміру вікна

    int countDone = 0;
    int countDel = 0;
    int countNote = 0;

// Шлях до файлу
    QString filePath = "stat/stat.txt";
    QFile file(filePath);

    // Створення QLabel для відображення числа
    QLabel *label = new QLabel(this);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        // Читання значення з першого рядка
        QString line = in.readLine();
        bool conversionOk;
        int value = line.toInt(&conversionOk);
        // Перевірка, чи вдалося сконвертувати рядок в число
        if (conversionOk) {
            // Відображення значення у QLabel
            label->setText("Всього завершаних нотаток: " + QString::number(value));
            label->setStyleSheet("font-size: 20px; color: black;");
            label->setGeometry(25, 30, 360, 50); // Встановлення координат і розмірів
            countDone = value * 5;
        } else {
            qDebug() << "Помилка конвертації значення з файлу:" << filePath;
        }
        // Закриття файлу
        file.close();
    } else {
        qDebug() << "Помилка відкриття файлу для читання:" << filePath;
    }
    qDebug() << countDone;

    //Створення QLabel для відображення кількості нотаток
    QString directoryPath = "note";
    // Отримати список файлів у директорії
    QDir directory(directoryPath);
    QStringList files = directory.entryList(QDir::Files);
    // Розмір списку - кількість файлів
    int fileCount = files.size();
    QLabel *labelNote = new QLabel(this);
            labelNote->setText("Не завершаних нотаток: " + QString::number(fileCount));
            labelNote->setStyleSheet("font-size: 20px; color: black;");
            labelNote->setGeometry(25, 55, 360, 50); // Встановлення координат і розмірів
            countNote = fileCount * 5;
            qDebug() << countNote;

    //Створення QLabel для відображення кількості файлів в корзині
    QString dirPath = "delete";

    // Отримати список файлів у директорії
    QDir dirDel(dirPath);
    QStringList filesDel = dirDel.entryList(QDir::Files);
    // Розмір списку - кількість файлів
    int fileCountDel = filesDel.size();
    QLabel *labelDelete = new QLabel(this);
            labelDelete->setText("Нотаток в кошику: " + QString::number(fileCountDel));
            labelDelete->setStyleSheet("font-size: 20px; color: black;");
            labelDelete->setGeometry(25, 80, 360, 50); // Встановлення координат і розмірів
            countDel = fileCountDel * 5;
            qDebug() << countDel;


    //діаграма статистики
    int countAll = 50;
    QLineEdit *firstLine = new QLineEdit(this);
    firstLine->setStyleSheet("background-color: rgb(255, 255, 0);border: none;");
    firstLine->setGeometry(countAll, 150, countNote, 30);
    firstLine->setReadOnly(true);

    countAll = countAll + countNote;
    QLineEdit *secondLine = new QLineEdit(this);
    secondLine->setStyleSheet("background-color: rgb(0, 255, 0);border: none;");
    secondLine->setGeometry(countAll, 150, countDone, 30);
    secondLine->setReadOnly(true);

    countAll = countAll + countDone;
    QLineEdit *thirddLine = new QLineEdit(this);
    thirddLine->setStyleSheet("background-color: rgb(255, 0, 0);border: none;");
    thirddLine->setGeometry(countAll, 150, countDel, 30);
    thirddLine->setReadOnly(true);
    //

    QDir dir("complete");
    if (!dir.exists())
        dir.mkpath(".");
    QStringList filters;
    filters << "*.txt"; // Фільтр для текстових файлів
    QStringList curFiles = dir.entryList(filters, QDir::Files);

    if (curFiles.isEmpty()) {
        ui->EmptyLine->setVisible(true);
        ui->EmptyText->setVisible(true);
    } else {
        ui->EmptyLine->setVisible(false);
        ui->EmptyText->setVisible(false);
    }

    QVBoxLayout *layout = new QVBoxLayout;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {


    QStringList currentFiles = dir.entryList(filters, QDir::Files);

    if (currentFiles.isEmpty()) {
        ui->EmptyLine->setVisible(true);
        ui->EmptyText->setVisible(true);\
    } else {
        ui->EmptyLine->setVisible(false);
        ui->EmptyText->setVisible(false);
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
        connect(deleteButton, &QPushButton::clicked, this, &FolderWindow::deleteFile);
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
        connect(backButton, &QPushButton::clicked, this, &FolderWindow::backFile);
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
    widget->setGeometry(400, 25, 400, 575);
    widget->setLayout(layout);
}

void FolderWindow::backFile()
{
    QPushButton *backButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (backButton) {
    QString fileName = backButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
    QString noteDirectory = "note";
    QString deleteDirectory = "complete";
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

void FolderWindow::deleteFile()
{
    QPushButton *deleteButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (deleteButton) {
    QString fileName = deleteButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
    QString deleteDirectory = "complete";
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

FolderWindow::~FolderWindow()
{
    delete ui;
}



void FolderWindow::on_clearButton_clicked()
{
    QString filePath = "stat/stat.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // Запис числа у файл
    QTextStream out(&file);
    out << "0";
    file.close();
    }
}


void FolderWindow::on_clearLastButton_clicked()
{
    QDir dirDelete("complete");
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


void FolderWindow::on_clearBasketButton_clicked()
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

