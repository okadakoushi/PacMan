#pragma once

/// <summary>
/// �T�E���h�}�l�[�W���N���X�B
/// </summary>
class SoundManager
{
public:
	/// <summary>
	/// ���[�h�^�C�v�B
	/// </summary>
	enum LOAD_TYPE
	{
		LoadType_MemNoPress,	//���k�Ȃ��T�E���h�f�[�^�[�ۑ��B�ǂݍ��ݑ��x�F�x���@�Đ����ׁF�����@�K�v�������̈�F�傫��
		LoadType_MemPress,		//���k����T�E���h�f�[�^�[�ۑ��B�ǂݍ��ݑ��x�F���ʁ@�Đ����ׁF�����d���@�K�v�������̈�F����
		LoadType_Streaming		//�X�g���[�~���O�Đ��B			�ǂݍ��ݑ��x�F�����@�Đ����ׁF�d���@�K�v�������̈�F�y�� 
	};

	/// <summary>
	/// �v���C�^�C�v�B
	/// </summary>
	enum PLAY_TYPE
	{
		PlayType_NORMAL = 0b000,		//�Đ��B�Đ��I���܂ŃQ�[�����[�v���~�܂�B
		PlayType_Back	= 0b001,		//�o�b�N�O���E���h�Đ��B���������ʂ̍Đ��B
		PlayType_Loop	= 0b010			//���[�v�Đ��B
	};

	/// <summary>
	/// �����T�E���h���A�Đ������������ɂǂ����邩�̗񋓁B
	/// </summary>
	enum PLAYING_TYPE 
	{
		PlayingType_EndPlaying,			//�Đ��I���܂ŗ����Ȃ��B
		PlayingType_MiddlePlay,			//���݂̉����͎c�����܂܁A���̉����𗬂�
		PlayingType_StopAndPlay,		//���݂̉������~�߂āA�ŏ����痬���B
	};

private:
	static SoundManager* m_instance;			//�C���X�^���X�B
	std::map<size_t, int> m_hashToSoundHandle;	//�n�b�V������T�E���h�n���h���B
	std::vector<int> m_duplicateSounds;			//�R�s�[���ꂽ�T�E���h�̃n���h���B�{�̂ł͂Ȃ��̂ŁA�Đ����I�����Ă�����폜����B

private:
	SoundManager() {};
	~SoundManager();

public:
	/// <summary>
	/// �C���X�^���X���擾�B
	/// </summary>
	/// <returns></returns>
	static SoundManager* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new SoundManager;
		}
		return m_instance;
	}

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

	/// <summary>
	/// �T�E���h���Đ��B
	/// <para>FlyWeight�݌v�B�߂�l�͑��֐����Ŏg�p�B</para>
	/// </summary>
	/// <param name="FilePath">�t�@�C���p�X�B</param>
	/// <param name="playType">�Đ��^�C�v�B</param>
	/// <param name="loadType">���[�h�^�C�v�B</param>
	/// <returns>�T�E���h�n���h���B</returns>
	int Load(const char* FilePath, LOAD_TYPE loadType = LoadType_MemNoPress);

	/// <summary>
	/// �Đ��B
	/// </summary>
	/// <param name="handle">�Đ�����T�E���h�̃n���h���B</param>
	/// <param name="playingType">�Đ����������ꍇ�ɂǂ��������������邩�B</param>
	/// <param name="playType">�Đ����@(Bit)�B</param>
	void Play(int handle, PLAYING_TYPE playingType = PlayingType_EndPlaying, int playType = PlayType_Back);

	/// <summary>
	/// ���ׂẲ����~�߂�B
	/// </summary>
	void AllStop();

	//bool IsPlaying()
	//{
	//	return CheckSoundFile();
	//}

};

static inline SoundManager* GameSound()
{
	return SoundManager::GetInstance();
}
