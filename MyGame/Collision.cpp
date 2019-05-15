#include "../../pch.h"
#include"Collision.h"
using namespace std;
using namespace DirectX::SimpleMath;

bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{	
	//��A��B�̒��S���W�̍����v�Z����
	Vector3 sub = _sphereA.Center - _sphereB.Center;

	//�O�����̒藝�ŁA�x�N�g���̒������v�Z����
	//�����x�N�g���̒����͂Q�_�Ԃ̋���
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	float radiusSqare = _sphereA.Radius + _sphereB.Radius;
	radiusSqare = radiusSqare * radiusSqare;

	//2�̋��̔��a�̘a���x�N�g���̒������Z���Ȃ�false��Ԃ�
	if (distanceSquare > radiusSqare) {
		return false;
	}

	return true;
}

/// <summary>
/// 3�_����O�p�`���\�z
/// </summary>
/// <param name="_p0">�_0���W</param>
/// <param name="_p1">�_1���W</param>
/// <param name="_p2">�_2���W</param>
/// <param name="tri">�O�p�`�i���ʂ��タ���傭�p�j</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// �@���x�N�g�����v�Z
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// 2�x�N�g���ɐ����ȃx�N�g���𓾂�
	_triangle->Normal = P0_P1.Cross(P1_P2);
	_triangle->Normal.Normalize();
}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�ƎO�p�`�̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _triangle, Vector3* _closest)
{
	// _point��P0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P0_P1 = _triangle.P1 - _triangle.P0;
	Vector3 P0_P2 = _triangle.P2 - _triangle.P0;
	Vector3 P0_PT = _point - _triangle.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0���ŋߖT
		*_closest = _triangle.P0;
		return;
	}

	// _point��P1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P1_PT = _point - _triangle.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1���ŋߖT
		*_closest = _triangle.P1;
		return;
	}

	// _point��P0_P1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*_closest = _triangle.P0 + v * P0_P1;

		return;
	}

	// _point��P2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P2_PT = _point - _triangle.P2;

	float d5 = P0_P1.Dot(P2_PT);
	float d6 = P0_P2.Dot(P2_PT);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _triangle.P2;
		return;
	}

	// _point��P0_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*_closest = _triangle.P0 + w * P0_P2;
		return;
	}

	// _point��P1_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P1_P2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*_closest = _triangle.P1 + w * (_triangle.P2 - _triangle.P1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*_closest = _triangle.P0 + P0_P1 * v + P0_P2 * w;

}

bool CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//�_�ƎO�p�`�͓��ꕽ�ʏ�ɂ�����̂Ƃ��Ă��܂��B���ꕽ�ʏ�ɖ����ꍇ�͐��������ʂɂȂ�܂���
	//����͊O�Ƃ݂Ȃ��܂��B
	//ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...

	// �_0��1�A 1��2�A 2��0 �̃x�N�g�������ꂼ��v�Z
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;
	// �O�p�`�̊e���_����_�ւ̃x�N�g�������ꂼ��v�Z
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;
	// �e�Ӄx�N�g���ƁA�_�ւ̃x�N�g���̊O�ς��v�Z
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);
	// ���ςœ����������ǂ������ׂ�
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);
	// �O�σx�N�g�����S�ē��������Ȃ�A�O�p�`�̓����ɓ_������
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//�O�p�`�̊O���ɓ_������
	return false;

}

