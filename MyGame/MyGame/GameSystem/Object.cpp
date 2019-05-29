#include "Object.h"



Teramoto::Object3D::Object3D()
{
	m_scale = DirectX::SimpleMath::Vector3(1, 1, 1);
}

Teramoto::Object3D::~Object3D()
{

}

void Teramoto::Object3D::Update()
{

	DirectX::SimpleMath::Matrix rotationMatrix;
	rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);

	DirectX::SimpleMath::Matrix translationMatrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_translation);

	m_world =  rotationMatrix * translationMatrix;
}

void Teramoto::Object3D::Draw()
{

}


void Teramoto::Object3D::SetLight()
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
			lights->SetLightDiffuseColor(0,DirectX::Colors::White);
			lights->SetLightDiffuseColor(1,DirectX::Colors::White);
			lights->SetLightDiffuseColor(2,DirectX::Colors::White);
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
	m_modelData->UpdateEffects(SetLight);
}

