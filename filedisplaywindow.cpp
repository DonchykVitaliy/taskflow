#include "filedisplaywindow.h"
#include "ui_filedisplaywindow.h"
#include "creatfolderwindow.h"
#include <QDir>

FileDisplayWindow::FileDisplayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDisplayWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500,650)); //вимкнення зміни розміру вікна


    QDir dir("folders");
    if (!dir.exists())
        dir.mkpath(".");
    QStringList filters;
    filters << "*.txt"; // Фільтр для текстових файлів

    QStringList curFiles = dir.entryList(filters, QDir::Files);

    if (curFiles.isEmpty()) {
        ui->EmptyLine->setVisible(true);
        ui->EmptyText->setVisible(true);

        qDebug() << "Директорія не містить файлів";
    } else {
        ui->EmptyLine->setVisible(false);
        ui->EmptyText->setVisible(false);
    }






}

FileDisplayWindow::~FileDisplayWindow()
{
    delete ui;
}

void FileDisplayWindow::on_creatButton_clicked()
{
    creatFolderWindow creat;
    creat.setModal(true);
    creat.exec();
}

