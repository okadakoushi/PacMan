#pragma once

#include "ItemBase.h"

class Cookie : public ItemBase
{
private:
	const int COOKIE_SCORE = 10;	//���_�B
public:
	Cookie(SceneGame* sceneBase);

	void Init() override;
	void Draw() override;
	/// <summary>
	/// �Փˎ����ʁB
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor) override;
};

