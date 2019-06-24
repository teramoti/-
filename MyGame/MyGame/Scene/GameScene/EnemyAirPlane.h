#ifndef ENEMY_AIR_PLANE
#define ENEMYA_IR_PLANE
#include ".././../GameSystem/Object.h"
#include <Model.h>
class EnemyAirPlane : Teramoto::Object3D
{
public:
	//�R���X�g���N�^
	EnemyAirPlane();
	//�f�X�g���N�^
	~EnemyAirPlane();

	//����������
	void Initilize();

	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	//���\�[�X�̐���
	void CreateResources();

private:

	//���f���̒�`
	std::unique_ptr<DirectX::Model> m_model;
};

#endif // !ENEMY_AIR_PLANE
