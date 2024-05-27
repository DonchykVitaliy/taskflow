#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creatwindow.h"
#include "settingswindow.h"
#include "folderwindow.h"
#include "calendarwindow.h"
#include "basketwindow.h"
#include "infowindow.h"
#include "filedisplaywindow.h"
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
#include <QTextStream>
#include <QScrollArea>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //текстури
    QPixmap search(":/textures/textures/search.png"); //текстура пошуку
    QPixmap menuButtonActive(":/textures/textures/menuButton_active.png");
    QPixmap menuButton(":/textures/textures/menuButton.png");
    QPixmap pluss(":/textures/textures/plus.png"); //текстура створення

    //оприділяємо розміри текстур
    int WidthPlus = ui->creatImg->width();
    int HeightPlus = ui->creatImg->height();
    int WidthBut = ui->buttonImgH->width();
    int HeightBut = ui->buttonImgH->height();
    int WidthSer = ui->ImgSearch->width();
    int HeightSer = ui->ImgSearch->height();

    //встановлюємо розміри текстур
    ui->ImgSearch->setPixmap(search.scaled(WidthSer,HeightSer,Qt::KeepAspectRatio));
    ui->creatImg->setPixmap(pluss.scaled(WidthPlus,HeightPlus,Qt::KeepAspectRatio));
    ui->buttonImgB->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgB_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgB_a->setVisible(false);
    ui->buttonImgC->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgC_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgC_a->setVisible(false);
    ui->buttonImgF->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgF_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgF_a->setVisible(false);
    ui->buttonImgSt->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgSt_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgSt_a->setVisible(false);
    ui->buttonImgI->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgI_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgI_a->setVisible(false);
    ui->buttonImgH->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgS->setPixmap(menuButton.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgS_a->setPixmap(menuButtonActive.scaled(WidthBut,HeightBut,Qt::KeepAspectRatio));
    ui->buttonImgS_a->setVisible(false);

    //стартовий текст в пошуку
    ui->searchLine->setPlaceholderText("Пошук...");
    ui->searchLine->setReadOnly(1);
    //вимкнення зміни розміру вікна
    this->setFixedSize(QSize(1100,600));
    //Директорії
    QDir dir("note");
    QDir dirSound("sound");
    //зчитування файлів
    QString searchDirectory = "note"; //шлях
    QDir directory(searchDirectory);
    QStringList filters;
    filters << "*.txt"; // Фільтр для текстових файлів




    /////нагадування
    //включення нагудувань
    timerNoti = new QTimer(this);
    connect(timerNoti, &QTimer::timeout, [=]() {
    QString filePathBool = "settings/bool.txt";
    QFile fileS(filePathBool);
    if (fileS.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileS);

        // Читання значення з першого рядка
        QString line = in.readLine();
        bool conversionOk;
        int value = line.toInt(&conversionOk);
        //якщо включено, то вивід нагадувань
        if (value == 1){
        QStringList soundList = dirSound.entryList(QDir::Files);
        QString noteDirectoryPath = "note";
        QString soundDir = "sound";

    // Створення та показ вікна для кожного файлу
    for (const QString &fileName : soundList) {
        // Створення вікна
        QString NoteName = fileName;
        NoteName.chop(4);
        QWidget *window = new QWidget();
        window->setWindowTitle("Нагадування: " + NoteName);
        window->setFixedSize(500, 500);

        QVBoxLayout *layoutSound = new QVBoxLayout(this);

        //назва нотатки
        QLabel *labelSoundName = new QLabel(this);
        labelSoundName->setText("Назва нотатки: " + NoteName);
        QFont fontSound = labelSoundName->font();
        fontSound.setPointSize(14);
        labelSoundName->setFont(fontSound);
        labelSoundName->setStyleSheet("color: dark_gray;");
        layoutSound->addWidget(labelSoundName);
        // Зчитування вмісту з папки "note"
        QFile noteFile(QDir(noteDirectoryPath).filePath(fileName));
        if (noteFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&noteFile);
            QString fileContent = in.readAll();
            QTextBrowser *textBrowserSound = new QTextBrowser(this);
            if (fileContent == ""){
                textBrowserSound->setPlainText("Нотатка порожня...");
            }else{
            textBrowserSound->setPlainText(fileContent + "\n");
            }
            QFont fontSoundText = textBrowserSound->currentFont();
            fontSoundText.setPointSize(14);
            textBrowserSound->setCurrentFont(fontSoundText);
            textBrowserSound->setStyleSheet("border-radius: 10px;border: none;color:rgb(85, 85, 85);font: 9pt;background-color: rgb(223, 223, 223);");
            layoutSound->addWidget(textBrowserSound);
            noteFile.close();
        }

        QPushButton *offButton = new QPushButton("Вимкнути нагадування", this);
        offButton->setStyleSheet(
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
        QObject::connect(offButton, &QPushButton::clicked, [window,fileName, soundDir]() {
            // Видалення файлу
            QFile::remove(QDir(soundDir).filePath(fileName));
            // Закриття вікна
            window->close();
        });

        QPushButton *okButton = new QPushButton("Гаразд", this);
        okButton->setStyleSheet(
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
        QObject::connect(okButton, &QPushButton::clicked, window, &QWidget::close);
        layoutSound->addWidget(offButton);
        layoutSound->addWidget(okButton);
        //показ вікна
        window->setLayout(layoutSound);
        window->show();
    }
        }
        fileS.close();
    }
});
    timerNoti->start(300000);




    /////////Список всіх нотаток на головному вінкі
    QVBoxLayout *layout = new QVBoxLayout;


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        QStringList currentFiles = directory.entryList(filters, QDir::Files);

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
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteFile);
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

        QPushButton *completeButton = new QPushButton("Виконано", this);
        completeButton->setProperty("FileName", fileName);
        connect(completeButton, &QPushButton::clicked, this, &MainWindow::completeFile);
        completeButton->setStyleSheet(
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
        layout->addWidget(completeButton);

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
widget->setGeometry(180, 60, 500, 525);
widget->setLayout(layout);

}




