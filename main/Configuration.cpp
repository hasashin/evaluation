#include "main/Configuration.h"
#include <fstream>

using namespace boost::program_options;

/** initializes boost options, sets default values
*/
Configuration::Configuration() {
	options_description generic("Generic options");
	generic.add_options()
		("height,h", value<int>()->default_value(600), "window height")
		("width,w", value<int>()->default_value(800), "window width")
		("map.actors.file", value<std::string>()->default_value("actors.eaf"), "file with actors definition")
		("map.filename", value<std::string>()->default_value("random"), "map to use")
		("respawns", "do agents respawn")
		("time", value<int>()->default_value(300), "battle time in seconds")
		;

	options_description config("Configuration file options");
	config.add_options()
		("actor.speed", value<double>()->default_value(10.0))
		("actor.maxHealth", value<int>()->default_value(100))
		("actor.maxArmour", value<int>()->default_value(100))
		("weapon.chaingun.ammo", value<int>()->default_value(50))
		("weapon.railgun.ammo", value<int>()->default_value(3))
		("weapon.rocket.ammo", value<int>()->default_value(5))
		("weapon.shotgun.ammo", value<int>()->default_value(4))
		("trigger.addHealth", value<int>()->default_value(25))
		("graphics.showHealthNumber", value<int>()->default_value(0))
		("graphics.showHealthBar", value<int>()->default_value(1))
		;

	options_description command("Command line options");
	command.add_options()
		("config-file", value<std::string>()->default_value("evaLUAtion.cfg"), "configuration file")
		;

	cmdline_options.add(generic).add(command);
	config_file_options.add(generic).add(config);
}

/** reads commandline parameters
*/
void Configuration::addOptions(int argc, char **argv) {
	store(parse_command_line(argc, argv, cmdline_options), vm);
	notify(vm);
}
/** reads parameters from file
*/
void Configuration::addOptions(std::string fileName) {
	std::ifstream ifs(fileName.c_str());
	store(parse_config_file(ifs, config_file_options), vm);
	notify(vm);
}
/**gets option value which is int
*/
int Configuration::getInt(std::string optionName) {
	return vm[optionName].as<int>();
}
/**gets option value which is bool
*/
bool Configuration::getBool(std::string optionName) {
	return vm.count(optionName) != 0 ? (vm[optionName].as<int>() != 0) : false;
}
/**gets option value which is double
*/
double Configuration::getDouble(std::string optionName) {
	return vm[optionName].as<double>();
}
/**gets option value which is string
*/
std::string Configuration::getString(std::string optionName) {
	return vm[optionName].as<std::string>();
}
/**checks if option value is set
*/
bool Configuration::isSet(std::string optionName) {
	return vm.count(optionName);
}