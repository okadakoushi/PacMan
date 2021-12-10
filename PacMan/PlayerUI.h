#pragma once

#include "PacMan.h"
#include "Font.h"

/// <summary>
/// PlayerUI.
/// </summary>
class PlayerUI : public Object
{
private:
	PacMan* m_pacManPtr = nullptr;	//�p�b�N�}���B
	Font m_scoreFont;				//�t�H���g�B
	int m_highScore = 10000;		//�n�C�X�R�A�B
	Font m_highScoreFont;			//�n�C�X�R�A�t�H���g�B
	Sprite m_sprites[3];			//�c�@�\���p�̃X�v���C�g�B

public:
	PlayerUI();
	virtual ~PlayerUI();

	void Init();
	void Update(int score, int life);
};

