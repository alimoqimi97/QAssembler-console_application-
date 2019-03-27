#ifndef J_TYPE_H
#define J_TYPE_H

#include"machinecode.h"
#include <iostream>
using namespace std;


class J_Type: public MachineCode
{
private:
    QVector<int> TargetAddress;

public:
    J_Type();

    //     get and set methods      //
    void setTargetAddress(QVector<int> ta);
    QVector<int> getTargetAddress();
    //      ------------------      //

    //          public methods          //
    virtual QVector<int> ToBinaryMachineCode();
};

#endif // J_TYPE_H
