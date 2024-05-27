#ifndef FOLDERWINDOW_H
#define FOLDERWINDOW_H

#include <QDialog>

namespace Ui {
class FolderWindow;
}

class FolderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FolderWindow(QWidget *parent = nullptr);
    ~FolderWindow();

private slots:

    void backFile();

    void deleteFile();

    void on_clearButton_2_clicked();

    void on_clearButton_clicked();

    void on_clearLast_clicked();

    void on_clearLastButton_clicked();

    void on_clearBasketButton_clicked();

private:
    QSet<QString> addedFiles;
    QTimer *timer;
    Ui::FolderWindow *ui;
};

#endif // FOLDERWINDOW_H
