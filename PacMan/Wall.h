#pragma once

class SceneGame;

class Wall : public Actor
{
private:
	char m_filePath[64] = "Assets/wall_fix.png";
	int m_clearMaskHandle = 0;
	bool m_isClear = true;

public:
	Wall(SceneBase* sceneBase);
	virtual ~Wall();

	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update()override;
	virtual void Draw() override;

	/// 	/// <summary>
	/// �t�@�C���p�X��ݒ肷��B
	/// </summary>
	/// <param name="fp"></param>
	void SetFilePath(const char* filePath)
	{
		//�R�s�[�B
		strcpy(m_filePath, filePath);
	}

	void SetClearFlag(bool flag)
	{
		m_isClear = flag;
	}
};

