#include "rIDE_new_c_project.h"
#include "ui_rIDE_new_c_project.h"
#include "reaktride.h"

rIDE_new_c_project::rIDE_new_c_project(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rIDE_new_c_project)
{
    ui->setupUi(this);
}

rIDE_new_c_project::~rIDE_new_c_project()
{
    delete ui;
}

void rIDE_new_c_project::on_rIDE_new_c_project_cancel_btn_clicked()
{
    this->close();
}

void rIDE_new_c_project::rIDE_create_file_structure (QString riDE_project_absolute_path,
                                                    bool is_readme_checked,
                                                    bool is_todo_checked,
                                                    bool is_cmakelists_checked){

    if (is_readme_checked || is_todo_checked || is_cmakelists_checked){ // if something checked
        QDir temp_dir_handle (riDE_project_absolute_path);
        if (is_readme_checked){
            QString rIDE_readme_file = "README.md";
            QString rIDE_readme_filepath = temp_dir_handle.filePath(rIDE_readme_file);
            QFile readme_file_handle (rIDE_readme_filepath);
            if (readme_file_handle.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream temp_text_stream (&readme_file_handle);
                temp_text_stream << "# My Awesome Project\n";
                temp_text_stream << "[More about Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)";
                readme_file_handle.close ();
            }
            else{
                qDebug () << "Cannot create/open README.md" << Qt::endl;
            }
        }
        if (is_todo_checked){
            QString rIDE_todo_file = ".todo";
            QString rIDE_todo_filepath = temp_dir_handle.filePath (rIDE_todo_file);
            QFile todo_file_handle (rIDE_todo_filepath);
            if (todo_file_handle.open (QIODevice::WriteOnly | QIODevice::Text)){
                todo_file_handle.close ();
            }
            else {
                qDebug () << "Cannot create/open .todo file" << Qt::endl;
            }
        }
        if (is_cmakelists_checked){
           QString rIDE_cmakelists_file = "CMakeLists.txt";
           QString rIDE_cmakelists_filepath = temp_dir_handle.filePath (rIDE_cmakelists_file);
           QFile cmakelists_file_handle (rIDE_cmakelists_filepath);
           if (cmakelists_file_handle.open (QIODevice::WriteOnly | QIODevice::Text)){
               cmakelists_file_handle.close ();
           }
           else {
               qDebug () << "Cannot create/open CMakeLists.txt file" << Qt::endl;
           }
        }
    } // end if something checked, else follows
    else{
        qDebug () << "Nothing checked, QDir object not created!" <<Qt::endl;
    } // end else of if something checked
}

void rIDE_new_c_project::on_rIDE_new_c_project_express_project_setup_checkbox_stateChanged(int arg1)
{
    if (arg1){
        ui->rIDE_new_c_project_extras_group->setEnabled(false);
        ui->rIDE_include_cmake_file_checkbox->setCheckState(Qt::Unchecked);
        ui->rIDE_include_readme_file_checkbox->setCheckState(Qt::Unchecked);
        ui->rIDE_include_todo_file_checkbox->setCheckState(Qt::Unchecked);
        ui->rIDE_new_c_project_create_empty_project_checkbox->setEnabled(false);
        ui->rIDE_new_c_project_create_empty_project_checkbox->setCheckState(Qt::Unchecked);
    }
    else{
        ui->rIDE_new_c_project_extras_group->setEnabled(true);
        ui->rIDE_new_c_project_create_empty_project_checkbox->setEnabled(true);
    }
}

void rIDE_new_c_project::on_rIDE_new_c_project_browse_btn_clicked()
{
    // TODO: 21 - read from a default setting file
    QUrl rIDE_default_workspace = QUrl("D:\\Workspace\\C++\\Qt\\reaktrIDE-prj\\reaktrIDE");
    QUrl rIDE_directory_url = QFileDialog::getExistingDirectoryUrl (this, "Select Project Workspace", rIDE_default_workspace);
    if (!rIDE_directory_url.isEmpty()){
        QString rIDE_directory_path = QFileInfo (rIDE_directory_url.path()).filePath();
        rIDE_directory_path = rIDE_directory_path.remove (0,1);
        rIDE_directory_path = rIDE_directory_path.replace("/","\\\\");
        QStringList rIDE_path_list = rIDE_directory_path.split("\\");
        QString rIDE_project_name = rIDE_path_list [rIDE_path_list.size()-1];
        // TODO: begin fix this: 1. Fix the slashes issue
        QString rIDE_directory_path_temp = rIDE_directory_path;
        rIDE_directory_path_temp.replace ("//", "\\");
        rIDE_directory_path_temp.replace ("/", "\\");
        // end fix this:
        ui->rIDE_new_c_project_directory_line_edit->setText(rIDE_directory_path_temp);
        QDir rIDE_project_workspace = QDir (rIDE_directory_path);
        if (rIDE_project_workspace.cd(rIDE_directory_path)){
            // get the directory path
            rIDE_pvt_directory_path = rIDE_directory_path;
        }
        else {
            QMessageBox::warning (this, tr ("Cannot access workspace!"), tr ("The workspace path cannot be accessed. \n"
                                                                     "Make sure you can write into the workspace or read the workspace."));
        }
    }
    else {
        QMessageBox::warning (this, tr ("Cannot determine the workspace path!"), tr("The workspace path must be selected in order to proceed. \n"
                                                                      "Click on the browse (...) button, select a workspace directory,"
                                                                      "and click on OK."));
    }
}

