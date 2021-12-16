#pragma once

/// <summary>
/// �t�H���g�N���X�B
/// </summary>
class Font
{
public:
	Font();
	virtual ~Font();

public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="dispStr">�\�����镶����B</param>
	/// <param name="size">�\�����镶���̃T�C�Y�B</param>
	/// <param name="thickness">�\�����镶���̑����B</param>
	void Init(const char* dispStr, int size, int thickness);
	
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="pos">�`�悷��ʒu�B</param>
	void Draw(const Vector2& pos, unsigned int color = GetColor(255,255,255));
	
	/// <summary>
	/// �\�����镶����ݒ�B
	/// </summary>
	/// <param name="dispChar">�\�����镶���B</param>
	void SetDispStr(const char* dispChar)
	{
		m_dispChar = dispChar;
	}
	
	/// <summary>
	/// �t�H���g�^�C�v��ݒ�B
	/// </summary>
	/// <param name="fontType">�t�H���g�̃t�@�C���p�X or �V�X�e���t�H���g�̖��O�B</param>
	void SetFontType(const char* fontType)
	{
		m_fontType = fontType;
		m_fontHandle = LoadFontDataToHandle(fontType);
	}
private:
	const char* m_fontType;
	const char* m_dispChar = "�\�����镶�����������܂��́A�ݒ肵�Ă��������B";
	int m_fontHandle = 0;
	int m_size = 10;
	int m_thickness = 5;
};
