#include "stdafx.h"
#include "Engine.h"
#include "SceneManager.h"
#include "SoundManager.h"

Engine::Engine()
{
}

int Engine::InitEngine()
{
	//window���[�h�ݒ�B
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT);

	//�c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		//�G���[���N�����璼���ɏI��
		return -1;
	}

	//SwapChain�ݒ�B
	SetDrawScreen(DX_SCREEN_BACK);
	//���ߐF��ݒ�B
	SetTransColor(TRANS_COLOR[0], TRANS_COLOR[1], TRANS_COLOR[2]);

	m_sceneManager.Init();
}

void Engine::ExcuteEngine()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		//�Q�[�����[�v
		//�v�����J�n�B
		GameTime()->StartTimer();
		//Clear.
		ClearDrawScreen();

		//�V�[���}�l�[�W���[�X�V�B
		m_sceneManager.Update();
		//�T�E���h�}�l�[�W���[�X�V�B
		GameSound()->Update();

		//�f�o�b�O�p�̃��C����`��B
#ifdef DEBUG
		//DebugLineDraw();
#endif // DEBUG


		
		//SwapChain�B
		ScreenFlip();
		//�v�����I���B
		GameTime()->StopTimer();
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
}

void Engine::DebugLineDraw()
{
	//�O���b�h�\���B
	for (int i = 0; i < 999; i++) 
	{
		DrawLine(SCREEN_WIDTH, i * 24, -SCREEN_WIDTH, i * 24, GetColor(100, 100, 100), 3);
		if (i * 24 < -SCREEN_HEIGHT) 
		{
			break;
		}
	}
	for (int i = 0; i < 999; i++) {
		DrawLine(i * 24 + 7.2, SCREEN_HEIGHT, i * 24 + 7.2, -SCREEN_HEIGHT, GetColor(100, 100, 100), 3);
		if (i * 24 < -SCREEN_WIDTH) 
		{
			break;
		}
	}
	//�����`��B
	DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH / 2, -SCREEN_HEIGHT, GetColor(255, 0, 0), 3);
	DrawLine(SCREEN_WIDTH, SCREEN_HEIGHT / 2, -SCREEN_WIDTH, SCREEN_HEIGHT / 2, GetColor(255, 0, 0), 3);
}

void Engine::ExcuteManager()
{
}
