/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#define WIDTH 281
#define HEIGHT 540
#define LOGIN_WIDTH 180
#define LOGIN_HEIGHT 271
#define ADD_CONTACT_HEIGHT 210

#define COLOR_DARK "background-color: rgb(30, 30, 32)"
#define COLOR_LIGHT "color: rgb(217, 203, 158)"

#include "common.hpp"

#include <QApplication>
#include <QPushButton>
#include <QDesktopWidget>
#include <QLabel>
#include <QListWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QFontDatabase>
#include <QDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QMainWindow>

namespace babel {
	class GUIManager;

	class LoginWindow : public QWidget {
		Q_OBJECT
	public:
		explicit LoginWindow(GUIManager &GUIManager, QWidget *parent = nullptr);
		~LoginWindow();

	signals:
		void registerRequest(QString name, QString password);
		void loginRequest(QString name, QString password);
		bool connectionStateRequest();
		void loggedIn();

	private slots:
		void slotSendLoginRequest(bool notClicked);
		void slotSendRegisterRequest(bool notClicked);
		void slotAuthentificationDone(uint32_t code);
		void slotAuthentificationFailed(uint32_t code);

	private:
		void paintEvent(QPaintEvent *) override;
		void draw();

		GUIManager &_GUIManager;

		QLabel *_title = nullptr;
		QLabel *_registerText = nullptr;
		QLineEdit *_loginInput = nullptr;
		QLineEdit *_passwordInput = nullptr;
		QPushButton *_buttonQuit = nullptr;
		QPushButton *_buttonLogin = nullptr;
		QPushButton *_buttonRegister = nullptr;
	};

	class AddContactWindow : public QDialog {
		Q_OBJECT
	public:
		explicit AddContactWindow(GUIManager &GUIManager, QWidget *parent = nullptr);
		~AddContactWindow();
	signals:
		void addContactRequest(QString);

	private slots:
		void slotCloseAddContactWindow(bool notClicked);
		void slotSendAddContactInfos(bool notClicked);

	private:
		void paintEvent(QPaintEvent *) override;
		void draw();

		GUIManager &_GUIManager;

		QLabel *_title = nullptr;
		QLineEdit *_friendInput = nullptr;
		QPushButton *_buttonQuit = nullptr;
		QPushButton *_buttonAdd = nullptr;
		QPushButton *_buttonCancel = nullptr;
	};

	class ConfirmationWindow : public QDialog {
		Q_OBJECT
	public:
		explicit ConfirmationWindow(GUIManager &GUIManager, QWidget *parent = nullptr);
		~ConfirmationWindow();
		void changeText(QString text);
		bool getState();
		void setState(bool state);

		QPushButton *_buttonYes = nullptr;

	private slots:
		void slotAccept(bool notClicked);
		void slotCancel(bool notClicked);

	private:
		void paintEvent(QPaintEvent *) override;
		void draw();

		GUIManager &_GUIManager;

		QLabel *_title = nullptr;
		QLabel *_text = nullptr;
		QPushButton *_buttonQuit = nullptr;
		QPushButton *_buttonNo = nullptr;
		bool _state;
	};

	class MainWindow : public QWidget {
		Q_OBJECT
	public:
		explicit MainWindow(GUIManager &GUIManager, QWidget *parent = nullptr);
		~MainWindow();
	signals:
		void changeConfirmationWindowText(QString text);
		void callRequest(QString text);
		void endCallRequest();
		void requestConfirmationForContactDeletion(QString);
		void callConfirmation();
		void callRefused();

	private slots:
		void slotAddContact(bool notClicked);
		void slotRemoveContact(bool notClicked);
		void slotRemoveContactDone(bool notClicked);
		void slotAddServerContacts(std::vector<QString> contacts);
		void slotCallContact(bool notClicked);
		void slotEndCall(bool notClicked);
		void slotCallFailed(uint32_t code);
		void slotIncomingCall(std::string contact);
		void slotAddContactAccepted(std::string);

	private:
		void paintEvent(QPaintEvent *) override;
		void draw();

		GUIManager &_GUIManager;

		QLabel *_title = nullptr;
		QLabel *_desc = nullptr;
		QLabel *_contactText = nullptr;
		QListWidget *_list = nullptr;
		QPushButton *_buttonQuit = nullptr;
		QPushButton *_buttonAddContact = nullptr;
		QPushButton *_buttonRemoveContact = nullptr;
		QPushButton *_buttonCall = nullptr;
		QPushButton *_buttonEndCall = nullptr;
		QPushButton *_buttonSettings = nullptr;
		ConfirmationWindow *_confirmationWindow = nullptr;
	};
}

#endif /* end of include guard: GUI_MANAGER_HPP */
