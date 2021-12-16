#pragma once
class Gate : public Actor
{
private:
	int m_drawHandle = 0;
public:
	Gate(SceneBase* sceneBase);
	virtual ~Gate();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor) override;
	virtual void Draw() override;
};

