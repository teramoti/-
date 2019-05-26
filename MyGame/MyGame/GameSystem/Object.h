/// <summary>
/// ���f���̊��N���X
/// </summary>

//�C���N���[�h
#include <d3d11.h>
#include <Windows.h>
#include <wrl\client.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Model.h>
#include <Keyboard.h>
//��
#include "Camera.h"
#include "../Utillity/DirectX11.h"

#pragma once

//�I�u�W�F�N�g3D�N���X
namespace MyLib
{
	class Object3D
	{
	public:

	protected:

		//���f��
		std::unique_ptr<DirectX::Model> m_modelData;

		//�ėp�X�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_States;
		std::unique_ptr<DirectX::EffectFactory> m_Factory;

		//�J����
		Camera* ccamera;

		//�X�P�[�����O
		DirectX::SimpleMath::Vector3 m_scale;
		//��]�p
		//DirectX::SimpleMath::Vector3 m_rotation;
		//���s
		DirectX::SimpleMath::Vector3 m_translation;

		//�s��
		DirectX::SimpleMath::Matrix m_world;

		DirectX::SimpleMath::Vector3 m_rotatrionV;

		DirectX::SimpleMath::Quaternion m_rotation;

		DirectX11& m_directX11 = DirectX11::Get();

		float m_angle;//�p�x
	public:

		//�R���X�g���N�^
		Object3D();
		~Object3D();

		//�X�V
		void Update();

		//�`��
		virtual void Draw();

		//�Z�b�g�֐�
		void SetScale(DirectX::SimpleMath::Vector3& scale)
		{
			m_scale = scale;
		}
		void SetTranslation(DirectX::SimpleMath::Vector3& translation)
		{
			m_translation = translation;
		}
		void SetWorld(DirectX::SimpleMath::Matrix world)
		{
			m_world = world;
		}

		void SetRotation(DirectX::SimpleMath::Quaternion rotation)
		{
			m_rotation = rotation;
		}

		void SetAngle(float angle)
		{
			m_angle = angle;
		}
		//�Q�b�g�֐�

		float GetAngle()
		{
			return  m_angle;
		}
		DirectX::SimpleMath::Vector3& GetScale()
		{
			return m_scale;
		}
		DirectX::SimpleMath::Vector3& GetTranslation()
		{
			return m_translation;
		}
		DirectX::SimpleMath::Matrix& GetWorld()
		{
			return m_world;
		}
		DirectX::SimpleMath::Quaternion GetRotation()
		{
			return m_rotation;
		}

		void SetLight();
	};

}
