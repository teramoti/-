//--------------------------------------------------------------------------------------
// File: Collision.h
//
// �Փ˔���p�R���W�����N���X
// ���l�F�Q�[���v���O���~���O�̂��߂̃��A���^�C���Փ˔�����Q�l�ɍ쐬
//
// Date: 2018.7.8
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Collision
{
public:
//------------------------------//
// ���E�{�����[���̍\����		//
//------------------------------//

	// ���̍\����
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 c; // ���̒��S
		float r;   // ���̔��a
	};

	// �J�v�Z���̍\����
	struct Capsule
	{
		DirectX::SimpleMath::Vector3 a; // ���ԕ��̐����̊J�n�_
		DirectX::SimpleMath::Vector3 b; // ���ԕ��̐����̏I���_
		float r;   // �J�v�Z���̔��a
	};

	// �{�b�N�X�̍\����
	struct Box
	{
		DirectX::SimpleMath::Vector3 c; // BOX�̒��S�_
		DirectX::SimpleMath::Vector3 r; // ���̔����͈̔�
	};

//--------------------------------------//
// ���E�{�����[�����m�̏Փ˔���֐�		//
//--------------------------------------//

	// ���Ƌ��̏Փ˔���֐�
	static bool HitCheck_Sphere2Sphere(const Sphere& sphere1, const Sphere& sphere2)
	{
		// ���S�Ԃ̋����̕������v�Z
		DirectX::SimpleMath::Vector3 d = sphere1.c - sphere2.c;
		float dist2 = d.Dot(d);
		// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
		float radiusSum = sphere1.r + sphere2.r;
		return dist2 <= radiusSum * radiusSum;
	}

	// ���ƃJ�v�Z���̏Փ˔���֐�
	static bool HitCheck_Sphere2Capsule(const Sphere& sphere, const Capsule& capsule)
	{
		// ���̒��S�ƃJ�v�Z���̒��S�̐����Ƃ̋����̕������v�Z
		float dist2 = SqDistPointSegment(capsule.a, capsule.b, sphere.c);
		float radius = sphere.r + capsule.r;
		return dist2 <= radius * radius;
	}

	// �J�v�Z���ƃJ�v�Z���̏Փ˔���֐�
	static bool HitCheck_Capsule2Capsule(const Capsule& capsule1, const Capsule& capsule2)
	{
		float s, t;
		DirectX::SimpleMath::Vector3 c1, c2;
		// �J�v�Z���̒��S�̐����Ԃ̋����̕������v�Z
		float dist2 = ClosestPtSegmentSegment(capsule1.a, capsule1.b, capsule2.a, capsule2.b, s, t, c1, c2);
		float radius = capsule1.r + capsule2.r;
		return dist2 <= radius * radius;
	}

	// �{�b�N�X�ƃ{�b�N�X�̏Փ˔���֐�
	static bool HitCheck_Box2Box(const Box& box1, const Box& box2)
	{
		if (fabsf(box1.c.x - box2.c.x) > (box1.r.x + box2.r.x)) return false;
		if (fabsf(box1.c.y - box2.c.y) > (box1.r.y + box2.r.y)) return false;
		if (fabsf(box1.c.z - box2.c.z) > (box1.r.z + box2.r.z)) return false;
		return true;
	}

	// ���ƃ{�b�N�X�̏Փ˔���֐�
	static bool HitCheck_Sphere2Box(const Sphere& sphere, const Box& box)
	{
		float sqDist = SqDistPointBox(sphere.c, box);
		return sqDist <= sphere.r * sphere.r;
	}

