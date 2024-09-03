#include "EnemyBullet.h"
#include"DxLib.h"

//インストラクタ
EnemyBullet::EnemyBullet() : animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	hitflag = false;
	animflag = false;
}

//デストラクタ
EnemyBullet::~EnemyBullet()
{
}

//初期化処理
void EnemyBullet::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	if (animation[0] == -1)
	{
		throw("爆弾の画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 20.0f;

	//初期画像の設定
	image = animation[0];

	//敵弾の速さの設定
	direction.y = -1.0f;

	//タイプ
	type = BULLET;

	
}

//更新処理
void EnemyBullet::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void EnemyBullet::Draw() const
{
	//敵弾の描画
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE);

	__super::Draw();
}

//終了時処理
void EnemyBullet::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//プレイヤーと当たったら
	if (hit_object->GetType() == PLAYER)
	{
		//当たった時の処理
		direction = 0.0f;
		animflag = true;
	}
}

//当たり判定フラグ取得処理
bool EnemyBullet::GetHitFlag()
{
	return hitflag;
}

//移動処理
void EnemyBullet::Movement()
{
	location.y += direction.y;
	//画面外に行ったら
	if (location.y >= 500 || location.y <= -20)
	{
		animflag = true;
	}
}

//アニメーション制御
void EnemyBullet::AnimationControl()
{
	if (animflag == true)
	{
		animation_count++;
		if (image == animation[0] && animation_count == 10)
		{
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
