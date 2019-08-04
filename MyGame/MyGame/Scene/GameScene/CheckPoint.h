#pragma once
#include "../../GameSystem/Object.h"

class CheckPoint : public Teramoto::Object3D
{
public:
	CheckPoint();
	~CheckPoint();

	void Initilize();
	void Update();
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	//�`�F�b�N�|�C���g�̕ϐ�
	bool CheckBlock[3];
	//�Ō�̃S�[���t���O
	bool m_FinalFlag;


	bool Checkhit1(bool flag);
	bool Checkhit2(bool flag);
	bool Checkhit3(bool flag);
	bool GetFlag();
	//�S�[���̃t���O
	bool m_Flag;


private:

	//�����蔻��̐ݒ�
	// m_box[3];
	std::unique_ptr<DirectX::Model> m_model;

};