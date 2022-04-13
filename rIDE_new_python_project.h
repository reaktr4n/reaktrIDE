#ifndef RIDE_NEW_PYTHON_PROJECT_H
#define RIDE_NEW_PYTHON_PROJECT_H

#include <QDialog>

namespace Ui {
class rIDE_new_python_project;
}

class rIDE_new_python_project : public QDialog
{
    Q_OBJECT

public:
    explicit rIDE_new_python_project(QWidget *parent = nullptr);
    ~rIDE_new_python_project();

private slots:
    void on_rIDE_new_py_project_cancel_btn_clicked();

private:
    Ui::rIDE_new_python_project *ui;
};

#endif // RIDE_NEW_PYTHON_PROJECT_H
