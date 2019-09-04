#include "Object.h"



Teramoto::Object3D::Object3D()
{
	m_scale = DirectX::SimpleMath::Vector3(1, 1, 1);
}

Teramoto::Object3D::~Object3D()
{

}

/// <summary>
/// Object�N���X��Update�֐�
/// </return> �Ȃ�
/// </summary>
void Teramoto::Object3D::Update()
{
	//��]�p�s��
	DirectX::SimpleMath::Matrix rotationMatrix;
	//��]�p�s��ɉ�]�p�ϐ�������
	rotationMatrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	//�ړ��p�s��
	DirectX::SimpleMath::Matrix translationMatrix;
	//�ړ��p�s��Ɉړ��p�ϐ�������
	translationMatrix=	DirectX::SimpleMath::Matrix::CreateTranslation(m_translation);

	//���[���h�̐ݒ�
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
			// �A���r�G���g�F��ݒ肷�� 
			lights->SetLightEnabled(0, true);
			// �P�Ԃ̃��C�gON 
			lights->SetLightEnabled(1, true);
			// �Q�Ԃ̃��C�gOFF 
			lights->SetLightEnabled(2, true);
			// �R�Ԃ̃��C�gOFF 
			lights->SetLightDiffuseColor(0,DirectX::Colors::White);
			lights->SetLightDiffuseColor(1,DirectX::Colors::White);
			lights->SetLightDiffuseColor(2,DirectX::Colors::White);
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

	m_modelData->UpdateEffects(SetLight);
}

