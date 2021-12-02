#pragma once

#include "ItemBase.h"

/// <summary>
/// パワークッキー。
/// </summary>
class PowerCookie : public ItemBase
{
private:
	const int POWER_COOKIE_SCORE = 50;
public:
	PowerCookie(SceneGame* sceneBase);
	void Init() override;
	void Draw() override;
	void HitEffect(Actor* actor) override;
};

