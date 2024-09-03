#include "Bomb.h"
#include"DxLib.h"

//コンストラクタ
Bomb::Bomb() : animation_count(0), direction(0.0f), b_speed(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	hitflag = false;
	animflag = false;
}

//デストラクタ
Bomb::~Bomb()
{
}

//初期化処理
void Bomb::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");

	if (animation[0] == -1)
	{
		throw("爆弾の画像がありません\n");
	}

	//向きの設定
	radian = DX_PI_F / 2;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//爆弾の速さの設定
	b_speed = 2.0f;

	//爆弾の進む向きの設定
	direction.y = b_speed;

	//タイプ
	type = BOMB;
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();

}

//描画処理
void Bomb::Draw() const
{
	//プレイヤーの弾の描画
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE);

	__super::Draw();
}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//敵と当たったら
	if (hit_object->GetType() == ENEMY)
	{
		//当たった時の処理
		direction.y = 0.0f;
		animflag = true;
	}
}

//当たり判定フラグ取得処理
bool Bomb::GetHitFlag()
{
	return hitflag;
}

//移動処理
void Bomb::Movement()
{
	location += direction;
	//画面外に行ったら
	if (location.y >= 400)
	{
		animflag = true;
	}
}

//アニメーション制御
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