#pragma once

#include "stdafx.h"

#include "offsets.h"
#include "memory.h"
#include "player.h"
#include "vectors.h"
#include "structures.h"
#include "entities.h"
#include "aimbot.h"
#include <thread>

// Global variables
EntStruct Entity[32];
int closestEnt = NULL;
float closestDistance = 999999;

bool aimAtTeam = false;
bool bAmmo = false;
bool bRecoil = false;
bool bHealth = false;
bool aimbotEnabled = false;
bool aimbotTeamMode = false;

int main()
{
	DWORD procId;
	HANDLE hProcess;
	uintptr_t moduleBase;

	// Wait for process to be found
	bool procFound = false;
	procId = GetProcId(L"ac_client.exe");

	while (!procId) {
		procId = GetProcId(L"ac_client.exe");
		Sleep(2500);
		std::cout << "\n" << " Couldn't locate target process... retrying." << "\n";
	}

	if (procId) {
		std::cout << "\n" << " Target process succesfully located." << "\n" << "\n";
		Memory mem;
		PlayerStruct playerObj;

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");
		mem.processHandle = hProcess;
		mem.moduleBase = moduleBase;

		int status = procId;

		// aiming is handled on new thread since it was an easy way to fix a small bug and not really a downside
		// should only really read from mem and status, so just passing via std::ref, don't see how race condition would happen.
		std::thread thread1(aim, hProcess, moduleBase, &playerObj, std::ref(mem), std::ref(status));

		std::cout << "\n\n BLOSSOM'S EXTERNAL ASSAULT CUBE TRAINER \n";
		std::cout << "\n This is a simple C++ trainer made after ~2 weeks of learning C++ and basic reverse engineering. \n Features include toggleable aimbot";
		std::cout << " with support for both team and non-team based mode,\n no-recoil, and infinite ammo / health hacks for offline mode.\n\n ";
		std::cout << "\n If reviewing the source code of this cheat, please feel free";
		std::cout << "\n to let me know what I can improve upon.\n";
		std::cout << "\n HOTKEYS:\n";
		std::cout << "\n          INSERT : Toggle infinite ammo";
		std::cout << "\n          HOME : Toggle recoil";
		std::cout << "\n          PAGE UP : Toggle infinite health";
		std::cout << "\n          DELETE : Toggle aimbot";
		std::cout << "\n          END : Toggle aimbot team-support";
		std::cout << "\n          PAGE DOWN : Disable cheat.";
		std::cout << "\n\n          F : Aimbot Key\n\n\n";

		while (status != 0) {
			updateLocal(&playerObj, mem, hProcess, moduleBase);
			updateEnt(hProcess, moduleBase, &playerObj);

			// ensures process is still valid is still valid
			status = GetProcId(L"ac_client.exe");

			if (GetAsyncKeyState(VK_NEXT) & 1) {
				status = 0;
			}
		}
		thread1.join();
		CloseHandle(hProcess);
	}
}