#ifndef ABOUT_REAKTRIDE_DIALOG_BOX_H
#define ABOUT_REAKTRIDE_DIALOG_BOX_H

#include <QDialog>
#include <QUrl>
#include <QtCore>
#include <QDesktopServices>

namespace Ui {
class about_reaktride_dialog_box;
}

class about_reaktride_dialog_box : public QDialog
{
    Q_OBJECT

public:
    explicit about_reaktride_dialog_box(QWidget *parent = nullptr);
    ~about_reaktride_dialog_box();

private slots:
    void on_about_rIDE_dialog_github_btn_clicked();

    void on_about_rIDE_dialog_ok_btn_clicked();

private:
    Ui::about_reaktride_dialog_box *ui;
};

#endif // ABOUT_REAKTRIDE_DIALOG_BOX_H
