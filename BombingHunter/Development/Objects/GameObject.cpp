#include"GameObject.h"
#include"DxLib.h"

#define D_PIVOT_CENTER
//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	radian(0.0),
	image(NULL),
	sound(NULL),
	type(0)
{

}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{
	
}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{

}

//終了時処理
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
}

//位置情報取得所理
Vector2D GameObject::GetLocation() const
{
	return location;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//当たり判定取得処理
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//タイプ取得処理
int GameObject::GetType() const
{
	return type;
}