
#include "MyCollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool CollisionNode::m_DebugVisible = true;


CollisionNode::CollisionNode()  :m_Trans(Vector3::Zero)
{
}

CollisionNode::~CollisionNode()
{
}

void CollisionNode::SetParent(MyLib::Object3D * parent)
{
	m_Obj.SetParent(parent);
}

void CollisionNode::SetTrans(DirectX::SimpleMath::Vector3 & trans)
{
	 m_Trans = trans; 
	 m_Obj.SetTranslation(trans); 
}

SphereNode::SphereNode()
{
	// �f�t�H���g�̔��a�P���[�g��
	m_localRadius = 1.0f;
}

void SphereNode::Initialize()
{
	m_Obj.Load(L"Resources/Model/Sphere.cmo");
}

void SphereNode::Update()
{

	m_Obj.SetTranslation(m_Trans);

	m_Obj.SetScale(Vector3(m_localRadius));

	m_Obj.Update();

	{// ���苅�̗v�f���v�Z
		const Matrix& worldm = m_Obj.GetWorld();

		// ���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		// ���f�����W�n�ł̉E�[�̓_
		Vector3 right(1, 0, 0);

		// ���[���h���W�n�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// ���苅�̗v�f����
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Render()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetTranslation(Vector3(m_localRadius));

	if (GetDebugVisible()) { m_Obj.Draw(); }
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//                          BoxNode�@�@�@�@�@�@�@�@�@�@�@�@�@ //
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

BoxNode::BoxNode() 
{
	m_size = Vector3(0.0f,0.0f,0.0f);
}

void BoxNode::Initialize() 
{
	m_size = Vector3(0.0f, 0.0f, 0.0f);
	m_Obj.Load(L"Resources/Model/box.cmo");
	SetPointPos();
}

void BoxNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	SetPointPos();
	m_Obj.Update();

}

void BoxNode::Render()
{
	m_Obj.SetTranslation(m_Trans);
	if (GetDebugVisible()) { m_Obj.Draw(); }
}

void BoxNode::SetPointPos()
{
	Pos0 = Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos1 = Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos2 = Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos3 = Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos4 = Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos5 = Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos6 = Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos7 = Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//                          CapsuleNode�@�@�@�@�@�@�@�@�@�@�@ //
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

CapsuleNode::CapsuleNode()
{
	//�����ݒ�
	Radius = 0.0f;
	Segment.Start = Vector3(0, 1, 0);
	Segment.Vec = Vector3(0, 0, 0);

	m_height = Segment.Start.y - Segment.Vec.y;

	if (Radius < 0)
	{
		Radius = Radius * -1;
	}
}

void CapsuleNode::Initialize()
{
	//m_Obj.LoadModel(L"Resources/CapsuleNode.cmo");
}

void CapsuleNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	SetPos();
	m_Obj.Update();
}

void CapsuleNode::Render()
{
	m_Obj.SetTranslation(m_Trans);
	if (GetDebugVisible()) { m_Obj.Draw(); }
}

//�������߂�A���̂��Əオ���܂�
void CapsuleNode::SetSize(Vector3 size)
{
	Segment.Vec = Vector3(size);

	Segment.Start = Vector3(Segment.Vec.x, Segment.Vec.y + m_height, Segment.Vec.z);
}

void CapsuleNode::SetHiehtRadius(float height, float radius)
{
	Radius = radius;
}

void CapsuleNode::SetPos()
{
	Segment.Vec = Vector3(m_Trans);

	Segment.Start = Vector3(Segment.Vec.x, Segment.Vec.y + m_height, Segment.Vec.z);
}

PlanarNode::PlanarNode()
{
}

void PlanarNode::Initialize()
{
}

void PlanarNode::Update()
{
}

void PlanarNode::Render()
{
}

void PlanarNode::SetVertex4(DirectX::SimpleMath::Vector3 Ver0, DirectX::SimpleMath::Vector3 Ver1, DirectX::SimpleMath::Vector3 Ver2, DirectX::SimpleMath::Vector3 Ver3)
{
	//0,1�͑O
	Vertex[0] = Ver0;
	Vertex[1] = Ver1;
	//2,3�͌�
	Vertex[2] = Ver2;
	Vertex[3] = Ver3;
}
