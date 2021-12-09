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
	Font m_font;					//フォント。
	Sprite m_sprites[3];
	SceneGame* m_sceneGamePtr = nullptr;
public:
	PlayerUI(SceneGame* sceneGame);
	virtual ~PlayerUI();

	void Init();
	void Update(int score, int life);
};

