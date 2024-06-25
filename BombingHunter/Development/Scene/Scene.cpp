#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Bullet/Bomb.h"
#include"../Objects/Bullet/EnemyBullet.h"
#include"../Utility/InputControl.h"
#include<stdlib.h>
#include"DxLib.h"

#define D_PIVOT_CENTER
#define CREATE_SPAN (120)

//コンストラクタ
Scene::Scene() : objects()
{
	gh = NULL;
	create_count = NULL;
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
	gh = LoadGraph("Resource/Images/BackGround.png");
	create_count = 0;
}

//更新処理
void Scene::Update()
{ 
	this->create_count++;

	int create_count = 0;
	std::vector<Vector2D> enemy_location;

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
		if (obj->GetType() == ENEMY)
		{
			if (dynamic_cast<Enemy*>(obj)->GetFlag())
			{
				create_count++;
				enemy_location.push_back((obj)->GetLocation());
			}
		}
	}

		for (int i = 0; i < create_count; i++)
		{
			CreateObject<EnemyBullet>(enemy_location[i]);
		}
		enemy_location.clear();

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//2秒に1回敵を生成する
	if (this->create_count >= CREATE_SPAN)
	{
		int RandomEnemy = GetRand(2);
		int randomlocationflag = GetRand(1);
		float x;
		if (randomlocationflag == 1)
		{
			x = 640.0f;
		}
		else
		{
			x = 0.0f;
		}


		switch (RandomEnemy)
		{
		case 0:
			CreateObject<Enemy>(Vector2D(x, 400.0f));
			break;
		case 1:
			CreateObject<Enemy>(Vector2D(x, 300.0f));
			break;
		case 2:
			CreateObject<Enemy>(Vector2D(x, 200.0f));
			break;
		}
		this->create_count = 0;
	}

	//弾の生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(objects[0]->GetLocation().x, objects[0]->GetLocation().y + 50.0f));
	}

}

//描画処理
void Scene::Draw() const
{
	DrawExtendGraph(0, 0, 640, 480, gh, FALSE);
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//オブジェクトリスト内が空なら、処理を終了する
	if (objects.empty())
	{
		return;
	}

	//オブジェクトリスト内のオブジェクトを解放する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定を取る）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	
	if (a->GetType() != b->GetType())
	{
		//距離より大きさが大きい場合、Hit判定とする
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//当たったことをオブジェクトに通知する
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
	
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();
	//左上頂点座標を取得する
	Vector2D a_upper_left = a->GetLocation() + a->GetBoxSize();
	Vector2D b_upper_left = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
		
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER