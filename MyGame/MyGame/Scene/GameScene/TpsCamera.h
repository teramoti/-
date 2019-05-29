#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/Camera.h"
#include "../../GameSystem/Object.h"

class TpsCamera :public Teramoto::Camera
{
private:
	//設定するObjectの位置
	DirectX::SimpleMath::Vector3 m_targetPos;
	//設定するobjectの角度
	float m_targetAngle;
	//設定するobjectの回転
	DirectX::SimpleMath::Vector3 m_targetRotation;
	//オブジェクトクラス
	Teramoto::Object3D* Object;

public:
	TpsCamera(int w, int h);
	~TpsCamera();
	void Update() override;

	void SetTranslation(DirectX::SimpleMath::Vector3 trangetpos);
	void SetAngle(float rotation);

	void SetObject3D(Teramoto::Object3D* object3D);

	DirectX::SimpleMath::Vector3 GetRotation();
	float GetAngle();
};