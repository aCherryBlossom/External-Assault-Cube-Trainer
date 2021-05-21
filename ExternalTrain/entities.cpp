#pragma once
#include "stdafx.h"
#include "offsets.h"
#include "memory.h"
#include "structures.h"

extern EntStruct Entity[32];
extern bool aimbotTeamMode;
extern int closestEnt;
extern float closestDistance;

void updateEnt(HANDLE hProc, uintptr_t modBase, struct PlayerStruct *player) {

	// UPDATE THIS CURRENT PLAYER AMOUNT PTR ! ! !
	uintptr_t pAmountAddr = FindDMAAddy(hProc, { modBase + 0x00027990 }, { 0x8 });
	int cPlayers = NULL;
	ReadProcessMemory(hProc, (BYTE*)pAmountAddr, &cPlayers, sizeof(&cPlayers), nullptr);

	int cHealth = NULL;
	int cTeam = NULL;

	int tempClosestEnt = NULL;
	float tempClosestDistance = 1000000;

	for (int i = 1; i < cPlayers; i++) {

		Vector3 entPos;

		uintptr_t z = i * 4;

		uintptr_t teamAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, TEAM });
		ReadProcessMemory(hProc, (BYTE*)teamAddr, &cTeam, sizeof(&cTeam), nullptr);

		uintptr_t healthAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEALTH });
		ReadProcessMemory(hProc, (BYTE*)healthAddr, &cHealth, sizeof(&cHealth), nullptr);

		uintptr_t xAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_X });
		ReadProcessMemory(hProc, (BYTE*)xAddr, &entPos.x, sizeof(&entPos.x), nullptr);
		uintptr_t yAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_Y });
		ReadProcessMemory(hProc, (BYTE*)yAddr, &entPos.y, sizeof(&entPos.y), nullptr);
		uintptr_t zAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_Z });
		ReadProcessMemory(hProc, (BYTE*)zAddr, &entPos.z, sizeof(&entPos.z), nullptr);
		
		float a = entPos.x - player->pos.x;
		float b = entPos.y - player->pos.y;
		float c = entPos.z - player->pos.z;

		float distance = sqrt((a * a) + (b * b) + (c * c));

		// IF ENT MEENS PARAMS & IS CLOSEST, SAVE TO TEMP CLOSEST.
		if (distance < tempClosestDistance && cHealth > 0) {
			if (aimbotTeamMode == true) {
				tempClosestDistance = distance;
				tempClosestEnt = i;
			}
			else if (aimbotTeamMode == false && cTeam != player->team){
				tempClosestDistance = distance;
				tempClosestEnt = i;
			}
		}

		// UPDATE ENTITY
		Entity[i].health = cHealth;
		Entity[i].team = cTeam;
		Entity[i].pos.x = entPos.x;
		Entity[i].pos.y = entPos.y;
		Entity[i].pos.z = entPos.y;
		//Entity[i].pDistance = distance;

		if (i == cPlayers - 1) {
			// DEFINE WHAT CLOSEST VALUES ARE AFTER FINISHING ITERATING THROUGH
			closestEnt = tempClosestEnt;
			closestDistance = tempClosestDistance;

			// RESET TEMP VALUES AND RECALCULATE TO KEEP VALUE CONSTANTLY ACCURATE
			tempClosestEnt = NULL;
			tempClosestDistance = 1000000;
		}
	}
	return;
};