#ifndef ASSEMBLYCODE_H
#define ASSEMBLYCODE_H

#include<QString>
#include<QStringList>

class AssemblyCode
{
private:
    QString Label;
    QString Instruction;
    QStringList Fields;

public:
    AssemblyCode();

    //          get and set methods         //
    void setLabel(QString &l);
    QString getLabel();

    void setInstruction(QString &ins);
    QString getInstruction();

    void setFields(QStringList &sl);
    QStringList getFields();

    void ReplaceField(int index,QString field);

    //          -------------------         //

    //          public methods              //

    void ParseAssemblyCode(QString assc);
    void ClearAssemblyCode();
};

#endif // ASSEMBLYCODE_H
