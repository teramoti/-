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
	void Render();//�`�揈��()

private:
		//�R�[�X�����蔻��
	BoxNode m_box[5];
};