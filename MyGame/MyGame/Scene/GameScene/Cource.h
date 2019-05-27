#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class Cource : public MyLib::Object3D
{

public:
	Cource();
	~Cource();

	void Initilize();//����������
	void Update();//�X�V����
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);//�`�揈��()
	void CreateResource();
private:

private:
	std::unique_ptr<DirectX::Model> m_model;

};