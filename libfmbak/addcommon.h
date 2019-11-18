#ifndef ADDCOMMON_H
#define ADDCOMMON_H

#include <QString>

class AddCommon
{
public:
    AddCommon();
    static bool ConfigureFirstPath();
    static QString GetOpenPath();
    static bool Encrypt(const QString& file_name, bool ignore_encryption = false);
    static bool EncryptFiles(const QStringList& files_name,bool ignore_encryption = false);
    static bool TraverseAndEncryptFolder(const QString& folder_name);
    static QString DecodeFile(QString &file_name);
    static QStringList DecodeFiles(const QStringList &files_name);
    static void ClearPlainFiles();
    static QString GetPlainDir();
    static bool ReWritePlainPathFiles();

    static QMap<QString,QString> plain_data;
};

#endif // ADDCOMMON_H
