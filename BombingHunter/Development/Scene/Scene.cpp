#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Bullet/Bomb.h"
#include"../Objects/Bullet/EnemyBullet.h"
#include"../Utility/InputControl.h"
#include<stdlib.h>
#include"DxLib.h"

#define CREATE_SPAN (120)

//コンストラクタ
Scene::Scene() : objects(), NumberImage()
{
	gh = NULL;
	create_count = NULL;
	BackGround_sound = NULL;
	gametime = NULL;
	TimerImage = NULL;
	ScoreImage = NULL;
	HighScoreImage = NULL;
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
	//背景画像読み込み
	gh = LoadGraph("Resource/Images/BackGround.png");
	//メインBGM読み込み
	BackGround_sound = LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	//タイマー画像読み込み
	TimerImage = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	//スコア画像読み込み
	ScoreImage = LoadGraph("Resource/Images/Score/font-21.png");
	//ハイスコア画像読み込み
	HighScoreImage = LoadGraph("Resource/Images/Score/hs.png");
	//数字画像読み込み
	 NumberImage[0] = LoadGraph("Resource/Images/Score/0.png");
	 NumberImage[1] = LoadGraph("Resource/Images/Score/1.png");
	 NumberImage[2] = LoadGraph("Resource/Images/Score/2.png");
	 NumberImage[3] = LoadGraph("Resource/Images/Score/3.png");
	 NumberImage[4] = LoadGraph("Resource/Images/Score/4.png");
	 NumberImage[5] = LoadGraph("Resource/Images/Score/5.png");
	 NumberImage[6] = LoadGraph("Resource/Images/Score/6.png");
	 NumberImage[7] = LoadGraph("Resource/Images/Score/7.png");
	 NumberImage[8] = LoadGraph("Resource/Images/Score/8.png");
	 NumberImage[9] = LoadGraph("Resource/Images/Score/9.png");

	create_count = 0;
	//ゲーム時間の初期化
	gametime = TIMELIMET;
}

//更新処理
void Scene::Update()
{ 
	//BGMの再生
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//敵の生成カウント
	this->create_count++;

	//敵の弾の生成カウント
	int create_count = 0;
	std::vector<Vector2D> enemy_location;

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
			obj->Update();
			//オブジェクトがENEMYだったら
			if (obj->GetType() == ENEMY)
			{
				//弾生成のフラグを受け取ったら
				if (dynamic_cast<Enemy*>(obj)->GetFlag())
				{
					create_count++;
					enemy_location.push_back((obj)->GetLocation());
				}

			}
	}
	    //カウント分だけ敵の弾を生成する
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
			//敵の当たり判定
			if (objects[i]->GetType() == ENEMY)
			{
				if (dynamic_cast<Enemy*>(objects[i])->GetHitFlag())
				{
					objects.erase(objects.begin() + i);
				}
			}
			//敵の弾の当たり判定
			if (objects[i]->GetType() == BULLET)
			{
				if (dynamic_cast<EnemyBullet*>(objects[i])->GetHitFlag())
				{
					objects.erase(objects.begin() + i);
				}
			}
			//弾の当たり判定
			if (objects[i]->GetType() == BOMB)
			{
				if (dynamic_cast<Bomb*>(objects[i])->GetHitFlag())
				{
					objects.erase(objects.begin() + i);
				}
			}
		}
	}

	//2秒に1回敵を生成する
	if (this->create_count >= CREATE_SPAN)
	{
		int RandomEnemy = GetRand(3);
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

		//ランダムに敵を生成する
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

	//時間カウント
	if (gametime == 0)
	{
		StopSoundMem(BackGround_sound);
		Finalize();
	}
	else
	{
		gametime--;
	}
}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawExtendGraph(0, 0, 640, 480, gh, FALSE);
	//タイマー画像の描画
	DrawExtendGraph(10, 440, 50, 480, TimerImage, TRUE);
	//スコアの描画
	DrawExtendGraph(150, 440, 240, 480, ScoreImage,TRUE);
	//ハイスコアの描画
	DrawExtendGraph(390, 440, 490, 480, HighScoreImage, TRUE);
	//時間の描画
	DrawExtendGraph(50, 440, 80, 480, NumberImage[gametime / 150 / 10], TRUE);  //10の位
	DrawExtendGraph(80, 440, 110, 480, NumberImage[gametime / 150 % 10], TRUE); //1の位

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
