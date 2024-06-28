#include "Bomb.h"
#include"DxLib.h"

Bomb::Bomb() : animation_count(0), direction(0.0f), b_speed(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	hitflag = false;
	animflag = false;
}

Bomb::~Bomb()
{
}

void Bomb::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	if (animation[0] == -1)
	{
		throw("”š’e‚Ì‰æ‘œ‚ª‚ ‚è‚Ü‚¹‚ñ\n");
	}

	radian = DX_PI_F / 2;

	box_size = 64.0f;

	image = animation[0];

	b_speed = 2.0f;

	direction.y = b_speed;

	type = BOMB;
}

void Bomb::Update()
{
	Movement();

	AnimationControl();

}

void Bomb::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE);

	__super::Draw();
}

void Bomb::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

void Bomb::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == ENEMY)
	{
		//“–‚½‚Á‚½Žž‚Ìˆ—
		direction.y = 0.0f;
		animflag = true;
	}
}

bool Bomb::GetHitFlag()
{
	return hitflag;
}

void Bomb::Movement()
{
	location += direction;
	if (location.y >= 400)
	{
		animflag = true;
	}
}

void Bomb::AnimationControl()
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