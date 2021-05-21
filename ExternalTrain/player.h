#pragma once
#include "offsets.h"
#include "stdafx.h"
#include "memory.h"

void updateLocal(struct PlayerStruct* player, Memory& mem, HANDLE hProcess, uintptr_t moduleBase);

