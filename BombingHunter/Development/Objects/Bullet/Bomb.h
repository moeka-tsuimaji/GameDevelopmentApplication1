#pragma once

#include"../GameObject.h"
class Bomb : public GameObject
{
private:
	int animation[4];
	int animation_count;
	Vector2D direction;    //進行方向
	float b_speed;         //弾の速さ
	bool hitflag;          //当たったかどうか
	bool animflag;         //アニメーションフラグ

public:
	Bomb();
	virtual ~Bomb();

	virtual void Initialize() override;     //初期化処理
	virtual void Update() override;          //更新処理
	virtual void Draw() const override;      //描画処理
	virtual void Finalize() override;        //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	//当たり判定フラグ取得処理
	bool GetHitFlag();

private:
	void Movement();             //移動処理
	void AnimationControl();     //アニメーション制御
};
