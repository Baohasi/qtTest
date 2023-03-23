#include "CPromInfo.h"
#include "ui_CPromInfo.h"

CPromInfo::CPromInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPromInfo)
{
    ui->setupUi(this);
}

CPromInfo::~CPromInfo()
{
    delete ui;
}

void CPromInfo::insertInfo(QString contentStr)
{
    if(contentStr=="")
    {
       ui->textEdit->setVisible(false);
    }
    else
    {
        ui->textEdit->setVisible(true);
    }

    ui->PB_Cancle->setEnabled(true);
    ui->PB_Center->setEnabled(true);

    ui->PB_Center->setText(tr("确定"));
    ui->PB_Cancle->setText(tr("取消"));

    ui->PB_Center->setGeometry(480,15,80,30);
    ui->PB_Cancle->setGeometry(570,15,80,30);

    ui->textEdit->setGeometry(10,5,440,70);
    ui->textEdit->setText(contentStr);
}

void CPromInfo::on_PB_Center_clicked()
{
    ui->PB_Cancle->setEnabled(false);
    ui->PB_Center->setEnabled(false);

    ui->PB_Cancle->setVisible(false);
    ui->PB_Center->setVisible(false);
//    buttonState=0;
    emit sendInfoSignal(1);

//    m_newInfoTimer.stop();
    this->hide();
}

void CPromInfo::on_PB_Cancle_clicked()
{
    ui->PB_Cancle->setEnabled(false);
    ui->PB_Center->setEnabled(false);

    ui->PB_Cancle->setVisible(false);
    ui->PB_Center->setVisible(false);
//    buttonState=0;
    emit sendInfoSignal(2);
//    m_newInfoTimer.stop();
    this->hide();
}

