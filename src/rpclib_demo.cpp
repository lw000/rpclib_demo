//============================================================================
// Name        : rpclib_demo.cpp
// Author      : lw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "example.h"

#include <string.h>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <numeric>
#include <limits>

#include <json/json.h>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char **argv) {
	if (argc < 2) {
		return 0;
	}

	std::string conf;
	int ch = 0;
	while ((ch = getopt(argc, argv, "c:")) != -1) {
		switch (ch) {
			case 'c': {
				if (optarg != NULL) {
					conf = optarg;
				}
				break;
			}
			default: {
				fprintf(stderr, "(-c config.conf)\n");
				break;
			}
		}
	}

	if (conf.empty()) {
		return 0;
	}

//	{
//		"platform":"s",
//	    "host": "127.0.0.1",
//	    "port": 8003
//	}

	std::string s;
	std::string host;
	int port;

#if 0
	char buff[1024];
	FILE *f;
	f = fopen(conf.c_str(), "r");
	fseek(f, 0, SEEK_SET);
	int i = fread(buff, sizeof(buff), 1, f);
	fclose(f);

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(buff, root, false)) {
		return -1;
	}

	s = root["platform"].asString();
	host = root["host"].asString();
	port = root["port"].asInt();

#else

	std::ifstream ifs;
	ifs.open(conf.c_str());
	assert(ifs.is_open());

	char buff[1024];
	ifs.read(buff, sizeof(buff) / sizeof(char));

	ifs.close();

	Json::Value root;
	Json::CharReaderBuilder builder;
	builder.settings_["allowSpecialFloats"] = true;
	std::string errs;
	Json::CharReader* reader(builder.newCharReader());
	bool ok = reader->parse(buff, buff + strlen(buff), &root, &errs);
	if (!ok) {
		fprintf(stderr, "fail parse json config. \n");
		return -1;
	}

//	Json::Reader reader;
//	Json::Value root;
//	bool ok = reader.parse(ifs, root, false);
//	if (!ok) {
//		fprintf(stderr, "fail parse json config. \n");
//		return -1;
//	}

	s = root["platform"].asString();
	host = root["host"].asString();
	port = root["port"].asInt();

#endif

	ILog4zManager::getInstance()->start();

	if (s.compare("s") == 0) {
		server_test(port);
	}
	else if (s.compare("c") == 0) {
		client_test(host.c_str(), port);
	}
	else {
		printf("error. \n");
	}

	return 0;
}
