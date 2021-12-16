#include "stdafx.h"
#include "EnemyBase.h"
#include "PacMan.h"

std::map<EnemyBase::DIRECTION, EnemyBase::ANIMATION> EnemyBase::m_directionToNormalAnimHandleIndex
{
	//方向、アニメーションハンドルインデックス。
	{ Direction_Left,	LeftAnimation },
	{ Direction_Right,	RightAnimation },
	{ Direction_Up,		UpAnimation },
	{ Direction_Down,	DownAnimation },
};

std::map<EnemyBase::DIRECTION, EnemyBase::ANIMATION> EnemyBase::m_directionToEyeAnimHandleIndex
{
	{ Direction_Left,	LeftEyeAnimation },
	{ Direction_Right,	RightEyeAnimation },
	{ Direction_Up,		UpEyeAnimation },
	{ Direction_Down,	DownEyeAnimation },
};


EnemyBase::EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr, Vector2 startPos) : 
	Actor(sceneBase, tag, prio, RectCollision::EnCollisionType_Dynamic),
	m_packManPtr(packPtr),
	START_POINT(startPos)
{
	m_sceneGame = dynamic_cast<SceneGame*>(sceneBase);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_position = START_POINT;
	m_collision.SetCollisionSize({ 18,18 });
	//最初のフレームはここでWayPointを計算しておく。
	WayPointSerch();
	Vector2 direction = (m_nextWayPoint - m_position).Normalized();
	m_direction = EngineMath::ConvertToIntVec(direction);
}

void EnemyBase::Update()
{	
	//自分の位置から次のWayPointまでの距離。
	float pos2nextWayLen = (m_nextWayPoint - m_position).Length();

	if (pos2nextWayLen > SPRITE_SIZE)
	{
		m_restMovePixcel = 0;
	}

	if (m_isTweek)
	{
		//タイマーを加算。
		m_tweekTimer += GameTime()->GetDeltaTime();
		m_currentMoveSpeed = TWEEK_MOVE_SPEED;

		if (m_tweekTimer > TWEEK_TIME)
		{
			//いじけモードが終了している。
			m_currentMoveSpeed = STANDARD_MOVE_SPEED;
			m_tweekTimer = 0.0f;
			m_isTweek = false;
		}

	}

	if (m_restMovePixcel <= 0.0f)
	{
		//指定pix分移動したので次のwayPointを計算する。
		if (m_isTweek && (m_currentState != GetOutPrisonMode) )
		{
			//いじけモード時の移動を実行。
			WayPointSerchForTweekMode();
		}
		else
		{
			//通常移動を実行。
			WayPointSerch();
		}
		//次のwayPointが更新されたため、進行方向も更新。
		Vector2 Direction = (m_nextWayPoint - m_position).Normalized();
		m_direction = EngineMath::ConvertToIntVec(Direction);
		//残り移動ピクセルを初期化。
		m_restMovePixcel = SPRITE_SIZE;
	}
	
	//残りの移動可能量を計算。これを行わないと移動量を変更した際の位置が不正になる(グリッド真ん中で止まらない）。
	float move = std::clamp(m_currentMoveSpeed, 0.0f, (float)m_restMovePixcel);
	m_position += m_direction * move;
	//移動した分引く。
	m_restMovePixcel -= move;

	AnimationUpdate();
}

void EnemyBase::Draw()
{
	Vector2 drawPos = { m_position.x + 12, m_position.y + 12 };
	Actor::m_spirte.Draw(drawPos, 1.5f, 0, m_drawHandle[m_currentAnimation]);


#ifdef DEBUG
	DrawLine(m_position.x + 12, m_position.y + 12, m_position.x + 12 + m_direction.x * 100, m_position.y + 12 + m_direction.y * 100, GetColor(255, 0, 0));
#endif
}

void EnemyBase::HitEffect(Actor* actor)
{
	if (m_isTweek)
	{
		//いじけ
		Death();
	}
	else
	{
		//普通
		PacMan* pacman = dynamic_cast<PacMan*>(actor);
		if (pacman != nullptr && (m_currentState != ReturnPrisonMode) )
		{
			pacman->Death();
		}
	}
}

void EnemyBase::Turning()
{
	if (!m_isTweek)
	{
		m_direction *= -1;
		//反転した分、残り移動可能ピクセルも変更。
		m_restMovePixcel = SPRITE_SIZE - m_restMovePixcel;
	}
}

void EnemyBase::TweekEvent()
{
	Turning();
	m_tweekTimer = 0.0f;
	m_isTweek = true;
}

void EnemyBase::Death()
{
	m_currentState = ReturnPrisonMode;
	m_isTweek = false;
	m_tweekTimer = 0.0f;
	m_callDeadEvent = false;
	m_currentMoveSpeed = STANDARD_MOVE_SPEED;
}

