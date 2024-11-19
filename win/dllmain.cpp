#include <Windows.h>

#include <plog/Log.h>

#include "client.h"
#include "utils.h"
#include "constants.h"

void init() {
	utils::initLogger();
	PLOGI.printf("Console Initialized");

	client::connect();
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA(GAME_HANDLE_NAME) != nullptr) {
		init();
	}

	return TRUE;
}
