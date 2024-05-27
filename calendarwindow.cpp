#include "calendarwindow.h"
#include "ui_calendarwindow.h"
#include <QCalendarWidget>
#include <QDate>
#include <QTextCharFormat>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QVBoxLayout>

CalendarWindow::CalendarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500,500)); //вимкнення зміни розміру вікна

    //створення календарю
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGeometry(30, 100, 440, 250);
    calendarWidget->setStyleSheet(
        "background-color:  rgb(223, 223, 223);"
        "QCalendarWidget QToolButton {"
            "color: black;"
        "}"
    );



    ///////////////////////////////////
    // помічення днів з нотаткою

    QDir dirCalendar("calendar");
    QStringList filters;
    filters << "*.txt";

    dirCalendar.setNameFilters(filters);
    QFileInfoList fileList = dirCalendar.entryInfoList();

    foreach (const QFileInfo &fileInfo, fileList) {
        QString fileName = fileInfo.fileName();
        QString dateString = fileName.left(fileName.lastIndexOf('.')); // Видал .txt
        QDate date = QDate::fromString(dateString, "dd.MM.yyyy"); // формат дати

        QTextCharFormat format;
        format.setBackground(QColor(235, 94, 0));
        calendarWidget->setDateTextFormat(date, format);
    }



    // Встановлюємо обробник подій для календаря
    connect(calendarWidget, &QCalendarWidget::clicked, [=](const QDate &date) {
        // Перевіряємо, чи натиснутий день має червоний фон
        QTextCharFormat clickedFormat = calendarWidget->dateTextFormat(date);
        if (clickedFormat.background().color() == QColor(235, 94, 0)) {
            qDebug() << "Вибраний день: " << date.toString("dd.MM.yyyy");

            // Формуємо назву файлу на основі дати
            QString fileName = date.toString("dd.MM.yyyy") + ".txt";

            // Шлях до файлу
            QString filePath = "calendar/" + fileName;

            // Перевіряємо, чи існує файл з такою назвою
            QFileInfo fileInfo(filePath);
            if (fileInfo.exists() && fileInfo.isFile()) {
                qDebug() << "Файл існує: " << filePath;
                QString noteDirectoryPath = "calendar/";
                QFile calendarFile(QDir(noteDirectoryPath).filePath(fileName));
if (calendarFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&calendarFile);
    while (!in.atEnd()) {
        QString searchNote = in.readLine().trimmed(); // Отримуємо кожен рядок файлу і видаляємо зайві пробіли
        qDebug() << searchNote;
        QFile fileN("note/" + searchNote + ".txt");
        // Читання вмісту файлу
        if (fileN.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream fileIn(&fileN);
            QString fileContent = fileIn.readAll();
            fileN.close();

            // Створення нового вікна для виведення файлу
            QDialog *fileDialog = new QDialog(this);
            fileDialog->setWindowTitle("Вміст нотатки: " + searchNote);

            QPlainTextEdit *textEdit = new QPlainTextEdit(fileContent, fileDialog);
            textEdit->setReadOnly(true);

            QVBoxLayout *layout = new QVBoxLayout(fileDialog);
            layout->addWidget(textEdit);

            fileDialog->exec();
        }
                 else {
                    // Вивести повідомлення про помилку читання файлу
                    QMessageBox::critical(this, "Помилка", "Не вдалося прочитати нотатку!");
                        }
                    }
                calendarFile.close();
                }
            }
        }
    });
}

CalendarWindow::~CalendarWindow()
{
    delete ui;
}

void CalendarWindow::on_clearButton_clicked()
{
    QDir dirDelete("calendar");
    QStringList files = dirDelete.entryList(QDir::Files);
    QDir dirDeleteC("calendar/calendarS");
    QStringList filesC = dirDeleteC.entryList(QDir::Files);

    // Видалення кожного файлу
    foreach (const QString &file, files) {
        QString filePath = dirDelete.filePath(file);
        if (QFile::remove(filePath)) {
            qDebug() << "Файл видалено:" << filePath;
        } else {
            qDebug() << "Помилка видалення файлу:" << filePath;
        }
    }
    foreach (const QString &file, filesC) {
        QString filePath = dirDeleteC.filePath(file);
        if (QFile::remove(filePath)) {
            qDebug() << "Файл видалено:" << filePath;
        } else {
            qDebug() << "Помилка видалення файлу:" << filePath;
        }
    }
    QMessageBox::information(nullptr, "Календар очищений!", "Перезавантажте це вікно, щоб побачити зміни.");
}

