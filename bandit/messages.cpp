#include "messages.h"

Messages::Messages()
	: PROMPT_FOR_NAME{ "Spielernamen eingeben!\n" }
	, PROMPT_FOR_PAYMENT{ "Ihr Guthaben betraegt 0.  Wieviele Dollar moechten"
		" Sie einwerfen ?\n" }
	, ERROR_INVALID_INPUT{ "Ungueltige Eingabe!\n" }
	, MSG_START_GAME{ "Sie duerfen '20 Drehs' spielen!  Ihr 'Highscore' nach dem"
		" letzten Dreh wird gespeichert!  Los gehts!\n" }
	, MSG_ANY_KEY_TO_CONT{"Druecke die Enter-Taste, um fortzufahren!"}
	, MSG_NOT_ENOUGH_CREDITS{"Sorry, nicht genug Guthaben :(\n"}
	, MSG_THANKS_FOR_PLAYING{"Thank you for playing!\n"}
	, MSG_BALANCE{"Guthaben:\n"}
{}