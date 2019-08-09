//----------------------------------------
/// <summary>
///	コースのクラス
/// GS2 寺本 啓志
/// </summary>
//----------------------------------------
#include "TitleSkyDome.h"



TitleSkyDome::TitleSkyDome()
{
	
	
}
TitleSkyDome::~TitleSkyDome()
{
	m_model.reset();
}


void TitleSkyDome::Initilize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");


	CreateResource();

}

void TitleSkyDome::Update()
{
	Teramoto::Object3D::Update();

}

void TitleSkyDome::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\TitleSkyDome.cmo", *m_directX11.Get().GetEffect());
}


void TitleSkyDome::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	SetLight();
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}
void TitleSkyDome::SetLight()
{
	auto SetLight = [&](DirectX::IEffect* effect)
	{
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights)
		{
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f));
			// アンビエント色を設定する 
			lights->SetLightEnabled(0, true);
			// １番のライトON 
			lights->SetLightEnabled(1, true);
			// ２番のライトOFF 
			lights->SetLightEnabled(2, true);
			// ３番のライトOFF 
			lights->SetLightDiffuseColor(0, DirectX::Colors::White);
			lights->SetLightDiffuseColor(1, DirectX::Colors::White);
			lights->SetLightDiffuseColor(2, DirectX::Colors::White);
			// ライトの色 
			DirectX::SimpleMath::Vector3 light_dir(-1, 1, 0);
			// ライトの方向ベクトル 
			light_dir.Normalize();
			// ライトの方向ベクトルを正規化する
			lights->SetLightDirection(0, light_dir);
			lights->SetLightDirection(1, DirectX::SimpleMath::Vector3(0, 1, -1));
			lights->SetLightDirection(2, DirectX::SimpleMath::Vector3(1, 1, 1));
			// １番のライトの方向を設定する 
			lights->SetPerPixelLighting(true);
			//ピクセルシェーダーでライトの計算をする
		}
	};
	m_model->UpdateEffects(SetLight);
}

