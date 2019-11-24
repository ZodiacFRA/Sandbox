/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "Window.hpp"
#include "GUIManager.hpp"

namespace babel {
	AddContactWindow::AddContactWindow(GUIManager &GUIManager, QWidget *parent)
		: QDialog(parent)
		, _GUIManager(GUIManager)
		, _title(new QLabel("BABEL", this))
		, _friendInput(new QLineEdit(this))
		, _buttonQuit(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonQuit.png")), "", this))
		, _buttonAdd(new QPushButton("Add", this))
		, _buttonCancel(new QPushButton("Cancel", this))
	{
		QDesktopWidget dw;
		int x=dw.width()*0.094;
		int y=dw.height()*0.195;

		this->setFixedSize(x, y);
		this->setStyleSheet(COLOR_DARK);
		this->setWindowTitle("Babel Client - Add contact");
		this->setWindowModality(Qt::ApplicationModal);

		connect(_buttonCancel, SIGNAL (clicked(bool)), this, SLOT(slotCloseAddContactWindow(bool)));
		connect(_buttonQuit, SIGNAL (clicked(bool)), this, SLOT(slotCloseAddContactWindow(bool)));
		connect(_buttonAdd, SIGNAL (clicked(bool)), this, SLOT(slotSendAddContactInfos(bool)));

		draw();
	}

	AddContactWindow::~AddContactWindow()
	{
		delete _title;
		delete _friendInput;
		delete _buttonQuit;
		delete _buttonAdd;
		delete _buttonCancel;
	}

	void AddContactWindow::draw()
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

		_friendInput->setGeometry(15, layoutYShift, 150, 35);
		_friendInput->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43); selection-color: rgb(42, 44, 43); selection-background-color: rgb(217, 203, 158)");
		_friendInput->setFont(descText);
		_friendInput->setText("  Friend's username");

		_buttonAdd->setGeometry(30, layoutYShift + 45, 120, 30);
		_buttonAdd->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonCancel->setGeometry(30, layoutYShift + 85, 120, 30);
		_buttonCancel->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");
	}

	void AddContactWindow::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);

		auto beige = QColor(55, 65, 64);
		auto pen = QPen(beige, 10, Qt::SolidLine);

		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(pen);
		painter.drawRect(0, 0, LOGIN_WIDTH, ADD_CONTACT_HEIGHT);

		QPainterPath path;
		path.addRect(QRectF(0, 51, LOGIN_WIDTH, 5));
		painter.fillPath(path, beige);
		path.addRect(QRectF(0, 61, LOGIN_WIDTH, 5));
		painter.fillPath(path, beige);

		path.addRect(QRectF(125, 0, 5, 52));
		painter.fillPath(path, beige);
	}

	void AddContactWindow::slotCloseAddContactWindow(bool notClicked)
	{
		this->hide();
	}

	void AddContactWindow::slotSendAddContactInfos(bool notClicked)
	{
		emit addContactRequest(_friendInput->text());
		this->hide();
	}
}
