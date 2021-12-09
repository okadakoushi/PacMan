#pragma once

#include "StageLoader.h"

/// <summary>
/// ���x���̏�������S���B
/// </summary>
class Stage : public Object
{
public:
	Stage(SceneGame* sceneBase);
	~Stage() {};

	/// <summary>
	/// �I�u�W�F�N�g�B
	/// </summary>
	enum PlaceObjectType
	{
		EnPlaceObjectType_None = -1,			//NoneObject
		EnPlaceObjectType_PowerCookie = 0,		//powerCookie
		EnPlaceObjectType_Cookie = 15,			//Cookie
		EnPlaceObjectType_WarpPoint = 45,		//Warp
		EnPlaceObjectType_Gate = 46,			//Gate �S������O�͂����邪�A�O����S���͂����Ȃ��B
		//��ɊY�����Ȃ��I�u�W�F�N�g�͂��ׂĕǁB
	};

	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	
	/// <summary>
	/// �X�e�[�W��_�ł�����B
	/// </summary>
	void BlinkingStage();

	/// <summary>
	/// �X�e�[�W�𐶐��B
	/// </summary>
	void CreateStage();

	/// <summary>
	/// �c��̃N�b�L�[�̐����擾�B
	/// </summary>
	/// <returns></returns>
	int GetRestCookieCount()
	{
		return m_restCookieCount;
	}

	/// <summary>
	/// �N�b�L�[�̐������炷�B
	/// </summary>
	void ReduceCookieCount()
	{
		m_restCookieCount--;
	}
private:
	SceneGame* m_sceneGame = nullptr;

	//�����p�B
	StageLoader m_stageLoader;							//�X�e�[�W���[�_�[�B
	std::vector<std::vector<int>> m_stageTable;			//�X�e�[�W�̃f�[�^�[�e�[�u���B	
	const int STAGE_TABLE_WIDTH = 36;					//�X�e�[�W�e�[�u���̉��B
	const int STAGE_TABLE_HEIGHT = 36;					//�X�e�[�W�e�[�u���̏c�B
	int m_restCookieCount = 0;							//�c��̃N�b�L�[�̐��B
	
	//�_�ŁB
	const int COLOR_TRIGGER_FRAME = 5;					//�_�Ő؂�ւ��t���[���B
	int m_colorTriggerFrame = 0;						
	bool m_colorTriggerFlag = false;					//���ǂ��炩�B
};

