#include "machinecode.h"

MachineCode::MachineCode()
{
    this->InitializeField(this->OpCode,0,4);
}

void MachineCode::setOpcode(QVector<int> &op)
{
    this->OpCode = op;
}

QVector<int> MachineCode::getOpcode()
{
    return this->OpCode;
}

//void MachineCode::setOpCode(int op[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->OpCode[i] = op[i];
//    }
//}

//int *MachineCode::getOpcode()
//{
//    return this->OpCode;
//}

QVector<int> MachineCode::ToBinaryMachineCode()
{}

void MachineCode::InitializeField(QVector<int> &f, int init,int size)
{
    for(int i = 0 ; i < size; i++)
    {
        f.push_back(init);
    }
}
