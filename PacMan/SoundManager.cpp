#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::~SoundManager()
{
	InitSoundMem();
}

void SoundManager::Update()
{
	//�R�s�[�̃T�E���h�n���h���̓���������������B
	for (auto duplicateSound : m_duplicateSounds)
	{
		if (!CheckSoundMem(duplicateSound))
		{
			//�Đ����I�����Ă��邽�߁A����B
			DeleteSoundMem(duplicateSound);
		}
	}
}

int SoundManager::Load(const char* fp, LoadType loadType)
{	
	//�����B
	int handle = m_hashToSoundHandle[std::hash<const char*>()(fp)];

	if (!handle)
	{
		//�o�^����Ă��Ȃ��B
		//�ǂݍ��݌`����ݒ�B
		SetCreateSoundDataType(loadType);
		handle = LoadSoundMem(fp);
		
		if (handle == -1)
		{
			//�s���B
			OutputDebugString("WARNING: Sound / SoundLoad filePath is invalid.");
			return -1;
		}

		//���\�[�X�Ƃ��ēo�^�B
		m_hashToSoundHandle[std::hash<const char*>()(fp)] = handle;
	}
	
	return handle;
}

void SoundManager::Play(int handle, PlayingType playingType, PlayType playType)
{
	//�Đ������̔���B
	bool isPlay = CheckSoundMem(handle);

	if (CheckSoundMem(handle))
	{
		//�Đ����B
		switch (playingType)
		{

		case SoundManager::PlayingType_EndPlaying:
			//�Đ����I������܂ŗ����Ȃ��B
			
			//�����I���B
			return;
			break;

		case SoundManager::PlayingType_MiddlePlay:
			//�������c���āA�V������������ė����B
			
			//�\�[�X���n���h�����R�s�[�B
			handle = DuplicateSoundMem(handle);
			//�R�s�[���X�g�ɐςށB
			m_duplicateSounds.push_back(handle);
			break;
		
		case SoundManager::PlayingType_StopAndPlay:
			//�Đ����I�����āA�ŏ����特�𗬂��B
			
			//�~�߂�B
			StopSoundMem(handle);
			break;
		
		default:
			OutputDebugString("WARNING: PlayingType is invalid.");
			break;
		
		}
	}

	PlaySoundMem(handle, playType);
}


