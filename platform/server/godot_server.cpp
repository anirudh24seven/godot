
/*  godot_server.cpp                                                     */



#include "main/main.h"
#include "os_server.h"

int main(int argc, char *argv[]) {
	OS_Server os;

	// We must override main when testing is enabled
	TEST_MAIN_OVERRIDE

	Error err = Main::setup(argv[0], argc - 1, &argv[1]);
	if (err != OK)
		return 255;

	if (Main::start())
		os.run(); // it is actually the OS that decides how to run
	Main::cleanup();

	return os.get_exit_code();
}
