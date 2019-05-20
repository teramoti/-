//------------------------//------------------------
// Contents(処理内容) SceneBase.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 08 / 13
// last updated (最終更新日) 2018 / 11 / 01
//------------------------//------------------------


// ヘッダファイルのインクルード ===============================================

#include "SceneBase.h"

#include "../SceneManager/SceneManager.h"



// メンバ関数の定義 ===========================================================
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager">登録されているシーンマネージャー</param>
SceneBase::SceneBase(SceneManager* sceneManager,bool SceneFlag)
	: m_sceneManager(sceneManager)
{

}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	
}