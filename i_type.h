#ifndef I_TYPE_H
#define I_TYPE_H

#include "machinecode.h"
#include <iostream>
using namespace std;


class I_Type: public MachineCode
{
private:
    QVector<int> Rs;
    QVector<int> Rt;
    QVector<int> Offset;

public:
    I_Type();

    //     get and set methods      //

    void setRs(QVector<int> rs);
    QVector<int> getRs();

    void setRt(QVector<int> rt);
    QVector<int> getRt();

    void setOffset(QVector<int> offs);
    QVector<int> getOffset();

    //    ---------------------     //

    //          public methods      //
    void InitializeFields(int r[]);

    virtual QVector<int> ToBinaryMachineCode();
};

#endif // I_TYPE_H
