#include "i_type.h"

I_Type::I_Type():MachineCode()
{
    this->InitializeField(this->Rt,0,4);
    this->InitializeField(this->Rs,0,4);
    this->InitializeField(this->Offset,0,16);

//    this->InitializeFields(this->Rt);
//    this->InitializeFields(this->Rs);
}

void I_Type::setRs(QVector<int> rs)
{
    this->Rs = rs;
}

QVector<int> I_Type::getRs()
{
    return this->Rs;
}

void I_Type::setRt(QVector<int> rt)
{
    this->Rt = rt;
}

QVector<int> I_Type::getRt()
{
    return this->Rt;
}

void I_Type::setOffset(QVector<int> offs)
{    
    if(offs.size() > 16)
    {
        cerr << "The size of offset is is bigger than 16 bits...!" << endl;
        exit(1);
    }
    else
    {
        this->Offset = offs;
    }
}

QVector<int> I_Type::getOffset()
{
    return this->Offset;
}

//void I_Type::setRs(int rs[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->Rs[i] = rs[i];
//    }
//}

//int *I_Type::getRs()
//{
//    return this->Rs;
//}

//void I_Type::setRt(int rt[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->Rt[i] = rt[i];
//    }
//}

//int *I_Type::getRt()
//{
//    return this->Rt;
//}

void I_Type::InitializeFields(int r[])
{
    for(int I = 0 ; I < 4 ; I++)
    {
        r[I] = 0;
    }
}

QVector<int> I_Type::ToBinaryMachineCode()
{
    QVector<int> binarymachinecode;

    binarymachinecode.fill(0,16 - this->Offset.size());

    for(int i = 0 ; i < this->Offset.size() ; i++)
    {
        binarymachinecode.push_back(this->Offset.at(i));
    }

    for(int j = 0 ; j < this->Rt.size() ; j++)
    {
        binarymachinecode.push_back(this->Rt.at(j));
    }

    for(int k = 0 ; k < this->Rs.size() ; k++)
    {
        binarymachinecode.push_back(this->Rs.at(k));
    }

    for(int g = 0 ; g < this->OpCode.size() ; g++)
    {
        binarymachinecode.push_back(this->OpCode.at(g));
    }
    for(int h = 0 ; h < 4 ; h++)
    {
        binarymachinecode.push_back(0);
    }

    return binarymachinecode;
}
