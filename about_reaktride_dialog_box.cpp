#include "about_reaktride_dialog_box.h"
#include "ui_about_reaktride_dialog_box.h"

about_reaktride_dialog_box::about_reaktride_dialog_box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about_reaktride_dialog_box)
{
    ui->setupUi(this);
}

about_reaktride_dialog_box::~about_reaktride_dialog_box()
{
    delete ui;
}

void about_reaktride_dialog_box::on_about_rIDE_dialog_github_btn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://gitlab.com/nitindesh/reaktrIDE/-/tree/master", QUrl::TolerantMode));
}

void about_reaktride_dialog_box::on_about_rIDE_dialog_ok_btn_clicked()
{
    this->close();
}
