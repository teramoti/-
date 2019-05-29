#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/Camera.h"
#include "../../GameSystem/Object.h"

class TpsCamera :public Teramoto::Camera
{
private:
	//�ݒ肷��Object�̈ʒu
	DirectX::SimpleMath::Vector3 m_targetPos;
	//�ݒ肷��object�̊p�x
	float m_targetAngle;
	//�ݒ肷��object�̉�]
	DirectX::SimpleMath::Vector3 m_targetRotation;
	//�I�u�W�F�N�g�N���X
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