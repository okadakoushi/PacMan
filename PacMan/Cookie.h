#pragma once

#include "ItemBase.h"

class Cookie : public ItemBase
{
private:
	const int COOKIE_SCORE = 10;	//���_�B
	int m_eatingSE = 0;

public:
	Cookie(SceneGame* sceneBase);
	virtual ~Cookie();

	virtual void Init() override;
	virtual void OnCollision(Actor* actor)override {};
	virtual void Update()override {} ;
	virtual void Draw() override;
	/// <summary>
	/// �Փˎ����ʁB
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor) override;
};

