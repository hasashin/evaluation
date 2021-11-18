#include "graphics/ResourceInfo.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int ResourceInfo::frameFieldWidth()
{
	int width = 1;
	int i = frames;
	while (i > 10)
	{
		i = i/10;
		width++;
	}
	return width;
}
/** constructs filemane from this resource info and given frame
*/
std::string ResourceInfo::getFilename(int frame_number) {
	if ((frame_number < 0 || frame_number >= frames) && frame_number != -1)
	{
		char errorTxt[50];
		snprintf( errorTxt, 50, "Invalid frame number %d of resource %s\n", frame_number, resourceName.c_str() );
		throw ResourceException(errorTxt);
	}
	//TODO lynx L dodac kontrol� parametr�w wej�ciowych!
	std::stringstream ss;
	if (frame_number != -1)
	{
		int width = frameFieldWidth();
		ss << filenameBase << std::setfill('0') << std::setw(width) << frame_number << "." << extension;
	} 
	else 
	{
		ss << filenameBase << "." << extension;
	}
	std::string filename = ss.str();
/*	std::cerr << "Resource filename base: " << filenameBase << std::endl;
	std::cerr << "Resource filename: " << filename << std::endl;*/
	return filename;
}
/** get transparent color for this resource
*/
Color ResourceInfo::getTransparentColor() 
{
	return transparentColor; 
}
/** get rectangle of interest for this resource
*/
Rectangle ResourceInfo::getRectangle()
{
	return rectangle;
}
/** get name of this resource
*/
std::string ResourceInfo::getResourceName()
{
	return resourceName;
}
/** returns number of frames in this resource
*/
int ResourceInfo::getFrames()
{
	return frames; 
}
/** creates resource
*/
ResourceInfo::ResourceInfo(std::string resourceName, std::string filenameBase, std::string extension, int frames, bool transparent, Color color, Rectangle rectangle)
{
	this->resourceName = resourceName;
	this->filenameBase = filenameBase;
	this->extension = extension;
	this->frames = frames;
	this->transparentDefined = transparent;
	this->transparentColor = color;
	this->rectangle = rectangle;
}