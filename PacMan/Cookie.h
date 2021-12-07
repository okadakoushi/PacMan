#pragma once

#include "ItemBase.h"

class Cookie : public ItemBase
{
private:
	const int COOKIE_SCORE = 10;	//得点。
public:
	Cookie(SceneGame* sceneBase);

	void Init() override;
	void Draw() override;
	/// <summary>
	/// 衝突時効果。
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor) override;
};

