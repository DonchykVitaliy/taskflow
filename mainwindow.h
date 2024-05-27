#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

int noteData(QString fileName,QString line); // Оголошення функції

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void completeFile();

    void deleteFile();

    void on_CreatButton_clicked();

    void on_searchLine_selectionChanged();

    void on_settingsButton_clicked();

    void on_foldersButton_clicked();

    void on_calendarButton_clicked();

    void on_basketButton_clicked();


    void on_searchLine_editingFinished();

    void on_infoButton_clicked();

    void on_foldButton_clicked();

private:
    bool noti;
    QSet<QString> addedFiles;
    QTimer *timer;
    QTimer *timerNoti;
    QTimer *timerRestartNoti;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
