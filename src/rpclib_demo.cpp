//============================================================================
// Name        : rpclib_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "example.h"

#include <getopt.h>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

#include <json/json.h>

int main(int argc, char **argv) {
	if (argc < 2) {
//		printf("server please input -t s -p 8001. \n");
//		printf("client please input -t s -h 127.0.0.1 -p 8001. \n");
		printf("client please input (-t s) or (-t c). \n");
		return 0;
	}

	std::string t;
//	std::string a;

	int ch = 0;
	while ((ch = getopt(argc, argv, "t:")) != -1) {
		switch (ch) {
		case 't': {
			if (optarg != NULL) {
				t = optarg;
			}
			break;
		}
//		case 'a': {
//			if (optarg != NULL) {
//				a = optarg;
//			}
//			break;
//		}
		default: {
			fprintf(stderr, "(-t s) or (-t c)\n");
			exit(1);
			break;
		}
		}
	}

//	Json::Reader reader;
//	Json::Value root;
//	if (!reader.parse(a, root, false)) {
//		return -1;
//	}
//
//	int port = root["p"].asInt();

	ILog4zManager::getInstance()->start();

	if (t.compare("s") == 0) {
		server_test(8003);
	} else if (t.compare("c") == 0) {
		client_test("127.0.0.1", 8003);
	} else {
		printf("error. \n");
	}

	return 0;
}
