#pragma once

#include"../GameObject.h"

class Enemy : public GameObject
{
private:
	int animation[2];      //アニメーション画像
	int animation_count;   //アニメーション時間
	Vector2D direction;    //進行方向
	bool shotflag;         //弾を撃つ判定
	int flag_count;        //フラグのカウント
	bool hitflag;          //当たったかどうか

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;     //初期化処理
	virtual void Update() override;         //更新処理
	virtual void Draw() const override;     //描画処理
	virtual void Finalize() override;       //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	bool GetFlag();
	bool GetHitFlag();
private:
	void Movement();           //移動処理
	void AnimationControl();   //アニメーション制御
};