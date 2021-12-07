#pragma once

class PacMan;
class Wall;
class SceneGame;

class EnemyBase : public Actor
{
public:
	enum EnemyState
	{
		InPrisonMode = 1,	//牢獄内。
		GetOutPrisonMode,	//牢獄から出る。
		ScatterMode,		//散開。
		ChaseMode,			//追跡。
		TweekMode,			//いじけ。
		ReturnPrisonMode,	//牢獄内帰還。
	};

protected:
	enum Animation
	{
		LeftAnimation = 0,
		RightAnimation = 2,
		UpAnimation = 4,
		DownAnimatiom = 6,
		LeftEyeAnimatiton = 8,
		RightEyeAnimatiton,
		UpEyeAnimatiton,
		DownEyeAnimatiton,
		TweekAnimation = 12,
		NearEndTweekAnimation = 14,
		AnimationNum
	};

protected:
	//定数。
	const float			TWEEK_TIME			= 10.0f;	//いじけモード時間。
	const float			STANDARD_MOVE_SPEED = 2.0f;		//通常時移動速度。
	const float			TWEEK_MOVE_SPEED	= 1.0f;		//いじけ時移動速度。
	const float			RETURN_PRISON_SPEED = 6.0f;		//牢獄帰還時のスピード。
	const float			GETOUT_PRISON_SPEED = 1.0f;		//牢獄から出る用のスピード。
	const Vector2		START_POINT;					//初期位置。
	const Vector2		PRISON_FRONT = { 504, 288 };	//牢獄の前。

	//ptr.
	PacMan*				m_packManPtr = nullptr;					//パックマンポインタ。
	SceneGame*			m_sceneGame = nullptr;

	//アニメーション。
	const int AnimationSpeed = 5;								//アニメーションの切り替え速度。
	int m_drawHandle[AnimationNum];								//アニメーションすべてのDrawHandle。
	unsigned int m_animationIndex = 0;							//アニメーションのインデックス。これを使用して次に流すアニメーションを決める。
	int m_currentAnimation = 0;									//再生するアニメーション。
	int m_animationWaitFrame = 0;								//何フレームアニメーションを流したか。
	static std::map<std::pair<int, int>, Animation> m_directionToHandleIndex;

	//移動用。
	bool				m_isArrive = true;			//wayPointに到着してる？
	Vector2				m_direction = { 0, -1 };	//方向。
	Vector2				m_target = {504, 374};		//ターゲットの位置。
	Vector2				m_nextWayPoint = START_POINT;				//次のwayPoint。
	float				m_currentMoveSpeed = STANDARD_MOVE_SPEED;
	EnemyState			m_currentState = InPrisonMode;
	EnemyState			m_fontState;

	//残りの移動可能ピクセル。
	int					m_restMovePixcel = 0;

	//いじけモード用。
	Sprite				m_tweekSprite;				//いじけモードのスプライト。
	float				m_tweekTimer = 0.0f;		//いじけモード用タイマー。
	bool				m_callTweekEvent = false;	//いじけモード用イベントを呼び出したか。
	bool				m_callDeadEvent = false;	//死亡用イベント
	int					m_nearEndTweekFrame = 2;

	//Sound
	int m_returnPrisonSE = 0;


public:
	EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr, Vector2 startPos);
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void OnCollision(Actor* actor) override {};
	
	/// <summary>
	/// 衝突効果。
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor);

	/// <summary>
	/// 反転処理。
	/// </summary>
	void Turning();
	
	/// <summary>
	/// 現在のステートを取得。
	/// </summary>
	/// <returns></returns>
	EnemyState GetCurrentState()
	{
		return m_currentState;
	}

	void SetFrontState(EnemyState state)
	{
		m_fontState = state;
	}

	/// <summary>
	/// デッドイベントが呼ばれたか。
	/// </summary>
	/// <returns></returns>
	bool IsCallDeadEvent()
	{
		return m_callDeadEvent;
	}

	/// <summary>
	/// ターゲットを設定。
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(Vector2& target)
	{
		m_target = target;
	}

	void SetDeadEvent(bool flag)
	{
		m_callDeadEvent = flag;
	}

	/// <summary>
	/// 現在のステートを変更。
	/// </summary>
	/// <param name="state"></param>
	void ChangeCurrentState(EnemyState state)
	{
		m_currentState = state;
	}
protected:
	/// <summary>
	/// 死亡時処理。
	/// </summary>
	void Death();
	
	/// <summary>
	/// 次の移動候補地点4点に対して、移動可能な場所を返す。
	/// <para>ローカル変数を返すため、戻り値を参照に変更しないでください。</para>
	/// </summary>
	/// <returns></returns>
	std::vector<Vector2> CanMoveNextWayPoint();

	/// <summary>
	/// いじけモード時以外の経路検索。
	/// </summary>
	void WayPointSerch();
	
	/// <summary>
	/// いじけモード時用の経路検索。
	/// </summary>
	void WayPointSerchForTweekMode();
	
	//マス目状にマップをみたときにどこに配置されているか。参照つけない。
	Vector2 GetPositionIndex(Vector2& pos)
	{
		Vector2 centerPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		Vector2 posIndex = pos - centerPos;
		return posIndex = { (posIndex.x / SPRITE_SIZE), (posIndex.y / SPRITE_SIZE) };
	}
private:
	void AnimationUpdate();
};

