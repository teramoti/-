#pragma once
#include "../Base/SceneBase.h"
#include "SkyDome.h"
#include "CountDown.h"
#include "GameTime.h"
#include "../../ADX2/ADX2Le.h"
//#include "../../GameSystem/Camera.h"
#include "TestPlayer.h"
#include "../../GameSystem/Camera.h"
#include "../../GameSystem/TpsCamera.h"
#include <SpriteFont.h>

#include "SpriteBatch.h"
#include "Cource.h"
#include "CheckPoint.h"
#include "Time.h"
#include "../../Collison/CollisionMesh.h"
#include "../../Collison/MyCollisionManager.h"
#include "../../Utillity/DirectX11.h"
class GameScene : public SceneBase
{
public:
	GameScene(SceneManager* scenemaneger);
	~GameScene();
public:
	// <初期化関数>
	void Initialize() override;
	// <更新関数>
	void Update(DX::StepTimer& stemTimer)override;
	// <描画関数>
	void Render()override;
	// <終了関数>
	void Finalize()override;

public:
	void HitManager();
	void SpriteRender();

	void FileLoad();
	void StageCheckPoint();//1ステージのチェックポイント
	void StageCollision();//1ステージのチェックポイント

private:
	const float PLAYER_RISE = 5.0f;
	//カメラ
	ID3D11Device* m_device;//デバイス取得用変数
	ID3D11DeviceContext* m_context;//コンテキスト取得変数
	std::unique_ptr<TpsCamera> m_Camera;//カメラクラスの作成

	//プレイヤー
	std::unique_ptr<TestPlayer> m_player;

	//スカイドーム
	std::unique_ptr<SkyDome>  m_skyDome;

	DX::StepTimer stept;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	CollisionManager*				m_CollisionManager;
	//時間
	std::unique_ptr<Time>			m_time;
	//チェックポイント
	std::unique_ptr<CheckPoint>		m_CheckPoint;

	CountDown*						m_Count;
	GameTime*						m_GameTime;
	//GameGoal* m_Goal;
	bool m_Node;
	bool m_startFlag;//ゲームが始まっているのかのフラグ用変数
	float m_GameTimer;//ゲームの時間用変数
	int m_CouceCount;
	bool m_start;//始まっているかのbool
	int m_GoalNum;//ゴールした時のフレームを少し回すよう変数
	int m_GoalRank;//敵がゴールしたのかの処理(今は不要）
	int m_StageNum;//ステージの番号

	bool m_goalFlag;//ゴールしているかのフラグ用変数

	//開始のカウントダウン
	float counter = 180.0f;
	bool m_SceneFlag;//シーン変更用フラグ

	std::unique_ptr<CollisionMesh> m_stageMesh;//当たり判定用メッシュ
	std::unique_ptr<CollisionMesh> m_stageMesh2;//外側の当たり判定用メッシュ
	std::unique_ptr<Cource> m_cource;//コースのクラス作成用変数
	MyLibrary::ADX2Le* m_adx2le;	// サウンド


	CriAtomExPlaybackId m_criAtomExPlaybackId;	// 音楽情報記憶用変数

	DirectX11& m_directX = DirectX11::Get();

};