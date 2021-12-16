#pragma once

#include "ItemBase.h"

/// <summary>
/// パワークッキー。
/// </summary>
class PowerCookie : public ItemBase
{
private:
	const int	POWER_COOKIE_SCORE = 50;
	const int	POWER_COOKIE_BLINKING_FRAME = 10;
	int	m_blinkingFrame = 0;

public:
	PowerCookie(SceneGame* sceneBase);
	virtual ~PowerCookie();
	
	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update()override;
	virtual void Draw() override;
	virtual void HitEffect(Actor* actor) override;
};

