#include "assembler.h"

Assembler::Assembler()
{
    this->InitializeCommandTypeTable();
    this->InitializeCommandsOpcode();
}

QMap<QString, QVector<int> > Assembler::getCommandsOpcode()
{
    return CommandsOpcode;
}

void Assembler::setCommandsOpcode(QMap<QString,QVector<int>> &value)
{
    CommandsOpcode = value;
}

void Assembler::setMcl(QList<QVector<int> > &l)
{
    this->Mcl = l;
}

QList<QVector<int> > Assembler::getMcl()
{
    return this->Mcl;
}

void Assembler::InitializeCommandTypeTable()
{
    this->DefineR_TypeCommand();
    this->DefineI_TypeCommand();
    this->DefineJ_TypeCommand();
}

void Assembler::DefineR_TypeCommand()
{
    QSet<QString> temp;

    temp.insert("add");
    temp.insert("sub");
    temp.insert("slt");
    temp.insert("or");
    temp.insert("nand");

    this->CommandTypeTable.insert("R_Type",temp);
}

void Assembler::DefineI_TypeCommand()
{
    QSet<QString> temp;

    temp.insert("addi");
    temp.insert("ori");
    temp.insert("slti");
    temp.insert("lui");
    temp.insert("lw");
    temp.insert("sw");
    temp.insert("beq");
    temp.insert("jalr");

    this->CommandTypeTable.insert("I_Type",temp);
}

void Assembler::DefineJ_TypeCommand()
{
    QSet<QString> temp;

    temp.insert("j");
    temp.insert("halt");

    this->CommandTypeTable.insert("J_Type",temp);
}

void Assembler::InitializeCommandsOpcode()
{
    QStringList s = {
        "add","sub","slt","or","nand",
        "addi","slti","ori","lui","lw","sw","beq","jalr",
        "j", "halt"
    };

    for(int i = 0 ; i < s.size() ; i++)
    {
        this->CommandsOpcode.insert(s.at(i),this->ToBinary(i));
    }
}

MachineCode *Assembler::AssemblyToMachineCode()
{
    MachineCode *m(nullptr);
    QString instruction = ac.getInstruction();
    QStringList fields = ac.getFields();

    if(this->CommandTypeTable["R_Type"].contains(instruction))
    {
        R_Type *r = new R_Type();

//          inserting binary codes into machinecode     //

        //          inserting rd            //
        r->setRd(this->ToBinary(fields.at(0)));

        //          inserting rs            //
        r->setRs(this->ToBinary(fields.at(1)));

        //          inserting rt            //
        r->setRt(this->ToBinary(fields.at(2)));

        m = r;
    }
    else if(this->CommandTypeTable["I_Type"].contains(instruction))
    {
        I_Type *I = new I_Type();

        //          inserting rt            //
        I->setRt(this->ToBinary(fields.at(0)));

        //          inserting rs            //
        if(this->ac.getInstruction() == "lui")
        {
            I->setRs(this->ToBinary("0"));
        }
        else
        {
            I->setRs(this->ToBinary(fields.at(1)));
        }

        //      inserting offset        //
        if(this->ac.getInstruction() == "jalr")
        {
            I->setOffset(this->ToBinary("0"));
        }
        else if(this->ac.getInstruction() == "lui")
        {
            I->setOffset(this->ToBinary(fields.at(1)));
        }
        else
        {
            I->setOffset(this->ToBinary(fields.at(2)));
        }

        m = I;
    }
    else if(this->CommandTypeTable["J_Type"].contains(instruction))
    {
        J_Type *J = new J_Type();

        if(this->ac.getInstruction() == "halt")
        {
            J->setTargetAddress(this->ToBinary("0"));
        }
        else
        {
            J->setTargetAddress(this->ToBinary(fields.at(0)));
        }

        m = J;
    }

    if(!this->CommandsOpcode.keys().contains(instruction))
    {
        cerr << "Undefined Opcode...!" << endl;
        exit(1);
    }

    m->setOpcode(this->CommandsOpcode[instruction]);

    return m;
}

QVector<int> Assembler::ToBinary(const QString &number)
{
    QStack<int> temp;
    QVector<int> binarycode;
    int remain, kh = number.toInt(),stacksize = 0;

    while(kh != 0)
    {
        remain = kh % 2;
        kh = kh / 2;
        temp.push_back(remain);
    }

    if(temp.size() < 4)
    {
       int ssize = temp.size();

       for(int j = 0 ; j < 4 - ssize ; j++)
       {
           temp.push_back(0);
       }
    }

    stacksize = temp.size();

    for(int i = 0 ; i < stacksize ; i++)
    {
        binarycode.push_back(temp.pop());
    }

    return binarycode;
}

QVector<int> Assembler::ToBinary(int &number)
{
    QStack<int> temp;
    QVector<int> binarycode;
    int remain, kh = number,stacksize = 0;

    while(kh != 0)
    {
        remain = kh % 2;
        kh = kh / 2;
        temp.push_back(remain);
    }

    if(temp.size() < 4)
    {
        int ssize = temp.size();

        for(int j = 0 ; j < 4 - ssize ; j++)
        {
            temp.push_back(0);
        }
    }

    stacksize = temp.size();

    for(int i = 0 ; i < stacksize ; i++)
    {
        binarycode.push_back(temp.pop());
    }

    return binarycode;

}

