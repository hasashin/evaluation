#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "main/Misc.h"
#include <string>
#include <boost/program_options.hpp>

#define ConfIsSet(X) Configuration::getInstance().isSet(X)
#define ConfInt(X) Configuration::getInstance().getInt(X)
#define ConfDouble(X) Configuration::getInstance().getDouble(X)
#define ConfString(X) Configuration::getInstance().getString(X)

/** reads and stores game configuration
 */
class Configuration
{
public:
	/** configuration singleton call
	*/
	static Configuration& getInstance()
	{
		//TODO PS L czy to aby napewno jest dobra implementacja wzorca singleton?
		static Configuration instance;
		return instance;
	}
	/** add comandline options
	*/
	void addOptions(int argc, char** argv);
	/** add configuration file options
	*/
	void addOptions(std::string fileName);

	/** this methods return option values
	*/
	bool getBool(std::string optionName);
	int getInt(std::string optionName);
	double getDouble(std::string optionName);
	std::string getString(std::string optionName);
	bool isSet(std::string optionName);

private:
	Configuration();
    boost::program_options::variables_map vm;
    boost::program_options::options_description cmdline_options;
    boost::program_options::options_description config_file_options;
};

#endif //CONFIGURATION_H