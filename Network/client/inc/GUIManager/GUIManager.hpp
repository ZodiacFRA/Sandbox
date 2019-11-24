/*
** EPITECH PROJET, 2018
** @Project: Pool
** filename
** description
*/

#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include "common.hpp"
#include "Window.hpp"
#include <map>

namespace babel {
	class ClientManager;

	class GUIManager : public QObject {
		Q_OBJECT
	public:
		GUIManager(ClientManager &root, QObject *parent);
		~GUIManager();
		int start();
		ClientManager &getRoot();
		std::string &getStringFromCode(uint32_t code);

		int showWindow(std::string const& windowName);
		int hideWindow(std::string const& windowName);
		QWidget *getWindow(std::string const& windowName);
	private:
		ClientManager &_parent;

		std::unordered_map<std::string, QWidget*> _windowList;
		std::map<uint32_t, std::string> _codeToStringProtocol;
	};
}

#endif /* end of include guard: GUI_MANAGER_HPP */
