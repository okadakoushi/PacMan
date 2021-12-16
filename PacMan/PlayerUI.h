#pragma once

#include "Character/PacMan.h"
#include "Engine/Font.h"

/// <summary>
/// PlayerUI.
/// </summary>
class PlayerUI : public Object
{
private:
	PacMan* m_pacManPtr = nullptr;	//パックマン。
	int m_highScore = 10000;		//ハイスコア。
	Sprite m_sprites[3];			//残機表示用のスプライト。

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