void MainWindow::completeFile(){
    QPushButton *completeButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (completeButton) {
        QString fileName = completeButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
        QString noteDirectory = "note";
        QString soundDirectory = "sound";
        QString completeDirectory = "complete";
        QString filePathNote = QDir(noteDirectory).filePath(fileName);
        QString filePathComplete = QDir(completeDirectory).filePath(fileName);
        QString fileSoundDel = QDir(soundDirectory).filePath(fileName);

        //вимнення нагадування
        QFile::remove(fileSoundDel);

        // Переміщення файлу до директорії "complete"
        if (QFile::rename(filePathNote, filePathComplete)) {
            qDebug() << "Файл успішно переміщено в директорію 'complete':" << fileName;
        } else {
            qDebug() << "Помилка переміщення файлу в директорію 'complete':" << fileName;
            QMessageBox::critical(this, "Помилка", "Не вдалося перемістити файл.");
            return; // Вихід з функції у випадку помилки переміщення
        }
    qDebug() << "Виконано: " << fileName;
            QString filePath = "stat/stat.txt";
            QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // Читання значення з першого рядка
            QString line = in.readLine();
            bool conversionOk;
            int value = line.toInt(&conversionOk);

            // Перевірка, чи вдалося сконвертувати рядок в число
            if (conversionOk) {
                // Додавання 1 до значення
                ++value;

                // Закриття файлу для читання
                file.close();

                // Відкриття файлу для запису (очищення вмісту)
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(&file);

                    // Запис нового значення у файл
                    out << value;
                    qDebug() << "Нове значення в файлі:" << value;

                    // Закриття файлу для запису
                    file.close();
                } else {
                    qDebug() << "Помилка відкриття файлу для запису:" << filePath;
                }
            } else {
                qDebug() << "Помилка конвертації значення з файлу:" << filePath;
            }
    } else {
            qDebug() << "Помилка відкриття файлу для читання:" << filePath;
        }
    }
}

