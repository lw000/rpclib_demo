/*
 * client.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: root
 */

#include "example.h"
#include "rpc/client.h"

#include <iostream>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int client_test(int argc, char **argv) {

	rpc::client client("127.0.0.1", rpc::constants::DEFAULT_PORT);
	int result;
	{
		result = client.call("add", 2, 3).as<int>();
		LOGFMTA("add:%d", result);

		result = client.call("sub", 10, 20).as<int>();
		LOGFMTA("sub:%d", result);
	}

	{
		clock_t t = clock();

		for (int i = 0; i < 10000; i++) {

			result = client.call("sum", 1000).as<int>();
			LOGFMTA("[%d] sum:%d", i, result);
		}

		clock_t t1 = clock();
		LOGFMTA("all exec times: %f, sum:%d", ((double)t1-t)/CLOCKS_PER_SEC,
				result);
	}

	return 0;
}
