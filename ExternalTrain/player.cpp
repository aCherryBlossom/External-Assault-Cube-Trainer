#pragma once
#include "stdafx.h"
#include "offsets.h"
#include "memory.h"
#include "structures.h"

extern bool bAmmo;
extern bool bRecoil;
extern bool bHealth;
extern bool aimbotEnabled;
extern bool aimbotTeamMode;

void updateLocal(struct PlayerStruct *player, Memory& mem, HANDLE hProcess, uintptr_t moduleBase) {
	// updates player structure
	player->team = mem.ReadMemory<int>(LOCAL_PLAYER, TEAM);
	player->health = mem.ReadMemory<int>(LOCAL_PLAYER, HEALTH);
	player->pos.x = mem.ReadMemory<float>(LOCAL_PLAYER, HEAD_X);
	player->pos.y = mem.ReadMemory<float>(LOCAL_PLAYER, HEAD_Y);
	player->pos.z = mem.ReadMemory<float>(LOCAL_PLAYER, HEAD_Z);
	player->rotation.pitch = mem.ReadMemory<float>(LOCAL_PLAYER, PITCH);
	player->rotation.yaw = mem.ReadMemory<float>(LOCAL_PLAYER, YAW);

	// ammo , recoil, health hacks 
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		bAmmo = !bAmmo;
		if (bAmmo) {
			std::cout << "Successfully enabled infinite ammo." << "\n";
			PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\xFF\x06", 2, hProcess);
		}
		else {
			std::cout << "Successfully disabled infinite ammo." << "\n";
			PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\xFF\x0E", 2, hProcess);
		}
	}

	if (GetAsyncKeyState(VK_HOME) & 1) {
		bRecoil = !bRecoil;
		if (bRecoil) {
			std::cout << "Successfully disabled recoil." << "\n";
			NopEx((BYTE*)(moduleBase + 0x63786), 10, hProcess);
		}
		else {
			std::cout << "Successfully re-enabled recoil." << "\n";
			PatchEx((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10, hProcess);
		}
	}

	if (GetAsyncKeyState(VK_PRIOR) & 1) {
		bHealth = !bHealth;
		if (bHealth) {
			std::cout << "Successfully enabled infinite health." << "\n";
		}
		else {
			std::cout << "Successfully disabled infinite health." << "\n";
			mem.WriteMemory<int>(LOCAL_PLAYER, HEALTH, 100);
		}
	}

	if (GetAsyncKeyState(VK_DELETE) & 1) {
		aimbotEnabled = !aimbotEnabled;
		if (aimbotEnabled) {
			std::cout << "Successfully enabled aimbot." << "\n";
		}
		else {
			std::cout << "Successfully disabled aimbot." << "\n";
		}
	}

	if (GetAsyncKeyState(VK_END) & 1) {
		aimbotTeamMode = !aimbotTeamMode;
		if (aimbotTeamMode) {
			std::cout << "Successfully set aimbot mode to NON team-based." << "\n";
		}
		else {
			std::cout << "Successfully set aimbot mode to team-based." << "\n";
		}
	}


	if (bHealth) {
		mem.WriteMemory<int>(LOCAL_PLAYER, HEALTH, 999);
	}

	return;
}