//--------------------------------------------------------------------------------------------
// ���@�� : �����i�L���j�Ɩ@���t���O�p�`�̓�����`�F�b�N
// ���@�� : _segment		�����̐����istart��end���������j
//			_tri		�@���t���O�p�`
//			_inter		��_�i�ȗ��j
// �߂�l : �������Ă��邩�ۂ�
// ���@�� : ���ʂ̓�����͂Ƃ�Ȃ�
//--------------------------------------------------------------------------------------------
bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& tri, Vector3 *inter)
{
	Vector3 p;

	//���̒��S�Ɉ�ԋ߂��_�ł���O�p�`��̓_�o���݂���
	ClosestPtPoint2Triangle(sphere.Center, tri, &p);

	Vector3 v = p - sphere.Center;

	// ���ƎO�p�`����������̂́A���̒��S����_p�܂ł̋��������̔��a�����������ꍇ
	if (v.Dot(v) <= sphere.Radius * sphere.Radius)
	{
		if (inter)
		{
			*inter = p;
		}

		return true;
	}

	return false;

	// ���ƕ��ʁi�O�p�`������Ă��镽�ʁj�̓����蔻��
	// ���ƕ��ʂ̋������v�Z
	float ds = sphere.Center.Dot(tri.Normal);
	float dt = tri.P0.Dot(tri.Normal);
	float dist = ds - dt;
	// ���������a�ȏ�Ȃ�A������Ȃ�
	if (fabsf(dist) > sphere.Radius)	return false;
	// ���S�_�𕽖ʂɎˉe�����Ƃ��A�O�p�`�̓����ɂ���΁A�������Ă���
	// �ˉe�������W
	Vector3 center = -dist * tri.Normal + sphere.Center;

	// �O�p�`�̊O���ɂȂ���΁A�������Ă��Ȃ�
	if (!CheckPoint2Triangle(center, tri))	return false;

	if (inter)
	{
		*inter = center;	// ��_���R�s�[
	}

	return true;
	
}

//�J�v�Z���Ƃ̔���
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, Vector3 *_inter)
{
	const float epsilon = -1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 	LayV;		// �����̏I�_���n�_
	Vector3 	tls;		// �O�p�`�̒��_0�������̎n�_
	Vector3 	tle;		// �O�p�`�̒��_0�������̏I�_
	float 	distl0;
	float 	distl1;
	float 	dp;
	float 	denom;
	float 	t;
	Vector3	s;			// �����ƕ��ʂƂ̌�_
	Vector3 	st0;		// ��_���O�p�`�̒��_0
	Vector3 	st1;		// ��_���O�p�`�̒��_1
	Vector3 	st2;		// ��_���O�p�`�̒��_2
	Vector3 	t01;		// �O�p�`�̒��_0�����_1
	Vector3 	t12;		// �O�p�`�̒��_1�����_2
	Vector3 	t20;		// �O�p�`�̒��_2�����_0
	Vector3	m;

	// �����̎n�_���O�p�n�̗����ɂ���΁A������Ȃ�
	tls = _segment.Start - _triangle.P0;
	distl0 = tls.Dot(_triangle.Normal);	// �����̎n�_�ƕ��ʂ̋���
	if (distl0 <= epsilon) return false;

	// �����̏I�_���O�p�n�̕\���ɂ���΁A������Ȃ�
	tle = _segment.Vec - _triangle.P0;
	distl1 = tle.Dot(_triangle.Normal);	// �����̏I�_�ƕ��ʂ̋���
	if (distl1 >= -epsilon) return false;

	// �����ƕ��ʂƂ̌�_s�����
	denom = distl0 - distl1;
	t = distl0 / denom;
	LayV = _segment.Vec - _segment.Start;	// �����̕����x�N�g�����擾
	s = t * LayV + _segment.Start;

	// ��_���O�p�`�̓����ɂ��邩�ǂ����𒲂ׂ�B
	// �O�p�`�̓����ɂ���ꍇ�A��_����e���_�ւ̃x�N�g���Ɗe�Ӄx�N�g���̊O�ρi�O�g�j���A�S�Ė@���Ɠ�������������
	// ��ł���������v���Ȃ���΁A������Ȃ��B
	st0 = _triangle.P0 - s;
	t01 = _triangle.P1 - _triangle.P0;
	m = st0.Cross(t01);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st1 = _triangle.P1 - s;
	t12 = _triangle.P2 - _triangle.P1;
	m = st1.Cross(t12);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st2 = _triangle.P2 - s;
	t20 = _triangle.P0 - _triangle.P2;
	m = st2.Cross(t20);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	if (_inter)
	{
		*_inter = s;	// ��_���R�s�[
	}

	return true;
}

