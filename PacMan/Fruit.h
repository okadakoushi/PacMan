#pragma once

#include "ItemBase.h"

class Fruit : public ItemBase
{
private:
	const int FRUIT_SCORE = 100;		//スコア。	
public:
	Fruit(SceneBase* sceneBase);
	void Init() override;
	void Draw() override;
	void HitEffect(Actor* actor) override;		
	//int furitType = 0;
};

