#pragma once
#include "../Base/SceneBase.h"
#include "SkyDome.h"
#include "CountDown.h"
#include "GameTime.h"
//#include "../../ADX2/ADX2Le.h"

#include "MyAirPlane.h"
#include "../../GameSystem/Camera.h"
#include "TpsCamera.h"
#include <SpriteFont.h>
#include "Shadow.h"
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
	void Update(const DX::StepTimer& stemTimer)override;
	// <描画関数>
	void Render()override;
	// <終了関数>
	void Finalize()override;

public:
	//あたり判定をまとめる関数
	void DetectCollisionManager();
	//画像の描画
	void SpriteRender();

	//CheckPointとのあたりはんていの関数
	void DetectCollisionMyAirPlaneToCheckPoint();
	//Meshとのあたりはんていの関数
	void DetectCollisionMyAirPlaneToMesh();

private:
	const float PLAYER_HEIGHT = 0.3f;

	//カメラクラスの作成
	std::unique_ptr<TpsCamera> m_camera;

	//プレイヤー
	std::unique_ptr<MyAirPlane> m_player;

	//スカイドーム
	std::unique_ptr<SkyDome>  m_skyDome;

	DX::StepTimer stept;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//コリジョンマネージャーの定義
	CollisionManager*				m_collisionManager;
	//時間
	std::unique_ptr<Time>			m_time;
	//チェックポイントクラスの定義
	std::unique_ptr<CheckPoint>		m_checkPoint;
	//カウントダウンクラスの定義
	CountDown*						m_count;
	//ゲームの時間クラスの定義
	GameTime*						m_gameTime;

	//
	bool m_node;
	//ゲームが始まっているのかのフラグ用変数
	bool m_startFlag;
	//ゲームの時間用変数
	float m_gameTimer;
	int m_couceCount;
	//Startしたかのフラグ
	bool m_start;
	//ゴールした時のフレームを少し回すよう変数
	int m_goalNum;
	//敵がゴールしたのかの処理(今は不要）
	//int m_goalRank;
	//ステージの番号
	int m_stageNum;

	//ゴールしているかのフラグ用変数
	bool m_goalFlag;

	//開始のカウントダウン
	float counter = 180.0f;
	//シーン変更用フラグ
	bool m_sceneFlag;

	bool m_isUpdateing;
	//当たり判定用メッシュ
	std::unique_ptr<CollisionMesh> m_stageMesh;
	//外側の当たり判定用メッシュ
	std::unique_ptr<CollisionMesh> m_stageMesh2;
	//コースのクラス作成用変数
	std::unique_ptr<Cource> m_cource;
	// サウンド
	//MyLibrary::ADX2Le* m_adx2le;	
	//影クラスの定義
	Shadow* m_shadow;
	// 音楽情報記憶用変数
	//CriAtomExPlaybackId m_criAtomExPlaybackId;	

	//プレイヤーとメッシュのあたり判定で生まれる高さ取得変数
	float m_playerHeight;
	//触手
	std::vector<DirectX::SimpleMath::Vector3> m_feelers;
	
	//DirectXGraphicsObjectへの参照
	DirectX11& m_directX = DirectX11::Get();

};