#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileDialog>
#include <QTextBrowser>
#include <QCloseEvent>
#include "highlighter.h"
#include "codeeditor.h"
#include "connection.h"
#include "ssettingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void closeEvent (QCloseEvent *event) override;

    void setServerSetting(QString newAddress, QString newPort);

    void isTextChanged();

    void on_action_New_File_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Cut_triggered();

    void on_action_Undo_triggered();

    void on_action_Redo_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_action_Select_All_triggered();

    void on_actionBuild_triggered();

    void on_actionRun_triggered();

    void on_actionServer_Settings_triggered();

private:
    bool saved;
    int fontSize;
    Ui::MainWindow *ui;
    QDirModel *model;

    CodeEditor *codeEditor;

    QTabWidget *outputTab;
    QTextEdit *browserOutput, *browserErrMsg;

    QString mFilename;
    Highlighter *highlighter;

    Connection *connection;
    QString serverAddress;
    QString serverPort;
    QString defaultServerAddress = "127.0.0.1";
    QString defaultServerPort = "12346";

    void setupTab();
    void setupListView();
    void setupTreeView();
    void setupEditor();
    bool close_helper();
};

#endif // MAINWINDOW_H
