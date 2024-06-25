#include"Enemy.h"
#include"DxLib.h"
#include"stdlib.h"
#include"time.h"

Enemy::Enemy() : animation_count(0), direction(0.0f), flag_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	shotflag = false;
}

Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize()
{
	srand((unsigned int)time(NULL));
	int RandomSpeed =  1 + rand() % 3;

	//画像の読み込み
	if (location.y >= 390.0f)
	{
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	}
	else if (location.y >= 290.0f)
	{
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	}
	else if (location.y >= 190.0f)
	{
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
	}
	if (location.x == 640.0f)
	{
		direction.x = -1.0f;//-RandomSpeed;
	}
	else
	{
		direction.x = 1.0f;//RandomSpeed;
	}

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	type = ENEMY;

}

//更新処理
void Enemy::Update()
{
	flag_count++;
	if (flag_count >= 180)
	{
		if (shotflag == false)
		{
			shotflag = true;
			flag_count = 0;
		}
	}
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();

}

//描画処理
void Enemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOMB)
	{
		//当たった時の処理
		direction = 0.0f;
	}
}

bool Enemy::GetFlag()
{
		bool flag = shotflag;
		shotflag = false;
		return flag;
	
}
//移動処理
void Enemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	/*if (((location.x + direction.x) < box_size.x) ||
		(640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}*/

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Enemy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		animation_count = 0;
		{
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
		}
	}
}