void rIDE_new_c_project::on_rIDE_new_c_project_create_project_btn_clicked()
{
    bool is_readme_checked = false;
    bool is_todo_checked = false;
    bool is_cmakelists_checked = false;
    if (!ui->rIDE_new_c_project_name_line_edit->text().isEmpty() &&
            !ui->rIDE_new_c_project_directory_line_edit->text().isEmpty()){
        ui->rIDE_new_c_project_project_name_warning_lbl->setText("<...>");
        ui->rIDE_new_c_project_workspace_warning_lbl->setText("<...>");
        QString rIDE_get_project_name = ui->rIDE_new_c_project_name_line_edit->text();
        QDir rIDE_cd_directory_path = QDir (rIDE_pvt_directory_path);
        QString rIDE_get_project_workspace_path = rIDE_cd_directory_path.filePath(rIDE_get_project_name);
        rIDE_cd_directory_path.cd (rIDE_pvt_directory_path);
        rIDE_cd_directory_path.mkpath (rIDE_get_project_name);
        if (rIDE_cd_directory_path.cd (rIDE_get_project_workspace_path)){
            // populate the checkbox choices and create the project structure, and load them in the tree structure
            if (ui->rIDE_new_c_project_express_project_setup_checkbox->isChecked()){ // if checked
                QDir temp_dir_handle (rIDE_get_project_workspace_path);
                const QString rIDE_c_project_readme_file = "README.md";
                const QString rIDE_c_project_cmakefile_file = "CMakeLists.txt";
                const QString rIDE_c_project_todo_file = ".todo";
                QString riDE_c_project_build_dir = "build";
                QString rIDE_c_project_include_dir = "include";
                QString rIDE_c_project_source_dir = "src";
                QString rIDE_c_project_readme_file_path = temp_dir_handle.filePath(rIDE_c_project_readme_file);
                QString rIDE_c_project_cmakefile_file_path = temp_dir_handle.filePath(rIDE_c_project_cmakefile_file);
                QString rIDE_c_project_todo_file_path = temp_dir_handle.filePath(rIDE_c_project_todo_file);
                QFile readme_filehandle (rIDE_c_project_readme_file_path);
                if (readme_filehandle.open (QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream readme_stream (&readme_filehandle);
                    readme_stream << "# My Awesome Project\n";
                    readme_stream << "[More about Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)";
                    readme_filehandle.close ();
                }
                else {
                    qDebug() << "Cannot open readme file";
                }
                QFile cmake_filehandle (rIDE_c_project_cmakefile_file_path);
                if (cmake_filehandle.open (QIODevice::WriteOnly | QIODevice::Text)){
                    cmake_filehandle.close ();
                }
                else {
                    qDebug() << "Cannot open CMakeLists.txt file";
                }

                QFile todo_filehandle (rIDE_c_project_todo_file_path);
                if (todo_filehandle.open (QIODevice::WriteOnly | QIODevice::Text))
                    todo_filehandle.close ();
                else
                    qDebug () << "Cannot open .todo file";

                temp_dir_handle.mkpath (riDE_c_project_build_dir);
                temp_dir_handle.mkpath (rIDE_c_project_include_dir);
                temp_dir_handle.mkpath (rIDE_c_project_source_dir);
           } // end if checked, else follows
           else{
                QDir temp_dir_handle (rIDE_get_project_workspace_path);
                // creation of directories
                QString riDE_c_project_build_dir = "build";
                QString rIDE_c_project_include_dir = "include";
                QString rIDE_c_project_source_dir = "src";

                temp_dir_handle.mkpath (riDE_c_project_build_dir);
                temp_dir_handle.mkpath (rIDE_c_project_include_dir);
                temp_dir_handle.mkpath (rIDE_c_project_source_dir);

                is_readme_checked = ui->rIDE_include_readme_file_checkbox->isChecked()?true:false;
                is_cmakelists_checked = ui->rIDE_include_cmake_file_checkbox->isChecked()?true:false;
                is_todo_checked = ui->rIDE_include_todo_file_checkbox->isChecked()?true:false;

                rIDE_create_file_structure (rIDE_get_project_workspace_path,
                                            is_readme_checked,
                                            is_todo_checked,
                                            is_cmakelists_checked);
           } // end if checked
        }
        // TODO: 19 - sort of solved
        rIDE_get_project_workspace_path = rIDE_get_project_workspace_path.replace ("//", "/");
        // TODO: 22. use the tr () function
        QString rIDE_project_creation_string = "Project succesfully created @ "+rIDE_get_project_workspace_path+". Happy Coding!";
        QMessageBox::information (this, tr("reaktrIDE project creation"), rIDE_project_creation_string);

        rIDE_list_model = new QFileSystemModel (this);
        rIDE_list_model->setRootPath (rIDE_project_creation_string);
        rIDE_list_model->setFilter (QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files);

        // the magic happens here, hopefully

        /*reaktr_ide->findChild<QTreeView*>("rIDE_main_source_tree_vw")->setModel(rIDE_list_model);
        ui_reaktr_ide->rIDE_main_source_tree_vw->setModel (rIDE_list_model);
        ui_reaktr_ide->rIDE_main_source_tree_vw->setRootIndex (rIDE_list_model->index(rIDE_project_creation_string));
        ui_reaktr_ide->rIDE_main_source_tree_lbl->setText (rIDE_get_project_name);*/
        this->close();
    }
    else {
        if (ui->rIDE_new_c_project_name_line_edit->text().isEmpty())
            ui->rIDE_new_c_project_project_name_warning_lbl->setText("Project Name cannot be empty!");
        if (ui->rIDE_new_c_project_directory_line_edit->text().isEmpty())
            ui->rIDE_new_c_project_workspace_warning_lbl->setText("Project workspace cannot be empty!");
    }
}
