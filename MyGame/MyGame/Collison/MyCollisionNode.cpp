
#include "MyCollisionNode.h"




bool CollisionNode::m_DebugVisible = true;


CollisionNode::CollisionNode()  :m_translation(DirectX::SimpleMath::Vector3::Zero)
{
	
}

CollisionNode::~CollisionNode()
{
}

void CollisionNode::CreateResource()
{
}

void CollisionNode::SetParent(Teramoto::Object3D * parent)
{
	//m_obj.SetParent(parent);
}

void CollisionNode::SetTrans(DirectX::SimpleMath::Vector3 & trans)
{
	 m_translation = trans; 
	 m_obj.SetTranslation(trans); 
}

SphereNode::SphereNode()
{
	// デフォルトの半径１メートル
	m_localRadius = 1.0f;
}

void SphereNode::Initialize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

	//m_obj.Load(L"Resources/Model/Sphere.cmo");
}

void SphereNode::Update()
{

	m_obj.SetTranslation(m_translation);

	m_obj.SetScale(DirectX::SimpleMath::Vector3(m_localRadius));

	m_obj.Update();

	{
		// 判定球の要素を計算
		const DirectX::SimpleMath::Matrix& worldm = m_obj.GetWorld();

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

void SphereNode::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
	m_obj.SetTranslation(m_translation);
	m_obj.SetTranslation(DirectX::SimpleMath::Vector3(m_localRadius));

	if (GetDebugVisible()) { m_obj.Draw(); }
}

void SphereNode::CreateResource()
{
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
	//m_obj.Load(L"Resources/Model/box.cmo");
	SetPointPos();
}

void BoxNode::Update()
{
	m_obj.SetTranslation(m_translation);
	SetPointPos();
	m_obj.Update();

}

void BoxNode::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
	m_obj.SetTranslation(m_translation);
	DirectX::SimpleMath::Matrix world;

	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.GetStates(), world, view, proj);
	if (GetDebugVisible()) { m_obj.Draw(); }
}

void BoxNode::CreateResource()
{
}

void BoxNode::SetPointPos()
{
	Pos0 = DirectX::SimpleMath::Vector3(m_translation.x - (m_size.x / 2.0f), m_translation.y - (m_size.y / 2.0f), m_translation.z - (m_size.z / 2.0f));
	Pos1 = DirectX::SimpleMath::Vector3(m_translation.x + (m_size.x / 2.0f), m_translation.y - (m_size.y / 2.0f), m_translation.z - (m_size.z / 2.0f));
	Pos2 = DirectX::SimpleMath::Vector3(m_translation.x - (m_size.x / 2.0f), m_translation.y + (m_size.y / 2.0f), m_translation.z - (m_size.z / 2.0f));
	Pos3 = DirectX::SimpleMath::Vector3(m_translation.x + (m_size.x / 2.0f), m_translation.y + (m_size.y / 2.0f), m_translation.z - (m_size.z / 2.0f));
	Pos4 = DirectX::SimpleMath::Vector3(m_translation.x - (m_size.x / 2.0f), m_translation.y - (m_size.y / 2.0f), m_translation.z + (m_size.z / 2.0f));
	Pos5 = DirectX::SimpleMath::Vector3(m_translation.x + (m_size.x / 2.0f), m_translation.y - (m_size.y / 2.0f), m_translation.z + (m_size.z / 2.0f));
	Pos6 = DirectX::SimpleMath::Vector3(m_translation.x - (m_size.x / 2.0f), m_translation.y + (m_size.y / 2.0f), m_translation.z + (m_size.z / 2.0f));
	Pos7 = DirectX::SimpleMath::Vector3(m_translation.x + (m_size.x / 2.0f), m_translation.y + (m_size.y / 2.0f), m_translation.z + (m_size.z / 2.0f));
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
	//m_obj.LoadModel(L"Resources/CapsuleNode.cmo");
}

void CapsuleNode::Update()
{
	m_obj.SetTranslation(m_translation);
	SetPos();
	m_obj.Update();
}

void CapsuleNode::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
	m_obj.SetTranslation(m_translation);
	if (GetDebugVisible()) { m_obj.Draw(); }
}

void CapsuleNode::CreateResource()
{
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
	Segment.Vec = DirectX::SimpleMath::Vector3(m_translation);

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

void PlanarNode::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
}

void PlanarNode::CreateResource()
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
