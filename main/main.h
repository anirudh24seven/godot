
/*  main.h                                                               */



#ifndef MAIN_H
#define MAIN_H

#include "core/error_list.h"
#include "core/os/thread.h"
#include "core/typedefs.h"

class Main {
	static void print_help(const char *p_binary);
	static uint64_t last_ticks;
	static uint32_t frames;
	static uint32_t frame;
	static bool force_redraw_requested;
	static int iterating;

public:
	static bool is_project_manager();
	static int test_entrypoint(int argc, char *argv[], bool &tests_need_run);
	static Error setup(const char *execpath, int argc, char *argv[], bool p_second_phase = true);
	static Error setup2(Thread::ID p_main_tid_override = 0);
#ifdef TESTS_ENABLED
	static Error test_setup();
	static void test_cleanup();
#endif
	static bool start();

	static bool iteration();
	static void force_redraw();

	static bool is_iterating();

	static void cleanup();
};

// Test main override is for the testing behaviour.
#define TEST_MAIN_OVERRIDE                                         \
	bool run_test = false;                                         \
	int return_code = Main::test_entrypoint(argc, argv, run_test); \
	if (run_test) {                                                \
		return return_code;                                        \
	}

#define TEST_MAIN_PARAM_OVERRIDE(argc, argv)                       \
	bool run_test = false;                                         \
	int return_code = Main::test_entrypoint(argc, argv, run_test); \
	if (run_test) {                                                \
		return return_code;                                        \
	}

#endif // MAIN_H