//------------------------------//
// �Փ˔���ɕK�v�ȕ⏕�֐��Q	//
//------------------------------//

	/// <summary>
	/// �_c�Ɛ���ab�̊Ԃ̋����̕�����Ԃ��֐�
	/// </summary>
	/// <param name="a">�����̎n�_</param>
	/// <param name="b">�����̏I�_</param>
	/// <param name="c">�_</param>
	/// <returns>�_c�Ɛ���ab�̊Ԃ̋����̕���</returns>
	static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
	{
		DirectX::SimpleMath::Vector3 ab = b - a;
		DirectX::SimpleMath::Vector3 ac = c - a;
		DirectX::SimpleMath::Vector3 bc = c - b;
		float e = ac.Dot(ab);
		if (e <= 0.0f) return ac.Dot(ac);
		float f = ab.Dot(ab);
		if (e >= f) return bc.Dot(bc);
		return ac.Dot(ac) - e * e / f;
	}

	// �N�����v�֐�
	static inline float Clamp(float n, float min, float max)
	{
		if (n < min) return min;
		if (n > max) return max;
		return n;
	}

	/// <summary>
	/// �Q�̐����̍ŒZ�����̕�����Ԃ��֐�
	/// </summary>
	/// <param name="p1">�����P�̎n�_</param>
	/// <param name="q1">�����P�̏I�_</param>
	/// <param name="p2">�����Q�̎n�_</param>
	/// <param name="q2">�����Q�̏I�_</param>
	/// <param name="s">�����P��̍ŒZ�ʒu��\���W��</param>
	/// <param name="t">�����Q��̍ŒZ�ʒu��\���W��</param>
	/// <param name="c1">�����P��̍ŒZ�����̈ʒu</param>
	/// <param name="c2">�����Q��̍ŒZ�����̈ʒu</param>
	/// <returns>�Q�̐����̍ŒZ�����̕���</returns>
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1
		, DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2
		, float &s, float &t
		, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
	{
		DirectX::SimpleMath::Vector3 d1 = q1 - p1;
		DirectX::SimpleMath::Vector3 d2 = q2 - p2;
		DirectX::SimpleMath::Vector3 r = p1 - p2;
		float a = d1.Dot(d1);
		float e = d2.Dot(d2);
		float f = d2.Dot(r);

		if (a <= FLT_EPSILON && e <= FLT_EPSILON)
		{
			s = t = 0.0f;
			c1 = p1;
			c2 = p2;
			return (c1 - c2).Dot(c1 - c2);
		}
		if (a <= FLT_EPSILON)
		{
			s = 0.0f;
			t = f / e;
			t = Clamp(t, 0.0f, 1.0f);
		}
		else
		{
			float c = d1.Dot(r);
			if (e <= FLT_EPSILON)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else
			{
				float b = d1.Dot(d2);
				float denom = a * e - b * b;
				if (denom != 0.0f)
				{
					s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
				}
				else
				{
					s = 0.0f;
				}
				float tnom = (b * s + f);
				if (tnom < 0.0f)
				{
					t = 0.0f;
					s = Clamp(-c / a, 0.0f, 1.0f);
				}
				else if (tnom > e)
				{
					t = 1.0f;
					s = Clamp((b - c) / a, 0.0f, 1.0f);
				}
				else
				{
					t = tnom / e;
				}
			}
		}
		c1 = p1 + d1 * s;
		c2 = p2 + d2 * t;
		return (c1 - c2).Dot(c1 - c2);
	}

	// �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�����̕������v�Z����֐�
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const Box& b)
	{
		float point[3] = { p.x, p.y, p.z };
		float min[3] = { b.c.x - b.r.x, b.c.y - b.r.y, b.c.z - b.r.z, };
		float max[3] = { b.c.x + b.r.x, b.c.y + b.r.y, b.c.z + b.r.z, };

		float sqDist = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			float v = point[i];
			if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
			if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
		}
		return sqDist;
	}

//------------------------------//
// �����ƎO�p�`�̌�������p		//
//------------------------------//

	// �O�p�`�̍\���́i�����ƎO�p�`�̌�������p�j
	struct Triangle
	{
		// �O�p�`�̕��ʕ�����
		DirectX::SimpleMath::Plane p;
		// ��BC�̕��ʕ������i�d�S���W�̒��_a�ɑ΂���d��u��^����j
		DirectX::SimpleMath::Plane edgePlaneBC;
		// ��CA�̕��ʕ������i�d�S���W�̒��_b�ɑ΂���d��v��^����j
		DirectX::SimpleMath::Plane edgePlaneCA;

		// �R���X�g���N�^���ŏՓ˔�����y�����邽�߂ɑO�����Ōv�Z���Ă���
		Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
		{
			DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);
			p = DirectX::SimpleMath::Plane(a, n);
			DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
			edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
			edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));
			p.Normalize(); edgePlaneBC.Normalize(); edgePlaneCA.Normalize();
			float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
			float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
			edgePlaneBC.x *= bc_scale; edgePlaneBC.y *= bc_scale; edgePlaneBC.z *= bc_scale; edgePlaneBC.w *= bc_scale;
			edgePlaneCA.x *= ca_scale; edgePlaneCA.y *= ca_scale; edgePlaneCA.z *= ca_scale; edgePlaneCA.w *= ca_scale;
		}
	};

	// ���������_�̌덷�œ�����ʂ�����̂ŏ����]�T������
	#define EPSILON 1.0e-06F

	/// <summary>
	/// �����ƎO�p�`�̌�������
	/// </summary>
	/// <param name="p">�����̎n�_</param>
	/// <param name="q">�����̏I�_</param>
	/// <param name="tri">�O�p�`</param>
	/// <param name="s">�����ƎO�p�`�̌����_</param>
	/// <returns>true�̏ꍇ�������Ă���</returns>
	static bool IntersectSegmentTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Triangle tri, DirectX::SimpleMath::Vector3* s)
	{
		float distp = p.Dot(tri.p.Normal()) + tri.p.D();
		if (distp < 0.0f) return false;
		float distq = q.Dot(tri.p.Normal()) + tri.p.D();
		if (distq >= 0.0f) return false;
		float denom = distp - distq;
		float t = distp / denom;
		*s = p + t * (q - p);
		float u = s->Dot(tri.edgePlaneBC.Normal()) + tri.edgePlaneBC.D();
		if (fabsf(u) < EPSILON) u = 0.0f;
		if (u < 0.0f || u > 1.0f) return false;
		float v = s->Dot(tri.edgePlaneCA.Normal()) + tri.edgePlaneCA.D();
		if (fabsf(v) < EPSILON) v = 0.0f;
		if (v < 0.0f) return false;
		float w = 1.0f - u - v;
		if (fabsf(w) < EPSILON) w = 0.0f;
		if (w < 0.0f) return false;
		return true;
	}

};

