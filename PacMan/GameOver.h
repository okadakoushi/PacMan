#pragma once
class GameOver : public SceneBase
{
private:
	Sprite m_gameOverSprite;	//ゲームオーバー用
	int m_drawHandle = 0;		//描画ハンドル
	bool m_isStart = false;		//Z押されたか。
	int m_fadeColor = 255;		//フェードカラー。
	const int FADE_SPEED = 3;	//フェード速度。(フレーム）

public:
	GameOver(SceneManager* sceneManager);
	virtual ~GameOver();

	void Init() override;
	void Update() override;
};

