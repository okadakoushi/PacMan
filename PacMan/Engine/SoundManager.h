#pragma once

/// <summary>
/// サウンドマネージャクラス。
/// </summary>
class SoundManager
{
public:
	/// <summary>
	/// ロードタイプ。
	/// </summary>
	enum LOAD_TYPE
	{
		LoadType_MemNoPress,	//圧縮なしサウンドデーター保存。読み込み速度：遅い　再生負荷：速い　必要メモリ領域：大きい
		LoadType_MemPress,		//圧縮ありサウンドデーター保存。読み込み速度：普通　再生負荷：少し重い　必要メモリ領域：普通
		LoadType_Streaming		//ストリーミング再生。			読み込み速度：速い　再生負荷：重い　必要メモリ領域：軽い 
	};

	/// <summary>
	/// プレイタイプ。
	/// </summary>
	enum PLAY_TYPE
	{
		PlayType_NORMAL = 0b000,		//再生。再生終了までゲームループが止まる。
		PlayType_Back	= 0b001,		//バックグラウンド再生。こいつが普通の再生。
		PlayType_Loop	= 0b010			//ループ再生。
	};

	/// <summary>
	/// 同じサウンドが、再生中だった時にどうするかの列挙。
	/// </summary>
	enum PLAYING_TYPE 
	{
		PlayingType_EndPlaying,			//再生終了まで流さない。
		PlayingType_MiddlePlay,			//現在の音源は残したまま、次の音源を流す
		PlayingType_StopAndPlay,		//現在の音源を止めて、最初から流す。
	};

private:
	static SoundManager* m_instance;			//インスタンス。
	std::map<size_t, int> m_hashToSoundHandle;	//ハッシュからサウンドハンドル。
	std::vector<int> m_duplicateSounds;			//コピーされたサウンドのハンドル。本体ではないので、再生が終了していたら削除する。

private:
	SoundManager() {};
	~SoundManager();

public:
	/// <summary>
	/// インスタンスを取得。
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
	/// 更新。
	/// </summary>
	void Update();

	/// <summary>
	/// サウンドを再生。
	/// <para>FlyWeight設計。戻り値は他関数内で使用。</para>
	/// </summary>
	/// <param name="FilePath">ファイルパス。</param>
	/// <param name="playType">再生タイプ。</param>
	/// <param name="loadType">ロードタイプ。</param>
	/// <returns>サウンドハンドル。</returns>
	int Load(const char* FilePath, LOAD_TYPE loadType = LoadType_MemNoPress);

	/// <summary>
	/// 再生。
	/// </summary>
	/// <param name="handle">再生するサウンドのハンドル。</param>
	/// <param name="playingType">再生中だった場合にどういう挙動をするか。</param>
	/// <param name="playType">再生方法(Bit)。</param>
	void Play(int handle, PLAYING_TYPE playingType = PlayingType_EndPlaying, int playType = PlayType_Back);

	/// <summary>
	/// すべての音を止める。
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
