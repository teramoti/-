
#include "MyCollisionNode.h"




bool CollisionNode::m_DebugVisible = true;


CollisionNode::CollisionNode()  :m_Trans(DirectX::SimpleMath::Vector3::Zero)
{
}

CollisionNode::~CollisionNode()
{
}

void CollisionNode::SetParent(Teramoto::Object3D * parent)
{
	//m_Obj.SetParent(parent);
}

void CollisionNode::SetTrans(DirectX::SimpleMath::Vector3 & trans)
{
	 m_Trans = trans; 
	 m_Obj.SetTranslation(trans); 
}

SphereNode::SphereNode()
{
	// デフォルトの半径１メートル
	m_localRadius = 1.0f;
}

void SphereNode::Initialize()
{
	//m_Obj.Load(L"Resources/Model/Sphere.cmo");
}

void SphereNode::Update()
{

	m_Obj.SetTranslation(m_Trans);

	m_Obj.SetScale(DirectX::SimpleMath::Vector3(m_localRadius));

	m_Obj.Update();

	{
		// 判定球の要素を計算
		const DirectX::SimpleMath::Matrix& worldm = m_Obj.GetWorld();

		// モデル座標系での中心点
		DirectX::SimpleMath::Vector3 center(0, 0, 0);
		// モデル座標系での右端の点
		DirectX::SimpleMath::Vector3 right(1, 0, 0);

		// ワールド座標系に変換
		center = DirectX::SimpleMath::Vector3::Transform(center, worldm);
		right = DirectX::SimpleMath::Vector3::Transform(right, worldm);

		// 判定球の要素を代入
		Sphere::Center = center;
		Sphere::Radius = DirectX::SimpleMath::Vector3::Distance(center, right);
	}
}

void SphereNode::Render()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetTranslation(DirectX::SimpleMath::Vector3(m_localRadius));

	if (GetDebugVisible()) { m_Obj.Draw(); }
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//                          BoxNode　　　　　　　　　　　　　 //
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

BoxNode::BoxNode() 
{
	m_size = DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f);
}

void BoxNode::Initialize() 
{
	m_size = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	//m_Obj.Load(L"Resources/Model/box.cmo");
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
	Pos0 = DirectX::SimpleMath::Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos1 = DirectX::SimpleMath::Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos2 = DirectX::SimpleMath::Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos3 = DirectX::SimpleMath::Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z - (m_size.z / 2.0f));
	Pos4 = DirectX::SimpleMath::Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos5 = DirectX::SimpleMath::Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y - (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos6 = DirectX::SimpleMath::Vector3(m_Trans.x - (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
	Pos7 = DirectX::SimpleMath::Vector3(m_Trans.x + (m_size.x / 2.0f), m_Trans.y + (m_size.y / 2.0f), m_Trans.z + (m_size.z / 2.0f));
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//                          CapsuleNode　　　　　　　　　　　 //
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

CapsuleNode::CapsuleNode()
{
	//初期設定
	Radius = 0.0f;
	Segment.Start = DirectX::SimpleMath::Vector3(0, 1, 0);
	Segment.Vec = DirectX::SimpleMath::Vector3(0, 0, 0);

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

//下を決める、そのあと上が決まる
void CapsuleNode::SetSize(DirectX::SimpleMath::Vector3 size)
{
	Segment.Vec = DirectX::SimpleMath::Vector3(size);

	Segment.Start = DirectX::SimpleMath::Vector3(Segment.Vec.x, Segment.Vec.y + m_height, Segment.Vec.z);
}

void CapsuleNode::SetHiehtRadius(float height, float radius)
{
	Radius = radius;
}

void CapsuleNode::SetPos()
{
	Segment.Vec = DirectX::SimpleMath::Vector3(m_Trans);

	Segment.Start = DirectX::SimpleMath::Vector3(Segment.Vec.x, Segment.Vec.y + m_height, Segment.Vec.z);
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
	//0,1は前
	Vertex[0] = Ver0;
	Vertex[1] = Ver1;
	//2,3は後
	Vertex[2] = Ver2;
	Vertex[3] = Ver3;
}
