#include "creatwindow.h"
#include "ui_creatwindow.h"
#include <QMessageBox>
#include <QString>
#include <QCheckBox>
#include <QDate>


CreatWindow::CreatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(700,550)); //вимкнення зміни розміру вікна
    ui->lineEdit->setPlaceholderText("Назва нотатки");
    ui->lineEdit->setReadOnly(1);
    ui->noteText->setPlaceholderText("Нотатка...");
    ui->noteText->setReadOnly(0);

    // Отримуємо поточну дату
    QDate currentDate = QDate::currentDate();

    // Встановлюємо поточну дату для QDateEdit
    ui->dateEdit->setDate(currentDate);
}


CreatWindow::~CreatWindow()
{
    delete ui;
}

void CreatWindow::on_creatButton_clicked()
{

}


//збереження текстового файлу
void CreatWindow::on_saveButton_clicked()
{
    //назва + дерикторія файлу
    QString nameNote = "";
    nameNote = ui->lineEdit->text();
    QString directoryName = "note";
    QString filePath = directoryName + '/' + nameNote + ".txt";
    QFile file(filePath);
    // Отримуємо дату з QDateEdit
    QDate date = ui->dateEdit->date();
    // Конвертуємо дату у рядок у форматі "день.місяць.рік"
    QString dateString = date.toString("dd.MM.yyyy");


    //перевірка назви
    if (nameNote==""){
        QMessageBox::warning(this, "Помилка", "Введіть назву нотатки!");
    }
    else{
        if (file.exists()) {
            QMessageBox::warning(this, "Помилка", "Файл з такою назвою вже існує!");
        } else {
            if (!file.open(QFile::WriteOnly | QFile::Text)) {
                QMessageBox::warning(this, "Помилка", "Файл не зберігся!");
            }
            //збереження
            else{
                QTextStream out(&file);
                QString text = ui->noteText->toPlainText();
                out << text;
                file.close();
                if (ui->checkBox->isChecked()) {
                    //нагадування
                    QString filePathSound = "sound/" + nameNote + ".txt";
                    QFile fileSound(filePathSound);
                    if (fileSound.open(QIODevice::ReadWrite)) {
                        fileSound.close();
                    }
                    //дата + НАЗВА
                    QString filePathCalendar = "calendar/" + dateString + ".txt";
                    QFile fileCalendar(filePathCalendar);
                    QString filePathCalendarS = "calendar/calendarS/" + nameNote + ".txt";
                    QFile fileCalendarS(filePathCalendarS);
                    //НАЗВА + дата
                    if (!QFile::exists(filePathCalendarS)) {
                        if (fileCalendarS.open(QIODevice::ReadWrite)) {
                            QTextStream out(&fileCalendarS);

                            // Запис нового значення у файл
                            out << dateString;
                            fileCalendarS.close();
                        }
                    }
                    if (!QFile::exists(filePathCalendar)) {
                        if (fileCalendar.open(QIODevice::ReadWrite)) {
                            QTextStream out(&fileCalendar);

                            // Запис нового значення у файл
                            out << nameNote;
                            fileCalendar.close();
                        }
                    }
                    else{
                        if (fileCalendar.open(QIODevice::Append | QIODevice::Text)) {
                            QTextStream out(&fileCalendar);

                            // Перехід на новий рядок, якщо файл не порожній
                            if (!fileCalendar.size() == 0)
                                out << "\n";

                            // Запис нового значення у файл
                            out << nameNote;
                            fileCalendar.close();
                        }
                    }
                }
                CreatWindow::close();
            }
        }
    }
}

//поле для назви файлу
void CreatWindow::on_lineEdit_selectionChanged()
{
    ui->lineEdit->setText("");
    ui->lineEdit->setReadOnly(0);
}

