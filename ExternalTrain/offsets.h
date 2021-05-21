#pragma once
#define M_PI 3.14159265358979323846

#define LOCAL_PLAYER 0x10F4F4
#define ENTITY_LIST 0x10F4F8

#define HEAD_X 0x4
#define HEAD_Y 0x8
#define HEAD_Z 0xC
#define MAIN_X 0x34
#define MAIN_Y 0x38
#define MAIN_Z 0x3C
#define YAW 0x40
#define PITCH 0x44
#define CAN_JUMP 0x69
#define FORWARD_SPEED 0x80
#define HEALTH 0xF8
#define ARMOUR 0xFC
#define CARBINE_CLIP 0x118
#define SHOTGUN_CLIP 0x11C
#define SUBMACHINE_CLIP 0x120
#define SNIPER_CLIP 0x124
#define AR_CLIP 0x128
#define PISTOL_CLIP 0x134
#define CARBINE_AMMO 0x140
#define SHOTGUN_AMMO 0x144
#define SUBMACHINE_AMMO 0x148
#define SNIPER_AMMO 0x14C
#define AR_AMMO 0x150
#define GRENADES 0x158
#define PISTOL_AMMO 0x15C
#define KNIFE_DELAY 0x160
#define NAME 0x225
#define TEAM 0x32C
#define AIMBOT_KEY 0x46

// current weapon ammo = local player + 374 + 14 + 0

/*
class N0000004E
{
public:
	float headX; //0x0004
	float headY; //0x0008
	float headZ; //0x000C
	char pad_0010[36]; //0x0010
	float mainX; //0x0034
	float mainY; //0x0038
	float mainZ; //0x003C
	float yaw; //0x0040
	float pitch; //0x0044
	char pad_0048[33]; //0x0048
	bool canJump; //0x0069
	char pad_006A[22]; //0x006A
	int32_t forwardSpeed; //0x0080
	char pad_0084[116]; //0x0084
	int32_t health; //0x00F8
	int32_t armour; //0x00FC
	char pad_0100[24]; //0x0100
	int32_t carbineClip; //0x0118
	int32_t shotgunClip; //0x011C
	int32_t submachineClip; //0x0120
	int32_t sniperAmmo; //0x0124
	int32_t arClip; //0x0128
	char pad_012C[8]; //0x012C
	int32_t pistolClip; //0x0134
	char pad_0138[8]; //0x0138
	int32_t carbineAmmo; //0x0140
	int32_t shotgunAmmo; //0x0144
	int32_t submachineAmmo; //0x0148
	int32_t sniperAmmmo; //0x014C
	int32_t arAmmo; //0x0150
	char pad_0154[4]; //0x0154
	int32_t grenades; //0x0158
	int32_t pistolAmmo; //0x015C
	int32_t knifeDelay; //0x0160
	char pad_0164[193]; //0x0164
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t team; //0x032C
	char pad_0330[360]; //0x0330
}

*/