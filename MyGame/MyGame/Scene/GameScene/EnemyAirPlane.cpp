#include "EnemyAirPlane.h"
#include "../../Collison/DebugBox.h"

#define	MAX_DATA		3
#define MAX_PARAMS		4

#define	MAX_SPEED_DATA			2
#define MAX_SPEED_PARAMS		3


EnemyAirPlane::EnemyAirPlane()
{
}

EnemyAirPlane::~EnemyAirPlane()
{
}

void EnemyAirPlane::Initilize(Shadow* shadow)
{
	m_shadow = shadow;
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

	CreateResources();

	m_translation = DirectX::SimpleMath::Vector3(0, 0, 0);
	m_shadow->Initialize();

	float AngleSet[MAX_DATA][MAX_PARAMS] = {
		0.8,	0.0f,	0.0f,	0.25f,
		0.0f,	0.8f,   0.0f,	0.5f,
		0.0f,	0.0f,	0.9f,	0.75f,


	};

	float SpeedSet[MAX_SPEED_DATA][MAX_SPEED_PARAMS] = {
		0.3f,	0.8f,	0.5f,
		0.8f,	0.3f,	0.2f,

	};

	// �j���[�����l�b�g���[�N�I�u�W�F�N�g�𐶐�����

	// �j���[�����l�b�g���[�N������������(���͑w:3�A�B��w:3�A�o�͑w:1)
	// Initialize neural network object
	m_theAngleBrain.Initialize(3, 3, 1);

	// �w�K����ݒ肷��
	// Setup learning rate
	m_theAngleBrain.SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	m_theAngleBrain.SetMomentum(true, 0.8);

	double	error = 1.0;
	int		count = 0;

	// �@�B�w�K����
	while (error > 0.01 && count < 10000) 
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA; i++) 
		{
			//��
			//�����ɓ��邩
			//0.0(���Ȃ�)
			//0.8(����)
			m_theAngleBrain.SetInput(0, AngleSet[i][0]);
			//�^��
			//�^�񒆂ɓ��邩
			//0.0(���Ȃ�)
			//0.8(����)
			m_theAngleBrain.SetInput(1, AngleSet[i][1]);
			//�E
			//�E�ɓ��邩
			//0.0(���Ȃ�)
			//0.8(����)
			m_theAngleBrain.SetInput(2, AngleSet[i][2]);
		
			// �U��
			m_theAngleBrain.SetDesiredOutput(0, AngleSet[i][3]);

			// �O���`�d����(Feed forward)
			m_theAngleBrain.FeedForward();
			// �덷���v�Z����(Calculate error)
			error += m_theAngleBrain.CalculateError();
			// �덷�t�`�d����(Back propagate)
			m_theAngleBrain.BackPropagate();
		}
		// �덷���v�Z����
		error = error / MAX_DATA;
	}


	// �j���[�����l�b�g���[�N�I�u�W�F�N�g�𐶐�����

	// �j���[�����l�b�g���[�N������������(���͑w:3�A�B��w:3�A�o�͑w:1)
	// Initialize neural network object
	m_theSpeedBrain.Initialize(3, 3, 1);

	// �w�K����ݒ肷��
	// Setup learning rate
	m_theSpeedBrain.SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	m_theSpeedBrain.SetMomentum(true, 0.8);
	
	
	error = 1.0;
	
	count = 0;

	// �@�B�w�K����
	while (error > 0.01 && count < 10000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA; i++)
		{
			//��
			//�����ɓ��邩
			//0.0(���Ȃ�)
			//0.8(����)
			m_theSpeedBrain.SetInput(0, SpeedSet[i][0]);
			//�^��
			//�^�񒆂ɓ��邩
			//0.0(���Ȃ�)
			//0.8(����)
			m_theSpeedBrain.SetInput(1, SpeedSet[i][1]);

			// �U��
			m_theSpeedBrain.SetDesiredOutput(0, SpeedSet[i][2]);

			// �O���`�d����(Feed forward)
			m_theSpeedBrain.FeedForward();
			// �덷���v�Z����(Calculate error)
			error += m_theSpeedBrain.CalculateError();
			// �덷�t�`�d����(Back propagate)
			m_theSpeedBrain.BackPropagate();
		}
		// �덷���v�Z����
		error = error / MAX_DATA;
	}

	m_box.c = m_translation;
	m_box.r = DirectX::SimpleMath::Vector3(0.5, 2.0, 0.5);


}

void EnemyAirPlane::Update(DX::StepTimer& timer)
{
	Teramoto::Object3D::Update();

	if (timer.GetFrameCount() % 60 == 0)
	{
		// ���̓f�[�^���j���[�����l�b�g���[�N�ɃZ�b�g����
		m_theAngleBrain.SetInput(0, 0.0);
		m_theAngleBrain.SetInput(1, 0.0);
		m_theAngleBrain.SetInput(2, 0.8);

		// �j���[�����l�b�g���[�N�ɖ₢���킹��
		m_theAngleBrain.FeedForward();


		// ���̓f�[�^���j���[�����l�b�g���[�N�ɃZ�b�g����
		m_theSpeedBrain.SetInput(0, 0.8);
		m_theSpeedBrain.SetInput(1, 0.3);

		// �j���[�����l�b�g���[�N�ɖ₢���킹��
		m_theSpeedBrain.FeedForward();

		int i = 0;
	}

	float result = m_theAngleBrain.GetOutput(0);
	float result2 = m_theSpeedBrain.GetOutput(0);

	int i = 0;

	m_angle = result;

	//Teramoto::Object3D::SetAngle(m_angle);
	//Teramoto::Object3D::SetTranslation(m_translation);


}

void EnemyAirPlane::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//���f���̕`��
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
	//DebugBox* playerdebugbox = new DebugBox(m_directX.GetDevice().Get(), m_box.c, m_box.r);
	//playerdebugbox->Draw(m_directX.GetContext().Get(), *m_directX.Get().GetStates(), m_world, view, proj);
	m_shadow->Render(view, proj, this, 0.3f);

}

void EnemyAirPlane::CreateResources()
{
	//���f���̐ݒ�
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Player.cmo", *m_directX11.Get().GetEffect());

}
