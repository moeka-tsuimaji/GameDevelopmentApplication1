#pragma once

#define D_KEYCODE_MAX (256)  //キー入力最大値

//入力制御クラス（メンバは静的で所有する）
class InputControl
{
	//基本的にメンバ変数はプライベート
private:
	static char now_key[D_KEYCODE_MAX];      //現在の入力値
	static char old_key[D_KEYCODE_MAX];      //前回の入力値

	//関数はパブリック
public:
	static void Update();         //更新処理

	//キー入力取得系
	static bool GetKey(int key_code);        //押し続けているか？
	static bool GetKeyDown(int key_code);    //押した瞬間か？
	static bool GetKeyUp(int key_code);      //離した瞬間か？

	//外部公開の必要性が無ければ、プライベート
private:
	static bool CheckKeyCodeRange(int key_code);     //キーコード範囲チェック
};