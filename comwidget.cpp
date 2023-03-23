#include "comwidget.h"
#include "ui_comwidget.h"
#include <QDebug>
#include <QStringList>
#include <QHash>
#include <QMenu>

// 更新于 2023.3.23 哈哈哈哈


comWidget::comWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comWidget)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget();

    /*    for(int i=0;i<InfoNUm;i++)
    {
        m_PromInfo[i]=new CPromInfo();
        m_PromInfo[i]->insertInfo("" );

        currentInfoNum = ui->stackedWidget->addWidget(m_PromInfo[i]);

        connect(m_PromInfo[i], SIGNAL(sendInfoSignal(int)), this, SLOT(receive_InfoSlot(int)));
    }
*/
    m_PromInfo = new CPromInfo();
    m_PromInfo->insertInfo("");
    currentInfoNum = stackedWidget->addWidget(m_PromInfo);
    connect(m_PromInfo, SIGNAL(sendInfoSignal(int)), this, SLOT(receive_InfoSlot(int)));

    ui->verticalLayout->addWidget(stackedWidget);
    stackedWidget->setCurrentIndex(0);

    qDebug() << "Comwidget start. " ;

    //QHash
    /*
    QHash<QString,QStringList> hashMap1; //定义一个哈希变量
    QHash<QString,QStringList>::const_iterator mi; //定义一个哈希迭代器
    //插入一条记录
    QString str;
    QStringList list;
    str = "1";
    list << "hello" << "world";
    hashMap1.insert(str,list);

    //查找
    mi = hashMap1.find(str);
    if (mi != hashMap1.end())
    {
        QStringList list1 = mi.value();
        qDebug() << "mi.value: " << list1;
    }
*/
    //从数据库中查找内容

    QString str1 = "milliinDatabase_ThreePumb.db";
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(str1);
    if (!db.open())
    {
        if((db.lastError().type())!=QSqlError::NoError)
        {
            qDebug() << db.lastError();
        }
    }
    else  qDebug() << "db open success!";



    QString  DataBaseName="defaultData_TestNew"; //数据库表

    QSqlQuery setquery(QSqlDatabase::database("QSQLITE", true));
    QString strQuery="SELECT * FROM "+ DataBaseName;
    setquery.exec(strQuery);
    setquery.record();


    QStringList ItemRow;
    ItemRow<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8";
    int RowNum=ItemRow.size();

    QString strTest="";
    QStringList strlist;

    QHash<QString,QStringList> hashMap;  //定义一个哈希变量
    QHash<QString,QStringList>::const_iterator mi; //定义一个哈希迭代器

    do {
        for(int j=0;j<RowNum;j++) //读取一条记录
        {
            strTest=setquery.value(ItemRow.at(j).toDouble()).toString();
            strlist<<strTest;
        }
        QString KeyString;
        KeyString = strlist.at(0)+strlist.at(1)+strlist.at(2)+strlist.at(3); //读取一条记录的前4列内容
        hashMap.insert(KeyString,strlist); //将内容插入到哈希变量中：(前4列,整条记录内容)
        strlist.clear();
    }while(setquery.next()); //将所有条记录都读出来

    QStringList ItemDestValue1;
    ItemDestValue1<<"置换液速率"<<"准备"<<"置换液"<<""; //读取内容的前4列内容

    QString SrcString;
    for(int i=0;i<ItemDestValue1.size();i++) //连接前4列内容
    {
        SrcString+=ItemDestValue1.at(i);
    }
    mi = hashMap.find(SrcString);//哈希变量中查找

    if(mi != hashMap.end())
    {
        QStringList list;
        list.clear();
        list=mi.value();
        qDebug() << "list: " << list;
    }

    QString str = QueryDatabase("defaultData_TestNew","QSQLITE","Num","3",5);
    int Value = str.toDouble();

    qDebug() << "Value :" << Value;

{
    //新建菜单


    m_menuTreatmentWay= new QMenu();//获得菜单，并向上面添加菜单;
    m_menuTreatmentWay->setStyleSheet("border: 10px;color:#595c63;background:#FCE6C9;font: 75 16pt '微软雅黑'");
    ui->PB_TreatmentWay->setMenu(m_menuTreatmentWay);//按键上添加菜单


    QString str;

    str=QueryDatabase("CureMode","QSQLITE","Num","2",1);
    m_actionTreatmentWay1 = m_menuTreatmentWay->addAction(str);
    m_menuTreatmentWay->addSeparator();
    str=QueryDatabase("CureMode","QSQLITE","Num","3",1);
    m_actionTreatmentWay2 = m_menuTreatmentWay->addAction(str);
    m_menuTreatmentWay->addSeparator();
    str=QueryDatabase("CureMode","QSQLITE","Num","4",1);
    m_actionTreatmentWay3 = m_menuTreatmentWay->addAction(str);

    connect(m_actionTreatmentWay1, SIGNAL(triggered()),this, SLOT(PB_TreatmentWayHD_clicked()));
    connect(m_actionTreatmentWay2, SIGNAL(triggered()),this, SLOT(PB_TreatmentWayHDF_clicked()));
    connect(m_actionTreatmentWay3, SIGNAL(triggered()),this, SLOT(PB_TreatmentWayHF_clicked()));




}




}
QString comWidget::QueryDatabase(QString DatabaseStr,QString DataBaseSign,QString ItemDest, QString ItemStr,int row )
{
    QString str="";
    QSqlQuery setquery(QSqlDatabase::database(DataBaseSign, true));
    QString strQuery="SELECT * FROM " + DatabaseStr+ " WHERE " + ItemDest+ " = \"" +ItemStr+ "\"";
    setquery.exec(strQuery);
    if((setquery.lastError().type())!=QSqlError::NoError)
    {
        qDebug()<< ItemStr;
        qDebug() << setquery.lastError();
        return str;
    }
    setquery.record();
    if(!setquery.first())
    {
        qDebug() << ItemStr;
        qDebug() << setquery.lastError();
        return str;
    }
    str=setquery.value(row).toString();
    return str;
}

comWidget::~comWidget()
{
    delete ui;
}

void comWidget::receive_InfoSlot(int value)
{
    qDebug() << "receive info: " << value;
}

void comWidget::on_pushButton_clicked()
{
    //    m_PromInfo[InfoNUm-1]->insertInfo("您确定要加班么？" );
    m_PromInfo->insertInfo("您确定要加班么？" );
    stackedWidget->setCurrentIndex(currentInfoNum);
}

void comWidget::PB_TreatmentWayHD_clicked()
{
    ui->PB_TreatmentWay->setText(m_actionTreatmentWay1->text());
}
void comWidget::PB_TreatmentWayHDF_clicked()
{
    ui->PB_TreatmentWay->setText(m_actionTreatmentWay2->text());
}
void comWidget::PB_TreatmentWayHF_clicked()
{
    ui->PB_TreatmentWay->setText(m_actionTreatmentWay3->text());
}