std::vector<Vector2> EnemyBase::CanMoveNextWayPoint()
{
	//どれか4点。
	const Vector2_Int NEXT_POSITION_LIST[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	Vector2_Int inverseDir = m_direction * -1;

	//進む３点
	std::vector<Vector2_Int> nextPosIndexList;
	//候補３点を算出。
	for (auto nextIndex : NEXT_POSITION_LIST) 
	{
		if (nextIndex == inverseDir) 
		{
			//反対方向と一緒なのでスキップ。
			continue;
		}
		nextPosIndexList.push_back(nextIndex);
	}
	
	std::vector<Vector2> nexPosList;
	//候補３点が進行可能なエリアか調べる。
	for (auto& nextPosIndex : nextPosIndexList) 
	{
		//次に進む予定のマス。
		nextPosIndex += GetPositionIndex(m_position);

		bool isHit = false;

		const std::vector<Actor*>& obstacleList = m_sceneGame->GetObstacles();

		//障害物と当たり判定を取る。
		for (Actor* obstacle : obstacleList)
		{
			//ゲートを通れるステートか
			bool isPassGateState = (m_currentState == GetOutPrisonMode) || (m_currentState == ReturnPrisonMode);
			
			if (isPassGateState)
			{
				if (obstacle->GetHash() == std::hash<std::string>()("Gate")) 
				{ 
					//牢獄から出る時と、牢獄に戻る時はゲートを障害物としては判定しない。
					continue; 
				}
			}

			Vector2_Int obstaclePosIndex = GetPositionIndex(obstacle->GetPosition());
			if (obstaclePosIndex == nextPosIndex)
			{
				isHit = true;
				break;
			}

		}

		//衝突しなかった。
		if (!isHit)
		{
			Vector2 nextPos = { (float)nextPosIndex.x * SPRITE_SIZE , (float)nextPosIndex.y * SPRITE_SIZE };
			nextPos += {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
			//きちんとした座標に戻してリストに積む。

			nexPosList.push_back(nextPos);
		}

	}

	return nexPosList;
}

void EnemyBase::WayPointSerch()
{
	//次に向かう位置のリストを取ってくる。
	std::vector<Vector2> nexPosList = CanMoveNextWayPoint();

	//長さ取って、一番Playerと距離がちかくなるものを採用。
	float lens[3];
	if (nexPosList.size() != 1)
	{
		for (int i = 0; i < nexPosList.size(); i++)
		{
			lens[i] = (nexPosList[i] - m_target).Length();
		}
	}
	else
	{
		m_nextWayPoint = nexPosList[0];
		return;
	}

	//一番距離が近いwayPointを見つけだす。
	float min = *std::min_element(lens, lens + nexPosList.size());

	//該当のlengthを持っている要素を検索。
	for (auto nextPos : nexPosList)
	{
		float target2nextPos = (nextPos - m_target).Length();
		if (target2nextPos == min)
		{
			m_nextWayPoint = nextPos;
		}
	}

}

void EnemyBase::WayPointSerchForTweekMode()
{
	std::vector<Vector2> CanMoveList = CanMoveNextWayPoint();
	//ランダムで次に進行する場所を選ぶ。
	int nextMoveIndex = std::rand() % CanMoveList.size();
	//決定。
	m_nextWayPoint = CanMoveList[nextMoveIndex];
}

void EnemyBase::AnimationUpdate()
{
	//方向インデックス。
	DIRECTION directionIndex;
	//インデックスを決める。
	if (m_direction == EngineMath::LEFT)
	{
		directionIndex = Direction_Left;
	}
	else if (m_direction == EngineMath::RIGHT)
	{
		directionIndex = Direction_Right;
	}
	else if (m_direction == EngineMath::UP)
	{
		directionIndex = Direction_Up;
	}
	else if (m_direction == EngineMath::DOWN)
	{
		directionIndex = Direction_Down;
	}

	//インデックスを上げる。
	if (++m_animationWaitFrame > AnimationSpeed)
	{
		m_animationWaitFrame = 0;
		m_animationIndex++;
	}

	//現在どちらのアニメーションを流しているか判定。
	int animationFrame = m_animationIndex % 2;

	if (m_isTweek)
	{
		if (m_tweekTimer > TWEEK_TIME * 0.7f)
		{
			//チカチカ。
			m_currentAnimation = animationFrame + TweekAnimation + 1;
		}
		else
		{
			m_currentAnimation = animationFrame + TweekAnimation;
		}
	}
	else if (m_currentState == ReturnPrisonMode)
	{
		//方向に応じてハンドルインデックスを返す。
		m_currentAnimation = m_directionToEyeAnimHandleIndex[directionIndex];
	}
	else
	{
		m_currentAnimation = animationFrame + m_directionToNormalAnimHandleIndex[directionIndex];
	}
}

