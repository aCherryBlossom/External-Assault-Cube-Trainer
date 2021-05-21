#pragma once
#include "stdafx.h"
#include "offsets.h"
#include "memory.h"
#include "structures.h"

void aim(HANDLE hProc, uintptr_t modBase, struct PlayerStruct* player, Memory& mem, int& threadStatus);