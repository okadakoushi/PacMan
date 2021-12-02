#pragma once

#include "EnemyBase.h"

class Enemy_BLINKY;

class Enemy_INKY : public EnemyBase
{
public:
	Enemy_INKY(SceneBase* sceneBase, PacMan* pacManPtr, Enemy_BLINKY* blinkyPtr);

public:
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	Enemy_BLINKY* m_blinkyPtr = nullptr;
	const Vector2 RESPAWN_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 PRISON_POINT = { 480.0f, 384.0f };
	const Vector2 SCATTER_POINT = { 200.0f, 720.0f };
};

