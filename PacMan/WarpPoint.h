#pragma once
class WarpPoint : public Actor
{
private:
	bool m_trigger = false;
public:
	WarpPoint(SceneBase* sceneBase);

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnCollision(Actor* actor);
	virtual void Draw() override;


};

