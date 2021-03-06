#include "Custom_APDU.h"
#include <ui_Custom_APDU.h>
#include <Qt>
#include <QString>
#include <XMLFile/tinyxml2.h>

extern QString BuildMessage(QString apdu, QString SA, QString ctrl_zone);

extern QString re_rever_add();

Custom_APDU::Custom_APDU(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(send()), Qt::UniqueConnection);
    ui->textEdit->setText("05 01 03 40 01 02 00 00");
}

void Custom_APDU::send()
{
    QString a = ui->textEdit->toPlainText().remove(' ');
    a.remove('\n');
    qDebug() << "get from textedit" << a;
    QString re_message;
    if (a[0] != '6')
    {
        QString add = re_rever_add();
        qDebug() << "发送add" << add;
        re_message = BuildMessage(a, add, "43");

    }
    emit send_write({re_message, "自定义APDU"});
}
