#pragma once

#include"../GameObject.h"
class EnemyBullet : public GameObject
{
private:
	int animation[4];
	int animation_count;
	Vector2D direction;
	float speed;
	bool hitflag;          //当たったかどうか
	bool animflag;

public:
	EnemyBullet();
	virtual ~EnemyBullet();

	virtual void Initialize() override;     //初期化処理
	virtual void Update() override;          //更新処理
	virtual void Draw() const override;      //描画処理
	virtual void Finalize() override;        //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	bool GetHitFlag();

private:
	void Movement();
	void AnimationControl();
};

