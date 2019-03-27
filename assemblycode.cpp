#include "assemblycode.h"

AssemblyCode::AssemblyCode()
{
}

void AssemblyCode::setLabel(QString &l)
{
    this->Label = l;
}

QString AssemblyCode::getLabel()
{
    return this->Label;
}

void AssemblyCode::setInstruction(QString &ins)
{
    this->Instruction = ins;
}

QString AssemblyCode::getInstruction()
{
    return this->Instruction;
}

void AssemblyCode::setFields(QStringList &sl)
{
    this->Fields = sl;
}

QStringList AssemblyCode::getFields()
{
    return this->Fields;
}

void AssemblyCode::ReplaceField(int index,QString field)
{
    this->Fields.replace(index,field);
}

//void AssemblyCode::setField1(QString &f1)
//{
//    this->Field1 = f1;
//}

//QString AssemblyCode::getField1()
//{
//    return this->Field1;
//}

//void AssemblyCode::setField2(QString &f2)
//{
//    this->Field2 = f2;
//}

//QString AssemblyCode::getField2()
//{
//    return this->Field2;
//}

//void AssemblyCode::setField3(QString &f3)
//{
//    this->Field3 = f3;
//}

//QString AssemblyCode::getField3()
//{
//    return this->Field3;
//}

void AssemblyCode::ParseAssemblyCode(QString assc)
{
    QStringList sl;

    sl = assc.split(' ');

    if(sl.contains("halt"))
    {
        this->Instruction = "halt";
        this->Label = sl.at(0);
        return;
    }


    if(sl.size() == 2)
    {
        this->Instruction = sl.at(0);
        this->Fields = sl.at(1).split(',');
    }
    else if(sl.size() == 3)
    {
        this->Label = sl.at(0);
        this->Instruction = sl.at(1);
        this->Fields = sl.at(2).split(',');
    }
}

void AssemblyCode::ClearAssemblyCode()
{
    this->Label.clear();
    this->Instruction.clear();
    this->Fields.clear();
}
