#pragma once

#include "EnemyBase.h"

/// <summary>
/// 追いかけて来る敵キャラ。
/// </summary>
class Enemy_BLINKY : public EnemyBase
{
private:
	const Vector2 RESPAWN_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 PRISON_POINT = { 480.0f, 384.0f };
	const Vector2 SCATTER_POINT = { 800.0f, 48.0f };

public:
	Enemy_BLINKY(SceneBase* sceneBase, PacMan* pacManPtr);

public:
	void Init() override;
	void Update() override;
	void Draw() override;
};

