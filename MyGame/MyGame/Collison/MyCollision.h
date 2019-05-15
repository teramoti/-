/// <summary>
/// �쐬��	2017/12/06
/// �쐬��	���{ �[�u
/// �p�@�r	�e�����蔻�菈���N���X�̐錾
/// </summary>
#pragma once

/// <summary>
/// �C���N���[�h
/// </summary>
#include<d3d11.h>
#include<SimpleMath.h>


//Segment�N���X(����)
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;
	DirectX::SimpleMath::Vector3 Vec;
};

//Sphere�N���X(��)
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;
	Segment segment;
	float Radius;

	Sphere()
	{
		Radius = 1.0f;
	}
};

//Box�N���X(��)
class Box {
public:
	// ���_���W
	DirectX::SimpleMath::Vector3 Pos0;// ����O
	DirectX::SimpleMath::Vector3 Pos1;// �E��O
	DirectX::SimpleMath::Vector3 Pos2;// �����O
	DirectX::SimpleMath::Vector3 Pos3;// �E���O

	DirectX::SimpleMath::Vector3 Pos4;// �����
	DirectX::SimpleMath::Vector3 Pos5;// �E���
	DirectX::SimpleMath::Vector3 Pos6;// ������
	DirectX::SimpleMath::Vector3 Pos7;// �E����

};


//Capsule�N���X(�J�v�Z��(
class Capsule
{
public:
	//��ӂƓV��
	Segment Segment;

	//�~�̔��a
	float Radius;

	//���ݒ�
	Capsule()
	{
		Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		Segment.Vec = DirectX::SimpleMath::Vector3(0, 1, 0);
		Radius = 1.0f;
	}
};
//����̕��ʃN���X
class Planar
{
public:
	//�l�̒��_
	DirectX::SimpleMath::Vector3 Vertex[4];
	DirectX::SimpleMath::Vector4 p;

	void SetPlane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point);
	void SetPlane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3);

};

//Triangle�N���X(�O�p�`)
class Triangle {
public:
	//	���_���W
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	// �@���x�N�g��
	DirectX::SimpleMath::Vector3 Normal;
	Planar plane;
};

//�e�폈��

//���Ƌ��̂����蔻��
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB);
//�O�p�`�����֐�
void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);
//�����ƎO�p�`�̂����蔻��
bool CheckSegment2Triangle(const Segment & _segment, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
//���ƎO�p�`�̂����蔻��
bool CheckSphere2Triangle(const Sphere & _sphere, Triangle & _triangle, DirectX::SimpleMath::Vector3* _inter);
//���Ɣ��̂����蔻��
bool CheckSphere2Box(const Sphere& _sphere, const Box& _box, DirectX::SimpleMath::Vector3* _inter);
//���Ɣ��̂����蔻��
bool CheckBox2BoxAABB(Box _box1, Box _box2);
//���̌��ʂ�Ԃ�
float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1);
//���Ƌ��̂����蔻��
bool CheckSphere2Triangle(const Sphere& sphere1, const Triangle& angle, DirectX::SimpleMath::Vector3 *inter);
//�_�ƎO�p�`�̂����蔻��
bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
//�J�v�Z���ƃJ�v�Z��
bool CheckCapsule2Capsule(Capsule _0, Capsule _1);
//�J�v�Z���Ɣ��̂����蔻��
bool CheckCapsuleSphere2Box(const Capsule& _Capsule, const Box& _box, DirectX::SimpleMath::Vector3* _inter);
//�J�v�Z���Ƌ��̂����蔻��
bool CheckCapsule2Sphere(const Capsule& _Capsule, const Sphere& _sphere, DirectX::SimpleMath::Vector3* _inter);

//���ƕ��ʂ̂����蔻��(��{�n�ʂƂ̔���
bool CheckPlane2box(const Planar& _planer,const Box& _box,DirectX::SimpleMath::Vector3* _inter);
inline float Clamp(float _x, float _min, float _max);