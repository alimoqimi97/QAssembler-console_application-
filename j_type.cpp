#include "j_type.h"

J_Type::J_Type():MachineCode()
{
    this->InitializeField(TargetAddress,0,16);

//    for(int j = 0 ; j < 16 ; j++)
//    {
//        this->TargetAddress[j] = 0;
//    }
}

void J_Type::setTargetAddress(QVector<int> ta)
{    
    if(ta.size() > 16)
    {
        cerr << "The size of offset or targetaddress is bigger than 16 bits...!" << endl;
        exit(1);
    }
    else
    {
        this->TargetAddress = ta;
    }
}

QVector<int> J_Type::getTargetAddress()
{
    return this->TargetAddress;
}

QVector<int> J_Type::ToBinaryMachineCode()
{
    QVector<int> binarymachinecode;

    binarymachinecode.fill(0,16 - this->TargetAddress.size());

    for(int i = 0 ; i < this->TargetAddress.size() ; i++)
    {
        binarymachinecode.push_back(TargetAddress.at(i));
    }

    for(int j = 0 ; j < 8 ; j++)
    {
        binarymachinecode.push_back(0);
    }

    for(int k = 0 ; k < this->OpCode.size() ; k++)
    {
        binarymachinecode.push_back(this->OpCode.at(k));
    }

    for(int a = 0 ; a < 4 ; a++)
    {
        binarymachinecode.push_back(0);
    }

    return binarymachinecode;
}

//void J_Type::setTargetAddress(int ta[])
//{
//    for(int i = 0 ; i < 16 ; i++)
//    {
//        this->TargetAddress[i] = ta[i];
//    }
//}

//int *J_Type::getTargetAddress()
//{
//    return this->TargetAddress;
//}
