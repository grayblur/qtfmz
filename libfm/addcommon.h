#ifndef ADDCOMMON_H
#define ADDCOMMON_H

#include <QString>
#include <QMap>
#define ACCOUNT "account"
#define ACCOUNT_VALUE "zbkj"
#define PSWD_VALUE "123456"
#define PSWD	"pswd"

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
    static void RemovePlainFileByEncryptFilePath(const QString& path);
    static void ConfigureAcountPaswd();

    static QMap<QString,QString> plain_data_;
    static QMap<QString,QString> data_plain_;
};

#endif // ADDCOMMON_H
