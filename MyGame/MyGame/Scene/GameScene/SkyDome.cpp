//----------------------------------------
/// <summary>
///	�R�[�X�̃N���X
/// GS2 ���{ �[�u
/// </summary>
//----------------------------------------
#include "SkyDome.h"



SkyDome::SkyDome()
{
	
	
}
SkyDome::~SkyDome()
{
	m_model.reset();
}


void SkyDome::Initilize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");


	CreateResource();

}

void SkyDome::Update()
{
	Teramoto::Object3D::Update();

}

void SkyDome::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\SkyDome.cmo", *m_directX11.Get().GetEffect());
}


void SkyDome::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}
void SkyDome::SetLight()
{
	auto SetLight = [&](DirectX::IEffect* effect)
	{
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights)
		{
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f));
			// �A���r�G���g�F��ݒ肷�� 
			lights->SetLightEnabled(0, true);
			// �P�Ԃ̃��C�gON 
			lights->SetLightEnabled(1, true);
			// �Q�Ԃ̃��C�gOFF 
			lights->SetLightEnabled(2, true);
			// �R�Ԃ̃��C�gOFF 
			lights->SetLightDiffuseColor(0, DirectX::Colors::White);
			lights->SetLightDiffuseColor(1, DirectX::Colors::White);
			lights->SetLightDiffuseColor(2, DirectX::Colors::White);
			// ���C�g�̐F 
			DirectX::SimpleMath::Vector3 light_dir(-1, 1, 0);
			// ���C�g�̕����x�N�g�� 
			light_dir.Normalize();
			// ���C�g�̕����x�N�g���𐳋K������
			lights->SetLightDirection(0, light_dir);
			lights->SetLightDirection(1, DirectX::SimpleMath::Vector3(0, 1, -1));
			lights->SetLightDirection(2, DirectX::SimpleMath::Vector3(1, 1, 1));
			// �P�Ԃ̃��C�g�̕�����ݒ肷�� 
			lights->SetPerPixelLighting(true);
			//�s�N�Z���V�F�[�_�[�Ń��C�g�̌v�Z������
		}
	};
	m_model->UpdateEffects(SetLight);
}

