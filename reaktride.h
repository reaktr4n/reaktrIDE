#ifndef REAKTRIDE_H
#define REAKTRIDE_H

#include <QMainWindow>
#include "about_reaktride_dialog_box.h"
#include "rIDE_new_c_project.h"
#include "rIDE_new_cpp_project.h"
#include "rIDE_new_python_project.h"
#include <QProcess>
#include <QFileDialog>
#include <QUrl>
#include <QDirIterator>
#include <QDir>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QFileSystemModel>
#include <QTextStream>
#include <QFile>
#include <QVector>

namespace Ui {
class reaktrIDE;
}

class reaktrIDE : public QMainWindow
{
    // QOBJECT macro allows Qt to work with the MOC - Meta Object Compiler
    // MOC connects all the signals with slots, and generates the code
    // MOC deos all the magic for you. One does not need to touch the code
    // generated.
    Q_OBJECT

public:
    explicit reaktrIDE(QWidget *parent = nullptr);
    ~reaktrIDE();

private slots:
    void on_rIDE_menu_actionQuit_triggered();
    void on_rIDE_menu_actionAbout_triggered ();
    void on_rIDE_actionRestart_triggered();
    void on_rIDE_actionOpen_Project_triggered();
    void on_rIDE_main_source_tree_vw_doubleClicked(const QModelIndex &index);
    void on_rIDE_main_open_buffers_cb_currentIndexChanged(int index);
    void on_rIDE_main_code_editor_cursorPositionChanged();
    void on_rIDE_actionC_triggered();
    void on_rIDE_actionCPP_triggered();

    void on_rIDE_actionPython_triggered();

private:
    Ui::reaktrIDE *ui;
    // for the customised About dialog box
    about_reaktride_dialog_box* about_rIDE_box;
    rIDE_new_c_project* rIDE_new_c_project_dialog;
    rIDE_new_cpp_project* rIDE_new_cpp_project_dialog;
    rIDE_new_python_project* rIDE_new_python_project_dialog;
    // for listing directories and files in a project
    QFileSystemModel* rIDE_list_model;
    QFileSystemModel* rIDE_file_model;
    QVector<QString> rIDE_open_files_vector;
};

#endif // REAKTRIDE_H
