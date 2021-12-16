#pragma once

#include "StageLoader.h"

/// <summary>
/// レベルの初期化を担当。
/// </summary>
class Stage : public Object
{
public:
	Stage(SceneGame* sceneBase);
	~Stage() {};

	/// <summary>
	/// オブジェクト。
	/// </summary>
	enum PlaceObjectType
	{
		EnPlaceObjectType_None = -1,			//NoneObject
		EnPlaceObjectType_PowerCookie = 0,		//powerCookie
		EnPlaceObjectType_Cookie = 15,			//Cookie
		EnPlaceObjectType_WarpPoint = 45,		//Warp
		EnPlaceObjectType_Gate = 46,			//Gate 牢獄から外はいけるが、外から牢獄はいけない。
		//上に該当しないオブジェクトはすべて壁。
	};

	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();
	
	/// <summary>
	/// ステージを点滅させる。
	/// </summary>
	void BlinkingStage();

	/// <summary>
	/// ステージを生成。
	/// </summary>
	void CreateStage();

	/// <summary>
	/// 残りのクッキーの数を取得。
	/// </summary>
	/// <returns></returns>
	int GetRestCookieCount()
	{
		return m_restCookieCount;
	}

	/// <summary>
	/// クッキーの数を減らす。
	/// </summary>
	void ReduceCookieCount()
	{
		m_restCookieCount--;
	}
private:
	SceneGame* m_sceneGame = nullptr;

	//生成用。
	StageLoader m_stageLoader;							//ステージローダー。
	std::vector<std::vector<int>> m_stageTable;			//ステージのデーターテーブル。	
	const int STAGE_TABLE_WIDTH = 36;					//ステージテーブルの横。
	const int STAGE_TABLE_HEIGHT = 36;					//ステージテーブルの縦。
	int m_restCookieCount = 0;							//残りのクッキーの数。
	
	//点滅。
	const int COLOR_TRIGGER_FRAME = 5;					//点滅切り替えフレーム。
	int m_colorTriggerFrame = 0;						
	bool m_colorTriggerFlag = false;					//今どちらか。
};

