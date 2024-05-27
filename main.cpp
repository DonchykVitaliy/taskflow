#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //створення папки "note"
    QDir dir("note");
    if (!dir.exists())
        dir.mkpath(".");
    //папка "delete"
    QDir dirDelete("delete");
    if (!dirDelete.exists())
        dirDelete.mkpath(".");
    //створення папки "complete"
    QDir dirComp("complete");
    if (!dirComp.exists())
        dirComp.mkpath(".");
    //створення папки "stat"
    QDir dirStat("stat");
    if (!dirStat.exists())
        dirStat.mkpath(".");
    //створення папки "sound"
    QDir dirSound("sound");
    if (!dirSound.exists())
        dirSound.mkpath(".");
    //створення папки "settings"
    QDir dirSettings("settings");
    if (!dirSettings.exists())
        dirSettings.mkpath(".");
    //створення папки "calendar"
    QDir dirCalendars("calendar");
    if (!dirCalendars.exists())
        dirCalendars.mkpath(".");
    //створення підпапки папки "calendarS"
    QDir dirCalendarsS("calendar/calendarS");
    if (!dirCalendarsS.exists())
        dirCalendarsS.mkpath(".");
    //створення папки "folders"
    QDir dirFolders("folders");
    if (!dirFolders.exists())
        dirFolders.mkpath(".");

    //створення потрібних файлів
    //файл "settingsBool"
    // Перевірка існування файлу
    QString fileBool = dirSettings.filePath("bool.txt");
    if (!QFile::exists(fileBool)) {
        QFile settingsBool(fileBool);
        int initValue = 1;
        if (settingsBool.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&settingsBool);
            // Запис числа у файл
            out << initValue;
            qDebug() << "Файл успішно створено:" << fileBool;
            settingsBool.close();
        }
    }
    //файл "settingsBoolDelete"
    // Перевірка існування файлу
    QString fileBoolDel = dirSettings.filePath("delete.txt");
    if (!QFile::exists(fileBoolDel)) {
        QFile settingsBoolDel(fileBoolDel);
        int initValue = 1;
        if (settingsBoolDel.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&settingsBoolDel);
            // Запис числа у файл
            out << initValue;
            qDebug() << "Файл успішно створено:" << fileBoolDel;
            settingsBoolDel.close();
        }
    }
    //файл "stat"
    // Перевірка існування файлу
    QString fileStat = dirStat.filePath("stat.txt");
    if (!QFile::exists(fileStat)) {
        QFile stat(fileStat);
        int initialValue = 0;
        if (stat.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&stat);
            // Запис числа у файл
            out << initialValue;
            qDebug() << "Файл успішно створено:" << fileStat;
            stat.close();
        }
    }


    //вивід нагадувань
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

        QVBoxLayout *layoutSound = new QVBoxLayout();

        //назва нотатки
        QLabel *labelSoundName = new QLabel();
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
            QTextBrowser *textBrowserSound = new QTextBrowser();
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

        QPushButton *offButton = new QPushButton("Вимкнути нагадування");
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

        QPushButton *okButton = new QPushButton("Гаразд");
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



    /////очистка кошику
    // перевірка налаштувань
    QString filePathDel = "settings/delete.txt";
    QFile fileDel(filePathDel);
    bool deleteSetting;
    if (fileDel.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileDel);

        // Читання значення з першого рядка
        QString line = in.readLine();
        bool conversionOk;
        int value = line.toInt(&conversionOk);

        // Додавання 1 до значення
        if (value == 1){
    deleteSetting = true;
        }else{
    deleteSetting = false;
        }

        // Закриття файлу для читання
        fileDel.close();
    }
    //очистка кошику
    if (deleteSetting){
        // Отримання списку всіх файлів у директорії
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


    //очищення нещодавних
    // Отримання списку всіх файлів у директорії
    QStringList filesComp = dirComp.entryList(QDir::Files);
    // Видалення кожного файлу
    foreach (const QString &file, filesComp) {
        QString filePath = dirComp.filePath(file);
        if (QFile::remove(filePath)) {
    qDebug() << "Файл видалено:" << filePath;
        } else {
    qDebug() << "Помилка видалення файлу:" << filePath;
        }
    }

    return a.exec();
}
