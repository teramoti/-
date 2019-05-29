#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class Cource : public Teramoto::Object3D
{

public:
	Cource();
	~Cource();

	//����������
	void Initilize();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void CreateResource();
private:

private:
	std::unique_ptr<DirectX::Model> m_model;

};