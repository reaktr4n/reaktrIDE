#include "rIDE_new_python_project.h"
#include "ui_rIDE_new_python_project.h"

rIDE_new_python_project::rIDE_new_python_project(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rIDE_new_python_project)
{
    ui->setupUi(this);
}

rIDE_new_python_project::~rIDE_new_python_project()
{
    delete ui;
}

void rIDE_new_python_project::on_rIDE_new_py_project_cancel_btn_clicked()
{
    this->close();
}
