#ifndef FILEDISPLAYWINDOW_H
#define FILEDISPLAYWINDOW_H

#include <QDialog>

namespace Ui {
class FileDisplayWindow;
}

class FileDisplayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileDisplayWindow(QWidget *parent = nullptr);
    ~FileDisplayWindow();

private slots:
    void on_creatButton_clicked();

private:
    Ui::FileDisplayWindow *ui;
};

#endif // FILEDISPLAYWINDOW_H
