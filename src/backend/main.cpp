#include "server.hpp"

int main() {
	Server srv{ip::make_address("0.0.0.0"), 8888};
	srv.run_forever();
}
