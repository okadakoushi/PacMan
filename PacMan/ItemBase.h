#pragma once

#include "SceneGame.h"

class PlayerUI;

class ItemBase : public Actor
{
protected:
	SceneGame* m_sceneGame = nullptr;
	int m_score = 10;
public:
	ItemBase(SceneBase* sceneBase, const char* tag, int prio);

	virtual void Init() override = 0;
	virtual void Draw() override = 0;
	/// <summary>
	/// 衝突時効果を実装。
	/// </summary>
	/// <param name="actor"></param>
	virtual void HitEffect(Actor* actor);
};

