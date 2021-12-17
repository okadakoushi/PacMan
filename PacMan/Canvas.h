#pragma once

#include "Engine/Font.h"
#include "ParentChildComponent.h"

class Canvas : public ParentChildComponent
{

private:
	std::vector<ParentChildComponent*> m_childs;

public:
	/// <summary>
	/// �q��o�^�B
	/// </summary>
	/// <param name="child"></param>
	virtual void RegistChild(ParentChildComponent* child) override;
	
	/// <summary>
	/// �q�����X�g���珜�O�B
	/// </summary>
	/// <param name="child"></param>
	virtual void RemoveChild(ParentChildComponent* child) override;
	
	///// <summary>
	///// �q���̃��X�g���擾�B
	///// </summary>
	///// <returns></returns>
	//virtual ParentChildComponent* GetChild() override;
};

