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
#pragma once

//�I�u�W�F�N�g3D�N���X
namespace MyLib
{
	class Object3D
	{
	public:
		//��ԏ��߂̏���������
		static void InitielizeStatic(
			Microsoft::WRL::ComPtr<ID3D11Device> _device,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context,
			Camera* _camera
		);

	protected:

		//���f��
		std::unique_ptr<DirectX::Model> m_ModelData;

		//�f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device> m_Device;

		//�e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;

		//�ėp�X�e�[�g
		static std::unique_ptr<DirectX::CommonStates> m_States;
		static std::unique_ptr<DirectX::EffectFactory> m_Factory;

		//�J����
		static Camera* ccamera;

		//�X�P�[�����O
		DirectX::SimpleMath::Vector3 m_Scale;
		//��]�p
		DirectX::SimpleMath::Vector3 m_Rotation;
		//���s
		DirectX::SimpleMath::Vector3 m_Translation;

		//�s��
		DirectX::SimpleMath::Matrix m_World;

		DirectX::SimpleMath::Vector3 m_RotatrionV;

		DirectX::SimpleMath::Quaternion m_rot;
		MyLib::Object3D* m_Parent;

		float m_angle;//�p�x
	public:

		//�R���X�g���N�^
		Object3D();
		~Object3D();

		//�f�[�^�����[�h
		void Load(const wchar_t* fileName);

		//�X�V
		void Update();

		//�`��
		virtual void Draw();

		//�Z�b�g�֐�
		void SetScale(DirectX::SimpleMath::Vector3& _scale)
		{
			m_Scale = _scale;
		}
		void SetRotation(DirectX::SimpleMath::Vector3& _rotation)
		{
			m_Rotation = _rotation;
		}
		void SetTranslation(DirectX::SimpleMath::Vector3& _translation)
		{
			m_Translation = _translation;
		}
		void SetParent(MyLib::Object3D* _parent)
		{
			m_Parent = _parent;
		}
		void SetWorld(DirectX::SimpleMath::Matrix _worlad)
		{
			m_World = _worlad;
		}

		void SetRot(DirectX::SimpleMath::Quaternion a)
		{
			m_rot = a;
		}

		void SetAngle(float a)
		{
			m_angle = a;
		}
		void ReUpdate();

		//�Q�b�g�֐�

		float GetAngle()
		{
			return  m_angle;
		}
		DirectX::SimpleMath::Vector3& GetScale()
		{
			return m_Scale;
		}
		DirectX::SimpleMath::Vector3& GetRotation()
		{
			return m_Rotation;
		}
		DirectX::SimpleMath::Vector3& GetTranslation()
		{
			return m_Translation;
		}
		DirectX::SimpleMath::Matrix& GetWorld()
		{
			return m_World;
		}
		DirectX::SimpleMath::Quaternion GetRot()
		{
			return m_rot;
		}

		//�e��ݒ肷��
		MyLib::Object3D* GetParent()
		{
			return m_Parent;
		}
		void SetLight();
	};

}
