#include "r_type.h"

R_Type::R_Type():MachineCode()
{
    this->InitializeField(this->Rd,0,4);
    this->InitializeField(this->Rs,0,4);
    this->InitializeField(this->Rt,0,4);

//    this->InitializeFields(this->Rs);
//    this->InitializeFields(this->Rt);
//    this->InitializeFields(this->Rd);
}

void R_Type::setRs(QVector<int> rs)
{
    this->Rs = rs;
}

QVector<int> R_Type::getRs()
{
    return this->Rs;
}

void R_Type::setRt(QVector<int> rt)
{
    this->Rt = rt;
}

QVector<int> R_Type::getRt()
{
    return this->Rt;
}

void R_Type::setRd(QVector<int> rd)
{
    this->Rd = rd;
}

QVector<int> R_Type::getRd()
{
    return this->Rd;
}

QVector<int> R_Type::ToBinaryMachineCode()
{
    QVector<int> binarymachinecode;

    binarymachinecode.fill(0,12);

    //        for(int i = 0 ; i < 12 ; i++)
    //        {
    //            binarymachinecode.push_back(0);
    //        }

    for(int j = 0 ; j < this->Rd.size() ; j++)
    {
        binarymachinecode.push_back(this->Rd.at(j));
    }

    for(int k = 0 ; k < this->Rt.size() ; k++)
    {
        binarymachinecode.push_back(this->Rt.at(k));
    }

    for(int a = 0 ; a < this->Rs.size() ; a++)
    {
        binarymachinecode.push_back(this->Rs.at(a));
    }

    for(int b = 0 ; b < this->OpCode.size() ; b++)
    {
        binarymachinecode.push_back(this->OpCode.at(b));
    }

    for(int h = 0 ; h < 4 ; h++)
    {
        binarymachinecode.push_back(0);
    }

    return binarymachinecode;
}

//void R_Type::setRs(int rs[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->Rs[i] = rs[i];
//    }
//}

//int *R_Type::getRs()
//{
//    return this->Rs;
//}

//void R_Type::setRd(int rd[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->Rd[i] = rd[i];
//    }
//}

//int *R_Type::getRd()
//{
//    return this->Rd;
//}

//void R_Type::setRt(int rt[])
//{
//    for(int i = 0 ; i < 4 ; i++)
//    {
//        this->Rt[i] = rt[i];
//    }
//}

//int *R_Type::getRt()
//{
//    return this->Rt;
//}
