/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Boost Network Manager implementation
*/

#include "NetworkMgr.hpp"
#include "CmdHandler.hpp"

namespace Babel {

	NetworkMgr::NetworkMgr(unsigned short port, CmdHandler &handler)
	: _ioc(),
	_signals(_ioc),
	_acceptor(_ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	_conMgr(),
	_comHandler(handler)
	{
		_signals.add(SIGINT);
		_signals.add(SIGTERM);

#if defined(SIGQUIT)
		_signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

		await_signals();

		accept();
	}

	NetworkMgr::~NetworkMgr()
	{}

	void NetworkMgr::run()
	{
		_ioc.run();
	}

	void NetworkMgr::accept()
	{
		auto new_conn = TCPConnection::create(_acceptor.get_executor().context(),
			_conMgr, _comHandler);

		_acceptor.async_accept(new_conn->socket(),
			boost::bind(&NetworkMgr::handle_accept, this, new_conn,
			boost::asio::placeholders::error));
	}

	void NetworkMgr::handle_accept(TCPConnection::ptr new_conn,
			const boost::system::error_code &err)
	{
		if(!_acceptor.is_open()){
			return;
		}

		if(!err) {
			std::cout << "Received connection from " <<
			new_conn->socket().remote_endpoint().address() << std::endl;
			_conMgr.start(new_conn);
		}

		accept();
	}

	void NetworkMgr::await_signals()
	{
		_signals.async_wait(
		[this](boost::system::error_code err, int sig){
			std::cout << "Server received Signal" << std::endl;
			_acceptor.close();
			_conMgr.stop_all();
		});
	}

} /* Babel */
