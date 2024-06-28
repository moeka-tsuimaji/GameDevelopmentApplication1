#include "EnemyBullet.h"
#include"DxLib.h"

EnemyBullet::EnemyBullet() : animation_count(0), speed(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	hitflag = false;
	animflag = false;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	if (animation[0] == -1)
	{
		throw("”š’e‚Ì‰æ‘œ‚ª‚ ‚è‚Ü‚¹‚ñ\n");
	}

	radian = 0.0f;

	box_size = 20.0f;

	image = animation[0];

	direction.y = -1.0f;

	type = BULLET;

	
}

void EnemyBullet::Update()
{
	Movement();

	AnimationControl();
}

void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE);

	__super::Draw();
}

void EnemyBullet::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == PLAYER)
	{
		//“–‚½‚Á‚½Žž‚Ìˆ—
		direction = 0.0f;
		animflag = true;
	}
}

bool EnemyBullet::GetHitFlag()
{
	return hitflag;
}

void EnemyBullet::Movement()
{
	location.y += direction.y;
	if (location.y >= 500 || location.y <= -20)
	{
		animflag = true;
	}
}

void EnemyBullet::AnimationControl()
{
	if (animflag == true)
	{
		animation_count++;
		if (image == animation[0] && animation_count == 10)
		{
			radian = 0.0f;
			image = animation[1];
			animation_count = 0;
		}
		else if (image == animation[1] && animation_count == 10)
		{
			image = animation[2];
			animation_count = 0;
		}
		else if (image == animation[2] && animation_count == 10)
		{
			image = animation[3];
			animation_count = 0;
		}
		else
		{
			hitflag = true;
		}
	}
}
