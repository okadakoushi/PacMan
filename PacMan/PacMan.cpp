#include "stdafx.h"
#include "PacMan.h"
#include "ItemBase.h"
#include "EnemyBase.h"
#include "SceneGame.h"
#include "RectCollision.h"

PacMan::PacMan(SceneBase* sceneBase) : Actor(sceneBase, "PacMan", 0, RectCollision::EnCollisionType_Dynamic)
{
	m_sceneGamePtr = dynamic_cast<SceneGame*>(sceneBase);
}

void PacMan::Init()
{
	LoadDivGraph("Assets/player_div.bmp", AniamtionNum, 5, 3, 24, 24, m_drawHandle);
	m_position = PLAYER_RESPAWN_POINT;
}

void PacMan::Update()
{
	if (m_isDying) { return; }

	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (Key == 0) 
	{
		//キー入力なし。先行入力されていたキーを使用する。
		Key = m_bufferedInput;
		m_bufferedInput = 0;
	}

	//前フレームで移動したベクトルを更新。
	m_frontFrameMoved = m_movedVector;

	if (Key & PAD_INPUT_UP) 
	{
		m_movedVector = { 0, -MOVE_SPEED };
		m_bufferedInput = 0;
	}
	else if (Key & PAD_INPUT_DOWN) 
	{
		m_movedVector = { 0, MOVE_SPEED };
		m_bufferedInput = 0;
	}
	else if (Key & PAD_INPUT_RIGHT)
	{
		m_movedVector = { MOVE_SPEED, 0 };
		m_bufferedInput = 0;
	}
	else if (Key & PAD_INPUT_LEFT) 
	{
		m_movedVector = { -MOVE_SPEED, 0 };
		m_bufferedInput = 0;
	}

	//キーの方向について移動できるのかを判定。
	if (CheckHitObstacle())
	{
		//衝突したので、この移動は不可能。
		//前フレームと同じ移動を行う。
		m_movedVector = m_frontFrameMoved;
		m_bufferedInput = Key;
	}

	m_position += Vector2(m_movedVector.x, m_movedVector.y);

	MoveAnimationUpdate();
}

void PacMan::MoveAnimationUpdate()
{
	if (++m_animationWaitFrame > AnimationSpeed)
	{
		m_animationWaitFrame = 0;
		m_animationIndex++;
		m_animationIndex %= moveAnimatiomEnd + 1;
	}
}

void PacMan::OnCollision(Actor* actor)
{
	if (actor->GetHash() == std::hash<std::string>()("Wall"))
	{
		//wallにヒットしたので、仮動かしはなかったことに。
		m_position -= m_movedVector;
	}
	else if (actor->GetHash() == std::hash<std::string>()("Cookie"))
	{
		//actor->ItemBaseに再解釈キャスト。
		ItemBase* cookie = dynamic_cast<ItemBase*>(actor);
		if (cookie != nullptr) 
		{
			cookie->HitEffect(this);
		}
	}
	else if (actor->GetHash() == std::hash<std::string>()("PowerCookie"))
	{
		ItemBase* pCookie = dynamic_cast<ItemBase*>(actor);
		if (pCookie != nullptr)
		{
			pCookie->HitEffect(this);
		}
	}
	else if (actor->GetHash() == std::hash<std::string>()("Fruit"))
	{
		ItemBase* fruit = dynamic_cast<ItemBase*>(actor);
		if (fruit != nullptr)
		{
			fruit->HitEffect(this);
		}
	}
	else if (actor->GetHash() == std::hash<std::string>()("Enemy"))
	{
		EnemyBase* enemy = dynamic_cast<EnemyBase*>(actor);
		if (enemy != nullptr)
		{
			enemy->HitEffect(this);
		}
	}
	
}

void PacMan::Draw()
{
	//上下逆なのでマイナス。
	m_spirte.Draw({m_position.x + 12, m_position.y + 12 }, 1.5, atan2f(m_movedVector.Normalized().x, -(m_movedVector.Normalized().y)), m_drawHandle[m_animationIndex]);
}

void PacMan::Death()
{
	m_isDying = true;
	m_animationIndex = 0;
	m_animationWaitFrame = 0;
}

bool PacMan::PlayDeadAnim()
{
	int wait = DEAD_ANIMATION_SPEED;

	if (m_animationIndex == 0 || m_animationIndex == AniamtionNum)
	{
		//先端、終端に関しては、60フレーム待つ。
		wait = DEAD_FIRST_EDN_ANIMATION_SPEED;
	}

	if (++m_animationWaitFrame > wait)
	{
		m_animationIndex++;
		m_animationWaitFrame = 0;
	}

	if (m_animationIndex == AniamtionNum + 1)
	{
		return true;
	}
	
	return false;
}

void PacMan::ResetParams()
{
	m_position = PLAYER_RESPAWN_POINT;
	m_bufferedInput = 0;
	m_movedVector = 0.0f;
	m_isDying = false;
}

bool PacMan::CheckHitObstacle()
{
	const std::vector<Actor*>& m_obstacleList = m_sceneGamePtr->GetObstacles();
	for (Actor* obstacle : m_obstacleList)
	{
		if (GetCollision().CheckHitAABB(GetPosition() + Vector2(m_movedVector.x, m_movedVector.y), {SPRITE_SIZE, SPRITE_SIZE}, obstacle->GetPosition(), { SPRITE_SIZE, SPRITE_SIZE }))
		{
			return true;
		}
	}
	//衝突しない。
	return false;
}
