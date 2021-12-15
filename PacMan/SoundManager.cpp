#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::~SoundManager()
{
	//�����[�X�����B
	InitSoundMem();
}

void SoundManager::Update()
{
	//�����I������R�s�[�����͍폜����B
	for (auto it = m_duplicateSounds.begin(); it != m_duplicateSounds.end();)
	{
		if (!CheckSoundMem(*it))
		{
			DeleteSoundMem(*it);
			it = m_duplicateSounds.erase(it);
		}
		else
		{
			++it;
		}
	}
}

int SoundManager::Load(const char* FilePath, LOAD_TYPE loadType)
{	
	//�����B
	int handle = m_hashToSoundHandle[std::hash<const char*>()(FilePath)];

	if (!handle)
	{
		//�o�^����Ă��Ȃ��B
		//�ǂݍ��݌`����ݒ�B
		SetCreateSoundDataType(loadType);
		handle = LoadSoundMem(FilePath);
		
		if (handle == -1)
		{
			//�s���B
			OutputDebugString("WARNING: Sound / SoundLoad filePath is invalid.");
			return -1;
		}

		ChangeVolumeSoundMem(DEFAULT_VOLUME, handle);
		//���\�[�X�Ƃ��ēo�^�B
		m_hashToSoundHandle[std::hash<const char*>()(FilePath)] = handle;
	}
	
	return handle;
}

void SoundManager::Play(int handle, PLAYING_TYPE playingType, int playType)
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
			//�{�����[���R�s�[���Ă���Ȃ��̂ŁA�R�s�[���̉����R�s�[�B
			ChangeVolumeSoundMem(GetVolumeSoundMem2(handle), handle);
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

void SoundManager::AllStop()
{
	for (auto sound : m_hashToSoundHandle)
	{
		//�������ׂĎ~�߂�B
		StopSoundMem(sound.second);
	}

	for (auto sound : m_duplicateSounds)
	{
		StopSoundMem(sound);
	}
}


