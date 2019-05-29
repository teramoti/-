#pragma once
#include "../Base/SceneBase.h"
#include "SkyDome.h"
#include "CountDown.h"
#include "GameTime.h"
//#include "../../ADX2/ADX2Le.h"

#include "Player.h"
#include "../../GameSystem/Camera.h"
#include "TpsCamera.h"
#include <SpriteFont.h>
#include "Shadow.h"
#include "SpriteBatch.h"
#include "Cource.h"
#include "CheckPoint.h"
#include "Time.h"
#include "../../Collison/CollisionMesh.h"
#include "../../Collison/MyCollisionManager.h"
#include "../../Utillity/DirectX11.h"
class GameScene : public SceneBase
{
public:
	GameScene(SceneManager* scenemaneger);
	~GameScene();
public:
	// <�������֐�>
	void Initialize() override;
	// <�X�V�֐�>
	void Update(const DX::StepTimer& stemTimer)override;
	// <�`��֐�>
	void Render()override;
	// <�I���֐�>
	void Finalize()override;

public:
	//�����蔻����܂Ƃ߂�֐�
	void DetectCollisionManager();
	//�摜�̕`��
	void SpriteRender();

	//CheckPoint�Ƃ̂�����͂�Ă��̊֐�
	void DetectCollisionPlayerToCheckPoint();
	//Mesh�Ƃ̂�����͂�Ă��̊֐�
	void DetectCollisionPlayerToMesh();

	void UpdatePlayerFeller();
private:
	const float PLAYER_RISE = 5.0f;

	//�J�����N���X�̍쐬
	std::unique_ptr<TpsCamera> m_camera;

	//�v���C���[
	std::unique_ptr<Player> m_player;

	//�X�J�C�h�[��
	std::unique_ptr<SkyDome>  m_skyDome;

	DX::StepTimer stept;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	CollisionManager*				m_collisionManager;
	//����
	std::unique_ptr<Time>			m_time;
	//�`�F�b�N�|�C���g�N���X�̒�`
	std::unique_ptr<CheckPoint>		m_checkPoint;
	//�J�E���g�_�E���N���X�̒�`
	CountDown*						m_count;
	//�Q�[���̎��ԃN���X�̒�`
	GameTime*						m_gameTime;
	//GameGoal* m_Goal;

	bool m_Node;
	//�Q�[�����n�܂��Ă���̂��̃t���O�p�ϐ�
	bool m_startFlag;
	//�Q�[���̎��ԗp�ϐ�
	float m_gameTimer;
	int m_CouceCount;
	//Start�������̃t���O
	bool m_start;
	//�S�[���������̃t���[���������񂷂悤�ϐ�
	int m_GoalNum;
	//�G���S�[�������̂��̏���(���͕s�v�j
	int m_GoalRank;
	//�X�e�[�W�̔ԍ�
	int m_StageNum;

				   //�S�[�����Ă��邩�̃t���O�p�ϐ�
	bool m_goalFlag;

	//�J�n�̃J�E���g�_�E��
	float counter = 180.0f;
	//�V�[���ύX�p�t���O
	bool m_SceneFlag;

	//�����蔻��p���b�V��
	std::unique_ptr<CollisionMesh> m_stageMesh;
	//�O���̓����蔻��p���b�V��
	std::unique_ptr<CollisionMesh> m_stageMesh2;
	//�R�[�X�̃N���X�쐬�p�ϐ�
	std::unique_ptr<Cource> m_cource;
	// �T�E���h
	//MyLibrary::ADX2Le* m_adx2le;	
	//�e�N���X�̒�`
	Shadow* m_shadow;
	// ���y���L���p�ϐ�
	//CriAtomExPlaybackId m_criAtomExPlaybackId;	

	//�G��
	std::vector<DirectX::SimpleMath::Vector3> m_feelers;
	
	//DirectXGraphicsObject�ւ̎Q��
	DirectX11& m_directX = DirectX11::Get();

};