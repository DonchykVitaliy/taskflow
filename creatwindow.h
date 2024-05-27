#ifndef CREATWINDOW_H
#define CREATWINDOW_H

#include <QMessageBox>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class CreatWindow;
}

class CreatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreatWindow(QWidget *parent = nullptr);
    ~CreatWindow();

private slots:
    void on_creatButton_clicked();

    void on_saveButton_clicked();

    void on_lineEdit_selectionChanged();

private:
    Ui::CreatWindow *ui;
    QString currentFile = "";
};

#endif // CREATWINDOW_H
