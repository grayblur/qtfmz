#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>
#include <mutex>

#include <functional>

using namespace std;
using Cb = std::function<void()>;

namespace Ui{
	class LoginFormUi;
}

class Login : public QMainWindow
{
	Q_OBJECT

public:
    Login(Cb cb, QWidget *parent = Q_NULLPTR);
	~Login();

signals:
//	void SignalDealLogin(const ApiResult& api_result);
	void SignalLoginSuccess();

protected:
	void keyPressEvent(QKeyEvent *ev) override;

private slots:
	void SLotBtnLoginClicked();
//	void SlotDealLogin(ApiResult api_result);

private:
	void OnModifyUi();
	void RegisterSignals();
    void PostLoginRequest(const std::string &account, const std::string &pwd, QString &pin);
	void SetLogining(bool b_login);
	void SetBackground();
    bool CheckUkey(QString pin_code,QString& error_msg);
	

private:
	Ui::LoginFormUi *ui;
	std::mutex mutex_;
	bool b_login_;
    Cb cb_;
};
