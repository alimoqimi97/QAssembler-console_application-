#ifndef MACHINECODE_H
#define MACHINECODE_H
#include <QVector>

class MachineCode
{
private:

protected:
    QVector<int> OpCode;
//    int OpCode[4];

public:
    MachineCode();

    //          get and set methods         //

    void setOpcode(QVector<int> &op);
    QVector<int> getOpcode();

//    void setOpCode(int op[]);
//    int *getOpcode();
    //          -------------------           //

    //              public methods          //
    virtual QVector<int> ToBinaryMachineCode();
    void InitializeField(QVector<int> &f, int init, int size);

    virtual ~MachineCode()
    {
    }
};

#endif // MACHINECODE_H
