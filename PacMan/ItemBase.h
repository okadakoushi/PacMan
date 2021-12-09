#pragma once

#include "SceneGame.h"

class PlayerUI;

class ItemBase : public Actor
{
protected:
	SceneGame* m_sceneGame = nullptr;
	int m_score = 10;
	int m_eatingSoundHandle = 0;		//eating.

public:
	ItemBase(SceneBase* sceneBase, const char* tag, int prio);
	virtual ~ItemBase();

	virtual void Init() override = 0;
	virtual void Draw() override = 0;
	/// <summary>
	/// Õ“ËŒø‰Ê‚ğÀ‘•B
	/// </summary>
	/// <param name="actor"></param>
	virtual void HitEffect(Actor* actor);
};

