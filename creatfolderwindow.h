#ifndef CREATFOLDERWINDOW_H
#define CREATFOLDERWINDOW_H

#include <QDialog>

namespace Ui {
class creatFolderWindow;
}

class creatFolderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit creatFolderWindow(QWidget *parent = nullptr);
    ~creatFolderWindow();

private slots:
    void on_saveButton_clicked();

private:
    Ui::creatFolderWindow *ui;
};

#endif // CREATFOLDERWINDOW_H
