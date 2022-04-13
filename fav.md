# reaktrIDE Learnings

-------------------------------------------------------------------
## URLs
* https://www.youtube.com/watch?v=E9eQO5czNrw - QMenu with UI files
* https://www.youtube.com/watch?v=tP70B-pdTH0 - Open a new window from a pushbutton in Qt
* https://www.youtube.com/watch?v=6KtOzh0StTc&list=PL2D1942A4688E9D63 - voidrealms
* https://www.youtube.com/watch?v=MvD_hFuLfzc - Open a file in Qt plain text editor
* https://stackoverflow.com/a/7947551 - restart application
* https://www.qt.io/blog/efficient-qstring-concatenation-with-c17-fold-expressions - Efficient QString concatenation with C++17 fold expressions
* https://www.youtube.com/watch?v=92biLZST6Vg - Open files from QTreeView
* https://www.youtube.com/watch?v=5Lb8DZhAAi8 - Adding items to combobox dynamically
* https://stackoverflow.com/a/35988271 - obtain filename from QString
* https://www.youtube.com/watch?v=NfT-Xo-4b50 - Creating , Deleting , Reading and writing to files with Qt
* https://www.youtube.com/watch?v=JtyCM4BTbYo - C++ Qt 4 - Signals and Slots
* https://stackoverflow.com/a/211045 | https://stackoverflow.com/a/295214 - How to create empty text file from a batch file?
* https://stackoverflow.com/a/10918705 - Platform independent path concatenation using “/” , “\”?
* https://stackoverflow.com/a/431720 - How do I change directory (cd) in Python?
* https://thispointer.com/how-to-create-a-directory-in-python/ - How to create a Directory in python?
* https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html - text editor example
* https://www.youtube.com/watch?v=ZGnuPIFKSJc - access the ui elements from another class (1)
* https://stackoverflow.com/a/27051725 - access the ui elements from another class (2)
* https://stackoverflow.com/a/37073463 - access the ui elements from another class (3)
* https://stackoverflow.com/a/23669506 - access the ui elements from another class (4)
* https://www.learncpp.com/cpp-tutorial/714-ellipsis-and-why-to-avoid-them/ - Avoid ellipsis

-------------------------------------------------------------------
## Excerpts / Code Snippets
* Restrict QDialog window to one instance - The normal way of doing this is to have a modal dialog box for your About window. Something like this - https://stackoverflow.com/a/35192597
```c++
void MyApp::on_actionAbout_triggered (){
    About dlg (this);
    // without dlg.show ()
    dlg.exec ();
}
```

* Restart Application via menu action
```c++
void reaktrIDE::on_rIDE_actionRestart_triggered (){
    QApplication::quit ();
    QProcess::startDetached (qApp->arguments ()[0], qApp->arguments ());
}
```

* Display the source code and its contents in a tree view
```c++
    QString rIDE_directory_path = QFileInfo (rIDE_directory_url.path()).filePath();
    rIDE_directory_path = rIDE_directory_path.remove (0,1);
    rIDE_directory_path = rIDE_directory_path.replace("/","\\\\");;
    QMessageBox::information (this, "Example", rIDE_directory_path);

    rIDE_list_model = new QFileSystemModel (this);
    rIDE_list_model->setRootPath(rIDE_directory_path);
    rIDE_list_model->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs|QDir::Files);
    ui->rIDE_main_source_tree_vw->setModel(rIDE_list_model);
    ui->rIDE_main_source_tree_vw->setRootIndex(rIDE_list_model->index(rIDE_directory_path));
```
* Hackish way, but an unsafe way to obtain the directory name from an absolute path
```c++
QStringList rIDE_path_list = rIDE_directory_path.split("\\");
QString rIDE_project_name = rIDE_path_list [rIDE_path_list.size()-1];
```
* Display the file contents in a code editor window
```c++
void reaktrIDE::on_rIDE_main_source_tree_vw_doubleClicked(const QModelIndex &index)
{
    rIDE_file_model = new QFileSystemModel (this);
    QString rIDE_file_path_for_code_editor = rIDE_file_model->fileInfo(index).absoluteFilePath();
    QFile rIDE_file_handler (rIDE_file_path_for_code_editor);

    if (!rIDE_file_handler.open(QIODevice::ReadOnly))
        QMessageBox::information(this, "Error!", rIDE_file_handler.errorString());

    QTextStream rIDE_text_stream (&rIDE_file_handler);
    ui->rIDE_main_code_editor->setText (rIDE_text_stream.readAll());
    qDebug() << index.row() << " : " << index.column() << " : Data ->" << index.data() << "File Path: " <<rIDE_file_path_for_code_editor;
}
```
* Obtain filename from (QString) absolute filepath
```c++
QFileInfo get_fileinfo (QString absolute_path);
QString get_filename = get_fileinfo.fileName();
```
* Modern C++ offers "nullptr" as a universal null pointer. You should use that instead of zero, because there are some obscure machines that have things like signed pointers where a null pointer is actually something like -1 rather than 0. Using nullptr is also a lot more explicit so it saves you from mixing up a pointer param and an int param. 0 could be valid for either, but if you try to pass nullptr to an int parameter it won't compile. If you put 0 thinking you were passing a null pointer, but it was actually an int parameter, the compiler could never warn you that you were doing something silly.
* Display the line number and column number in the code editor window (status bar)
```c++
void reaktrIDE::on_rIDE_main_code_editor_cursorPositionChanged()
{
    int rIDE_code_editor_line = ui->rIDE_main_code_editor->textCursor().blockNumber() + 1;
    int rIDE_code_editor_position = ui->rIDE_main_code_editor->textCursor().columnNumber() + 1;
    ui->rIDE_statusBar->showMessage(QString("Line: %1 | Col: %2").arg(rIDE_code_editor_line).arg(rIDE_code_editor_position));
}
```
* Set font to widgets using QFonts
```c++
//specify a new font.
QFont newFont("Courier", 8, QFont::Bold, true);
//set font of application
QApplication::setFont(newFont);
```
* Change directory
```c++
bool QDir::cd(QString path)
```
* Create directory
```c++
if (QDir::cd(QString path)){
	QDir::mkpath(QString dirname);
}
```
* File creation in Qt: The file handler needs full path of the file that needs to be open.
```c++
QDir parent_directory_handle (QString parent_directory_path);
QString file_name = "some_file.ext";
// join the filename with the parent_directory_path
QString filename_full_path = parent_directory_handle.filePath(file_name);
// create a QFile object that acts as a file handler
QFile some_file_handler(filename_full_path);
// check if the file is open with some set permissions
if (some_File_handler.open (QIODevice::SomePermission)){
	// create a text stream object to write to the file
    // pass thep pointer to the file handler object
    QTextStream text_stream (&some_file_handler);
    text_stream << "Some text";
    // close the file once the file is written
    some_file_handler.close ();
}
else
	// display that the file cannot be opened for processing	
```