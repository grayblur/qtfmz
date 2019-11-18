#include "addcommon.h"
#include <QSettings>
#include "common.h"
#include <QDir>
#include "SFDll_fm.h"
#include <QDir>

#define OPENPATH "openPath"
#define PLAIN_PATH "plainFile"

QMap<QString,QString> AddCommon::plain_data;

AddCommon::AddCommon()
{

}

bool AddCommon::ConfigureFirstPath()
{
    QSettings settings(Common::configFile(), QSettings::IniFormat);
    if(settings.value(OPENPATH).toString().isEmpty())
    {
        settings.setValue("openPath","/home/zle/Test");
    }
    else
    {
    }
}

QString AddCommon::GetOpenPath()
{
    QSettings settings(Common::configFile(), QSettings::IniFormat);
    return settings.value(OPENPATH).toString();
}

bool AddCommon::Encrypt(const QString& file_name, bool ignore_encryption)
{
    QString path = file_name;

    SToken ptoken;
    memset(ptoken.exCert, 0, 128);
    memset(ptoken.signCert, 0, 128);
    memcpy(ptoken.exCert, "administrator", 13);
    memcpy(ptoken.signCert, "administrator", 13);

    if(ignore_encryption)
    {
        if (IsEncrypted(file_name.toStdString().data()))
        {
            return true;
        }
    }
    int ret = SUCCESS;


    ret = Server_Create(&ptoken, file_name.toStdString().data(), file_name.toStdString().data());
    if (ret != SUCCESS) {
        printf("%x", ret);
        return false;
    }

    return true;
}

bool AddCommon::EncryptFiles(const QStringList &files_name, bool ignore_encryption)
{
    foreach(QString file_name,files_name)
        Encrypt(file_name,ignore_encryption);
}

bool AddCommon::TraverseAndEncryptFolder(const QString& folder_name)
{
    QDir dir(folder_name);
    QFileInfoList all = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

    foreach(QFileInfo one, all)
    {
        if(one.isDir())
        {
            TraverseAndEncryptFolder(one.filePath());
        }
        else
        {
            Encrypt(one.absoluteFilePath(),true);
        }
    }

    return true;
}

QString AddCommon::DecodeFile(QString &file_name)
{
    SToken ptoken;
    memset(ptoken.exCert, 0, 128);
    memset(ptoken.signCert, 0, 128);
    memcpy(ptoken.exCert, "administrator", 13);
    memcpy(ptoken.signCert, "administrator", 13);

    int ret = SUCCESS;

    QString temp_dir = GetPlainDir();

    if(temp_dir.isEmpty())
        return QString();


    QString file_plain_name(file_name.mid(GetOpenPath().length()+1));

    file_plain_name.replace("/","_");


    QString plain_path = temp_dir + "/" + file_plain_name;


    if(!QFile::exists(plain_path))
    {
        ret = Server_InternalRead(&ptoken, file_name.toStdString().data(), plain_path.toStdString().data());

        if (ret != SUCCESS) {
            printf("%x", ret);
            return QString();
        }

    }
    plain_data[plain_path] = file_name;

    file_name = plain_path;
    return plain_path;
}

QStringList AddCommon::DecodeFiles(const QStringList &files_name)
{
    QStringList list;
    foreach(QString file_name,files_name)
    {
        list << DecodeFile(file_name);
    }

    return list;
}

QString AddCommon::GetPlainDir()
{
    QString temp_dir = Common::configDir() + "/" + PLAIN_PATH;
    if(!QFile::exists(temp_dir))
    {
        QDir makedir(temp_dir);
        if (!makedir.mkpath(temp_dir)) { temp_dir.clear();
        }
    }
    if(temp_dir.isEmpty())
        return QString();
    return temp_dir;
}
//xie hui qian que ren fumulu cunzai
bool AddCommon::ReWritePlainPathFiles()
{
    QString plain_path = GetPlainDir();
    if(!plain_path.isEmpty())
    {
        QDir dir(plain_path);
        dir.setFilter(QDir::Files);
        int fileCount = dir.count();
        for (int i = 0; i < fileCount; i++)
        {
            QString file_name = dir[i];
            auto origin_file = plain_data.find(plain_path + "/" + file_name);
            if(origin_file != plain_data.end())
            {
                QString origin_file_name = origin_file.value();


                if(QFile::exists(origin_file_name))
                {

                    SToken ptoken;
                    memset(ptoken.exCert, 0, 128);
                    memset(ptoken.signCert, 0, 128);
                    memcpy(ptoken.exCert, "administrator", 13);
                    memcpy(ptoken.signCert, "administrator", 13);

                    int ret = SUCCESS;

                    ret = Server_Create(&ptoken, origin_file.key().toStdString().data(), origin_file_name.toStdString().data());
                    if (ret != SUCCESS) {
                        printf("%x", ret);
                        return false;
                    }

                }
            }

            dir.remove(dir[i]);
        }
    }
    return false;
}

void AddCommon::ClearPlainFiles()
{
    ReWritePlainPathFiles();
    QString temp_dir = GetPlainDir();
    if(!temp_dir.isEmpty())
    {
        QDir dir(temp_dir);
        dir.setFilter(QDir::Files);
        int fileCount = dir.count();
        for (int i = 0; i < fileCount; i++)
        {
            QString string = dir[i];
            dir.remove(dir[i]);
        }
    }
}
