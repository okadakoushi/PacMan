#pragma once
class GameOver : public SceneBase
{
private:
	Sprite m_gameOverSprite;
	int m_drawHandle = 0;
	bool m_isStart = false;
	int m_fadeColor = 255;
public:
	GameOver(SceneManager* sceneManager);
	void Init() override;
	void Update() override;
};

