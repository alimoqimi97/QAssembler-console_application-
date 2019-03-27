#ifndef R_TYPE_H
#define R_TYPE_H

#include "machinecode.h"

class R_Type: public MachineCode
{
private:
    QVector<int> Rs;
    QVector<int> Rt;
    QVector<int> Rd;

public:
    R_Type();

    //      get and set methods         //

    void setRs(QVector<int> rs);
    QVector<int> getRs();

    void setRt(QVector<int> rt);
    QVector<int> getRt();

    void setRd(QVector<int> rd);
    QVector<int> getRd();

    //      ------------------          //

    //      public methods          //

    virtual QVector<int> ToBinaryMachineCode();
};

#endif // R_TYPE_H
