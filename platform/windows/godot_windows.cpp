
/*  godot_windows.cpp                                                    */

#include "main/main.h"
#include "os_windows.h"

#include <locale.h>
#include <stdio.h>

// For export templates, add a section; the exporter will patch it to enclose
// the data appended to the executable (bundled PCK)
#ifndef TOOLS_ENABLED
#if defined _MSC_VER
#pragma section("pck", read)
__declspec(allocate("pck")) static char dummy[8] = { 0 };
#elif defined __GNUC__
static const char dummy[8] __attribute__((section("pck"), used)) = { 0 };
#endif
#endif

PCHAR *
CommandLineToArgvA(
		PCHAR CmdLine,
		int *_argc) {
	PCHAR *argv;
	PCHAR _argv;
	ULONG len;
	ULONG argc;
	CHAR a;
	ULONG i, j;

	BOOLEAN in_QM;
	BOOLEAN in_TEXT;
	BOOLEAN in_SPACE;

	len = strlen(CmdLine);
	i = ((len + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);

	argv = (PCHAR *)GlobalAlloc(GMEM_FIXED,
			i + (len + 2) * sizeof(CHAR));

	_argv = (PCHAR)(((PUCHAR)argv) + i);

	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;

	while ((a = CmdLine[i])) {
		if (in_QM) {
			if (a == '\"') {
				in_QM = FALSE;
			} else {
				_argv[j] = a;
				j++;
			}
		} else {
			switch (a) {
				case '\"':
					in_QM = TRUE;
					in_TEXT = TRUE;
					if (in_SPACE) {
						argv[argc] = _argv + j;
						argc++;
					}
					in_SPACE = FALSE;
					break;
				case ' ':
				case '\t':
				case '\n':
				case '\r':
					if (in_TEXT) {
						_argv[j] = '\0';
						j++;
					}
					in_TEXT = FALSE;
					in_SPACE = TRUE;
					break;
				default:
					in_TEXT = TRUE;
					if (in_SPACE) {
						argv[argc] = _argv + j;
						argc++;
					}
					_argv[j] = a;
					j++;
					in_SPACE = FALSE;
					break;
			}
		}
		i++;
	}
	_argv[j] = '\0';
	argv[argc] = nullptr;

	(*_argc) = argc;
	return argv;
}

char *wc_to_utf8(const wchar_t *wc) {
	int ulen = WideCharToMultiByte(CP_UTF8, 0, wc, -1, nullptr, 0, nullptr, nullptr);
	char *ubuf = new char[ulen + 1];
	WideCharToMultiByte(CP_UTF8, 0, wc, -1, ubuf, ulen, nullptr, nullptr);
	ubuf[ulen] = 0;
	return ubuf;
}

int widechar_main(int argc, wchar_t **argv) {
	OS_Windows os(nullptr);

	setlocale(LC_CTYPE, "");

	char **argv_utf8 = new char *[argc];

	for (int i = 0; i < argc; ++i) {
		argv_utf8[i] = wc_to_utf8(argv[i]);
	}

	TEST_MAIN_PARAM_OVERRIDE(argc, argv_utf8)

	Error err = Main::setup(argv_utf8[0], argc - 1, &argv_utf8[1]);

	if (err != OK) {
		for (int i = 0; i < argc; ++i) {
			delete[] argv_utf8[i];
		}
		delete[] argv_utf8;
		return 255;
	}

	if (Main::start())
		os.run();
	Main::cleanup();

	for (int i = 0; i < argc; ++i) {
		delete[] argv_utf8[i];
	}
	delete[] argv_utf8;

	return os.get_exit_code();
};

int _main() {
	LPWSTR *wc_argv;
	int argc;
	int result;

	wc_argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (nullptr == wc_argv) {
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	}

	result = widechar_main(argc, wc_argv);

	LocalFree(wc_argv);
	return result;
}

int main(int argc, char **argv) {
	// override the arguments for the test handler / if symbol is provided
	// TEST_MAIN_OVERRIDE

	// _argc and _argv are ignored
	// we are going to use the WideChar version of them instead
#ifdef CRASH_HANDLER_EXCEPTION
	__try {
		return _main();
	} __except (CrashHandlerException(GetExceptionInformation())) {
		return 1;
	}
#else
	return _main();
#endif
}

HINSTANCE godot_hinstance = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	godot_hinstance = hInstance;
	return main(0, nullptr);
}
