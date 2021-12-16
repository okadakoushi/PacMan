#pragma once

#include "EnemyBase.h"

/// <summary>
/// í«Ç¢Ç©ÇØÇƒóàÇÈìGÉLÉÉÉâÅB
/// </summary>
class Enemy_BLINKY : public EnemyBase
{
private:
	const Vector2 WAIT_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 SCATTER_POINT = { 800.0f, 48.0f };

public:
	Enemy_BLINKY(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos);
	virtual ~Enemy_BLINKY();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update() override;
	virtual void Draw() override;
};

