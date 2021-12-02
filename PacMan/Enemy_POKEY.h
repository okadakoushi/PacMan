#pragma once

#include "EnemyBase.h"

class Enemy_POKEY : public EnemyBase
{
public:
	Enemy_POKEY(SceneBase* sceneBase, PacMan* pacManPtr);

public:
	void Init() override;
	void Update() override;
	void Draw() override;

private:
	const Vector2 RESPAWN_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 PRISON_POINT = { 480.0f, 384.0f };
	const Vector2 SCATTER_POINT = { 800.0, 720.0f };
};

