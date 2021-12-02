#pragma once

#define DEBUG

//EngineSetting.
static const int SCREEN_WIDTH = 1024;				//w
static const int SCREEN_HEIGHT = 768;				//h
static const int COLOR_BIT = 32;					//カラービット。
static const int TRANS_COLOR[3] = { 0, 255, 0 };	//透過する色。


//GameSetting.
static const Vector2	CENTER_POSITION = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };	//中央。
static const int		SPRITE_SIZE = 24;											//サイズ。