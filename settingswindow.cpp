#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500,500)); //вимкнення зміни розміру вікна

    QString filePath = "settings/bool.txt";
    QFile file(filePath);
    QString filePathDel = "settings/delete.txt";
    QFile fileDel(filePathDel);

    // нагадування кнопка
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Читання значення з першого рядка
        QString line = in.readLine();
        bool conversionOk;
        int value = line.toInt(&conversionOk);

        // Додавання 1 до значення
        if (value == 1){
            ui->checkNoti->setChecked(true);
        }else{
            ui->checkNoti->setChecked(false);
        }

        // Закриття файлу для читання
        file.close();
    }

    // очищення кошику
    if (fileDel.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileDel);

        // Читання значення з першого рядка
        QString line = in.readLine();
        bool conversionOk;
        int value = line.toInt(&conversionOk);

        // Додавання 1 до значення
        if (value == 1){
            ui->checkDel->setChecked(true);
        }else{
            ui->checkDel->setChecked(false);
        }

        // Закриття файлу для читання
        fileDel.close();
    }


}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_checkNoti_stateChanged(int arg1)
{

}


void SettingsWindow::on_checkNoti_clicked()
{
    QString filePath = "settings/bool.txt";
    QFile file(filePath);

    if (ui->checkNoti->isChecked()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            // Читання значення з першого рядка
            QString line = in.readLine();
            int value = line.toInt();

            value=1;

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
            }
        }
    } else{
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            // Читання значення з першого рядка
            QString line = in.readLine();
            int value = line.toInt();

            value=0;

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
            }
        }
    }
}


void SettingsWindow::on_checkDel_clicked()
{
    QString filePath = "settings/delete.txt";
    QFile file(filePath);

    if (ui->checkDel->isChecked()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            // Читання значення з першого рядка
            QString line = in.readLine();
            int value = line.toInt();

            value=1;

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
            }
        }
    } else{
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            // Читання значення з першого рядка
            QString line = in.readLine();
            int value = line.toInt();

            value=0;

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
            }
        }
    }
}

