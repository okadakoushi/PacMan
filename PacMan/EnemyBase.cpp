#include "stdafx.h"
#include "EnemyBase.h"
#include "PacMan.h"

EnemyBase::EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr) : 
	Actor(sceneBase, tag, prio, RectCollision::EnCollisionType_Dynamic),
	m_packManPtr(packPtr) 
{
	//tweekSpriteは共通のため、ここで初期化しておく。
	//m_tweekSprite.Init("Assets/weak.bmp");
	m_sceneGame = dynamic_cast<SceneGame*>(sceneBase);
}

void EnemyBase::Update()
{	
	if (m_isArrive) {

		if ((int)m_position.x % 24 + 12 != 0 || (int)m_position.y % 24 != 0)
		{
			m_position = { floor(m_position.x / 24) * 24 + 12, floor(m_position.y / 24) * 24 };
		}

		if (m_currentState != TweekMode)
		{
			//ウェイポイントを検索する。
			WayPointSerch();
		}
		else
		{
			if (!m_callTweekEvent)
			{
				//いじけモード時、移動パラメーターを変更する。
				m_direction *= -1;
				m_callTweekEvent = true;
				m_currentMoveSpeed = TWEEK_MOVE_SPEED;
			}

			//いじけモード用の移動。
			WayPointSerchForTweekMode();

			//いじけモードが終了しているか。
			if (m_tweekTimer > TWEEK_TIME)
			{
				m_currentState = ChaseMode;
				m_currentMoveSpeed = STANDARD_MOVE_SPEED;
				m_tweekTimer = 0.0f;
				m_callTweekEvent = false;
			}
		}

		//方向を計算。
		m_direction = (GetPositionIndex(m_nextWayPoint) - GetPositionIndex(GetPosition())).Normalized();
		m_isArrive = false;
	}

	//次のwayPointまで移動させる。
	m_position += m_direction * m_currentMoveSpeed;

	if (m_nextWayPoint == m_position)
	{
		//到着している。
		m_isArrive = true;
	}

	if (m_currentState == TweekMode)
	{
		m_tweekTimer += GameTime()->GetDeltaTime();
	}

	AnimationUpdate();
}

void EnemyBase::Draw()
{
	Actor::m_spirte.Draw({ m_position.x + 12, m_position.y + 12 }, 1.5, 0, m_drawHandle[m_currentAnimation]);


#ifdef DEBUG
	DrawLine(m_position.x + 12, m_position.y + 12, m_position.x + 12 + m_direction.x * 100, m_position.y + 12 + m_direction.y * 100, GetColor(255, 0, 0));
#endif
}

void EnemyBase::HitEffect(Actor* actor)
{
	if (m_currentState == TweekMode)
	{
		//いじけ
		Death();
	}
	else
	{
		//普通
		PacMan* pacman = dynamic_cast<PacMan*>(actor);
		if (pacman != nullptr && m_currentState != ReturnPrisonMode)
		{
			pacman->Death();
		}
	}
}

void EnemyBase::Death()
{
	m_currentState = ReturnPrisonMode;
	m_isArrive = true;
	m_tweekTimer = 0.0f;
	m_callDeadEvent = false;
	m_callTweekEvent = false;
	m_currentMoveSpeed = STANDARD_MOVE_SPEED;
}

std::vector<Vector2> EnemyBase::CanMoveNextWayPoint()
{
	//どれか4点。
	const Vector2 NEXT_POSITION_LIST[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	Vector2 inverseDir = m_direction * -1;

	//進む３点
	std::vector<Vector2> nextPosIndexList;
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
		nextPosIndex += Vector2(GetPositionIndex(GetPosition()).x, GetPositionIndex(GetPosition()).y);

		bool isHit = false;

		const std::vector<Actor*>& m_obstacleList = m_sceneGame->GetObstacles();

		//障害物と当たり判定を取る。
		for (Actor* obstacle : m_obstacleList)
		{
			if (m_currentState == GetOutPrisonMode || m_currentState == ReturnPrisonMode && obstacle->GetHash() == std::hash<std::string>()("Gate"))
			{
				continue;
			}

			Vector2 obstaclePosIndex = GetPositionIndex(obstacle->GetPosition());
			if (obstaclePosIndex == nextPosIndex)
			{
				isHit = true;
				break;
			}

		}

		//衝突しなかった。
		if (!isHit)
		{
			Vector2 nextPos = { nextPosIndex.x * SPRITE_SIZE , nextPosIndex.y * SPRITE_SIZE };
			nextPos += {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
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
		if ((nextPos - m_target).Length() == min)
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
	if (++m_animationWaitFrame > AnimationSpeed)
	{
		m_animationWaitFrame = 0;
		m_animationIndex++;
	}

	//汚すぎる todo:リファクタリング。
	if (m_currentState == TweekMode)
	{
		if (m_tweekTimer > TWEEK_TIME * 0.8f)
		{
			m_currentAnimation = m_animationIndex % 2 + TweekAnimation + 1;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + TweekAnimation;
		}
	}
	else if (m_direction.x == -1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = LeftEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + LeftAnimation;
		}
	}
	else if (m_direction.x == 1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = RightEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + RightAnimation;
		}
	}
	else if (m_direction.y == -1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = UpEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + UpAnimation;
		}
	}
	else if (m_direction.y == 1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = DownEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + DownAnimatiom;
		}
	}

}

