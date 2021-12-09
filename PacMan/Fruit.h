#pragma once

#include "ItemBase.h"

class Fruit : public ItemBase
{
private:
	const int FRUIT_SCORE = 100;		//スコア。
	Font	m_scoreFont;				//スコア表示用フォント。
	int		m_eatFruitSound = 0;		//フルーツ。
	bool	m_getFlag = false;			//取得されているか。
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

