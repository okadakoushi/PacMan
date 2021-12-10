#pragma once
class GameOver : public SceneBase
{
private:
	Sprite m_gameOverSprite;	//�Q�[���I�[�o�[�p
	int m_drawHandle = 0;		//�`��n���h��
	bool m_isStart = false;		//Z�����ꂽ���B
	int m_fadeColor = 255;		//�t�F�[�h�J���[�B
	const int FADE_SPEED = 3;	//�t�F�[�h���x�B(�t���[���j

public:
	GameOver(SceneManager* sceneManager);
	virtual ~GameOver();

	void Init() override;
	void Update() override;
};

