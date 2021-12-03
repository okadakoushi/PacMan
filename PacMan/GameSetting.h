#pragma once

#define DEBUG

//EngineSetting.
static const int SCREEN_WIDTH = 1024;				//w
static const int SCREEN_HEIGHT = 768;				//h
static const int COLOR_BIT = 32;					//�J���[�r�b�g�B
static const int TRANS_COLOR[3] = { 0, 255, 0 };	//���߂���F�B


//GameSetting.
static const Vector2	CENTER_POSITION = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };	//�����B
static const int		SPRITE_SIZE = 24;											//�T�C�Y�B

//Position��SpriteSize�{���ɂ��邽�߂̒l�B
//�𑜓x�̓s���ŁA�������W��SpriteSize�{�ɂȂ�Ȃ��B
static const int		FIX_VALUE_X = (int)CENTER_POSITION.x % SPRITE_SIZE;
static const int		FIX_VALUE_Y = (int)CENTER_POSITION.y % SPRITE_SIZE;
static const Vector2	FIX_VALUE = {float(FIX_VALUE_X), float(FIX_VALUE_Y)};