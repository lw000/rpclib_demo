#include "example.h"

#include "rpc/server.h"

#include <iostream>

#include <log4z/log4z.h>
using namespace zsummer::log4z;

struct Sub{
	int operator()(int a, int b) {
		return a - b;
	}
};

void foo() {
	std::cout << "foo was called!" << std::endl;
}

void bad(int x) {
	if (x == 5) {
		throw std::runtime_error("x == 5. I really don't like 5.");
	}
}

int server_test(int argc, char **argv) {

	// Create a server that listens on port 8080, or whatever the user selected
	rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);

	// Binding the name "foo" to free function foo.
	// note: the signature is automatically captured
	srv.bind("foo", &foo);

	// Binding a lambda function to the name "add".
	srv.bind("add", [](int a, int b) { return a + b; });

	srv.bind("sum", [](int v) {
			int c = 0;
			for (int i = 0; i < v; i++) {
				c += i;
			}
			return c;
			});

	// Throwing an exception will cause the server to write
	// an error response. This call will make it also
	// suppress the exception (note that this is not default
	// because this behavior might hide errors in the
	// code).
	srv.suppress_exceptions(true);
	srv.bind("bad", &bad);

	Sub sub;
	srv.bind("sub", sub);

	// Run the server loop.
	srv.run();

	return 0;
}

