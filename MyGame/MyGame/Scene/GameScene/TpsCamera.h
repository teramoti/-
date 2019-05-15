#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/Camera.h"
#include "../../GameSystem/Object.h"

class TpsCamera :public MyLib::Camera
{
private:
	DirectX::SimpleMath::Vector3 m_TargetPos;

	float m_TargetRot;
	float m_TargetRotX;
	float m_TargetRotZ;

	MyLib::Object3D* Object;

public:
	TpsCamera(int w, int h);
	~TpsCamera();
	void Update() override;

	void SetTrans(DirectX::SimpleMath::Vector3 trangetpos);
	void SetAngle(float tragetangle);
	void SetAngleX(float tragetangle);
	void SetAngleZ(float tragetangle);

	void SetObject3D(MyLib::Object3D* object3D);

	float GetAngle();
	float GetAngleX();
	float GetAngleZ();
};