#pragma once
class SceneTitle : public SceneBase
{
private:
	Sprite m_title;
	bool m_isStart = false;
	const int FADE_SPEED = 3;
	int m_fadeColor = 255;
	
public:
	SceneTitle(SceneManager* sceneManager);
	~SceneTitle();
	void Init() override;
	void Update() override;
};

