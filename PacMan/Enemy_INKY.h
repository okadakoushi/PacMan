#pragma once

#include "EnemyBase.h"

class Enemy_BLINKY;

class Enemy_INKY : public EnemyBase
{
private:
	Enemy_BLINKY* m_blinkyPtr = nullptr;
	const Vector2 RESPAWN_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 SCATTER_POINT = { 200.0f, 720.0f };

public:
	Enemy_INKY(SceneBase* sceneBase, PacMan* pacManPtr, Enemy_BLINKY* blinkyPtr, Vector2 StartPos);
	~Enemy_INKY();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update() override;
	virtual void Draw() override;
};

