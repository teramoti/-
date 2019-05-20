#pragma once
#include "../Base/SceneBase.h"
#include "SkyDome.h"
#include "CountDown.h"
#include "GameTime.h"
#include "../../ADX2/ADX2Le.h"
//#include "../../GameSystem/Camera.h"
#include "TestPlayer.h"
#include "../../GameSystem/Camera.h"
#include "../../GameSystem/TpsCamera.h"
#include <SpriteFont.h>

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
	void Update(DX::StepTimer& stemTimer)override;
	// <�`��֐�>
	void Render()override;
	// <�I���֐�>
	void Finalize()override;

public:
	void HitManager();
	void SpriteRender();

	void FileLoad();
	void StageCheckPoint();//1�X�e�[�W�̃`�F�b�N�|�C���g
	void StageCollision();//1�X�e�[�W�̃`�F�b�N�|�C���g

private:
	const float PLAYER_RISE = 5.0f;
	//�J����
	ID3D11Device* m_device;//�f�o�C�X�擾�p�ϐ�
	ID3D11DeviceContext* m_context;//�R���e�L�X�g�擾�ϐ�
	std::unique_ptr<TpsCamera> m_Camera;//�J�����N���X�̍쐬

	//�v���C���[
	std::unique_ptr<TestPlayer> m_player;

	//�X�J�C�h�[��
	std::unique_ptr<SkyDome>  m_skyDome;

	DX::StepTimer stept;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	CollisionManager*				m_CollisionManager;
	//����
	std::unique_ptr<Time>			m_time;
	//�`�F�b�N�|�C���g
	std::unique_ptr<CheckPoint>		m_CheckPoint;

	CountDown*						m_Count;
	GameTime*						m_GameTime;
	//GameGoal* m_Goal;
	bool m_Node;
	bool m_startFlag;//�Q�[�����n�܂��Ă���̂��̃t���O�p�ϐ�
	float m_GameTimer;//�Q�[���̎��ԗp�ϐ�
	int m_CouceCount;
	bool m_start;//�n�܂��Ă��邩��bool
	int m_GoalNum;//�S�[���������̃t���[���������񂷂悤�ϐ�
	int m_GoalRank;//�G���S�[�������̂��̏���(���͕s�v�j
	int m_StageNum;//�X�e�[�W�̔ԍ�

	bool m_goalFlag;//�S�[�����Ă��邩�̃t���O�p�ϐ�

	//�J�n�̃J�E���g�_�E��
	float counter = 180.0f;
	bool m_SceneFlag;//�V�[���ύX�p�t���O

	std::unique_ptr<CollisionMesh> m_stageMesh;//�����蔻��p���b�V��
	std::unique_ptr<CollisionMesh> m_stageMesh2;//�O���̓����蔻��p���b�V��
	std::unique_ptr<Cource> m_cource;//�R�[�X�̃N���X�쐬�p�ϐ�
	MyLibrary::ADX2Le* m_adx2le;	// �T�E���h


	CriAtomExPlaybackId m_criAtomExPlaybackId;	// ���y���L���p�ϐ�

	DirectX11& m_directX = DirectX11::Get();

};