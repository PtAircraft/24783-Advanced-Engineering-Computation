#include "ssettingdialog.h"
#include "ui_ssettingdialog.h"

SsettingDialog::SsettingDialog(QString address, QString port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SsettingDialog)
{
    ui->setupUi(this);

    currentAddress = address;
    currentPort = port;

    ui->horizontalLayout_2->setStretch(0, 1);
    ui->horizontalLayout_2->setStretch(1, 2);

    ui->horizontalLayout_3->setStretch(0, 1);
    ui->horizontalLayout_3->setStretch(1, 2);

    ui->horizontalLayout->setStretch(0, 1);
    ui->horizontalLayout->setStretch(1, 1);
    ui->horizontalLayout->setStretch(2, 1);

    ui->lineEdit->setText(currentAddress);
    ui->lineEdit_2->setText(currentPort);
}

SsettingDialog::~SsettingDialog()
{
    delete ui;
}

void SsettingDialog::setDefault(QString address, QString port)
{
    defaultAddress = address;
    defaultPort = port;
}

void SsettingDialog::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(defaultAddress);
    ui->lineEdit_2->setText(defaultPort);
}

void SsettingDialog::on_pushButton_clicked()
{
    emit paramsChanged(ui->lineEdit->text(), ui->lineEdit_2->text());
}

