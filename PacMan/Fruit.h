#pragma once

#include "ItemBase.h"

class Fruit : public ItemBase
{
private:
	const int FRUIT_SCORE = 100;		//�X�R�A�B
	Font	m_scoreFont;				//�X�R�A�\���p�t�H���g�B
	int		m_eatFruitSound = 0;		//�t���[�c�B
	bool	m_getFlag = false;			//�擾����Ă��邩�B
	float	m_socreDispTime = 0.0f;
	char	m_buffer[8];
public:
	Fruit(SceneBase* sceneBase);
	virtual ~Fruit();

	virtual void Init() override;
	virtual void Draw() override;
	virtual void Update() override; 
	virtual void HitEffect(Actor* actor) override;	

};

