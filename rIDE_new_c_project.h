#ifndef RIDE_NEW_C_PROJECT_H
#define RIDE_NEW_C_PROJECT_H

#include "ui_reaktride.h"
#include <QDir>
#include <QUrl>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileSystemModel>
#include <QObject>

namespace Ui {
class rIDE_new_c_project;
}

class rIDE_new_c_project : public QDialog
{
    Q_OBJECT

public:
    //reaktrIDE reaktrIDE_main;
    explicit rIDE_new_c_project(QWidget *parent = nullptr);
    ~rIDE_new_c_project();

private slots:
    void on_rIDE_new_c_project_cancel_btn_clicked();
    void on_rIDE_new_c_project_express_project_setup_checkbox_stateChanged(int arg1);
    void on_rIDE_new_c_project_browse_btn_clicked();
    void on_rIDE_new_c_project_create_project_btn_clicked();

private:
    Ui::rIDE_new_c_project *ui;
    QString rIDE_pvt_get_project_workspace_path;
    QString rIDE_pvt_directory_path;
    QFileSystemModel* rIDE_list_model;
    void rIDE_create_file_structure (QString riDE_project_absolute_path,
                                     bool is_readme_checked,
                                     bool is_todo_checked,
                                     bool is_cmakelists_checked);

};

#endif // RIDE_NEW_C_PROJECT_H
