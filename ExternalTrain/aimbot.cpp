#pragma once
#include "stdafx.h"
#include "offsets.h"
#include "memory.h"
#include "structures.h"

extern int closestEnt;
extern float closestDistance;
extern bool aimbotEnabled;

void aim(HANDLE hProc, uintptr_t modBase, struct PlayerStruct *player, Memory &mem, int &threadStatus) {
	while (threadStatus != 0 ) {
		Vector3 vect;

		uintptr_t z = closestEnt * 4;

		uintptr_t xAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_X });
		ReadProcessMemory(hProc, (BYTE*)xAddr, &vect.x, sizeof(&vect.x), nullptr);
		uintptr_t yAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_Y });
		ReadProcessMemory(hProc, (BYTE*)yAddr, &vect.y, sizeof(&vect.y), nullptr);
		uintptr_t zAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEAD_Z });
		ReadProcessMemory(hProc, (BYTE*)zAddr, &vect.z, sizeof(&vect.y), nullptr);

		float a = vect.x - player->pos.x;
		float b = vect.y - player->pos.y;
		float c = vect.z - player->pos.z;

		// MATH FUNCT ATAN2F RETURNS YAW VALUE IN RADIAN
		float atan_yx = atan2f(b, a);
		float atan_zy = NULL;

		float yaw = (float)(atan_yx * (180.0 / M_PI));
		float writeYaw = yaw + 90;

		if (player->rotation.yaw < 45 && player->rotation.yaw > -45 || player->rotation.yaw > 135 && player->rotation.yaw < 225) {
			atan_zy = atan2f(c, b);
		}
		else {
			atan_zy = atan2f(c, a);
		}

		float pitch = (float)(atan_zy * (180.0 / M_PI));
		float pitchAdjusted;
		float writePitch;

		/*
		Since game works with pitch values -90 - 90 , & 
		pitch is 360 degree, inverts pitch once smaller than -90 or greater than 90
		as yaw has already ensured pointing directly at enemy player. 
		*/
		if (pitch > 90) {
			pitchAdjusted = 180 - pitch;
		}
		else if (pitch < -90) {
			float P = 180 + pitch;
			pitchAdjusted = -P;
		}
		else if (pitch == 180) {
			pitchAdjusted = 0;
		}
		else {
			pitchAdjusted = pitch;
		}

		/* 
		Just don't even ask

		Aimbot didn't aim at head with the amount it was off by larger depending on how large the pitch
		was, fixed this fairly well by adding an offset that's based on how large the pitch is.
		*/
		if (pitchAdjusted < 0) {
			writePitch = pitchAdjusted + (6 * (-pitchAdjusted / 90));
		}
		else if (pitchAdjusted > 0) {
			writePitch = pitchAdjusted - (10 * (pitchAdjusted / 90));
		}
		else {
			writePitch = pitchAdjusted;
		}

		if (GetAsyncKeyState(AIMBOT_KEY)) {

			/*
			Sanity Check

			Fixes bugs with when there are no valid entities to aim at , or there is only 
			one enemy player & they are dead
			*/
			int cPlayers = NULL;
			int cHealth = NULL;
			uintptr_t pAmountAddr = FindDMAAddy(hProc, { modBase + 0x00027990 }, { 0x8 });
			ReadProcessMemory(hProc, (BYTE*)pAmountAddr, &cPlayers, sizeof(&cPlayers), nullptr);
			uintptr_t healthAddr = FindDMAAddy(hProc, { modBase + ENTITY_LIST }, { z, HEALTH });
			ReadProcessMemory(hProc, (BYTE*)healthAddr, &cHealth, sizeof(&cHealth), nullptr);

			if (cPlayers > 0 && cHealth > 0 && cHealth <= 100 && aimbotEnabled == true) {
				mem.WriteMemory<float>(LOCAL_PLAYER, YAW, writeYaw);
				mem.WriteMemory<float>(LOCAL_PLAYER, PITCH, writePitch);
			}
		}
	}
	return;
};