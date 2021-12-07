#pragma once
class GameOver : public SceneBase
{
private:
	Sprite m_gameOverSprite;
	int m_drawHandle = 0;
	bool m_isStart = false;
	int m_fadeColor = 255;
	const int FADE_SPEED = 3;
public:
	GameOver(SceneManager* sceneManager);
	~GameOver();
	void Init() override;
	void Update() override;
};

