//参考文献のサンプルコード、いずれ関数を自作する予定

/**
* @file Input.h
* @brief 入力に関する関数、定数の宣言
*/
#ifndef INPUT_H_
#define INPUT_H_



/** @brief マウスボタンの種類 */
enum MouseButton
{
	Left,		//!< 左
	Right,		//!< 右
	Center,		//!< 真ん中
	SideDown,
	SideUp
};

/**
* @brief Input機能初期化関数@n
* デバイスの入力取得に必要な初期化を行う
* ※InitEngineで実行されるので開発側が実行する必要はない
* @return 初期化結果(成功はtrue)
*/
bool InitInput();

/**
* @brief Input機能終了関数@n
* Input機能を終了させる@n
* ※EndEngineで実行されるので開発側が実行する必要はない
*/
void ReleaseInput();

/**
* @brief 入力情報の更新@n
* デバイスの入力情報の更新を行う@n
* 毎フレームに１度必ず実行する必要がある
*/
void UpdateInput();

/**
* @brief ボタンが押されているかの判定関数
* @retval true：押されている
* @retval false：押されていない
* @param[in] button 判定したいボタンの種類
*/
bool OnMousePush(MouseButton button_type);

/**
* @brief ボタンが押された瞬間の判定関数
* @retval true：押した瞬間
* @retval false：押した瞬間ではない
* @param[in] button 判定したいボタンの種類
*/
bool OnMouseDown(MouseButton button_type);

/**
* @brief ボタンを離した瞬間の判定関数
* @retval true：離した瞬間
* @retval false：瞬間ではない
* @param[in] button 判定したいボタンの種類
*/
bool OnMouseUp(MouseButton button_type);


#endif
