#include "creatfolderwindow.h"
#include "ui_creatfolderwindow.h"
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QCheckBox>
#include <QPushButton>
#include <QDebug>

creatFolderWindow::creatFolderWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatFolderWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500,650)); //вимкнення зміни розміру вікна


    ui->lineEdit->setPlaceholderText("Назва папки");
    ui->lineEdit->setReadOnly(0);


    // Створення лейауту для прапорців та кнопки
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Отримання списку файлів у директорії
    QDir directory("note");
    QStringList files = directory.entryList(QDir::Files);

// Додавання прапорців для кожного файлу
QList<QCheckBox*> checkBoxes;
for (const QString &file : files) {
    QCheckBox *checkBox = new QCheckBox(file);
    layout->addWidget(checkBox);
    checkBoxes.append(checkBox);
}

}

creatFolderWindow::~creatFolderWindow()
{
    delete ui;
}

void creatFolderWindow::on_saveButton_clicked()
{
    QString nameFolder = "";
    nameFolder = ui->lineEdit->text();

    if (nameFolder==""){
        QMessageBox::warning(this, "Помилка", "Введіть назву папки!");
    }
}

