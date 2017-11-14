/********************************************************************************
** Form generated from reading UI file 'ssettingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSETTINGDIALOG_H
#define UI_SSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SsettingDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *SsettingDialog)
    {
        if (SsettingDialog->objectName().isEmpty())
            SsettingDialog->setObjectName(QStringLiteral("SsettingDialog"));
        SsettingDialog->resize(349, 253);
        gridLayout = new QGridLayout(SsettingDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_3 = new QPushButton(SsettingDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(SsettingDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(SsettingDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(SsettingDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(SsettingDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(true);

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(SsettingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(SsettingDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        retranslateUi(SsettingDialog);
        QObject::connect(pushButton_2, SIGNAL(clicked()), SsettingDialog, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(clicked()), SsettingDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(SsettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SsettingDialog)
    {
        SsettingDialog->setWindowTitle(QApplication::translate("SsettingDialog", "Dialog", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("SsettingDialog", "Default", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SsettingDialog", "Ok", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SsettingDialog", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("SsettingDialog", "Server Address", Q_NULLPTR));
        label_2->setText(QApplication::translate("SsettingDialog", "Server Port", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SsettingDialog: public Ui_SsettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSETTINGDIALOG_H
