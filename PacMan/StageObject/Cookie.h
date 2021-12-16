#pragma once

#include "StageObject/ItemBase.h"

class Cookie : public ItemBase
{
private:
	const int COOKIE_SCORE = 10;	//“¾“_B

public:
	Cookie(SceneGame* sceneBase);
	virtual ~Cookie();

	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update()override {} ;
	virtual void Draw() override;
	
	/// <summary>
	/// Õ“ËŒø‰ÊB
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor) override;
};