//--------------------------------------------------------------------------------------------
// ���@�� : ���Ɩ@���t���O�p�`�̓�����`�F�b�N
// ���@�� : _sphere		��
//			_tri		�@���t���O�p�`
//			_inter		��_�i�ȗ��j
// �߂�l : �������Ă��邩�ۂ�
// ���@�� : ���ʂ̓�����͂Ƃ�Ȃ�
//--------------------------------------------------------------------------------------------
bool CheckSphere2Triangle(const Sphere& _sphere,  Triangle& _triangle, Vector3 *_inter)
{
	Vector3 p;

	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(_sphere.Center, _triangle, &p);

	Vector3 v = p - _sphere.Center;

	// ���ƎO�p�`����������̂́A���̒��S����_p�܂ł̋��������̔��a�����������ꍇ
	if (v.Dot(v) <= _sphere.Radius * _sphere.Radius)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}

	return false;

	// ���ƕ��ʁi�O�p�`������Ă��镽�ʁj�̓����蔻��
	// ���ƕ��ʂ̋������v�Z
	float ds = _sphere.Center.Dot(_triangle.Normal);
	float dt = _triangle.P0.Dot(_triangle.Normal);
	float dist = ds - dt;
	// ���������a�ȏ�Ȃ�A������Ȃ�
	if (fabsf(dist) > _sphere.Radius)	return false;
	// ���S�_�𕽖ʂɎˉe�����Ƃ��A�O�p�`�̓����ɂ���΁A�������Ă���
	// �ˉe�������W
	Vector3 center = -dist * _triangle.Normal + _sphere.Center;

	// �O�p�`�̊O���ɂȂ���΁A�������Ă��Ȃ�
	if (!CheckPoint2Triangle(center, _triangle))	return false;

	if (_inter)
	{
		*_inter = center;	// ��_���R�s�[
	}

	return true;
}
/// <summary>
/// ���Ƌ��̂����蔻��
/// </summary>
/// <param name="_sphere">Sphere�F�����蔻��𒲂ׂ鋅</param>
/// <param name="_box">Box�F�����蔻��𒲂ׂ锠</param>
/// <param name="_inter">Inter�F��_�i�ȗ��j</param>
/// <returns></returns>
bool CheckSphere2Box(const Sphere& _sphere, const Box& _box, Vector3* _inter)
{
	Vector3 p;

	Triangle boxTriangle[12];

	//�O�p�`���쐬
	ComputeTriangle(_box.Pos0, _box.Pos1, _box.Pos2, &boxTriangle[0]);
	ComputeTriangle(_box.Pos1, _box.Pos2, _box.Pos3, &boxTriangle[1]);
	ComputeTriangle(_box.Pos1, _box.Pos5, _box.Pos3, &boxTriangle[2]);
	ComputeTriangle(_box.Pos5, _box.Pos3, _box.Pos7, &boxTriangle[3]);
	ComputeTriangle(_box.Pos4, _box.Pos5, _box.Pos6, &boxTriangle[4]);
	ComputeTriangle(_box.Pos5, _box.Pos6, _box.Pos7, &boxTriangle[5]);
	ComputeTriangle(_box.Pos2, _box.Pos4, _box.Pos6, &boxTriangle[6]);
	ComputeTriangle(_box.Pos0, _box.Pos2, _box.Pos4, &boxTriangle[7]);
	ComputeTriangle(_box.Pos1, _box.Pos4, _box.Pos5, &boxTriangle[8]);
	ComputeTriangle(_box.Pos4, _box.Pos0, _box.Pos1, &boxTriangle[9]);
	ComputeTriangle(_box.Pos2, _box.Pos3, _box.Pos7, &boxTriangle[10]);
	ComputeTriangle(_box.Pos2, _box.Pos7, _box.Pos6, &boxTriangle[11]);

	//���Ɣ��̂����蔻��
	if (
		CheckSphere2Triangle(_sphere,boxTriangle[0],&p) || 
		CheckSphere2Triangle(_sphere, boxTriangle[1], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[2], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[3], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[4], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[5], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[6], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[7], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[8], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[9], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[10], &p) ||
		CheckSphere2Triangle(_sphere, boxTriangle[11], &p)
		)
	{
		//�������Ă���
		if (_inter) 
		{
			*_inter = p;
		}
		return true;
	}

	//�������Ă��Ȃ�
	return false;
}

