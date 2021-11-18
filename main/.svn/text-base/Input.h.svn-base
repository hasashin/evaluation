#ifndef INPUT_H
#define INPUT_H
#include "Misc.h"

class UserInterface;
/** process SDL events and dispathes input to user interface
*/
class Input
{
public:
	bool update();
	void setUserInterface(UserInterface * ui) {
		this->ui = ui;
	}
private:
	UserInterface * ui;
	Vector4d mouse;
};

#endif //INPUT_H