#include "ride_new_project.h"
#include "ui_ride_new_project.h"

rIDE_new_project::rIDE_new_project(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rIDE_new_project)
{
    ui->setupUi(this);
}

rIDE_new_project::~rIDE_new_project()
{
    delete ui;
}

void rIDE_new_project::on_rIDE_new_project_cancel_btn_clicked()
{
    this->close();
}
