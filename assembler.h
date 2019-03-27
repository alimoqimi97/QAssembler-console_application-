#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "assemblycode.h"
#include "r_type.h"
#include "i_type.h"
#include "j_type.h"
#include <fstream>
#include <QMap>
#include <QString>
#include <QSet>
#include <QStack>
#include <iostream>
#include <QVector>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;

class Assembler
{
private:
    MachineCode *mc;
    AssemblyCode ac;
    QMap<QString,QString> SymbolTable;
    QMap<QString,QSet<QString>> CommandTypeTable;
    QMap<QString,QVector<int>> CommandsOpcode;
    QList<QVector<int>> Mcl;

public:
    Assembler();

    //          public methods      //
    void setMachineCode(MachineCode *Mc);
    MachineCode *getMachineCode();

    void setAssemblyCode(AssemblyCode &Ac);
    AssemblyCode getAssemblyCode();

    void setSymbolTable(QMap<QString,QString> &st);
    QMap<QString,QString> getSymbolTable();

    void setCommandTypeTable(QMap<QString,QSet<QString>> &ctt);
    QMap<QString,QSet<QString>> getCommandTypeTable();

    QMap<QString,QVector<int>> getCommandsOpcode();
    void setCommandsOpcode(QMap<QString,QVector<int>> &value);

    void setMcl(QList<QVector<int>> &l);
    QList<QVector<int>> getMcl();
    //          ----------------        //

    //          public methods          //
    void InitializeCommandTypeTable();
    void DefineR_TypeCommand();
    void DefineI_TypeCommand();
    void DefineJ_TypeCommand();

    void InitializeCommandsOpcode();

    MachineCode *AssemblyToMachineCode();

    QVector<int> ToBinary(const QString &number);
    QVector<int> ToBinary(int &number);

    void OperateOnAssemblyLine(QString assemblyline);
    void OperateOnAssemblyFile(QString FileAddress);

    void ProcessAssemblyCode(QString FileAddress);

    void FirstScan(QString fileaddress);
    void InsertLabelAddress();

    void WriteAssemblyFile();

    void PrintMCL();

    //          testing             //
    void printASMFile();
    //          -------             //

//    void WriteInAssemblyFile(QString txtfileaddress);
};

#endif // ASSEMBLER_H
