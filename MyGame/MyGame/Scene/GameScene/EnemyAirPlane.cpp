#include "EnemyAirPlane.h"
#include "../../Collison/DebugBox.h"

#define	MAX_DATA		3
#define MAX_PARAMS		4

#define	MAX_SPEED_DATA			2
#define MAX_SPEED_PARAMS		3


EnemyAirPlane::EnemyAirPlane()
{
}

EnemyAirPlane::~EnemyAirPlane()
{
}

void EnemyAirPlane::Initilize(Shadow* shadow)
{
	m_shadow = shadow;
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

	CreateResources();

	m_translation = DirectX::SimpleMath::Vector3(0, 0, 0);
	m_shadow->Initialize();

	float AngleSet[MAX_DATA][MAX_PARAMS] = {
		0.8,	0.0f,	0.0f,	0.25f,
		0.0f,	0.8f,   0.0f,	0.5f,
		0.0f,	0.0f,	0.9f,	0.75f,


	};

	float SpeedSet[MAX_SPEED_DATA][MAX_SPEED_PARAMS] = {
		0.3f,	0.8f,	0.5f,
		0.8f,	0.3f,	0.2f,

	};

	// ニューラルネットワークオブジェクトを生成する

	// ニューラルネットワークを初期化する(入力層:3、隠れ層:3、出力層:1)
	// Initialize neural network object
	m_theAngleBrain.Initialize(3, 3, 1);

	// 学習率を設定する
	// Setup learning rate
	m_theAngleBrain.SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	m_theAngleBrain.SetMomentum(true, 0.8);

	double	error = 1.0;
	int		count = 0;

	// 機械学習する
	while (error > 0.01 && count < 10000) 
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA; i++) 
		{
			//左
			//左側に入るか
			//0.0(いない)
			//0.8(いる)
			m_theAngleBrain.SetInput(0, AngleSet[i][0]);
			//真ん中
			//真ん中に入るか
			//0.0(いない)
			//0.8(いる)
			m_theAngleBrain.SetInput(1, AngleSet[i][1]);
			//右
			//右に入るか
			//0.0(いない)
			//0.8(いる)
			m_theAngleBrain.SetInput(2, AngleSet[i][2]);
		
			// 攻撃
			m_theAngleBrain.SetDesiredOutput(0, AngleSet[i][3]);

			// 前方伝播する(Feed forward)
			m_theAngleBrain.FeedForward();
			// 誤差を計算する(Calculate error)
			error += m_theAngleBrain.CalculateError();
			// 誤差逆伝播する(Back propagate)
			m_theAngleBrain.BackPropagate();
		}
		// 誤差を計算する
		error = error / MAX_DATA;
	}


	// ニューラルネットワークオブジェクトを生成する

	// ニューラルネットワークを初期化する(入力層:3、隠れ層:3、出力層:1)
	// Initialize neural network object
	m_theSpeedBrain.Initialize(3, 3, 1);

	// 学習率を設定する
	// Setup learning rate
	m_theSpeedBrain.SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	m_theSpeedBrain.SetMomentum(true, 0.8);
	
	
	error = 1.0;
	
	count = 0;

	// 機械学習する
	while (error > 0.01 && count < 10000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA; i++)
		{
			//左
			//左側に入るか
			//0.0(いない)
			//0.8(いる)
			m_theSpeedBrain.SetInput(0, SpeedSet[i][0]);
			//真ん中
			//真ん中に入るか
			//0.0(いない)
			//0.8(いる)
			m_theSpeedBrain.SetInput(1, SpeedSet[i][1]);

			// 攻撃
			m_theSpeedBrain.SetDesiredOutput(0, SpeedSet[i][2]);

			// 前方伝播する(Feed forward)
			m_theSpeedBrain.FeedForward();
			// 誤差を計算する(Calculate error)
			error += m_theSpeedBrain.CalculateError();
			// 誤差逆伝播する(Back propagate)
			m_theSpeedBrain.BackPropagate();
		}
		// 誤差を計算する
		error = error / MAX_DATA;
	}

	m_box.c = m_translation;
	m_box.r = DirectX::SimpleMath::Vector3(0.5, 2.0, 0.5);


}

void EnemyAirPlane::Update(DX::StepTimer& timer)
{
	Teramoto::Object3D::Update();

	if (timer.GetFrameCount() % 60 == 0)
	{
		// 入力データをニューラルネットワークにセットする
		m_theAngleBrain.SetInput(0, 0.0);
		m_theAngleBrain.SetInput(1, 0.0);
		m_theAngleBrain.SetInput(2, 0.8);

		// ニューラルネットワークに問い合わせる
		m_theAngleBrain.FeedForward();


		// 入力データをニューラルネットワークにセットする
		m_theSpeedBrain.SetInput(0, 0.8);
		m_theSpeedBrain.SetInput(1, 0.3);

		// ニューラルネットワークに問い合わせる
		m_theSpeedBrain.FeedForward();

		int i = 0;
	}

	float result = m_theAngleBrain.GetOutput(0);
	float result2 = m_theSpeedBrain.GetOutput(0);

	int i = 0;

	m_angle = result;

	//Teramoto::Object3D::SetAngle(m_angle);
	//Teramoto::Object3D::SetTranslation(m_translation);


}

void EnemyAirPlane::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//モデルの描画
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
	//DebugBox* playerdebugbox = new DebugBox(m_directX.GetDevice().Get(), m_box.c, m_box.r);
	//playerdebugbox->Draw(m_directX.GetContext().Get(), *m_directX.Get().GetStates(), m_world, view, proj);
	m_shadow->Render(view, proj, this, 0.3f);

}

void EnemyAirPlane::CreateResources()
{
	//モデルの設定
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Player.cmo", *m_directX11.Get().GetEffect());

}
