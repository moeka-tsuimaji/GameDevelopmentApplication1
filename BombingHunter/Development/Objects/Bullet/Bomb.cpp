#include "Bomb.h"
#include"DxLib.h"

Bomb::Bomb() : animation_count(0), b_speed(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
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
	
}

void Bomb::Movement()
{
	location.y += b_speed;
}

void Bomb::AnimationControl()
{

}