/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "Window.hpp"
#include "GUIManager.hpp"

namespace babel {
	MainWindow::MainWindow(GUIManager &GUIManager, QWidget *parent)
		: QWidget(parent)
		, _GUIManager(GUIManager)
		, _title(new QLabel("BABEL", this))
		, _desc(new QLabel("audio chat 1.0", this))
		, _contactText(new QLabel("CONTACTS LIST :", this))
		, _list(new QListWidget(this))
		, _buttonQuit(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonQuit.png")), "", this))
		, _buttonAddContact(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonAddContact.png")), "", this))
		, _buttonRemoveContact(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonRemoveContact.png")), "", this))
		, _buttonCall(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonCall.png")), "", this))
		, _buttonEndCall(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonEndCall.png")), "", this))
		, _buttonSettings(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonSettings.png")), "", this))
		, _confirmationWindow(new ConfirmationWindow(_GUIManager))
	{
		QDesktopWidget dw;
		int x=dw.width()*0.1465;
		int y=dw.height()*0.5;

		this->setFixedSize(x, y);
		this->setStyleSheet(COLOR_DARK);
		this->setWindowTitle("Babel - Client");

		connect(_buttonQuit, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));
		connect(_buttonAddContact, SIGNAL (clicked(bool)), this, SLOT (slotAddContact(bool)));
		connect(_buttonRemoveContact, SIGNAL (clicked(bool)), this, SLOT (slotRemoveContact(bool)));

		connect(_buttonCall, SIGNAL (clicked(bool)), this, SLOT (slotCallContact(bool)));
		connect(_buttonEndCall, SIGNAL (clicked(bool)), this, SLOT (slotEndCall(bool)));

		connect(_confirmationWindow->_buttonYes, SIGNAL (clicked(bool)), this, SLOT(slotRemoveContactDone(bool)));


		draw();
	}

	MainWindow::~MainWindow()
	{
		delete _title;
		delete _desc;
		delete _contactText;
		delete _list;
		delete _buttonQuit;
		delete _buttonAddContact;
		delete _buttonRemoveContact;
		delete _buttonCall;
		delete _buttonEndCall;
		delete _buttonSettings;
		delete _confirmationWindow;
	}

	void MainWindow::draw()
	{
		QFontDatabase::addApplicationFont("./client/rsc/fonts/Arial.ttf");
		QFont fontTitle("Arial", 25);
		QFont fontText("Arial", 15);
		QFont listText("Arial", 13);
		QFont descText("Arial", 10, -1, true);

		_title->setGeometry(15, 9, 200, 31);
		_title->setFont(fontTitle);
		_title->setStyleSheet(COLOR_LIGHT);

		_desc->setGeometry(125, 12, 90, 17);
		_desc->setFont(descText);
		_desc->setStyleSheet(COLOR_LIGHT);

		_contactText->setGeometry(15, 75, 200, 20);
		_contactText->setFont(fontText);
		_contactText->setStyleSheet(COLOR_LIGHT);

		_list->setGeometry(15, 105, 200, HEIGHT - 120);
		_list->setSortingEnabled(true);
		_list->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		for (int i = 0; i < _list->count(); i++)
			_list->item(i)->setFont(listText);

		_buttonQuit->setGeometry(234, 9, 38, 38);
		_buttonQuit->setIconSize(QSize(25, 25));
		_buttonQuit->setToolTip("Quit");
		_buttonQuit->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonAddContact->setGeometry(234, 105, 38, 38);
		_buttonAddContact->setIconSize(QSize(25, 25));
		_buttonAddContact->setToolTip("Add a new contact");
		_buttonAddContact->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonRemoveContact->setGeometry(234, 146, 38, 38);
		_buttonRemoveContact->setIconSize(QSize(25, 25));
		_buttonRemoveContact->setToolTip("Remove selected contact");
		_buttonRemoveContact->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonCall->setGeometry(234, 187, 38, 38);
		_buttonCall->setIconSize(QSize(25, 25));
		_buttonCall->setToolTip("Call selected contact");
		_buttonCall->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonEndCall->setGeometry(234, 228, 38, 38);
		_buttonEndCall->setIconSize(QSize(25, 25));
		_buttonEndCall->setToolTip("End active call");
		_buttonEndCall->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonSettings->setGeometry(234, 269, 38, 38);
		_buttonSettings->setIconSize(QSize(25, 25));
		_buttonSettings->setToolTip("Settings");
		_buttonSettings->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");
	}

	void MainWindow::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);

		auto beige = QColor(55, 65, 64);
		auto pen = QPen(beige, 10, Qt::SolidLine);

		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(pen);
		painter.drawRect(0, 0, WIDTH, HEIGHT);

		QPainterPath path;
		path.addRect(QRectF(0, 51, WIDTH, 5));
		painter.fillPath(path, beige);
		path.addRect(QRectF(0, 61, WIDTH, 5));
		painter.fillPath(path, beige);

		path.addRect(QRectF(225, 0, 5, HEIGHT));
		painter.fillPath(path, beige);
	}

	void MainWindow::slotRemoveContact(bool notClicked)
	{
		if (_list->count() > 0) {
			QString command("Remove contact?\n");
			command.append(_list->currentItem()->text());
			_confirmationWindow->setState(false);
			_confirmationWindow->changeText(command);
			_confirmationWindow->show();
			if (_confirmationWindow->getState())
				emit requestConfirmationForContactDeletion(_list->currentItem()->text());
		}
	}

	void MainWindow::slotRemoveContactDone(bool notClicked)
	{
		_confirmationWindow->hide();
		_list->takeItem(_list->currentRow());
	}

	void MainWindow::slotAddContact(bool notClicked)
	{
		this->_GUIManager.showWindow("AddContactWindow");
	}

	void MainWindow::slotAddContactAccepted(std::string name)
	{
		QFont listText("Arial", 13);
		_list->addItem(QString::fromStdString(name));
		for (int i = 0; i < _list->count(); i++)
			_list->item(i)->setFont(listText);
	}

	void MainWindow::slotAddServerContacts(std::vector<QString> contacts)
	{
		QFont listText("Arial", 13);
		for (size_t i = 0; i < contacts.size(); i++)
			_list->addItem(contacts[i]);
		for (int i = 0; i < _list->count(); i++)
			_list->item(i)->setFont(listText);
		std::cout << COLOR_GREEN << "---> Contact list added!" << COLOR_RESET << std::endl;
	}

	void MainWindow::slotCallContact(bool notClicked)
	{
		if (_list->count() > 0)
			emit callRequest(_list->currentItem()->text());
	}

	void MainWindow::slotEndCall(bool notClicked)
	{
		emit endCallRequest();
	}

	void MainWindow::slotCallFailed(uint32_t code)
	{
		this->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(30, 30, 32); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		QMessageBox::about(this, "ERROR", QString::fromStdString(_GUIManager.getStringFromCode(code)));
		this->setStyleSheet(COLOR_DARK);
	}

	void MainWindow::slotIncomingCall(std::string contact)
	{
		QString command("Incoming call from:\n");
		command.append(QString::fromStdString(contact));
		_confirmationWindow->setState(false);
		_confirmationWindow->changeText(command);
		_confirmationWindow->show();
		if (_confirmationWindow->getState())
			emit callConfirmation();
		else
			emit callRefused();
	}
}
