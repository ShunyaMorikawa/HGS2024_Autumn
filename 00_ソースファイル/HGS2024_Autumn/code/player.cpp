//========================================
//
// �v���C���[[player.cpp]
// Author�F�X��x��
//
//========================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"
#include "particle.h"
#include "useful.h"
#include "gauge.h"
#include "main.h"
#include "model.h"
#include "motion.h"
#include "effect.h"
#include "object2D.h"
#include "object3D.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "calculation.h"

#include "stageobj.h"
#include "obstacle.h"
#include "reverse.h"

//========================================
// �萔��`
//========================================
namespace
{
	const int LIFE = 10;			// �̗�
	const float SPEED = 500.0f;		// ���x
	const float JUMP_MOVE = 1500.0f;	// �W�����v��
	const float JUMP_SAB = JUMP_MOVE * 0.04f;	// �W�����v����
	const float ROLL_TIME = 1.0f;	// �]����p������
	const float RADIUS = 90.0f;		// ���a
	const float HEIGHT = 200.0f;	// �g��
	const float HEIGHT_SCALE = 0.5f;	// �]���蒆�̐g���{��
	const int DAMAGE_COUNT = 80;		// �_���[�W�J�E���g
}

//========================================
// �ÓI�����o�ϐ�
//========================================
CPlayer* CPlayer::m_pPlayer = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority),
m_apNumModel	(0),			// ���f���̑���
m_nLife			(0),			// �̗�
m_nOldMotion	(0),			// �O��̃��[�V����
m_WalkCounter	(0),			// ���s���G�t�F�N�g�o���p�̃J�E���^�[
m_State			(STATE_NONE),	// ���
m_fRadius		(0.0f),			// ���a
m_fHeight		(0.0f),			// �g��
m_fRollTime		(0.0f),			// �]���莞��
m_bJump			(false),		// �W�����v�t���O
m_bRoll			(false),		// �]����t���O
m_pEffect		(nullptr),		// �G�t�F�N�g�̃|�C���^
m_pGauge		(nullptr),		// �Q�[�W�̃|�C���^
m_type			(TYPE_NONE),	// �^�C�v
m_typeDefault	(TYPE_NONE)		// �f�t�H���g�^�C�v
{
	memset(&m_apModel[0], 0, sizeof(m_apModel));	//���f�����
}

//========================================
//�f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{
}

//========================================
//�v���C���[�̐���
//========================================
CPlayer *CPlayer::Create(std::string pfile)
{
	if (m_pPlayer == nullptr)
	{
		//�v���C���[����
		m_pPlayer = new CPlayer;

		//������
		m_pPlayer->Init(pfile);
	}

	//�|�C���^��Ԃ�
	return m_pPlayer;
}

//========================================
// ������
//========================================
HRESULT CPlayer::Init(std::string pfile)
{
	// �L�����̏�����
	CCharacter::Init(pfile);

	// �v���C���[��Ԃ̏�����
	m_State = STATE_NORMAL;
	m_typeDefault = m_type = TYPE_TURTLE;

	// �ʒu�ݒ�
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �����ݒ�
	SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �ړ��ʐݒ�
	SetMove(D3DXVECTOR3(SPEED, 0.0f, 0.0));

	// ���s���̃J�E���^�[
	m_WalkCounter = 0;

	// ����������
	m_nLife = LIFE;
	m_fRadius = RADIUS;
	m_fHeight = HEIGHT;

	// �Q�[�W����
	m_pGauge = CGauge::Create(m_nLife);

	// �ʒu�ݒ�
	m_pGauge->SetPos(D3DXVECTOR3(50.0f, 600.0f, 0.0f));

	// �T�C�Y�ݒ�
	m_pGauge->SetSize(50.0f, 50.0f);

	return S_OK;
}

//========================================
//�I��
//========================================
void CPlayer::Uninit(void)
{
	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	// �I��
	CCharacter::Uninit();
	m_pPlayer = nullptr;
}

//========================================
//�X�V
//========================================
void CPlayer::Update(void)
{
	// ���g�̏����擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// �f���^�^�C���̎擾
	const float fDeltaTime = CManager::GetInstance()->GetDeltaTime();

	// �J�����̒Ǐ]�ݒ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->Following(pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// �ړ�����
	Move(pos, move, fDeltaTime);

	// ���n����
	Land(pos, move);

	// �_���[�W�J�E���^�[
	DamageCounter();

	// �X�e�[�W�I�u�W�F�Ƃ͈̔̓`�F�b�N
	CheckStageObjRange();

	// ���]�I�u�W�F�̓����蔻��
	CollisionReverseObj();

	// �Q�[�W�ɑ̗͐ݒ�
	m_pGauge->SetLife(m_nLife);

	// ���[�V����
	Motion();

	// ����ݒ�
	SetPos(pos);
	SetMove(move);

	// �����蔻�菈��
	Collision();

	D3DXVECTOR3 rot = GetRot();

	// �f�o�b�O�\��
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̈ʒu�F%f�A%f�A%f\n", pos.x, pos.y, pos.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̈ړ��ʁF%f�A%f�A%f\n", move.x, move.y, move.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̌����F%f�A%f�A%f\n", rot.x, rot.y, rot.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̃T�C�Y�F%f�A%f�A%f\n", m_fRadius, m_fHeight, m_fRadius);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̗̑́F%d\n", m_nLife);
}

