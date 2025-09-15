#ifndef MESSAGES_H
#define MESSAGES_H
#include <string>

class Messages {
public:
	Messages();
	std::string PROMPT_FOR_NAME;
	std::string PROMPT_FOR_PAYMENT;
	std::string ERROR_INVALID_INPUT;
	std::string MSG_START_GAME;
	std::string MSG_ANY_KEY_TO_CONT;
	std::string MSG_NOT_ENOUGH_CREDITS;
	std::string MSG_THANKS_FOR_PLAYING;
	std::string MSG_BALANCE;
};

#endif
