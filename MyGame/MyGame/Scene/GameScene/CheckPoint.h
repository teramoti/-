#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class CheckPoint : public MyLib::Object3D
{
public:
	CheckPoint();
	~CheckPoint();

	void Initilize();
	void Update();
	void Render();

	BoxNode& GetBoxStartPos()
	{
		return m_box[0];
	}

	BoxNode& GetBoxCheckPos1()
	{
		return m_box[1];
	}
	BoxNode& GetBoxCheckPos2()
	{
		return m_box[2];
	}

	bool CheckBlock[3];//�`�F�b�N�|�C���g�̕ϐ�
	bool m_FinalFlag;//�Ō�̃S�[���t���O


	bool Checkhit1(bool flag);
	bool Checkhit2(bool flag);
	bool Checkhit3(bool flag);
	bool GetFlag();
	bool m_Flag;//�S�[���̃t���O


private:

	BoxNode m_box[3];//�����蔻��̐ݒ�

};