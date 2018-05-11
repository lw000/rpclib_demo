/*
 * client.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: root
 */

#include "example.h"
#include "rpc/client.h"

#include <getopt.h>
#include <iostream>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int client_test(const char* host, int port) {

	//-t c -h 127.0.0.1 -p 8001

//	std::string host("127.0.0.1");
//	int port = 0;
//
//	int ch = 0;
//	while ((ch = getopt(argc, argv, "h:p:")) != -1) {
//		switch (ch) {
//		case 'h': {
//			if (optarg != NULL) {
//				host = optarg;
//			}
//			break;
//		}
//		case 'p': {
//			if (optarg != NULL) {
//				port = atoi(optarg);
//			}
//
//			break;
//		}
//		default: {
//			fprintf(stderr, "Usage: thrift_demo "
//					"[--h=<h>] [--host] "
//					"[--p=<p>] [--port]\n");
//			exit(1);
//			break;
//		}
//		}
//	}

	rpc::client client(host, (port != 0) ? port : rpc::constants::DEFAULT_PORT);

	{
		int c;
		c = client.call("add", 2, 3).as<int>();
		LOGFMTA("add:%d", c);

		c = client.call("sub", 10, 20).as<int>();
		LOGFMTA("sub:%d", c);

		c = client.call("fact", 10).as<int>();
		LOGFMTA("fact:%d", c);
	}

	{
		clock_t t = clock();
		int exec = 10000;
		for (int i = 0; i < exec; i++) {
//			clock_t t = clock();
//			int c = client.call("sum", 1000).as<int>();
			client.call("fact", 10).as<int>();
//			clock_t t1 = clock();
//			LOGFMTA("exec:[%d] c:[%d], times:[%f]", i, c,
//					((double) t1 - t) / CLOCKS_PER_SEC);
		}
		clock_t t1 = clock();
		LOGFMTA("exec:[%d], times:[%f]", exec, ((double)t1-t)/CLOCKS_PER_SEC);
	}

	int c = getchar();
	printf("%d", c);
	return 0;
}
