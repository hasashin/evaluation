#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <memory>
#include "main/Misc.h"

struct SDL_Surface;
/** SDL graphics class
*/
class Graphics
{
public:
	Graphics();
	~Graphics();
	/** flips buffers
	*/
	void update();
	/** return screen pointer
	*/
	SDL_Surface* getScreen();
	/** coordinate transformers ;D
	*/
	double transformXToViewCoordinate(double x);
	double transformYToViewCoordinate(double y);
	double transformXToWorldCoordinate(double x);
	double transformYToWorldCoordinate(double y);
	/**zoom in/out
	*/
	void zoom(double value) {
		ooPoint->val[2] += value;
	}
	/**move world view up/down
	*/
	void moveHorizontal(double value) {
		ooPoint->val[0] += value;
	}
	/**move world view left/right
	*/
	void moveVertical(double value) {
		ooPoint->val[1] += value;
	}
	/**reset world view
	*/
	void setOOPoint(double x = 0, double y = 0, double scale = 10) {
		ooPoint->val[0] = x;
		ooPoint->val[1] = y;
		ooPoint->val[2] = scale;
	}
	/**gets zoom factor
	*/
	double getZoomFactor() {
		return ooPoint->val[2];
	}
	/** window height
	*/
	int getHeight() {
		return height;
	}
	/** window width
	*/
	int getWidth() {
		return width;
	}
private:
	SDL_Surface* screen;
	std::unique_ptr<Vector4d> ooPoint;
	int height;
	int width;
};

#endif //GRAPHICS_H