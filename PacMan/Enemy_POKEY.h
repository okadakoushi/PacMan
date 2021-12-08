#pragma once

#include "EnemyBase.h"

class Enemy_POKEY : public EnemyBase
{
private:
	const Vector2 RESPAWN_POINT = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f };
	const Vector2 SCATTER_POINT = { 800.0, 720.0f };

public:
	Enemy_POKEY(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos);
	~Enemy_POKEY();
public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update() override;
	virtual void Draw() override;


};

