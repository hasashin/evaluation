#ifndef IMAGES_MANAGER_H
#define IMAGES_MANAGER_H
#include <string>
//#include <hash_map>
#include <unordered_map>
#include <map>
#include <boost/tuple/tuple_comparison.hpp>
#include "graphics/ResourceInfo.h"
#include "main/Misc.h"

#define ERROROUS_RESOURCE_NAME -1

struct SDL_Surface;

typedef boost::tuples::tuple <int, int, Vector4d> IntPair;
typedef std::map<IntPair, SDL_Surface*> IntPair2SDL_SurfaceMap;

//TODO PS L
//zmienic poczatek nazwy pliku resourca na string formatujacy // pozniejszy komentarz -> ale o co chodzi?
//zarz?danie cachem, np. definowanie kt?rych wcale nie ma wywalac, ale czy jest sens co? takiego robi??
class ImagesManager
{
public:
	int addResourceInfo(std::string resourceName, std::string filenameBase, std::string extension, int frames, bool transparent, Color color, Rectangle rectangle);
	void loadResourceFile( const std::string filename );
	/** set memory limit
	*/
	void setMaxMemory( int maxMemory ) { this->maxMemory = maxMemory; }
	/** get memory limit
	*/
	int getMaxMemory() { return maxMemory; }
//TODO PS L zwracac referencje? // pozniejszy komentarz -> ale o co chodzi?
	int getResourceHandler(const std::string resource_name);
	const ResourceInfo & getResourceInfo(const std::string resource_name);
	const SDL_Surface* getSurface( int resource_handler, Vector4d scale, int frame_number = -1 );
	const SDL_Surface* getSurface( const std::string resource_name, Vector4d scale, int frame_number = -1 );
	/** ImagesManager singleton call
	*/
	static ImagesManager& getInstance() 
	{
		//TODO PS L czy to aby napewno jest dobra implementacja wzorca singleton?
		static ImagesManager instance;
		return instance;
	}
private:
	unsigned int memory;
	unsigned int maxMemory;

	//stdext::hash_map<std::string, int> resourceNames;
	std::unordered_map<std::string, int> resourceNames;
	IntPair2SDL_SurfaceMap surfaces;
	std::unordered_map<int, ResourceInfo> resources;
	//stdext::hash_map<int, ResourceInfo> resources;

	ImagesManager() : maxMemory(1024*1024*10), memory(0) {}
    ImagesManager( const ImagesManager & );
    ImagesManager& operator=( const ImagesManager& );
	~ImagesManager();
	bool parse_line(char const* str);
};

#endif //IMAGES_MANAGER_H