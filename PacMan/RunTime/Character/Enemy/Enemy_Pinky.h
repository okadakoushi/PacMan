#pragma once

#include "EnemyBase.h"

class Enemy_Pinky : public EnemyBase
{
private:
	const Vector2 WAIT_POINT = { CENTER_POSITION.x, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 SCATTER_POINT = { 200.0f, 48.0f };

public:
	Enemy_Pinky(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos);
	virtual ~Enemy_Pinky();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {} ;
	virtual void Update() override;
	virtual void Draw() override;

};

