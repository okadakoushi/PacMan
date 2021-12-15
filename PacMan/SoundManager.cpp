#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::~SoundManager()
{
	//リリース処理。
	InitSoundMem();
}

void SoundManager::Update()
{
	//流し終わったコピー音源は削除する。
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
	//検索。
	int handle = m_hashToSoundHandle[std::hash<const char*>()(FilePath)];

	if (!handle)
	{
		//登録されていない。
		//読み込み形式を設定。
		SetCreateSoundDataType(loadType);
		handle = LoadSoundMem(FilePath);
		
		if (handle == -1)
		{
			//不正。
			OutputDebugString("WARNING: Sound / SoundLoad filePath is invalid.");
			return -1;
		}

		ChangeVolumeSoundMem(DEFAULT_VOLUME, handle);
		//リソースとして登録。
		m_hashToSoundHandle[std::hash<const char*>()(FilePath)] = handle;
	}
	
	return handle;
}

void SoundManager::Play(int handle, PLAYING_TYPE playingType, int playType)
{
	//再生中かの判定。
	bool isPlay = CheckSoundMem(handle);

	if (CheckSoundMem(handle))
	{
		//再生中。
		switch (playingType)
		{

		case SoundManager::PlayingType_EndPlaying:
			//再生が終了するまで流さない。
			
			//処理終了。
			return;
			break;

		case SoundManager::PlayingType_MiddlePlay:
			//音源を残して、新しい音を作って流す。
			
			//ソースよりハンドルをコピー。
			handle = DuplicateSoundMem(handle);
			//ボリュームコピーしてくれないので、コピー元の音をコピー。
			ChangeVolumeSoundMem(GetVolumeSoundMem2(handle), handle);
			//コピーリストに積む。
			m_duplicateSounds.push_back(handle);
			break;
		
		case SoundManager::PlayingType_StopAndPlay:
			//再生を終了して、最初から音を流す。
			
			//止める。
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
		//音をすべて止める。
		StopSoundMem(sound.second);
	}

	for (auto sound : m_duplicateSounds)
	{
		StopSoundMem(sound);
	}
}


