//============================================================================
// Name        : rpclib_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "example.h"

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("please input s or c. \n");
		return 0;
	}

	ILog4zManager::getInstance()->start();

	std::string s(argv[1]);

	if (s.compare("s") == 0) {
		server_test(argc, argv);
	} else if (s.compare("c") == 0) {
		client_test(argc, argv);
	} else {
		printf("error. \n");
	}

	return 0;
}
