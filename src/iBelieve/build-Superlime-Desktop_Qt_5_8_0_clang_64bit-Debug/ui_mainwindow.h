/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New_File;
    QAction *actionOpen_File;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Paste;
    QAction *action_Select_All;
    QAction *actionGo_To_Line;
    QAction *actionSave;
    QAction *actionSave_All;
    QAction *actionClose;
    QAction *actionClose_All;
    QAction *actionExit;
    QAction *actionCount_Line;
    QAction *actionBuild;
    QAction *actionBuild_All;
    QAction *actionRun;
    QAction *actionServer_Settings;
    QAction *actionDisconnect;
    QAction *actionQuick_Find;
    QAction *actionQuick_Replace;
    QAction *actionFind_In_File;
    QAction *actionReplace_In_File;
    QAction *actionJava_Doc;
    QAction *actionTechnical_Support;
    QAction *actionReport_Bug;
    QAction *actionSystem_Information;
    QAction *actionAbout_Superlime;
    QAction *actionFull_Screen;
    QAction *actionOptions;
    QAction *actionHide;
    QAction *actionAbout_Qt;
    QAction *actionStop;
    QAction *actionConnect;
    QAction *actionTerminal;
    QAction *actionSave_As;
    QAction *actionZoom_Out;
    QAction *actionZoom_In;
    QAction *actionShow;
    QAction *actionExit_Full_Screen;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QTreeView *treeView;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSplitter *splitter_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menuFind_Replace;
    QMenu *menuBuild;
    QMenu *menu_Tools;
    QMenu *menu_Window;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Images/lemon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_New_File = new QAction(MainWindow);
        action_New_File->setObjectName(QStringLiteral("action_New_File"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Images/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New_File->setIcon(icon1);
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_File->setIcon(icon2);
        action_Undo = new QAction(MainWindow);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Images/editundo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Undo->setIcon(icon3);
        action_Redo = new QAction(MainWindow);
        action_Redo->setObjectName(QStringLiteral("action_Redo"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/Images/editredo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Redo->setIcon(icon4);
        action_Cut = new QAction(MainWindow);
        action_Cut->setObjectName(QStringLiteral("action_Cut"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/Images/editcut.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cut->setIcon(icon5);
        action_Copy = new QAction(MainWindow);
        action_Copy->setObjectName(QStringLiteral("action_Copy"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/Images/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copy->setIcon(icon6);
        action_Paste = new QAction(MainWindow);
        action_Paste->setObjectName(QStringLiteral("action_Paste"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/Images/editpaste.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Paste->setIcon(icon7);
        action_Select_All = new QAction(MainWindow);
        action_Select_All->setObjectName(QStringLiteral("action_Select_All"));
        actionGo_To_Line = new QAction(MainWindow);
        actionGo_To_Line->setObjectName(QStringLiteral("actionGo_To_Line"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/Images/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon8);
        actionSave_All = new QAction(MainWindow);
        actionSave_All->setObjectName(QStringLiteral("actionSave_All"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose_All = new QAction(MainWindow);
        actionClose_All->setObjectName(QStringLiteral("actionClose_All"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/Images/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon9);
        actionCount_Line = new QAction(MainWindow);
        actionCount_Line->setObjectName(QStringLiteral("actionCount_Line"));
        actionBuild = new QAction(MainWindow);
        actionBuild->setObjectName(QStringLiteral("actionBuild"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/Images/Registry.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBuild->setIcon(icon10);
        actionBuild_All = new QAction(MainWindow);
        actionBuild_All->setObjectName(QStringLiteral("actionBuild_All"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/Images/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon11);
        actionServer_Settings = new QAction(MainWindow);
        actionServer_Settings->setObjectName(QStringLiteral("actionServer_Settings"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/Images/Settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionServer_Settings->setIcon(icon12);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionQuick_Find = new QAction(MainWindow);
        actionQuick_Find->setObjectName(QStringLiteral("actionQuick_Find"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/Images/Zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuick_Find->setIcon(icon13);
        actionQuick_Replace = new QAction(MainWindow);
        actionQuick_Replace->setObjectName(QStringLiteral("actionQuick_Replace"));
        actionFind_In_File = new QAction(MainWindow);
        actionFind_In_File->setObjectName(QStringLiteral("actionFind_In_File"));
        actionReplace_In_File = new QAction(MainWindow);
        actionReplace_In_File->setObjectName(QStringLiteral("actionReplace_In_File"));
        actionJava_Doc = new QAction(MainWindow);
        actionJava_Doc->setObjectName(QStringLiteral("actionJava_Doc"));
        actionTechnical_Support = new QAction(MainWindow);
        actionTechnical_Support->setObjectName(QStringLiteral("actionTechnical_Support"));
        actionReport_Bug = new QAction(MainWindow);
        actionReport_Bug->setObjectName(QStringLiteral("actionReport_Bug"));
        actionSystem_Information = new QAction(MainWindow);
        actionSystem_Information->setObjectName(QStringLiteral("actionSystem_Information"));
        actionAbout_Superlime = new QAction(MainWindow);
        actionAbout_Superlime->setObjectName(QStringLiteral("actionAbout_Superlime"));
        actionFull_Screen = new QAction(MainWindow);
        actionFull_Screen->setObjectName(QStringLiteral("actionFull_Screen"));
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionHide = new QAction(MainWindow);
        actionHide->setObjectName(QStringLiteral("actionHide"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/Images/qt-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon14);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/Images/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon15);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionTerminal = new QAction(MainWindow);
        actionTerminal->setObjectName(QStringLiteral("actionTerminal"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icons/Images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon16);
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icons/Images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon17);
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QStringLiteral("actionShow"));
        actionExit_Full_Screen = new QAction(MainWindow);
        actionExit_Full_Screen->setObjectName(QStringLiteral("actionExit_Full_Screen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QStringLiteral("treeView"));
        splitter->addWidget(treeView);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        listView = new QListView(verticalLayoutWidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(verticalLayoutWidget);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        horizontalLayoutWidget = new QWidget(splitter_2);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(true);

        horizontalLayout_4->addWidget(pushButton_3);

        splitter_2->addWidget(horizontalLayoutWidget);
        splitter_3->addWidget(splitter_2);

        gridLayout->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QStringLiteral("menu_Edit"));
        menuFind_Replace = new QMenu(menu_Edit);
        menuFind_Replace->setObjectName(QStringLiteral("menuFind_Replace"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QStringLiteral("menu_Tools"));
        menu_Window = new QMenu(menuBar);
        menu_Window->setObjectName(QStringLiteral("menu_Window"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Window->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New_File);
        menu_File->addAction(actionOpen_File);
        menu_File->addSeparator();
        menu_File->addAction(actionSave);
        menu_File->addAction(actionSave_As);
        menu_File->addAction(actionSave_All);
        menu_File->addSeparator();
        menu_File->addAction(actionClose);
        menu_File->addAction(actionClose_All);
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menu_Edit->addAction(action_Undo);
        menu_Edit->addAction(action_Redo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(action_Copy);
        menu_Edit->addAction(action_Paste);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Select_All);
        menu_Edit->addSeparator();
        menu_Edit->addAction(menuFind_Replace->menuAction());
        menu_Edit->addAction(actionGo_To_Line);
        menu_Edit->addAction(actionCount_Line);
        menuFind_Replace->addAction(actionQuick_Find);
        menuFind_Replace->addAction(actionQuick_Replace);
        menuFind_Replace->addSeparator();
        menuFind_Replace->addAction(actionFind_In_File);
        menuFind_Replace->addAction(actionReplace_In_File);
        menuBuild->addAction(actionBuild);
        menuBuild->addAction(actionBuild_All);
        menuBuild->addSeparator();
        menuBuild->addAction(actionRun);
        menuBuild->addAction(actionStop);
        menuBuild->addSeparator();
        menuBuild->addAction(actionConnect);
        menuBuild->addAction(actionDisconnect);
        menuBuild->addAction(actionServer_Settings);
        menu_Tools->addAction(actionTerminal);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionOptions);
        menu_Window->addAction(actionFull_Screen);
        menu_Window->addAction(actionExit_Full_Screen);
        menu_Window->addAction(actionHide);
        menu_Window->addAction(actionShow);
        menu_Help->addAction(actionJava_Doc);
        menu_Help->addSeparator();
        menu_Help->addAction(actionTechnical_Support);
        menu_Help->addAction(actionReport_Bug);
        menu_Help->addAction(actionSystem_Information);
        menu_Help->addSeparator();
        menu_Help->addAction(actionAbout_Superlime);
        menu_Help->addAction(actionAbout_Qt);
        mainToolBar->addAction(action_New_File);
        mainToolBar->addAction(actionOpen_File);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Undo);
        mainToolBar->addAction(action_Redo);
        mainToolBar->addAction(actionQuick_Find);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionBuild);
        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionStop);
        mainToolBar->addAction(actionServer_Settings);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoom_Out);
        mainToolBar->addAction(actionZoom_In);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_New_File->setText(QApplication::translate("MainWindow", "New File", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_New_File->setToolTip(QApplication::translate("MainWindow", "New File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_New_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen_File->setToolTip(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOpen_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        action_Undo->setText(QApplication::translate("MainWindow", "Undo", Q_NULLPTR));
        action_Undo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", Q_NULLPTR));
        action_Redo->setText(QApplication::translate("MainWindow", "Redo", Q_NULLPTR));
        action_Redo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", Q_NULLPTR));
        action_Cut->setText(QApplication::translate("MainWindow", "Cut", Q_NULLPTR));
        action_Cut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
        action_Copy->setText(QApplication::translate("MainWindow", "Copy", Q_NULLPTR));
        action_Copy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
        action_Paste->setText(QApplication::translate("MainWindow", "Paste", Q_NULLPTR));
        action_Paste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", Q_NULLPTR));
        action_Select_All->setText(QApplication::translate("MainWindow", "Select All", Q_NULLPTR));
        action_Select_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", Q_NULLPTR));
        actionGo_To_Line->setText(QApplication::translate("MainWindow", "Go To Line", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionSave_All->setText(QApplication::translate("MainWindow", "Save All", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", Q_NULLPTR));
        actionClose_All->setText(QApplication::translate("MainWindow", "Close All", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        actionCount_Line->setText(QApplication::translate("MainWindow", "Count Line", Q_NULLPTR));
        actionBuild->setText(QApplication::translate("MainWindow", "Build", Q_NULLPTR));
        actionBuild_All->setText(QApplication::translate("MainWindow", "Build All", Q_NULLPTR));
        actionRun->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        actionServer_Settings->setText(QApplication::translate("MainWindow", "Server Settings", Q_NULLPTR));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        actionQuick_Find->setText(QApplication::translate("MainWindow", "Quick Find", Q_NULLPTR));
        actionQuick_Find->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", Q_NULLPTR));
        actionQuick_Replace->setText(QApplication::translate("MainWindow", "Quick Replace", Q_NULLPTR));
        actionFind_In_File->setText(QApplication::translate("MainWindow", "Find In File", Q_NULLPTR));
        actionReplace_In_File->setText(QApplication::translate("MainWindow", "Replace In File", Q_NULLPTR));
        actionJava_Doc->setText(QApplication::translate("MainWindow", "Java Doc", Q_NULLPTR));
        actionTechnical_Support->setText(QApplication::translate("MainWindow", "Technical Support", Q_NULLPTR));
        actionReport_Bug->setText(QApplication::translate("MainWindow", "Report Bug", Q_NULLPTR));
        actionSystem_Information->setText(QApplication::translate("MainWindow", "System Information", Q_NULLPTR));
        actionAbout_Superlime->setText(QApplication::translate("MainWindow", "About Superlime", Q_NULLPTR));
        actionFull_Screen->setText(QApplication::translate("MainWindow", "Full Screen", Q_NULLPTR));
        actionOptions->setText(QApplication::translate("MainWindow", "Options", Q_NULLPTR));
        actionHide->setText(QApplication::translate("MainWindow", "Hide", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", Q_NULLPTR));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        actionTerminal->setText(QApplication::translate("MainWindow", "Terminal", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_As->setToolTip(QApplication::translate("MainWindow", "Save As", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom Out", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoom_Out->setToolTip(QApplication::translate("MainWindow", "Zoom Out", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionZoom_Out->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", Q_NULLPTR));
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoom_In->setToolTip(QApplication::translate("MainWindow", "Zoom In", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionZoom_In->setShortcut(QApplication::translate("MainWindow", "Ctrl+=", Q_NULLPTR));
        actionShow->setText(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        actionExit_Full_Screen->setText(QApplication::translate("MainWindow", "Window Size", Q_NULLPTR));
        actionExit_Full_Screen->setShortcut(QApplication::translate("MainWindow", "Esc", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Find", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", Q_NULLPTR));
        menuFind_Replace->setTitle(QApplication::translate("MainWindow", "Find/Replace", Q_NULLPTR));
        menuBuild->setTitle(QApplication::translate("MainWindow", "&Build", Q_NULLPTR));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", Q_NULLPTR));
        menu_Window->setTitle(QApplication::translate("MainWindow", "&Window", Q_NULLPTR));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
