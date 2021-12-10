#pragma once

#include "PacMan.h"
#include "Font.h"

/// <summary>
/// PlayerUI.
/// </summary>
class PlayerUI : public Object
{
private:
	PacMan* m_pacManPtr = nullptr;	//パックマン。
	Font m_scoreFont;				//フォント。
	int m_highScore = 10000;		//ハイスコア。
	Font m_highScoreFont;			//ハイスコアフォント。
	Sprite m_sprites[3];			//残機表示用のスプライト。

public:
	PlayerUI();
	virtual ~PlayerUI();

	void Init();
	void Update(int score, int life);
};

