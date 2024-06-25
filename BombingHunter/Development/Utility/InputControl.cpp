#include"InputControl.h"
#include"DxLib.h"

//静的メンバ変数定義
char InputControl::now_key[D_KEYCODE_MAX] = {};
char InputControl::old_key[D_KEYCODE_MAX] = {};

//更新処理
void InputControl::Update()
{
	//前回入力値を更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//現在入力値を更新
	GetHitKeyStateAll(now_key);
}

//キー取得系：押し続けているか？
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE &&
		old_key[key_code] == TRUE);
}

//キー取得系：押した瞬間か？
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == TRUE &&
		old_key[key_code] == FALSE);
}

//キー取得系：離した瞬間か？
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && (now_key[key_code] == FALSE &&
		old_key[key_code] == TRUE);
}

//キーコード範囲チェック
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}