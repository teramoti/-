/// <summary>
/// モデルの基底クラス
/// </summary>

//インクルード
#include <d3d11.h>
#include <Windows.h>
#include <wrl\client.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <Model.h>
#include <Keyboard.h>

//仮
#include "Camera.h"
#pragma once

//オブジェクト3Dクラス
namespace MyLib
{
	class Object3D
	{
	public:
		//一番初めの初期化処理
		static void InitielizeStatic(
			Microsoft::WRL::ComPtr<ID3D11Device> _device,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context,
			Camera* _camera
		);

	protected:

		//モデル
		std::unique_ptr<DirectX::Model> m_ModelData;

		//デバイス
		static Microsoft::WRL::ComPtr<ID3D11Device> m_Device;

		//テキスト
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;

		//汎用ステート
		static std::unique_ptr<DirectX::CommonStates> m_States;
		static std::unique_ptr<DirectX::EffectFactory> m_Factory;

		//カメラ
		static Camera* ccamera;

		//スケーリング
		DirectX::SimpleMath::Vector3 m_Scale;
		//回転角
		DirectX::SimpleMath::Vector3 m_Rotation;
		//平行
		DirectX::SimpleMath::Vector3 m_Translation;

		//行列
		DirectX::SimpleMath::Matrix m_World;

		DirectX::SimpleMath::Vector3 m_RotatrionV;

		DirectX::SimpleMath::Quaternion m_rot;
		MyLib::Object3D* m_Parent;

		float m_angle;//角度
	public:

		//コンストラクタ
		Object3D();
		~Object3D();

		//データをロード
		void Load(const wchar_t* fileName);

		//更新
		void Update();

		//描画
		virtual void Draw();

		//セット関数
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

		//ゲット関数

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

		//親を設定する
		MyLib::Object3D* GetParent()
		{
			return m_Parent;
		}
		void SetLight();
	};

}
