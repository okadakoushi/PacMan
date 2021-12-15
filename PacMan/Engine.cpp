#include "stdafx.h"
#include "Engine.h"
#include "SceneManager.h"
#include "SoundManager.h"

Engine::Engine()
{
}

int Engine::InitEngine()
{
	//windowモード設定。
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT);

	//ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		//エラーが起きたら直ちに終了
		return -1;
	}

	//SwapChain設定。
	SetDrawScreen(DX_SCREEN_BACK);
	//透過色を設定。
	SetTransColor(TRANS_COLOR[0], TRANS_COLOR[1], TRANS_COLOR[2]);

	m_sceneManager.Init();
	return 0;
}

void Engine::ExcuteEngine()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		//ゲームループ
		//計測を開始。
		GameTime()->StartTimer();
		//Clear.
		ClearDrawScreen();

		//シーンマネージャー更新。
		m_sceneManager.Update();
		//サウンドマネージャー更新。
		GameSound()->Update();

		//デバッグ用のラインを描画。
#ifdef DEBUG
		//DebugLineDraw();
#endif // DEBUG


		//SwapChain。
		ScreenFlip();
		//計測を終了。
		GameTime()->StopTimer();
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
}

void Engine::DebugLineDraw()
{
	//グリッド表示。
	for (int i = 0; i < 999; i++) 
	{
		DrawLine(SCREEN_WIDTH, i * SPRITE_SIZE, -SCREEN_WIDTH, i * SPRITE_SIZE, GetColor(100, 100, 100), 3);
		if (i * SPRITE_SIZE < -SCREEN_HEIGHT)
		{
			break;
		}
	}
	for (int i = 0; i < 999; i++) {
		Vector2_Int GridPosStart = { i * SPRITE_SIZE + 7, SCREEN_HEIGHT };
		Vector2_Int GridPosEnd = { i * SPRITE_SIZE + 7, -SCREEN_HEIGHT };
		DrawLine(GridPosStart.x, GridPosStart.y, GridPosEnd.x, GridPosEnd.y, GetColor(100, 100, 100), 3);
		if (i * SPRITE_SIZE < -SCREEN_WIDTH)
		{
			break;
		}
	}
	//中央描画。
	DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH / 2, -SCREEN_HEIGHT, GetColor(255, 0, 0), 3);
	DrawLine(SCREEN_WIDTH, SCREEN_HEIGHT / 2, -SCREEN_WIDTH, SCREEN_HEIGHT / 2, GetColor(255, 0, 0), 3);
}

void Engine::ExcuteManager()
{
}
