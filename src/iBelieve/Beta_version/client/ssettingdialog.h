#ifndef SSETTINGDIALOG_H
#define SSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SsettingDialog;
}

class SsettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SsettingDialog(QString address, QString port, QWidget *parent = 0);
    ~SsettingDialog();

    void setDefault(QString address, QString port);

signals:
    void paramsChanged(QString, QString);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::SsettingDialog *ui;

    QString defaultAddress;
    QString defaultPort;
    QString currentAddress;
    QString currentPort;

};

#endif // SSETTINGDIALOG_H
