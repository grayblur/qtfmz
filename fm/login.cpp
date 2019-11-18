#include "login.h"
#include "ui_login.h"
#include <iostream>
#include "qevent.h"
#include <QMessageBox>
#include "QDir"
#include <QSettings>
#include "common.h"
#include "addcommon.h"

#include "fm_def.h"
#include "fm_sic_pub.h"
#include "fm_sic_cmd_def.h"

Login::Login(Cb cb, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::LoginFormUi),
    b_login_(false),
    cb_(cb)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("Zb Security File"));
    OnModifyUi();
}

Login::~Login()
{
    if (ui != nullptr)
        delete ui;
}

void Login::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        SLotBtnLoginClicked();
    }
    QMainWindow::keyPressEvent(e);
}

void Login::SLotBtnLoginClicked()
{
    if (b_login_)
    {
        return;
    }

    /*bool b_card_verification = LoginManager::GetInstance()->IfTFCardVerificationSuccess(ui->le_pin->text().toStdString());
    if (false != b_card_verification)
    {
        return;
    }*/

    //bool b_card_verification = LoginManager::GetInstance()->IfUKeyVerificationSuccess(ui->le_pin->text().toStdString());
    //if (false == b_card_verification)
    //{
    //	return;
    //}



    SetLogining(true);
    std::string account = ui->le_account->text().toStdString();
    std::string pwd = ui->le_pswd->text().toStdString();
    QString pin = ui->le_pin->text();

    if (ui->chbox_remenber_pwd->isChecked() && (account != "" && pwd != ""))
    {
//        LoginCookie::GetInstance()->Update(account, pwd);
    }
    else if (!ui->chbox_remenber_pwd->isChecked())
    {
//        LoginCookie::GetInstance()->Update("", "");
    }
    PostLoginRequest(account, pwd,pin);
}

//void Login::SlotDealLogin( ApiResult api_result)
//{
//    if (api_result.Success())
//    {
//        std::cout << "HTTP request succeed!" << std::endl;
//        ApiSetting::api_token_ = api_result.GetDataString("token");
//        ApiSetting::user_id_ = api_result.GetDataInt("userid");
//        emit SignalLoginSuccess();
//    }
//    else
//    {
//        std::wstring wmsg;

//        std::string smsg = api_result.GetMsg();

//        commontool::MBCSToUnicode(smsg, wmsg);
//        //std::wstring msg = nbase::UTF8ToUTF16(smsg);
//        QMessageBox::warning(this, QString::fromLocal8Bit("wrong password"), QString::fromStdWString(wmsg));
//    }
//    SetLogining(false);
//}

void Login::OnModifyUi()
{
    this->setFixedSize(470, 315);
    SetBackground();
//    ui->le_mac_addr->hide();
//    ui->label_5->hide();
//    ui->label_4->hide();
//    ui->le_pin->hide();


    ui->btn_login->setCursor(Qt::PointingHandCursor);
    ui->le_pswd->setEchoMode(QLineEdit::Password);
    ui->le_pin->setEchoMode(QLineEdit::Password);

    ui->le_account->setFixedWidth(200);
//    ui->le_mac_addr->setFixedWidth(200);
//    ui->le_mac_addr->hide();
    ui->le_pswd->setFixedWidth(200);
    ui->le_pin->setFixedWidth(200);
    ui->btn_login->setFixedHeight(20);

    ui->chbox_remenber_pwd->hide();

    RegisterSignals();


//    LoginCookie::GetInstance()->Init();
    std::string account = "";
    std::string pwd = "";
//    LoginCookie::GetInstance()->Read(account, pwd);

    if (account != "")
    {
        ui->chbox_remenber_pwd->setChecked(true);
        ui->le_account->setText(QString::fromStdString(account));
        ui->le_pswd->setText(QString::fromStdString(pwd));
    }

    std::string mac_addr;
//    bool b_ok = commontool::GetMacAddress(mac_addr);
    bool b_ok = false;
    if (b_ok)
    {
//        ui->le_mac_addr->setReadOnly(true);
//        ui->le_mac_addr->setText(QString::fromStdString(mac_addr));
    }
    else
    {
//        ui->le_mac_addr->setReadOnly(false);
//        ui->le_mac_addr->setPlaceholderText(QString::fromLocal8Bit("mac errorַ"));
    }
}

