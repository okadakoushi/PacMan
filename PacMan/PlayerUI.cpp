#include "stdafx.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(SceneGame* sceneGame)
{
	m_font.Init("Score\n", 15, 3);
	m_sceneGamePtr = sceneGame;
	
	for (auto& sprite : m_sprites)
	{
		sprite.Init("Assets/life_char.bmp");
	}
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{

}

void PlayerUI::Update(int score, int life)
{
	//str格納用。
	char str[16];
	//スコアを表示。
	sprintf(str, "Score\n  %05d", score);

	m_font.SetDispStr(str);
	m_font.Draw({ 150, 30 }, GetColor(255, 255, 255));

	for (int i = 0; i < life; i++)
	{
		m_sprites[i].Draw({ 150.0f + i * 44, 720.0f });
	}
}

