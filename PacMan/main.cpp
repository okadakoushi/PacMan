#include "stdafx.h"
#include "Engine.h"
#include "GameSetting.h"

static float time = 0.0f;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�G���W���������B
	Engine engine;

	if (engine.InitEngine() == -1) 
	{
		//�G���W���̏��������s�B
		return -1;
	}

	//�G���W�����������s�B
	engine.ExcuteEngine();

	return 0;				// �\�t�g�̏I�� 
}
