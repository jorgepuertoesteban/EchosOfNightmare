#pragma once

enum UserDatas {
	D_PLAYER         = 1,
	D_WALL           = 2,
	D_DEADWALL       = 3,
	D_SOUNDWAVE      = 4,
	D_GOAL           = 5,
	D_WATER          = 6,
	D_ENEMY          = 7,
	D_ROCK           = 8,
};

enum categoryBits {
	C_NONE           = 512,
	C_PLAYER         = 1,
	C_WALL           = 2,
	C_DEADWALL       = 4,
	C_SOUNDWAVE      = 8,
	C_GOAL           = 16,
	C_WATER          = 32,
	C_ENEMY          = 64,
	C_ENEMYSOUNDWAVE = 128,
	C_ROCK           = 256,
};