void Assembler::OperateOnAssemblyLine(QString assemblyline)
{
    ac.ParseAssemblyCode(assemblyline);

    this->InsertLabelAddress();

    this->mc = this->AssemblyToMachineCode();

    this->Mcl.push_back(this->mc->ToBinaryMachineCode());

    ac.ClearAssemblyCode();
    delete this->mc;
}

void Assembler::OperateOnAssemblyFile(QString FileAddress)
{
    this->FirstScan(FileAddress);
    this->ProcessAssemblyCode(FileAddress);
}

void Assembler::ProcessAssemblyCode(QString FileAddress)
{
    QFile asfile(FileAddress);
    QTextStream see(&asfile);
    QString line;

    asfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        line = see.readLine();

        if(line.isEmpty())
        {
            break;
        }

        this->OperateOnAssemblyLine(line);
    }
    asfile.close();
}

void Assembler::FirstScan(QString fileaddress)
{
    QFile asmfile(fileaddress);
    QTextStream Fetch(&asmfile);
    QString line = "a";
    int labeladdress = 0;

    asmfile.open(QIODevice ::ReadOnly);

    while(!line.isEmpty())
    {
        QStringList sl;

        line = Fetch.readLine();
        sl = line.split(' ');

        if(sl.size() == 3 || (sl.size() == 2 && sl.contains("halt")))
        {
            this->SymbolTable.insert(sl.at(0),QString ::number(labeladdress));
        }
        ++labeladdress;
    }

    asmfile.close();
}

void Assembler::InsertLabelAddress()
{
    bool r;
    QString instruct = ac.getInstruction();

    r = (instruct == "beq") || (instruct == "lw") || (instruct == "sw") || (instruct == "j");

    if(!r)
    {
        return;
    }

    QString label = ac.getFields().last();
    int lbl = label.toInt();

    // this means that label(offset) is a number that must not alternate using symbol table.   //
    if(lbl != 0)
    {
        return;
    }


    if(this->SymbolTable.keys().contains(label))
    {
        ac.ReplaceField((ac.getFields().size() - 1),SymbolTable[label]);
    }
    else
    {
        cerr << "Undefined label" << endl;
        exit(1);
    }
}

void Assembler::WriteAssemblyFile()
{
    ofstream write("result.ASM");
    QStringList codes = { "start add 1,2,3" ,
                          "nand 13,14,15" ,
                          "ori 7,8,9" ,
                          "compare slti 4,5,6" ,
                          "subtract sub 4,5,6" ,
                          "beq 1,2,compare" ,
                          "sw 13,14,subtract" ,
                          "Exit hal" ,
                          "beq 4,7,Exit" ,
                          "j start" ,
                          "lui 9,2" ,
                          "jalr 4,5"
                        };

    if(!write)
    {
        cout << "assembly file isn't open" << endl;
    }

    for(int i = 0 ; i < codes.size() ; i++)
    {
        write << codes.at(i).toStdString() << endl;
    }
    write.close();
}

void Assembler::PrintMCL()
{
    QList<QVector<int>>::iterator itr;

    for(itr = this->Mcl.begin() ; itr != this->Mcl.end() ; itr++)
    {
        for(int j = 0 ; j < itr->size() ; j++)
        {
            cout << itr->at(j);

            if((j + 1) % 4 == 0)
            {
                cout << ',';
            }
        }
        cout << endl;
    }
}

void Assembler::printASMFile()
{
    QFile file("result.ASM");
    QTextStream qout(&file);
    QString line = "a";

    file.open(QIODevice::ReadOnly);

    while(!line.isEmpty())
    {
        line = qout.readLine();

        cout << line.toStdString() << endl;
    }

    file.close();
}

//void Assembler::WriteInAssemblyFile(QString txtfileaddress)
//{
//    QFile txtfile(txtfileaddress);
//    QTextStream see(&txtfile);
//    QString line;

//    ofstream assfile("result.ASM");

//    if(!assfile)
//    {
//        cout << "assembly file isn't open" << endl;
//        exit(0);
//    }

//    txtfile.open(QIODevice::ReadOnly);

//    while(see.atEnd())
//    {
//        line = see.readLine();

//        assfile << line.toStdString() << endl;
//    }

//    assfile.close();
//    txtfile.close();
//}

//void Assembler::InsertLabelsAddress()
//{
//    if(this->ac.getInstruction() == "sw" | this->ac.getInstruction() == "lw" | this->ac.getInstruction() == "beq")
//    {
//        this->ac.ReplaceField(2,this->SymbolTable[ac.getFields().at(2)]);
//    }
//    if(this->ac.getInstruction() == "j")
//    {
//        this->ac.ReplaceField(0,this->SymbolTable[ac.getFields().at(0)]);
//    }
//}

void Assembler::setMachineCode(MachineCode *Mc)
{
    this->mc = Mc;
}

MachineCode *Assembler::getMachineCode()
{
    return this->mc;
}

void Assembler::setAssemblyCode(AssemblyCode &Ac)
{
    this->ac = Ac;
}

AssemblyCode Assembler::getAssemblyCode()
{
    return this->ac;
}

void Assembler::setSymbolTable(QMap<QString, QString> &st)
{
    this->SymbolTable = st;
}

QMap<QString, QString> Assembler::getSymbolTable()
{
    return this->SymbolTable;
}

void Assembler::setCommandTypeTable(QMap<QString, QSet<QString> > &ctt)
{
    this->CommandTypeTable = ctt;
}

QMap<QString, QSet<QString> > Assembler::getCommandTypeTable()
{
    return this->CommandTypeTable;
}
