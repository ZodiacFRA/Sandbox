/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "Window.hpp"
#include "GUIManager.hpp"

namespace babel {
	LoginWindow::LoginWindow(GUIManager &GUIManager, QWidget *parent)
		: QWidget(parent)
		, _GUIManager(GUIManager)
		, _title(new QLabel("BABEL", this))
		, _registerText(new QLabel("Don't have an account?", this))
		, _loginInput(new QLineEdit(this))
		, _passwordInput(new QLineEdit(this))
		, _buttonQuit(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonQuit.png")), "", this))
		, _buttonLogin(new QPushButton("Login", this))
		, _buttonRegister(new QPushButton("Register", this))
	{
		QDesktopWidget dw;
		int x=dw.width()*0.094;
		int y=dw.height()*0.251;

		this->setFixedSize(x, y);
		this->setStyleSheet(COLOR_DARK);
		this->setWindowTitle("Babel Client - Login");

		connect(_buttonLogin, SIGNAL (clicked(bool)), this, SLOT(slotSendLoginRequest(bool)));
		connect(_buttonRegister, SIGNAL (clicked(bool)), this, SLOT(slotSendRegisterRequest(bool)));
		connect(_buttonQuit, SIGNAL (clicked(bool)), QApplication::instance(), SLOT(quit()));

		draw();
	}

	LoginWindow::~LoginWindow()
	{
		delete _title;
		delete _registerText;
		delete _loginInput;
		delete _passwordInput;
		delete _buttonQuit;
		delete _buttonLogin;
		delete _buttonRegister;
	}

	void LoginWindow::draw()
	{
		QFontDatabase::addApplicationFont("./client/rsc/fonts/Arial.ttf");
		QFont fontTitle("Arial", 25);
		QFont fontText("Arial", 15);
		QFont listText("Arial", 13);
		QFont descText("Arial", 10, -1, true);

		_title->setGeometry(12, 9, 105, 31);
		_title->setFont(fontTitle);
		_title->setStyleSheet(COLOR_LIGHT);

		_buttonQuit->setGeometry(133, 9, 38, 38);
		_buttonQuit->setIconSize(QSize(25, 25));
		_buttonQuit->setToolTip("Quit");
		_buttonQuit->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		size_t layoutYShift = 76;

		_loginInput->setGeometry(15, layoutYShift, 150, 35);
		_loginInput->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		_loginInput->setFont(descText);
		_loginInput->setText("Login");

		_passwordInput->setGeometry(15, layoutYShift + 45, 150, 35);
		_passwordInput->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		_passwordInput->setFont(descText);
		_passwordInput->setText("Password");
		_passwordInput->setEchoMode(QLineEdit::Password);

		_buttonLogin->setGeometry(30, layoutYShift + 90, 120, 30);
		_buttonLogin->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_registerText->setGeometry(20, layoutYShift + 125, LOGIN_WIDTH - 30, 15);
		_registerText->setFont(descText);
		_registerText->setStyleSheet(COLOR_LIGHT);

		_buttonRegister->setGeometry(30, layoutYShift + 150, 120, 30);
		_buttonRegister->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");
	}

	void LoginWindow::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);

		auto beige = QColor(55, 65, 64);
		auto pen = QPen(beige, 10, Qt::SolidLine);

		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(pen);
		painter.drawRect(0, 0, LOGIN_WIDTH, LOGIN_HEIGHT);

		QPainterPath path;
		path.addRect(QRectF(0, 51, LOGIN_WIDTH, 5));
		painter.fillPath(path, beige);
		path.addRect(QRectF(0, 61, LOGIN_WIDTH, 5));
		painter.fillPath(path, beige);

		path.addRect(QRectF(125, 0, 5, 52));
		painter.fillPath(path, beige);
	}

	void LoginWindow::slotSendLoginRequest(bool notClicked)
	{
		if (emit connectionStateRequest()) {
			emit loginRequest(_loginInput->text(), _passwordInput->text());
		} else {
			this->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(30, 30, 32); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
			QMessageBox::about(this, "ERROR", QString::fromStdString("Not connected to the server, please check the given IP adress and port"));
			this->setStyleSheet(COLOR_DARK);
		}
	}

	void LoginWindow::slotSendRegisterRequest(bool notClicked)
	{
		emit connectionStateRequest();
		emit registerRequest(_loginInput->text(), _passwordInput->text());
	}

	void LoginWindow::slotAuthentificationDone(uint32_t code)
	{
		this->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(30, 30, 32); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		QMessageBox::about(this, "WELCOME", QString::fromStdString(_GUIManager.getStringFromCode(code)));
		this->setStyleSheet(COLOR_DARK);
		this->hide();
		emit loggedIn();
		_GUIManager.getWindow("MainWindow")->show();
	}

	void LoginWindow::slotAuthentificationFailed(uint32_t code)
	{
		this->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(30, 30, 32); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		QMessageBox::about(this, "ERROR", QString::fromStdString(_GUIManager.getStringFromCode(code)));
		this->setStyleSheet(COLOR_DARK);
	}
}
