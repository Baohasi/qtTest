#ifndef COMWIDGET_H
#define COMWIDGET_H

#include "CPromInfo.h"

#include <QWidget>
#include <QStackedWidget>

#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class comWidget;
}

class comWidget : public QWidget
{
    Q_OBJECT

public:
    explicit comWidget(QWidget *parent = 0);
    ~comWidget();

    QString QueryDatabase(QString DatabaseStr,QString DataBaseSign,QString ItemDest, QString ItemStr,int row );

private:
    Ui::comWidget *ui;

    QStackedWidget * stackedWidget;

    QSqlDatabase db;

    QMenu * m_menuTreatmentWay;	//治疗方式

    QAction* m_actionTreatmentWay1;
    QAction* m_actionTreatmentWay2;
    QAction* m_actionTreatmentWay3;



// #define InfoNUm 10

    int currentInfoNum;

//    CPromInfo * m_PromInfo[InfoNUm];
    CPromInfo * m_PromInfo;

    int DisplacementFluidWay;


private slots:
    void receive_InfoSlot(int value);
    void on_pushButton_clicked();

    void PB_TreatmentWayHD_clicked();
    void PB_TreatmentWayHDF_clicked();
    void PB_TreatmentWayHF_clicked();


};


#endif // COMWIDGET_H
