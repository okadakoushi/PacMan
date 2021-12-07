#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::~SoundManager()
{
	InitSoundMem();
}

void SoundManager::Update()
{
	//コピーのサウンドハンドルはメモリから解放する。
	for (auto duplicateSound : m_duplicateSounds)
	{
		if (!CheckSoundMem(duplicateSound))
		{
			//再生が終了しているため、解放。
			DeleteSoundMem(duplicateSound);
		}
	}
}

int SoundManager::Load(const char* fp, LoadType loadType)
{	
	//検索。
	int handle = m_hashToSoundHandle[std::hash<const char*>()(fp)];

	if (!handle)
	{
		//登録されていない。
		//読み込み形式を設定。
		SetCreateSoundDataType(loadType);
		handle = LoadSoundMem(fp);
		
		if (handle == -1)
		{
			//不正。
			OutputDebugString("WARNING: Sound / SoundLoad filePath is invalid.");
			return -1;
		}

		//リソースとして登録。
		m_hashToSoundHandle[std::hash<const char*>()(fp)] = handle;
	}
	
	return handle;
}

void SoundManager::Play(int handle, PlayingType playingType, PlayType playType)
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


