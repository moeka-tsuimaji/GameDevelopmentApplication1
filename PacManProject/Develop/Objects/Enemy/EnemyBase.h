#pragma once

#include"../GameObject.h"
#include"../../Utility/StageData.h"

//エネミー状態
enum eEnemyState
{
	TERRITORY,     //縄張り状態
	CHACE,         //追跡状態
	IJIKE,         //いじけ状態
	EYE,           //目玉状態
};
/// <summary>
/// エネミーベースクラス
/// </summary>
class EnemyBase : public GameObject
{
private:
	//進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

private:
	std::vector<int> move_animation;   //移動のアニメーション画像
	std::vector<int> eyes_animation;   //目玉のアニメーション画像
	Vector2D old_location;             //前回の位置
	Vector2D velocity;                //移動量
	eEnemyState enemy_state;           //エネミー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	float animation_time;              //アニメーション時間
	int animation_count;               //アニメーション添え字
	int eyes_animation_count;          //目玉アニメーション添え字
	ePanelID old_panel;						// 前回パネル情報
	bool is_destroy;                   //死んだ状態になったか？

	//移動アニメーションの順番
	const int animation_num[2] = { 0, 1, };

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// エネミーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// エネミーが死んだかどうか確認する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	bool GetDestroy() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	void AnimationControl(float delta_second);
};