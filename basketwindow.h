#ifndef BASKETWINDOW_H
#define BASKETWINDOW_H

#include <QDialog>

namespace Ui {
class BasketWindow;
}

class BasketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BasketWindow(QWidget *parent = nullptr);
    ~BasketWindow();

private slots:

    void deleteFile();

    void backFile();

    void on_clearButton_clicked();

private:
    QSet<QString> addedFiles;
    QTimer *timer;
    Ui::BasketWindow *ui;
};

#endif // BASKETWINDOW_H
