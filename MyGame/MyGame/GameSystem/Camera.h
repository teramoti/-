#pragma once
#include <d3d11.h>
#include <SimpleMath.h>


namespace MyLib
{
	class Camera
	{
	protected:

		DirectX::SimpleMath::Matrix m_View;

		DirectX::SimpleMath::Vector3 m_Eyepos;

		DirectX::SimpleMath::Vector3 m_Refpos;

		DirectX::SimpleMath::Vector3 m_Upvec;

		DirectX::SimpleMath::Matrix m_Proj;

		DirectX::SimpleMath::Vector3 m_target;

		float m_FovY;

		float m_Aspect;

		float m_NearClip;

		float m_FarClip;

	public:
		Camera(float w, float h);
		virtual ~Camera();

		virtual void Update();

		const DirectX::SimpleMath::Matrix& GetView();

		const DirectX::SimpleMath::Matrix& GetProj();

		void Seteyepos(const DirectX::SimpleMath::Vector3& eyepos);
		void Setrefpos(const DirectX::SimpleMath::Vector3& refpos);
		void Setupvec(const DirectX::SimpleMath::Vector3& upvec);
		void SetfovY(float fovY);
		void Settaspect(float aspect);
		void SetanerClip(float nearclip);
		void SetfarClip(float farclip);

		void SetTargetPos(DirectX::SimpleMath::Vector3 target);
	};

}
