#pragma once
class Sprite
{
private:
	int m_drawHandle = 0;					//�`��n���h���B
	int* m_animationHandle;					//�A�j���[�V�����n���h���B
	bool m_transFlag = false;				//�����x��L���ɂ��邩�̃t���O�B
public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="filePath">Sprite�̃t�@�C���p�X�BAssets....</param>
	void Init(const char* filePath);
	
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="pos">�`��ʒu�B</param>
	/// <param name="spriteSize">�X�v���C�g�̃T�C�Y�B</param>
	void Draw(Vector2 pos, double scale, double Angle, int drawHandle);
	void Draw(Vector2 pos, double scale, double Angle);
	void Draw(Vector2 pos, int drawHandle);
	void Draw(Vector2 pos);
	void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int drawHandle);

	/// <summary>
	/// �`��p�n���h���̎擾�B
	/// </summary>
	/// <returns></returns>
	int GetDrawHandle()
	{
		return m_drawHandle;
	}
};

