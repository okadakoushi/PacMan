#pragma once

#include "StageLoader.h"
#include "EnemyBase.h"
#include "Font.h"

class Fruit;
class PlayerUI;
class PacMan;
class EnemyBase;

/// <summary>
/// �Q�[���V�[���B
/// </summary>
class SceneGame : public SceneBase
{
public:
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

protected:
	enum IsCallDeadEventFlag
	{
		EnCalledDeadEvent_None		= 0b0000,
		EnCalledDeadEvent_BLINKY	= 0b0001,
		EnCalledDeadEvent_PINKY		= 0b0010,
		EnCalledDeadEvent_INKY		= 0b0100,
		EnCalledDeadEvent_CLYDE		= 0b1000,
	};

private:
	//UI�p�����[�^�[�B
	int m_leftCookieCount = 0;							//�N�b�L�[�̐��B
	int m_lifePoint = 3;								//�c�@���B
	int m_score = 0;									//���_�B

	//�C���X�^���X��ptr�L���B
	SceneManager* m_sceneManager = nullptr;				//SceneManager�B
	PacMan* m_pacMan			 = nullptr;				//PacMan�B
	PlayerUI* m_playerUI		 = nullptr;				//PlayerUI�B
	std::vector<EnemyBase*> m_enemyList;				//�G�l�~�[�̃��X�g�B

	//�X�e�[�W�f�[�^�[�ǂݍ��ݗp�v���p�e�B�[�B
	StageLoader m_stageLoader;							//�X�e�[�W���[�_�[�B
	std::vector<std::vector<int>> m_stageTable;			//�X�e�[�W�̃f�[�^�[�e�[�u���B
	std::vector<Actor*> m_obstacleList;					//��Q���ꗗ�B
	const int STAGE_TABLE_WIDTH = 36;					//�X�e�[�W�e�[�u���̉��B
	const int STAGE_TABLE_HEIGHT = 36;					//�X�e�[�W�e�[�u���̏c�B

	//���[�v�p�B
	Vector2 m_warpPoints[2];

	//�t���[�c�����p�̃p�����[�^�[�B
	const float FRUIT_APPEAR_DISAPPEAR_TIME = 10.0f;	//�t���[�c�p�A�o��or�����^�C�}�[�B
	Vector2 m_apperFruitPosition;						//�t���[�c�̏o���n�_�B
	float m_fruitTimer = 0.0f;							//�t���[�c�p�̃^�C�}�[�B
	Fruit* m_fruit = nullptr;							//�t���[�c�B

	//Enemy��H�ׂ��C�x���g�p�B
	const float WAIT_EATING_TINE = 1.0f;				//�H�ׂ鉉�o�̎��ԁB
	int m_isCallDeadEventFlags = EnCalledDeadEvent_None;//�ǂ̓G���H�ׂ�ꂽ�̂����ʗp�B
	Font m_scoreFont;									//�G�l�~�[���H�ׂ�ꂽ���̃X�R�A�\���B
	int m_currentEatScore = 100;						//���݂̃X�R�A�B
	char m_scoreBuffer[12];								//�X�R�A�p�̃o�b�t�@�[�B

	//EnemyState�؂�ւ��p�p�����[�^�[�B
	float m_enemyChaseTimer = 0.0f;						//�G�L�����̒ǐՁA�U�J��؂�ւ���p�̃^�C�}�[�B
	float m_eatingWaitTimer = 0.0f;						//�H�ׂ鉉�o��҂������ԁB
	Vector2 m_frontPrison = {504, 288};					//�S���̑O�B

	//CHASE_SCATTER�؂�ւ��p�B
	const float	CHASE_TIME = 20.0f;						//�ǐՃ��[�h���̎��ԁB
	const float SCATTER_TIME = 6.0f;					//�U�J���[�h�B
	bool m_isChaseMode = false;							//���݂ǂ���̃X�e�[�g���B														
	static std::map<bool, std::pair<const float, EnemyBase::EnemyState>> m_isChaseToChageStateTimeAndMoveState;	//chase���[�h�t���O����؂�ւ����ԂƎ��̈ړ��X�e�[�g���擾�B
	
	//�Q�[���i�s�p�B
	const float CHARACTER_SPAWN_TIME = 3.0f;					//�L�����N�^�[�𐶐�����
	const float START_GAME_TIME = CHARACTER_SPAWN_TIME + 1.5f;	//�Q�[�����J�n����B
	const float BLINKING_TIME = 1.5f;							//�_�Ŏ��ԁB
	const float NEXT_STAGE_TIME = BLINKING_TIME + 1.0f;			//���X�e�[�W�B

	//timer
	float m_sceneStartDeltaTime = 0.0f;					//�V�[�����n�܂��Ă���̎��ԁB
	float m_nextStageTimer = 0.0f;

	//Ready
	Sprite m_readySprite;
	int m_drawHandle = 0;
	//Stage
	const int COLOR_TRIGGER_FRAME = 5;
	int m_colorTriggerFrame = 0;
	bool m_colorTriggerFlag = false;

	//�G��waitTime
	const float ENEMY_WAIT_TIME[3] = {
		START_GAME_TIME + 1.0f,		//PINKY�o���B
		START_GAME_TIME + 5.0f,		//INKY�o���B
		START_GAME_TIME + 9.0f		//CLYDE�o���B
	};

	//�G�̏����ʒu�B
	const Vector2 ENEMY_START_POS[4] = {
		{ CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 4.0f },
		{ CENTER_POSITION.x, CENTER_POSITION.y - SPRITE_SIZE * 2.0f },
		{ CENTER_POSITION.x - SPRITE_SIZE * 3, CENTER_POSITION.y - SPRITE_SIZE * 1.0f },
		{ CENTER_POSITION.x + SPRITE_SIZE * 2, CENTER_POSITION.y - SPRITE_SIZE * 1.0f }
	};

public:
	SceneGame(SceneManager* sceneManager);
	virtual void Init() override;
	virtual void Update() override;

	/// <summary>
	/// ��Q���̃��X�g���擾�B
	/// </summary>
	/// <returns></returns>
	const std::vector<Actor*>& GetObstacles() const 
	{
		return m_obstacleList;
	}

	/// <summary>
	/// �X�R�A�����Z�B
	/// </summary>
	/// <param name="score"></param>
	void AddScore(int score)
	{
		m_score += score;
		m_score = std::clamp(m_score, 0, 99999);
	}

	/// <summary>
	/// �N�b�L�[�J�E���g�����炷�B
	/// </summary>
	void ReduceCookieCount()
	{
		m_leftCookieCount--;
	}
protected:
	/// <summary>
	/// �X�e�[�W���O���t�@�C����胍�[�h�B
	/// </summary>
	void LoadStage();

	/// <summary>
	/// �X�e�[�W�𐶐��B
	/// </summary>
	void CreateStage();

	/// <summary>
	/// �G�l�~�[�����B
	/// </summary>
	void CreateEnemy();

	/// <summary>
	/// Player�����S�����ۂɌĂ΂��C�x���g�B
	/// </summary>
	void PlayerDeadEvent();

	/// <summary>
	/// �G�l�~�[�̃X�e�[�g��ύX����C�x���g�B
	/// </summary>
	void EnemyEvent();

	/// <summary>
	/// ���̃��E���h�ցB
	/// </summary>
	void NextRound();

private:
	/// <summary>
	/// �t���[�c���o���ł��邩�B
	/// </summary>
	void FruitEvent();

};