//========================================
//�`��
//========================================
void CPlayer::Draw(void)
{
	// �`��
	CCharacter::Draw();
}

//========================================
// �_���[�W�J�E���^�[
//========================================
void CPlayer::DamageCounter()
{
	// �_���[�W�J�E���g��0�ɂ���
	m_nDamageCount--;

	if (m_nDamageCount <= 0)
	{ // �J�E���g�����l�ȉ��̏ꍇ

		// �J�E���g��␳����
		m_nDamageCount = 0;
	}
}

//========================================
// ���[�V�����Ǘ�
//========================================
void CPlayer::Motion()
{
	// ���[�V�������擾
	CMotion* pMotion = GetMotion();

	// ���[�V������null�̏ꍇ�֐��𔲂���
	if (pMotion == nullptr)
	{
		assert(false);
		return;
	}

	// ���[�V������ݒ�
	if (m_bJump) // �W�����v���
	{
		// TODO : �W�����v���[�V������ݒ�
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_STRONGATTACK);
		DebugProc::Print(DebugProc::POINT_CENTER, "�W�����v���\n");
	}
	else if (m_bRoll) // �]������
	{
		// TODO : �]���胂�[�V������ݒ�
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_CUTDOWN);
		DebugProc::Print(DebugProc::POINT_CENTER, "�]������\n");
	}
	else // ���̑��̏��
	{
		// ���s���[�V������ݒ�
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_WALK);
	}

	// ���[�V�������X�V
	pMotion->Update();
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Move(D3DXVECTOR3& pos, D3DXVECTOR3& move, const float fDeltaTime)
{
	// �C���v�b�g���̎擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetInputPad();

#ifdef _DEBUG
	// 2�L�[�ŏ����ʒu�ɖ߂�
	if (pKeyboard->GetTrigger(DIK_2))
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	// �f�o�b�O���͉E�V�t�g�������Ȃ��Ɠ����Ȃ�
	if (!pKeyboard->GetPress(DIK_RSHIFT))
	{
		return;
	}

#endif

	// ��Ԃ̐؂�ւ�
	SwitchType(pPad, pKeyboard);

	// ��Ԃ��Ƃ̏���
	switch (m_type)
	{
	case TYPE_RABBIT:
		// �W�����v����
		Jump(move, pPad, pKeyboard);
		DebugProc::Print(DebugProc::POINT_CENTER, "���A�e�ł��I�I�I\n");
		break;

	case TYPE_TURTLE:
		// �]���菈��
		Roll(move, pPad, pKeyboard, fDeltaTime);
		DebugProc::Print(DebugProc::POINT_CENTER, "���A�T�ł��I�I�I\n");
		break;

	default:
		assert(false);
		break;
	}

	// TODO : �^�C�}�[���o���������������ǉ�

	// ���W�Ɉړ��ʂ����Z
	pos += move * fDeltaTime;
}

//==========================================
//  �W�����v����
//==========================================
void CPlayer::Jump(D3DXVECTOR3& move, CInputPad* pPad, CInputKeyboard* pKeyboard)
{
	// �W�����v���̏ꍇ�֐��𔲂���
	if (m_bJump) { return; }

	// �{�^���������ꂽ��W�����v����
	if (pPad->GetTrigger(CInputPad::BUTTON_A, 0) || pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �W�����v�t���O��ݒ�
		m_bJump = true;

		// �ړ��ʂ����Z
		move.y += JUMP_MOVE;
	}
}

//==========================================
//  �]���菈��
//==========================================
void CPlayer::Roll(D3DXVECTOR3& move, CInputPad* pPad, CInputKeyboard* pKeyboard, const float fDeltaTime)
{
	// �]���蒆�̏ꍇ���Ԃ����Z
	if (m_bRoll)
	{
		// ���Z
		m_fRollTime += fDeltaTime;

		// ��]
		MyLib::Vector3 rot = GetRot();
		rot.y = UtilFunc::Correction::EasingLinear(0.0f, (D3DX_PI * 2.0f) * 10.0f, 0.0f, ROLL_TIME, m_fRollTime);
		rot.y += -D3DX_PI * 0.5f;
		SetRot(rot);

		Myparticle::Create(Myparticle::TYPE::TYPE_ROLLINGTURTLE, GetPos());

		// ��莞�Ԍo�߂��Ă��Ȃ��ꍇ�֐��𔲂���
		if (m_fRollTime < ROLL_TIME) { return; }

		// �]�����Ԃ���������
		m_fRollTime = 0.0f;
		m_bRoll = false;
		m_fHeight = HEIGHT;

		return;
	}

	// �{�^���������ꂽ��]�����ԂɂȂ�
	if (pPad->GetTrigger(CInputPad::BUTTON_A, 0) || pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �t���O��true
		m_bRoll = true;

		// �g�������炷
		m_fHeight *= HEIGHT_SCALE;
	}
}

