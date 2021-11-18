#ifndef RESOURCE_INFO_H
#define RESOURCE_INFO_H
#include <string>

struct Color
{
	unsigned short r;
	unsigned short g;
	unsigned short b;
};

struct Rectangle
{
	int x;
	int y;
	int w;
	int h;

	Rectangle() 
	{
		x = -1;
		y = -1;
		w = -1;
		h = -1;
	}
};

class ResourceException {
public:
	ResourceException(const char * pTxt) : pReason(pTxt) {};
	const char * pReason;
};
/** it is a class describing images set with common parameters which differ only by frame number
*/
class ResourceInfo
{
public:
	std::string getFilename(int frame_number);
	std::string getResourceName();
	Color getTransparentColor();
	Rectangle getRectangle();
	int getFrames();
	ResourceInfo(std::string resourceName, std::string filenameBase, std::string extension, int frames, bool transparent, Color color, Rectangle rectangle);
private:
	int frameFieldWidth();

	std::string resourceName;
	std::string filenameBase;
	std::string extension;
	int frames;
	bool transparentDefined;
	Color transparentColor;
	Rectangle rectangle;
};

#endif //RESOURCE_INFO_H