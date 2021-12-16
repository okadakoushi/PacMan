#pragma once

#include "Character/PacMan.h"
#include "Engine/Font.h"

/// <summary>
/// PlayerUI.
/// </summary>
class PlayerUI : public Object
{
private:
	PacMan* m_pacManPtr = nullptr;	//�p�b�N�}���B
	int m_highScore = 10000;		//�n�C�X�R�A�B
	Sprite m_sprites[3];			//�c�@�\���p�̃X�v���C�g�B

	Font m_scoreMassage;
	Font m_scoreValueFont;

	Font m_highScoreMassage;
	Font m_highScoreValueFont;


public:
	PlayerUI();
	virtual ~PlayerUI();

	void Init();
	void Update(int score, int life);
};

