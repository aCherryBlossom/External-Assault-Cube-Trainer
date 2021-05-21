#pragma once

#include "stdafx.h"

class Memory
{
public:
	HANDLE processHandle;
	uintptr_t moduleBase;

	template <class T>
	T ReadMemory(uintptr_t pointer, DWORD offset)
	{
		T VALUE;
		uintptr_t passAddress;

		uintptr_t combine = moduleBase + pointer;
		ReadProcessMemory(processHandle, (BYTE*)combine, &passAddress, sizeof(passAddress), 0);

		uintptr_t readAddress = passAddress + offset;

		ReadProcessMemory(processHandle, (LPCVOID)readAddress, &VALUE, sizeof(T), 0);
		return VALUE;
	}

	template <class T>
	void WriteMemory(uintptr_t pointer, DWORD offset, T input)
	{

		T VALUE;
		VALUE = input;
		uintptr_t passAddress;

		uintptr_t combine = moduleBase + pointer;

		ReadProcessMemory(processHandle, (BYTE*)combine, &passAddress, sizeof(passAddress), 0);

		uintptr_t readAddress = passAddress + offset;

		WriteProcessMemory(processHandle, (BYTE*)readAddress, &VALUE, sizeof(T), 0);

		return;
	}
};

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);

void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);