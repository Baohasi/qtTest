#ifndef CPROMINFO_H
#define CPROMINFO_H

#include <QWidget>

namespace Ui {
class CPromInfo;
}

class CPromInfo : public QWidget
{
    Q_OBJECT

public:
    explicit CPromInfo(QWidget *parent = 0);
    ~CPromInfo();

    void insertInfo(QString contentStr);

signals:
    void sendInfoSignal(int value);

private slots:
    void on_PB_Center_clicked();

    void on_PB_Cancle_clicked();

private:
    Ui::CPromInfo *ui;

};

#endif // CPROMINFO_H