/// <summary>
/// AABB�ɂ�锠�Ɣ��̂����蔻��
/// </summary>
/// <param name="_box1">Box�F1�ڂ̔��̂����蔻��</param>
/// <param name="_box2">BOX�F2�ڂ̔��̂����蔻��</param>
/// <param name="_inter">Inter�F��_�i�ȗ��j</param>
/// <returns></returns>
bool CheckBox2BoxAABB(Box _box1, Box _box2) 
{
	if (_box1.Pos0.x > _box2.Pos7.x)return false;
	if (_box1.Pos7.x < _box2.Pos0.x)return false;
	if (_box1.Pos0.y > _box2.Pos7.y)return false;
	if (_box1.Pos7.y < _box2.Pos0.y)return false;
	if (_box1.Pos0.z > _box2.Pos7.z)return false;
	if (_box1.Pos7.z < _box2.Pos0.z)return false;
	return true;   // �ՓˁI�I
}

//�J�v�Z�����m�̂����蔻��
bool CheckCapsule2Capsule(Capsule _0, Capsule _1)
{
	float disSQ = GetSqDistanceSegment2Segment(_0.Segment,_1.Segment);
	float radiusSum = _0.Radius + _1.Radius;
	float radSQ = radiusSum * radiusSum;

	if (disSQ > radSQ) return false;

	return true;
}

float GetSqDistancePoint2Segment(const Vector3& _point, const Segment& _segment)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 SegmentSub;
	Vector3 SegmentPoint;
	Vector3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = _segment.Vec - _segment.Start;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = _point - _segment.Start;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return SegmentPoint.Dot(SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = _segment.Vec - _point;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return SegmentPoint.Dot(SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	CP.Cross(SegmentSub, SegmentPoint);

	return CP.Dot(CP) / SegmentSub.Dot(SegmentSub);
}

float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 d0, d1, r;
	Vector3 c0, c1;	// ��̐�����̍Őڋߓ_
	Vector3 v;		// c1��c0�x�N�g��
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.Vec - _segment0.Start;	// ����0�̕����x�N�g��
	d1 = _segment1.Vec - _segment1.Start; // ����1�̕����x�N�g��
	r = _segment0.Start - _segment1.Start; // ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.Dot(d0);		// ����0�̋����̓��
	e = d1.Dot(d1);		// ����1�̋����̓��


						// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		v = _segment0.Start - _segment1.Start;

		return v.Dot(v);
	}

	if (a <= epsilon)
	{// ����0������0
		return GetSqDistancePoint2Segment(_segment0.Start, _segment1);
	}

	if (e <= epsilon)
	{// ����1������0
		return GetSqDistancePoint2Segment(_segment1.Start, _segment0);
	}

	b = d0.Dot(d1);
	f = d1.Dot(r);
	c = d0.Dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	c0 = s * d0 + _segment0.Start;
	c1 = t * d1 + _segment1.Start;
	v = c0 - c1;

	return v.Dot(v);
}

