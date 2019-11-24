/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#include "GUIManager.hpp"
#include "ClientManager.hpp"

namespace babel {
	GUIManager::GUIManager(ClientManager &root, QObject *parent)
		: QObject(parent)
		, _parent(root)
		, _windowList({
			{"LoginWindow", new LoginWindow(*this)},
			{"AddContactWindow", new AddContactWindow(*this)},
			{"MainWindow", new MainWindow(*this)}
		})
		, _codeToStringProtocol({
			//SUCCESS
			{200, "Something worked, but what???"},
			//auth success
			{210, "Hello new user, hope you'll like it! Add your friends to begin the chat"},
			{211, "Welcome back dude!"},
			//contacts success
			{220, "Contact added!"},
			{221, "Contact deleted!"},
			{222, "Got contact list!"},
			//call success
			{230, "Your call has been accepted!"},
			{231, "Your call validation has been received!"},
			{232, "Call successfully ended!"},

			//{310, "Pending contact list!"},

			//ERRORS
			{500, "Ach... Internal server error, someone's gonna get fired!"},
			{400, "Something failed, but what???"},
			//auth error
			{410, "Username is already used! choose another one"},
			{411, "Invalid credentials"},
			//contacts error
			{420, "Unknown user"},
			{421, "This user is already in your contacts"},
			{422, "This user is not in your contacts"},
			//call error
			{430, "Your contact refused the call"},
			{431, "Your contact is already in a call, try again later!"},
			{432, "Your contact is not connected, try again later!"},

			{450, "You already are in a call, this should not have happened!"},
			{451, "You are not invited to any call, this should not have happened!"},
			{452, "You are not in a call, this should not have happened!"},
			//connection error
			{460, "You are not logged in"},
			{461, "You are already logged in"},
			{462, "You are already connected"},

			{700, "Incoming Call"},
			{701, "Contact is closing the call..."}
		})
	{}

	GUIManager::~GUIManager()
	{
		delete _windowList["LoginWindow"];
		delete _windowList["MainWindow"];
		delete _windowList["AddContactWindow"];
	}

	int GUIManager::start()
	{
		return showWindow("LoginWindow");
	}

	int GUIManager::showWindow(std::string const& windowName)
	{
		if (!_windowList[windowName])
			return (FAILURE);
		_windowList[windowName]->show();
		return SUCCESS;
	}

	int GUIManager::hideWindow(std::string const& windowName)
	{
		if (!_windowList[windowName])
			return (FAILURE);
		_windowList[windowName]->hide();
		return (SUCCESS);
	}

	QWidget *GUIManager::getWindow(std::string const& windowName)
	{
		return _windowList[windowName];
	}

	std::string &GUIManager::getStringFromCode(uint32_t code)
	{
		return _codeToStringProtocol[code];
	}
}
