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
#include "../Utillity/DirectX11.h"

#pragma once

//オブジェクト3Dクラス
namespace MyLib
{
	class Object3D
	{
	public:

	protected:

		//モデル
		std::unique_ptr<DirectX::Model> m_modelData;

		//汎用ステート
		std::unique_ptr<DirectX::CommonStates> m_States;
		std::unique_ptr<DirectX::EffectFactory> m_Factory;

		//カメラ
		Camera* ccamera;

		//スケーリング
		DirectX::SimpleMath::Vector3 m_scale;
		//回転角
		//DirectX::SimpleMath::Vector3 m_rotation;
		//平行
		DirectX::SimpleMath::Vector3 m_translation;

		//行列
		DirectX::SimpleMath::Matrix m_world;

		DirectX::SimpleMath::Vector3 m_rotatrionV;

		DirectX::SimpleMath::Quaternion m_rotation;

		DirectX11& m_directX11 = DirectX11::Get();

		float m_angle;//角度
	public:

		//コンストラクタ
		Object3D();
		~Object3D();

		//更新
		void Update();

		//描画
		virtual void Draw();

		//セット関数
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
		//ゲット関数

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