void Login::RegisterSignals()
{
    connect(ui->btn_login, SIGNAL(clicked()), this, SLOT(SLotBtnLoginClicked()));
//    connect(this, &Login::SignalDealLogin, this, &Login::SlotDealLogin);
}

void Login::PostLoginRequest(const std::string &account, const std::string &pwd, QString &pin)
{
    QSettings settings(Common::configFile(), QSettings::IniFormat);

    bool b_success = false;
    QString error_string;

    do{
        if(settings.value(ACCOUNT).toString().isEmpty() ||  account != settings.value(ACCOUNT).toString().toStdString())
        {
            error_string = "wrong account";
            break;
        }

        if(settings.value(PSWD).toString().isEmpty() || pwd != settings.value(PSWD).toString().toStdString())
        {
            error_string = "wrong password";
            break;
        }

        if(!CheckUkey(pin,error_string))
        {
            break;
        }

        b_success = true;
    }
    while(false);

    if(b_success)
    {
        if(cb_)
        {
            cb_();
            this->hide();
        }
    }
    else
    {
         QMessageBox::warning(this, QString("wrong!! "),  error_string);
         SetLogining(false);
    }


//    auto cb = [this](ApiResult api_result){
//        emit SignalDealLogin(api_result);
//    };

//    SS_MAP param;
//    param["username"] = account;
//    param["password"] = pwd;
//    param["macAddr"] = ui->le_mac_addr->text().toStdString();

//    ApiCaller().AsyncCallPost(API_LOGIN, param, cb);

}

void Login::SetLogining(bool b_login)
{
    b_login_ = b_login;
    ui->btn_login->setEnabled(!b_login_);
    ui->le_account->setEnabled(!b_login_);
    ui->le_pswd->setEnabled(!b_login_);
    ui->chbox_remenber_pwd->setEnabled(!b_login_);
}

void Login::SetBackground()
{
    QString dir = QApplication::applicationDirPath();
    QDir::setCurrent(dir);
    QPixmap *pixmap = new QPixmap("./res/images/login_bg.png");
    ui->lb_bg->setFixedHeight(160);
    pixmap->scaled(ui->lb_bg->size(), Qt::KeepAspectRatio);
    ui->lb_bg->setScaledContents(true);
    ui->lb_bg->setPixmap(*pixmap);
}

void PrintErro(FM_U32 u32Error)
{
    FM_U32 u32Len = 128;
    FM_S8 as8Info[128] = {0};
    printf("?????0x%08x\n", u32Error);
    FM_SIC_GetErrInfo(FM_LAN_EN, u32Error, &u32Len, as8Info);
    as8Info[u32Len] = 0;
    printf("%s\n", as8Info);
}

bool Login::CheckUkey(QString pin,QString& error_msg)
{
    FM_U32 u32Error;
    FM_U8 u8Index = 0;
    FM_HANDLE g_hDev = (FM_HANDLE)-1;

    bool b_success = true;

    u32Error = FM_SIC_OpenDevice(&u8Index, 0, (FM_OPEN_MULTITHREAD|FM_OPEN_MULTIPROCESS), &g_hDev);

    if(u32Error != FME_OK)
    {
        error_msg = "open device failed!\n";
        b_success = false;
    }
    else
    {
        FM_U8 au8Buf[30] = {0};
        FM_U32 u32Retry = 0;
        FM_U32 u32PinLen = 0;

        memcpy(au8Buf,pin.toStdString().data(),8);
        u32PinLen = strlen(reinterpret_cast<const char*>(au8Buf));
        u32Error = FM_SIC_USER_Login(g_hDev, FM_PIN_OPER, au8Buf, u32PinLen, 0, &u32Retry);

        if (FME_OK != u32Error)
        {
            error_msg = "ukey logining failed!\n";
            b_success = false;
        }

        //????
        u32Error = FM_SIC_CloseDevice(g_hDev);

//        if (FME_OK != u32Error)
//        {
//            error_msg = "close device failed!\n";
//            b_success = false;
//        }
    }

    return b_success;
}
