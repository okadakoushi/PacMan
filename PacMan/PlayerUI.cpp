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
	//スコア。
	m_scoreMassage.Init("Score", 15, 3);
	m_scoreMassage.SetPosition({ 360, 30 });
	
	m_scoreValueFont.Init("00", 15, 3);
	m_scoreValueFont.SetParent(&m_scoreMassage);
	m_scoreValueFont.SetPosition({ 40, 20 });

	//ハイスコア。
	m_highScoreMassage.Init("Score", 15, 3);
	m_highScoreMassage.SetParent(&m_scoreMassage);
	m_highScoreMassage.SetPosition({ 170, 0 });

	m_highScoreValueFont.Init("Score", 15, 3);
	m_highScoreValueFont.SetParent(&m_highScoreMassage);
	m_highScoreValueFont.SetPosition({ 30, 20 });

	for (auto& sprite : m_sprites)
	{
		sprite.Init(PacMan_LeftLifeSprite_FilePath);
	}
}

void PlayerUI::Update(int score, int life)
{
	//スコア。
	m_scoreMassage.SetDispStr("Score");
	
	//数値側。
	char scoreBuffer[8];
	sprintf(scoreBuffer, "%02d", score);
	m_scoreValueFont.SetDispStr(scoreBuffer);

	//ハイスコア。
	m_highScoreMassage.SetDispStr("HighScore");

	//数値側。
	char highScoreBuffer[16];
	sprintf(highScoreBuffer, "%d", m_highScore);
	m_highScoreValueFont.SetDispStr(highScoreBuffer);

	//ドロー。
	m_scoreMassage.Draw(GetColor(255, 255, 255));
	m_scoreValueFont.Draw(GetColor(255, 255, 255));
	m_highScoreMassage.Draw(GetColor(255, 255, 255));
	m_highScoreValueFont.Draw(GetColor(255, 255, 255));

	for (int i = 0; i < life; i++)
	{
		m_sprites[i].Draw({ 150.0f + i * 44, 720.0f });
	}
}
