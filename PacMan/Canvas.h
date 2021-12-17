#pragma once

#include "Engine/Font.h"
#include "ParentChildComponent.h"

class Canvas : public ParentChildComponent
{

private:
	std::vector<ParentChildComponent*> m_childs;

public:
	/// <summary>
	/// 子を登録。
	/// </summary>
	/// <param name="child"></param>
	virtual void RegistChild(ParentChildComponent* child) override;
	
	/// <summary>
	/// 子をリストから除外。
	/// </summary>
	/// <param name="child"></param>
	virtual void RemoveChild(ParentChildComponent* child) override;
	
	///// <summary>
	///// 子供のリストを取得。
	///// </summary>
	///// <returns></returns>
	//virtual ParentChildComponent* GetChild() override;
};

