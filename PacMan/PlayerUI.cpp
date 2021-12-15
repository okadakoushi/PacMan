#include "stdafx.h"
#include "PlayerUI.h"

static const char* PacMan_LeftLifeSprite_FilePath = "Assets/life_char.bmp";

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	m_scoreFont.Init("Score\n", 15, 3);
	m_highScoreFont.Init("Score\n", 15, 3);

	for (auto& sprite : m_sprites)
	{
		sprite.Init(PacMan_LeftLifeSprite_FilePath);
	}
}

void PlayerUI::Update(int score, int life)
{
	//スコアを表示。
	char scoreBuffer[16];
	sprintf(scoreBuffer, "Score\n  %02d", score);
	m_scoreFont.SetDispStr(scoreBuffer);
	
	//ハイスコアを表示。
	char highScoreBuffer[32];
	m_highScore = max(score, m_highScore);
	sprintf(highScoreBuffer, "HIGH SCORE\n   %02d", m_highScore);
	m_highScoreFont.SetDispStr(highScoreBuffer);

	//ドロー。
	m_scoreFont.Draw({ 150, 30 }, GetColor(255, 255, 255));
	m_highScoreFont.Draw({ 330, 30 }, GetColor(255, 255, 255));

	for (int i = 0; i < life; i++)
	{
		m_sprites[i].Draw({ 150.0f + i * 44, 720.0f });
	}
}
