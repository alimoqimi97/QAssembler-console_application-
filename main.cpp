#include"assemblycode.h"
#include "assembler.h"
#include<iostream>
#include <QTextStream>
using namespace std;

#include<QStringList>

int main()
{
    Assembler assembler;
    QString FileAddress = "result.ASM";

//    cout << "Enter Your file address :" << endl;
//    see >> FileAddress;

    assembler.WriteAssemblyFile();
    assembler.OperateOnAssemblyFile(FileAddress);

    assembler.PrintMCL();

//    cout << "done!..." << endl;


}
