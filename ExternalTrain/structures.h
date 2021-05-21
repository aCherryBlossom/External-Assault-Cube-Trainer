#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "vectors.h"

struct EntStruct {
	// main entity info
	Vector3 pos{};
	int health{};
	int team{};
	// how far ent is from local player ; used for aimbot calculations
	float pDistance{};
};

struct PlayerStruct {
	int team{};
	int health{};
	float pitch{};
	float yaw{};
	Vector3 pos{};
	Vector2 rotation{};
};

#endif