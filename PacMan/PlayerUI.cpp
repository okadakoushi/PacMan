#include "stdafx.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(SceneGame* sceneGame)
{
	m_font.Init("Score = 0", 25, 5);
	m_sceneGamePtr = sceneGame;
	
	for (auto& sprite : m_sprites)
	{
		sprite.Init("Assets/life_char.bmp");
	}
}

void PlayerUI::Init()
{

}

void PlayerUI::Update(int score, int life)
{
	//str格納用。
	char str[16];
	//スコアを表示。
	sprintf(str, "Score = %d", score);
	m_font.SetDispStr(str);
	m_font.Draw({ 0, 0 });

	for (int i = 0; i < life; i++)
	{
		m_sprites[i].Draw({ 872.0f + i * 36, 48.0f });
	}
}