bool CheckPlane2box(const Planar & _planer, const Box & _box, DirectX::SimpleMath::Vector3 * _inter)
{
	//�͂������ꎞ�I�ɍ쐬
	Segment segment[2];

	segment[0].Start = _planer.Vertex[0];
	segment[0].Vec = _planer.Vertex[1];

	segment[1].Start = _planer.Vertex[2];
	segment[1].Vec = _planer.Vertex[3];

	//���̒�ӂ̒��_�ƕ��ʂ̂����蔻��
	//if (segment[0].Start <= _box.)
	{
		//��������
		return true;
	}

	//������Ȃ�����
	return false;
}

// �ŏ��l�ƍő�l�̊ԂɃN�����v����
inline float Clamp(float _x, float _min, float _max)
{
	return std::min(std::max(_x, _min), _max);
}

bool CheckCapsuleSphere2Box(const Capsule& _Capsule, const Box& _box, Vector3* _inter)
{
	Vector3 p;

	Triangle boxTriangle[12];

	ComputeTriangle(_box.Pos0, _box.Pos1, _box.Pos2, &boxTriangle[0]);
	ComputeTriangle(_box.Pos1, _box.Pos2, _box.Pos3, &boxTriangle[1]);
	ComputeTriangle(_box.Pos1, _box.Pos4, _box.Pos3, &boxTriangle[2]);
	ComputeTriangle(_box.Pos4, _box.Pos3, _box.Pos6, &boxTriangle[3]);
	ComputeTriangle(_box.Pos4, _box.Pos5, _box.Pos6, &boxTriangle[4]);
	ComputeTriangle(_box.Pos5, _box.Pos6, _box.Pos7, &boxTriangle[5]);
	ComputeTriangle(_box.Pos5, _box.Pos0, _box.Pos7, &boxTriangle[6]);
	ComputeTriangle(_box.Pos0, _box.Pos7, _box.Pos2, &boxTriangle[7]);
	ComputeTriangle(_box.Pos5, _box.Pos4, _box.Pos0, &boxTriangle[8]);
	ComputeTriangle(_box.Pos4, _box.Pos0, _box.Pos1, &boxTriangle[9]);
	ComputeTriangle(_box.Pos2, _box.Pos3, _box.Pos7, &boxTriangle[10]);
	ComputeTriangle(_box.Pos3, _box.Pos7, _box.Pos6, &boxTriangle[11]);

	Sphere CapsuleSphere;

	CapsuleSphere.Center;

	//�������o��
	float h = _Capsule.Segment.Start.y - _Capsule.Segment.Vec.y;

	//����������-�Ȃ琳�K��
	if (h < 0)
	{
		h = h * -1.0f;
	}

	for (int i = 0; i < h; i++)
	{
		CapsuleSphere.Center = Vector3(_Capsule.Segment.Vec.x, _Capsule.Segment.Vec.y + h, _Capsule.Segment.Vec.z);

		if (CheckSphere2Triangle(CapsuleSphere, boxTriangle[0], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[1], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[2], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[3], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[4], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[5], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[6], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[7], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[8], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[9], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[10], &p) ||
			CheckSphere2Triangle(CapsuleSphere, boxTriangle[11], &p))
		{

			if (_inter)
			{
				*_inter = p;
			}

			return true;
		}
	}

	return false;
}

bool CheckCapsule2Sphere(const Capsule & _Capsule, const Sphere & _sphere, DirectX::SimpleMath::Vector3 * _inter)
{
	float distance2 = GetSqDistancePoint2Segment(_sphere.Center, _Capsule.Segment);

	float radius = _sphere.Radius + _Capsule.Radius;

	if (distance2 > radius*radius) return false;

	return true;
}

void Planar::SetPlane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
{
	normal.Normalize();
	p.x = normal.x;
	p.y = normal.y;
	p.z = normal.z;

	p.w = -((normal.x*point.x) + (normal.y*point.y) + (normal.z*point.z));
}

void Planar::SetPlane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
{
	DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
	DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

	DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);//vec_a�̊O��

	SetPlane(normal, pos1);
}
