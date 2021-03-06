#include "graphics/ImagesManager.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/qi.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>

using namespace  boost::spirit::classic;
//using namespace boost::spirit::qi;
//TODO doda� tu obs�ug� tekst�w regularnie wy�wietlanych??
/** adds resourceInfo to map, check if it is not allready there
*/
int ImagesManager::addResourceInfo(std::string resourceName, std::string filenameBase, std::string extension, int frames, bool transparent, Color color, Rectangle rectangle)
{
int resourceHandler = -1;
std::unordered_map<std::string, int>::const_iterator resourceNamesIterator;
resourceNamesIterator = resourceNames.find(resourceName);
if ( resourceNamesIterator == resourceNames.end( ) )
{
resourceHandler = resourceNames.size();//IMPORTANT REMARK resourceInfos shall newer be removed, becouse size is used as handler genarting sequence
ResourceInfo resourceInfo(resourceName, filenameBase, extension, frames, transparent, color, rectangle);
resourceNames.insert(std::pair <std::string, int>(resourceName, resourceHandler));
resources.insert(std::pair <int, ResourceInfo>(resourceHandler, resourceInfo));
//std::cerr << "Registred resource: " << resourceName << std::endl;
} else {
resourceHandler = resourceNamesIterator->second;
}
return resourceHandler;
}
/** parse line of file with resource specification
*/
bool ImagesManager::parse_line(char const* str)
{
//resource_name "filename_base" extension nof_frames transparent_color [r] [g] [b] [x] [y] [w] [h]
std::string resourceName;
std::string filenameBase;
std::string extension;
int frames = 0;
bool transparent = false;
Color color;
Rectangle rectangle;
/*	std::cerr << "STR " << str << std::endl;*/

rule<phrase_scanner_t> resource_name = alnum_p >> *(alnum_p | ch_p('.') | ch_p('_'));
rule<phrase_scanner_t> filename = alnum_p >> *(alnum_p | ch_p(' ') | ch_p('_'));
rule<phrase_scanner_t> filename_base = filename >> *(ch_p('/') >> filename);
rule<phrase_scanner_t> extension_p = lexeme_d[ alnum_p >> *alnum_p ];
rule<phrase_scanner_t> color_p = uint_p[assign_a(color.r)] >> uint_p[assign_a(color.g)] >> uint_p[assign_a(color.b)];
rule<phrase_scanner_t> rect_p = uint_p[assign_a(rectangle.x)] >> uint_p[assign_a(rectangle.y)] >> uint_p[assign_a(rectangle.w)] >> uint_p[assign_a(rectangle.h)];
rule<phrase_scanner_t> line = resource_name[assign_a(resourceName)]
>> ch_p('\"') >> filename_base[assign_a(filenameBase)] >> ch_p('\"')
>> extension_p[assign_a(extension)]
>> int_p[assign_a(frames)]
>> (ch_p('F')[assign_a(transparent, false)] | ch_p('T')[assign_a(transparent, true)])
>> !(color_p >> !(rect_p));

bool result = parse(str, line, space_p).hit;

if (result)
{
addResourceInfo(resourceName, filenameBase, extension, frames, transparent, color, rectangle);
}
return result;
}
/** loads file with resource specification
*/
void ImagesManager::loadResourceFile(const std::string filename)
{
//za�adowanie resource info z pliku
std::ifstream ifs ( filename.c_str() , std::ifstream::in );
std::string str;
while (getline(ifs, str))
{
if (str.empty())
break;

if (parse_line(str.c_str()))
{
//			std::cerr << "Parsing succeeded\n";
}
else
{
//TODO lynx error logging
std::cerr << "Parsing failed at line: " << str << "\n";
}
}
ifs.close();
}
/** gets image for given name, frame and scale
*/
const SDL_Surface* ImagesManager::getSurface( const std::string resource_name, Vector4d scale, int frame_number )
{
int resource_handler = getResourceHandler(resource_name);
if ( resource_handler == ERROROUS_RESOURCE_NAME )
{
//TODO lynx error logging
printf("Could not load resource with given name: %s\n", resource_name.c_str());
return NULL;
}
else
{
return getSurface( resource_handler, scale, frame_number );
}
}
/** translates resource name to resource handler
*/
int ImagesManager::getResourceHandler(const std::string resource_name)
{
std::unordered_map<std::string, int>::const_iterator resourceNamesIterator;
resourceNamesIterator = resourceNames.find(resource_name);
if ( resourceNamesIterator == resourceNames.end( ) )
{
return ERROROUS_RESOURCE_NAME;
}
else
{
return resourceNamesIterator->second;
}
}
/** gets resource info for resorce of given name
*/
const ResourceInfo & ImagesManager::getResourceInfo(const std::string resource_name)
{
std::unordered_map<std::string, int>::const_iterator resourceNamesIterator;
resourceNamesIterator = resourceNames.find(resource_name);
if ( resourceNamesIterator == resourceNames.end( ) )
{
//TODO lynx error logging
//return NULL;
assert(false);
return ResourceInfo("invalid","invalid","invalid", -1, false, Color(), Rectangle());
}
else
{
int resource_handler = resourceNamesIterator->second;
std::unordered_map<int, ResourceInfo>::iterator it;
it = resources.find(resource_handler);
if ( it == resources.end( ) )
{
//TODO lynx error logging
//return NULL;
assert(false);
return ResourceInfo("invalid","invalid","invalid", -1, false, Color(), Rectangle());
}
return it->second;
}
}
/** gets image for given resource handler, frame and scale
*/
const SDL_Surface* ImagesManager::getSurface( int resource_handler, Vector4d scale, int frame_number )
{
//try to obtain surface from cache first
IntPair intPair ( resource_handler, frame_number, scale );
IntPair2SDL_SurfaceMap::const_iterator surfacesIterator;
surfacesIterator = surfaces.find(intPair);
if ( surfacesIterator == surfaces.end( ) )
{
std::unordered_map<int, ResourceInfo>::iterator it;
it = resources.find(resource_handler);
if ( it == resources.end( ) )
{
//TODO lynx error logging
printf("Could not load resource with given handler: %d\n", resource_handler);
return NULL;
}
//get requested surface info
ResourceInfo & resourceInfo = it->second;
const std::string & filename = resourceInfo.getFilename(frame_number);

//get requested surface
SDL_Surface* tmp = IMG_Load(filename.c_str());
if (!tmp)
{
//TODO lynx error logging
printf("Unable to load bitmap: %s\n", SDL_GetError());
return NULL;
}
SDL_Surface * out = zoomSurface(const_cast<SDL_Surface*>(tmp), scale.val[0], scale.val[1], 1);
//SDL_Surface * out = shrinkSurface(const_cast<SDL_Surface*>(tmp), 1.0/scale.val[0], 1.0/scale.val[1]);
SDL_FreeSurface(tmp);
if (!out)
{
//TODO lynx error logging
printf("Unable to load bitmap: %s\n", SDL_GetError());
return NULL;
}
SDL_Surface* surface = SDL_DisplayFormat(out);
SDL_FreeSurface(out);
if (!surface)
{
//TODO lynx error logging
printf("Unable to load bitmap: %s\n", SDL_GetError());
return NULL;
}

//set transparent color
const Color & color = resourceInfo.getTransparentColor();
Uint32 col = SDL_MapRGB(surface->format,color.r,color.g,color.b);
SDL_SetColorKey(surface, SDL_SRCCOLORKEY, col);

//obs�uga rectangle of interest
const Rectangle & rectangle = resourceInfo.getRectangle();
SDL_Rect rect;
rect.h = rectangle.h * (1.0/scale.val[1]);
rect.w = rectangle.w * (1.0/scale.val[0]);
rect.x = rectangle.x * (1.0/scale.val[0]);
rect.y = rectangle.y * (1.0/scale.val[1]);
SDL_SetClipRect(surface, &rect);

unsigned int size = surface->h * surface->pitch;

if (size > maxMemory)
{
char * errorTxt = NULL;
snprintf( errorTxt, 50, "Resource %s is to big to be loaded\n", resourceInfo.getResourceName().c_str());
throw ResourceException(errorTxt);
}

while (memory + size > maxMemory)
{
//TODO PS L wybierz wed�ug LRU
surfacesIterator = surfaces.begin();
SDL_Surface * toRemove = surfacesIterator->second;
unsigned int retrived = toRemove->h * toRemove->pitch;
SDL_FreeSurface(toRemove);
surfaces.erase(surfacesIterator);
memory -= retrived;
}

surfaces.insert(std::pair <IntPair, SDL_Surface*>(intPair, surface));
memory += size;
return surface;
}
else
{
return surfacesIterator->second;
}
}
/** cleans up images manager
*/
ImagesManager::~ImagesManager()
{
resourceNames.clear();
resources.clear();
IntPair2SDL_SurfaceMap::iterator it;
for (it = surfaces.begin(); it != surfaces.end(); ++it)
{
//thats the way SDL_Surfaces are deleted
SDL_FreeSurface(it->second);
}
surfaces.clear();
}