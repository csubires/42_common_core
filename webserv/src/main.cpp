#include <csignal>
#include <cstdlib>

#include "../includes/Webserv.hpp"
#include "../includes/ConfigParsing.hpp"
#include "../includes/utils.hpp"

Webserv *webserv = NULL;

void signalHandler(int signum) {
	(void) signum;
	if (webserv)
		webserv->stop();
}

int main(int argc, char **argv) {

	std::string config_file = "configs/default.conf";
	if (argc > 1)
		config_file = argv[1];

	ConfigParsing config;
	config.setConfigFile(config_file);
	if (!config.isFileReadable(config_file)) {
		logger(STDOUT_FILENO, ERROR,  "Configuration file is not readable");
		return (EXIT_FAILURE);
	}
	std::vector<std::string> tokens = config.tokenize(config_file, " \n\t");
	config.parse(tokens);

	signal(SIGINT, signalHandler);

	try {
		webserv = new Webserv(config);
		webserv->initializePorts();
		webserv->start();
	} catch (const std::exception &e) {
		logger(STDOUT_FILENO, ERROR, e.what());
		if (webserv) {
			delete webserv;
			webserv = NULL;
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
