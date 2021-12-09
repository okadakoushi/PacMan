#pragma once

#include "StageLoader.h"
#include "EnemyBase.h"
#include "Font.h"
#include "Stage.h"

class Fruit;
class PlayerUI;
class PacMan;
class EnemyBase;

/// <summary>
/// �Q�[���V�[���B
/// </summary>
class SceneGame : public SceneBase
{
protected:
	enum IsCallDeadEventFlag
	{
		EnCalledDeadEvent_None		= 0b0000,
		EnCalledDeadEvent_BLINKY	= 0b0001,
		EnCalledDeadEvent_PINKY		= 0b0010,
		EnCalledDeadEvent_INKY		= 0b0100,
		EnCalledDeadEvent_CLYDE		= 0b1000,
	};

	enum GameBGMType
	{
		GameBGMType_Normal,		//�m�[�}���T�C������
		GameBGMType_PowerMode,	//PowerMode
		GameBGMType_Return,		//�S���A�҉�
		GameBGMType_Num			//�T�E���h�̐��B
	};

	enum GameState
	{
		GameState_WaitGameStart,
		GameState_Running,
		GameState_EatingWait,
		GameState_PlayerDead,
		GameState_NextRound,
	};

private:

	std::vector<Actor*> m_obstacleList;						//��Q���ꗗ�B
	GameState m_currentGameState = GameState_WaitGameStart;	//���݂̃Q�[���X�e�[�g�B

	//UI�p�����[�^�[�B
	int m_lifePoint = 3;								//�c�@���B
	int m_score = 0;									//���_�B
	int m_lifeExtendSocre = 10000;							

	//�C���X�^���X��ptr�L���B
	SceneManager* m_sceneManager = nullptr;				//SceneManager�B
	PacMan* m_pacMan			 = nullptr;				//PacMan�B
	PlayerUI* m_playerUI		 = nullptr;				//PlayerUI�B
	Stage m_stage;										//�X�e�[�W�B
	std::vector<EnemyBase*> m_enemyList;				//�G�l�~�[�̃��X�g�B

	//�t���[�c�����p�̃p�����[�^�[�B
	const float FRUIT_APPEAR_DISAPPEAR_TIME = 10.0f;	//�t���[�c�p�A�o��or�����^�C�}�[�B
	Vector2 m_apperFruitPosition;						//�t���[�c�̏o���n�_�B
	float m_fruitTimer = 0.0f;							//�t���[�c�p�̃^�C�}�[�B
	Fruit* m_fruit = nullptr;							//�t���[�c�B

	//Enemy��H�ׂ��C�x���g�p�B
	const float WAIT_EATING_TINE = 1.0f;				//�H�ׂ鉉�o�̎��ԁB
	bool m_isPowerMode = false;							//�p���[���[�h�t���O�B
	int m_isCallDeadEventFlags = EnCalledDeadEvent_None;//�ǂ̓G���H�ׂ�ꂽ�̂����ʗp�B
	Font m_scoreFont;									//�G�l�~�[���H�ׂ�ꂽ���̃X�R�A�\���B
	int m_currentEatScore = 100;						//���݂̃X�R�A�B
	char m_scoreBuffer[12];								//�X�R�A�p�̃o�b�t�@�[�B

	//CHASE_SCATTER�؂�ւ��p�B
	const float	CHASE_TIME = 20.0f;						//�ǐՃ��[�h���̎��ԁB
	const float SCATTER_TIME = 6.0f;					//�U�J���[�h�B
	bool m_isChaseMode = false;							//���݂ǂ���̃X�e�[�g���B														
	static std::map<bool, std::pair<const float, EnemyBase::EnemyState>> m_isChaseToChageStateTimeAndMoveState;	//chase���[�h�t���O����؂�ւ����ԂƎ��̈ړ��X�e�[�g���擾�B
	static std::map<int, int> m_restCookieCountToFrequency;	//�c��̃N�b�L�[�̐�������g�����擾�B
	
	//�Q�[���i�s�p�B
	const float CHARACTER_SPAWN_TIME = 3.0f;					//�L�����N�^�[�𐶐�����
	const float START_GAME_TIME = CHARACTER_SPAWN_TIME + 1.5f;	//�Q�[�����J�n����B
	const float BLINKING_TIME = 1.5f;							//�_�Ŏ��ԁB
	const float NEXT_STAGE_TIME = BLINKING_TIME + 1.0f;			//���X�e�[�W�B

	//sound.
	int m_enemySEList[GameBGMType_Num];
	int m_openingBGM = 0;								//�I�[�v�j���O�B
	int m_eatingEnemySE = 0;							//�G��H�ׂ��B
	int m_extraSE = 0;									//���C�t�|�C���g�ǉ��B

	GameBGMType m_nextPlaySound = GameBGMType_Normal;	//���ɗ����ȁB

	//Timer.
	//�V�[���p�B
	float m_sceneStartDeltaTime = 0.0f;					//�V�[�����n�܂��Ă���̎��ԁB
	float m_nextStageTimer = 0.0f;						//�_�ŊǗ�
	//Ghost�p�B
	float m_enemyChaseTimer = 0.0f;						//�G�L�����̒ǐՁA�U�J��؂�ւ���p�̃^�C�}�[�B
	float m_eatingWaitTimer = 0.0f;						//�H�ׂ鉉�o��҂������ԁB

	//Ready
	Sprite m_readySprite;
	int m_drawHandle = 0;

	//�G��waitTime
	const float ENEMY_WAIT_TIME[3] = {
		START_GAME_TIME + 1.0f,		//PINKY�o���B
		START_GAME_TIME + 5.0f,		//INKY�o���B
		START_GAME_TIME + 9.0f		//CLYDE�o���B
	};

	//�G�̏����ʒu�B
	const Vector2 ENEMY_START_POS[4] = {
		{ CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 4.0f },
		{ CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f },
		{ CENTER_POSITION.x - SPRITE_SIZE * 3, CENTER_POSITION.y - SPRITE_SIZE * 1.0f },
		{ CENTER_POSITION.x + SPRITE_SIZE * 2, CENTER_POSITION.y - SPRITE_SIZE * 1.0f }
	};

public:
	SceneGame(SceneManager* sceneManager);
	virtual ~SceneGame();
	virtual void Init() override;
	virtual void Update() override;

	/// <summary>
	/// ��Q�����X�g�B
	/// </summary>
	/// <param name="actor"></param>
	void AddObstacle(Actor* actor)
	{
		m_obstacleList.push_back(actor);
	}

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
	void AddScore(int score);

	/// <summary>
	/// �N�b�L�[�J�E���g�����炷�B
	/// </summary>
	void ReduceCookieCount()
	{
		m_stage.ReduceCookieCount();
	}

protected:
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

	/// <summary>
	/// �p�����[�^�[�����Z�b�g�B
	/// </summary>
	void ResetParams();
};

