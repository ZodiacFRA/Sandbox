/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Replies
*/

#include <cstdint>

namespace Babel {
	namespace client {
		enum class codes: uint32_t {
			REGISTER = 10,
			LOGIN = 11,
			ADD_CONTACT = 21,
			DEL_CONTACT = 22,
			GET_CONTACTS = 23,
			INVITE_CALL = 30,
			ACCEPT_CALL = 31,
			HANGUP_CALL = 32,
			REJECT_CALL = 33,
			DISCONNECT = 42
		};
	} /* client */
	namespace reply {
		enum class codes : uint32_t {
			SUCCESS_CMD = 200,
			SUCCESS_REGISTER = 210,
			SUCCESS_LOGIN = 211,
			SUCCESS_ADD = 220,
			SUCCESS_DEL = 221,
			SUCCESS_CONTACTS = 222,
			ACCEPTED = 230,
			SUCCESS_CALL = 231,
			CALL_ENDED = 232,
			SUCCESS_REJECT = 233,
			PENDING_CONTACTS = 330,
			BAD_COMMAND = 400,
			USERNAME_USED = 410,
			INVALID_CREDENTIALS = 411,
			UNKNOWN_USER = 420,
			ALREADY_IN_CONTATCS = 421,
			NOT_IN_CONTACT_LIST = 422,
			CANT_ADD_YOURSELF = 423,
			REJECTED = 430,
			USER_ALREADY_IN_CALL = 431,
			USER_NOT_CONNECTED = 432,
			ALREADY_IN_CALL = 450,
			NOT_INVITED = 451,
			NOT_IN_CALL = 452,
			NOT_LOGGED_IN = 460,
			ALREADY_LOGGED_IN = 461,
			ALREADY_CONNECTED = 462,
			INTERNAL_ERROR = 500,
			INVITE_CALL = 700,
			LEAVE_CALL = 701
		};
	} /* reply */
} /* Babel */
