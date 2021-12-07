#pragma once

#include "ItemBase.h"

class Fruit : public ItemBase
{
private:
	const int FRUIT_SCORE = 100;		//�X�R�A�B	
	int m_eatFruitSound = 0;							//�t���[�c�B
public:
	Fruit(SceneBase* sceneBase);
	~Fruit();
	void Init() override;
	void Draw() override;
	void HitEffect(Actor* actor) override;		
	//int furitType = 0;
};

