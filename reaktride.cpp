#include "reaktride.h"
#include "ui_reaktride.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPixmap>
#include <QDialog>

reaktrIDE::reaktrIDE (QWidget *parent) :
    QMainWindow (parent),
    ui (new Ui::reaktrIDE)
{
    ui->setupUi (this);
}

reaktrIDE::~reaktrIDE ()
{
    delete ui;
}

void reaktrIDE::on_rIDE_menu_actionQuit_triggered ()
{
    QApplication::quit ();
}

void reaktrIDE::on_rIDE_menu_actionAbout_triggered (){
    about_rIDE_box = new about_reaktride_dialog_box (this);
    about_rIDE_box->exec ();
}

void reaktrIDE::on_rIDE_actionRestart_triggered()
{
    QApplication::quit ();
    QProcess::startDetached (qApp->arguments ()[0], qApp->arguments ());
}

void reaktrIDE::on_rIDE_actionOpen_Project_triggered ()
{
    QString rIDE_default_source_tree_set_text = "Source Tree";
    // TODO: the default workspace should be obtained from the rIDE solution file
    QUrl rIDE_default_workspace = QUrl ("D:\\Workspace\\C++\\Qt\\reaktrIDE-prj\\reaktrIDE");
    QUrl rIDE_directory_url = QFileDialog::getExistingDirectoryUrl (this, "Open Project Directory", rIDE_default_workspace);

    if (!rIDE_directory_url.isEmpty ()){
        QString rIDE_directory_path = QFileInfo (rIDE_directory_url.path ()).filePath ();
        rIDE_directory_path = rIDE_directory_path.remove (0,1);
        rIDE_directory_path = rIDE_directory_path.replace ("/","\\\\");
        QStringList rIDE_path_list = rIDE_directory_path.split ("\\");
        QString rIDE_project_name = rIDE_path_list [rIDE_path_list.size ()-1];
        QString rIDE_source_tree_text = "Source Tree";
        rIDE_source_tree_text.append (": (");
        rIDE_source_tree_text.append (rIDE_project_name);
        rIDE_source_tree_text.append (")");
        rIDE_list_model = new QFileSystemModel (this);
        rIDE_list_model->setRootPath (rIDE_directory_path);
        rIDE_list_model->setFilter (QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files);
        ui->rIDE_main_source_tree_vw->setModel (rIDE_list_model);
        ui->rIDE_main_source_tree_vw->setRootIndex (rIDE_list_model->index(rIDE_directory_path));
        // TODO: 4. display the project name in the Source Tree view
        ui->rIDE_main_source_tree_lbl->setText (rIDE_source_tree_text);
    }
    else {
        ui->rIDE_main_source_tree_vw->setModel (nullptr);
        // set the default source tree label text in case the file dialog is ex-ed or closed or canceled
        ui->rIDE_main_source_tree_lbl->setText (rIDE_default_source_tree_set_text);
    }
}

void reaktrIDE::on_rIDE_main_source_tree_vw_doubleClicked (const QModelIndex &index)
{
    QString rIDE_main_code_editor_lbl_default_text = "reaktrIDE Editor";
    rIDE_file_model = new QFileSystemModel (this);
    QString rIDE_file_path_for_code_editor = rIDE_file_model->fileInfo (index).absoluteFilePath ();
    QFile rIDE_file_handler (rIDE_file_path_for_code_editor);
    QFileInfo rIDE_code_file_info (rIDE_file_path_for_code_editor);
    QString rIDE_code_filename = rIDE_code_file_info.fileName ();

    if (!rIDE_file_handler.open (QIODevice::ReadWrite))
        QMessageBox::information (this, "Error!", rIDE_file_handler.errorString ());

    QString rIDE_main_code_editor_lbl_modified_text = "reaktrIDE Editor";
    rIDE_main_code_editor_lbl_modified_text.append (": (");
    rIDE_main_code_editor_lbl_modified_text.append (rIDE_code_filename);
    rIDE_main_code_editor_lbl_modified_text.append (")");
    QTextStream rIDE_text_stream (&rIDE_file_handler);
    ui->rIDE_main_code_editor->setPlainText (rIDE_text_stream.readAll ());
    ui->rIDE_main_code_editor_lbl->setText (rIDE_main_code_editor_lbl_modified_text);

    // TODO: 7.
    // 1. get the absolute path for the file from the tree view
    // 2. store them in a QVector
    // 3. extract the filename from absolute path -> rIDE_code_filename
    // 4. add one after the other in a combobox -> rIDE_main_open_buffers_cb
    // 5. allow one entry of the filename in the combobox of the IDE -> TODO 20
    rIDE_open_files_vector.append (rIDE_file_path_for_code_editor);
    ui->rIDE_main_open_buffers_cb->addItem (rIDE_code_filename);
}

void reaktrIDE::on_rIDE_main_open_buffers_cb_currentIndexChanged (int index)
{
    if (index >= 0){
        rIDE_file_model = new QFileSystemModel (this);
        QString rIDE_current_filepath = rIDE_open_files_vector [index];
        QFile rIDE_file_handler (rIDE_current_filepath);

        if (!rIDE_file_handler.open (QIODevice::ReadWrite))
            QMessageBox::information (this, "Error!", rIDE_file_handler.errorString ());

        QFileInfo rIDE_current_file_info (rIDE_current_filepath);
        QString rIDE_current_filename = rIDE_current_file_info.fileName ();
        QTextStream rIDE_text_stream (&rIDE_file_handler);
        ui->rIDE_main_code_editor->setPlainText (rIDE_text_stream.readAll ());
        QString rIDE_main_code_editor_lbl_modified_text = "reaktrIDE Editor";
        rIDE_main_code_editor_lbl_modified_text.append (": (");
        rIDE_main_code_editor_lbl_modified_text.append (rIDE_current_filename);
        rIDE_main_code_editor_lbl_modified_text.append (")");
        ui->rIDE_main_code_editor_lbl->setText(rIDE_main_code_editor_lbl_modified_text);
    }
}

void reaktrIDE::on_rIDE_main_code_editor_cursorPositionChanged ()
{
    int rIDE_code_editor_line = ui->rIDE_main_code_editor->textCursor ().blockNumber () + 1;
    int rIDE_code_editor_position = ui->rIDE_main_code_editor->textCursor ().columnNumber () + 1;
    ui->rIDE_statusBar->showMessage (QString ("Line: %1 | Col: %2").arg(rIDE_code_editor_line).arg (rIDE_code_editor_position));
}


void reaktrIDE::on_rIDE_actionC_triggered ()
{
    rIDE_new_c_project_dialog = new rIDE_new_c_project (this);
    rIDE_new_c_project_dialog->exec ();
}

void reaktrIDE::on_rIDE_actionCPP_triggered ()
{
    rIDE_new_cpp_project_dialog = new rIDE_new_cpp_project (this);
    rIDE_new_cpp_project_dialog->exec ();
}

void reaktrIDE::on_rIDE_actionPython_triggered ()
{
    rIDE_new_python_project_dialog = new rIDE_new_python_project (this);
    rIDE_new_python_project_dialog->exec ();
}
