/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "Window.hpp"
#include "GUIManager.hpp"

namespace babel {
	ConfirmationWindow::ConfirmationWindow(GUIManager &GUIManager, QWidget *parent)
		: QDialog(parent)
		, _GUIManager(GUIManager)
		, _title(new QLabel("BABEL", this))
		, _text(new QLabel("e.g: Remove contact?", this))
		, _buttonQuit(new QPushButton(QIcon(QPixmap("./client/rsc/icons/buttonQuit.png")), "", this))
		, _buttonYes(new QPushButton("Yes", this))
		, _buttonNo(new QPushButton("No", this))
		, _state(false)
	{
		QDesktopWidget dw;
		int x=dw.width()*0.094;
		int y=dw.height()*0.195;

		this->setFixedSize(x, y);
		this->setStyleSheet(COLOR_DARK);
		this->setWindowTitle("Babel Client");
		this->setWindowModality(Qt::ApplicationModal);

		connect(_buttonQuit, SIGNAL (clicked(bool)), this, SLOT(slotCancel(bool)));
		connect(_buttonNo, SIGNAL (clicked(bool)), this, SLOT(slotCancel(bool)));

		draw();
	}

	ConfirmationWindow::~ConfirmationWindow()
	{
		delete _title;
		delete _text;
		delete _buttonQuit;
		delete _buttonYes;
		delete _buttonNo;
	}

	void ConfirmationWindow::draw()
	{
		QFontDatabase::addApplicationFont("./client/rsc/fonts/Arial.ttf");
		QFont fontTitle("Arial", 25);
		QFont fontText("Arial", 15);
		QFont listText("Arial", 13);
		QFont descText("Arial", 12, -1, true);

		_title->setGeometry(12, 9, 105, 31);
		_title->setFont(fontTitle);
		_title->setStyleSheet(COLOR_LIGHT);


		_buttonQuit->setGeometry(133, 9, 38, 38);
		_buttonQuit->setIconSize(QSize(25, 25));
		_buttonQuit->setToolTip("Quit");
		_buttonQuit->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		size_t layoutYShift = 66;

		_text->setGeometry(12, layoutYShift, LOGIN_WIDTH - 24, 45);
		_text->setAlignment(Qt::AlignCenter);
		_text->setFont(descText);
		_text->setStyleSheet(COLOR_LIGHT);

		_buttonYes->setGeometry(30, layoutYShift + 60, 120, 30);
		_buttonYes->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");

		_buttonNo->setGeometry(30, layoutYShift + 100, 120, 30);
		_buttonNo->setStyleSheet("color: rgb(217, 203, 158); background-color: rgb(42, 44, 43)");
	}

	void ConfirmationWindow::paintEvent(QPaintEvent *)
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

	void ConfirmationWindow::slotAccept(bool notClicked)
	{
		std::cout << SEPARATOR << "\nACCEPT" << SEPARATOR << std::endl;
		_state = true;
		this->hide();
	}

	void ConfirmationWindow::slotCancel(bool notClicked)
	{
		_state = false;
		this->hide();
	}

	void ConfirmationWindow::changeText(QString text)
	{
		_text->setText(text);
	}

	bool ConfirmationWindow::getState()
	{
		return _state;
	}

	void ConfirmationWindow::setState(bool state)
	{
		_state = state;
	}
}