void MainWindow::deleteFile()
{
    QPushButton *deleteButton = qobject_cast<QPushButton*>(sender()); // Отримання відправника події (кнопки)
    if (deleteButton) {
        QString fileName = deleteButton->property("FileName").toString(); // Отримання імені файлу з властивості кнопки
        QString noteDirectory = "note";
        QString soundDirectory = "sound";
        QString deleteDirectory = "delete";
        QString calendarTimeDirectory = "calendar";
        QString calendarDirectory = "calendar/calendarS";
        QString filePathCalendar = QDir(calendarDirectory).filePath(fileName);
        QString filePathNote = QDir(noteDirectory).filePath(fileName);
        QString filePathDelete = QDir(deleteDirectory).filePath(fileName);
        QString fileSoundDel = QDir(soundDirectory).filePath(fileName);

        //видалення з календаря
        QFile fileC(filePathCalendar);
        if (fileC.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream inC(&fileC);
            QString fileContent = inC.readAll().trimmed();
            QString fileCalendarName = fileContent + ".txt";
            fileC.close();

            QString filePthCalendar = QDir(calendarTimeDirectory).filePath(fileCalendarName);
            QFile fileCalendar(filePthCalendar);
            if (fileCalendar.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream in(&fileCalendar);
            QString content;

            while (!in.atEnd()) {
                QString line = in.readLine();
                QString deleteName = fileName.chopped(4);;
                if (!line.contains(deleteName)) {
                    if (!content.isEmpty()) { // Перевіряємо, чи змінна content не є пустою
                        content += "\n"; // Додаємо абзац, якщо рядок не пустий
                    }
                    content += line; // Додаємо текст зі змінної line
                }
            }

            fileCalendar.resize(0); // Очищаємо вміст файлу
            QTextStream out(&fileCalendar);
            out << content; // Записуємо вміст без видалених рядків
            fileCalendar.close();
            QFile::remove(filePathCalendar);
        }
        //якщо число в календарі пусте, то видалення замітки
        if (fileCalendar.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QTextStream inV(&fileCalendar);
                QString fileCalendarCount = inV.readAll();
                fileCalendar.close();

                if (fileCalendarCount==""){
                    QFile::remove(filePthCalendar);
                }
            }
        }
        // Переміщення файлу до директорії "delete"
        if (QFile::rename(filePathNote, filePathDelete)) {
            qDebug() << "Файл успішно переміщено в директорію 'delete':" << fileName;
        } else {
            qDebug() << "Помилка переміщення файлу в директорію 'delete':" << fileName;
            QMessageBox::critical(this, "Помилка", "Не вдалося перемістити нотатку в кошик!");
            return; // Вихід з функції у випадку помилки переміщення
        }
        //вимнення нагадування
        QFile::remove(fileSoundDel);
    }
}







MainWindow::~MainWindow()
{
    delete ui;
}

//вікно створення
void MainWindow::on_CreatButton_clicked()
{
    CreatWindow Creat;
    Creat.setModal(true);
    Creat.exec();
}


//пошук
void MainWindow::on_searchLine_selectionChanged()
{
    ui->searchLine->setText("");
    ui->searchLine->setReadOnly(0);
}


//вікно налаштувань
void MainWindow::on_settingsButton_clicked()
{
    ui->buttonImgS_a->setVisible(true);
    SettingsWindow Settings;
    Settings.setModal(true);
    Settings.exec();
    ui->buttonImgS_a->setVisible(false);
}


//вікно статистики
void MainWindow::on_foldersButton_clicked()
{
    ui->buttonImgSt_a->setVisible(true);
    FolderWindow Folder;
    Folder.setModal(true);
    Folder.exec();
    ui->buttonImgSt_a->setVisible(false);
}


//вікно календаря
void MainWindow::on_calendarButton_clicked()
{
    ui->buttonImgC_a->setVisible(true);
    CalendarWindow Calendar;
    Calendar.setModal(true);
    Calendar.exec();
    ui->buttonImgC_a->setVisible(false);
}


//вікно кошику
void MainWindow::on_basketButton_clicked()
{
    ui->buttonImgB_a->setVisible(true);
    BasketWindow Busket;
    Busket.setModal(true);
    Busket.exec();
    ui->buttonImgB_a->setVisible(false);
}


void MainWindow::on_searchLine_editingFinished()
{
// Отримати текст з QLineEdit
    QString fileName = ui->searchLine->text();

    // Перевірити наявність файлу
    QFile file("note/" + fileName + ".txt");
    if (!file.exists()) {
        // Вивести повідомлення про помилку
        QMessageBox::critical(this, "Помилка", "Нотатка не знайдена!");
        return;
    }

    // Читання вмісту файлу
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        // Створення нового вікна для виведення файлу
        QDialog *fileDialog = new QDialog(this);
        fileDialog->setWindowTitle("Вміст нотатки: " + fileName);

        QPlainTextEdit *textEdit = new QPlainTextEdit(fileContent, fileDialog);
        textEdit->setReadOnly(true);

        QVBoxLayout *layout = new QVBoxLayout(fileDialog);
        layout->addWidget(textEdit);


        fileDialog->exec();
    } else {
        // Вивести повідомлення про помилку читання файлу
        QMessageBox::critical(this, "Помилка", "Не вдалося прочитати нотатку!");
    }
}


void MainWindow::on_infoButton_clicked()
{
    ui->buttonImgI_a->setVisible(true);
    InfoWindow Info;
    Info.setModal(true);
    Info.exec();
    ui->buttonImgI_a->setVisible(false);
}


void MainWindow::on_foldButton_clicked()
{
    ui->buttonImgF_a->setVisible(true);
    FileDisplayWindow Folders;
    Folders.setModal(true);
    Folders.exec();
    ui->buttonImgF_a->setVisible(false);
}