//==========================================
//  ��Ԃ̐؂�ւ�
//==========================================
void CPlayer::SwitchType(CInputPad* pPad, CInputKeyboard* pKeyboard)
{
	// �]�����Ԃ������̓W�����v���̏ꍇ�֐��𔲂���
	if (m_bJump || m_bRoll) { return; }

	// �^�C�v���f�t�H���g�ŏ㏑������
	m_type = m_typeDefault;

	// �{�^����������Ă��Ȃ��ꍇ�֐��𔲂���
	if(!pPad->GetPress(CInputPad::BUTTON_LB, 0) && !pKeyboard->GetPress(DIK_LSHIFT)) { return; }

	// �f�t�H���g�^�C�v�����ă^�C�v��ύX����
	m_type = m_typeDefault == TYPE_TURTLE ? TYPE_RABBIT : TYPE_TURTLE;
}

//==========================================
//  ���n����
//==========================================
void CPlayer::Land(D3DXVECTOR3& pos, D3DXVECTOR3& move)
{
	// y���W��0.0����������ꍇ�␳����
	if (pos.y < 0.0f)
	{
		// �W�����v�t���O��false
		m_bJump = false;

		// ���W��␳
		pos.y = 0.0f;

		// �ړ��ʂ��폜
		move.y = 0.0f;
	}

	// �W�����v���Ȃ�ړ��ʂ�����������
	if (m_bJump)
	{
		move.y -= JUMP_SAB;
	}
}

//==========================================
// �_���[�W�֐�
//==========================================
void CPlayer::Damage()
{
	// �_���[�W�J�E���g��ݒ肷��
	m_nDamageCount = DAMAGE_COUNT;

	// ���������Z����
	m_nLife--;

	// �p�[�e�B�N�����o��
	Myparticle::Create(Myparticle::TYPE_DEATH, GetPos());
}

//==========================================
// �X�e�[�W�I�u�W�F�͈̔̓`�F�b�N
//==========================================
void CPlayer::CheckStageObjRange()
{
	// �X�e�[�W�I�u�W�F�̃��X�g�擾
	CListManager<CStageObj> list = CStageObj::GetList();

	// �I�[��ۑ�
	std::list<CStageObj*>::iterator itr = list.GetEnd();
	CStageObj* pObj = nullptr;

	// �ʒu�擾
	MyLib::Vector3 pos = GetPos();

	// �I�[�܂Ń��[�v
	while (list.ListLoop(itr))
	{
		CStageObj* pObj = *itr;
		pObj->CollisionRange(pos);
	}
}

//==========================================
// ���]�I�u�W�F�̓����蔻��
//==========================================
void CPlayer::CollisionReverseObj()
{
	// ���]�I�u�W�F�̃��X�g�擾
	CListManager<CReverse> list = CReverse::GetList();

	// �I�[��ۑ�
	std::list<CReverse*>::iterator itr = list.GetEnd();
	CReverse* pObj = nullptr;

	// �ʒu�擾
	D3DXMATRIX mtx = GetmtxWorld();

	// �I�[�܂Ń��[�v
	while (list.ListLoop(itr))
	{
		CReverse* pObj = *itr;
		if (pObj->Collision(mtx, MyLib::Vector3(RADIUS, HEIGHT, RADIUS)))
		{
			// ���]
			m_typeDefault = (m_typeDefault == TYPE_RABBIT) ? PLAYERTYPE::TYPE_TURTLE : PLAYERTYPE::TYPE_RABBIT;
			return;
		}
	}
}

//==========================================
// �����蔻��
//==========================================
void CPlayer::Collision()
{
	// �_���[�W���󂯂Ȃ���Ԃ̏ꍇ�A���̊֐��𔲂���
	if (m_nDamageCount > 0) { return; }

	// ��Q���̃��X�g�擾
	CListManager<CObstacle> list = CObstacle::GetList();

	// �I�[��ۑ�
	std::list<CObstacle*>::iterator itr = list.GetEnd();
	CObstacle* pObj = nullptr;

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXMATRIX mtx;
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	SetmtxWorld(mtx);

	// �I�[�܂Ń��[�v
	while (list.ListLoop(itr))
	{
		CObstacle* pObj = *itr;

		if (pObj->Collision(mtx, D3DXVECTOR3(RADIUS, HEIGHT, RADIUS)))
		{ // �����蔻��ɓ��������ꍇ

			// �_���[�W����
			Damage();
		}
	}
}
