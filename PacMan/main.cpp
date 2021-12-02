#include "stdafx.h"
#include "Engine.h"
#include "GameSetting.h"

static float time = 0.0f;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//エンジン初期化。
	Engine engine;

	if (engine.InitEngine() == -1) 
	{
		//エンジンの初期化失敗。
		return -1;
	}

	//エンジン処理を実行。
	engine.ExcuteEngine();

	return 0;				// ソフトの終了 
}
