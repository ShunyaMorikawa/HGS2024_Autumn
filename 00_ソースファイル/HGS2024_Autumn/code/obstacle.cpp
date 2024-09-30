//========================================
//
// ��Q���̏���[obstacle.cpp]
// Author�F��������
//
//========================================
#include "obstacle.h"
#include "model.h"

#include "obstacleTree.h"
#include "obstacleRiver.h"
#include "obstacleStone.h"
#include "obstacleHole.h"
#include "obstacleSoftRock.h"

//========================================
//���O���
//========================================
namespace
{
	const char* MODEL[] =		// ���f���̃p�X
	{
		"data\\MODEL\\obstacle\\wood00.x",		// ��
		"data\\MODEL\\obstacle\\wood00.x",		// ��
		"data\\MODEL\\obstacle\\wood00.x",		// ��
		"data\\MODEL\\obstacle\\wood00.x",		// ��
		"data\\MODEL\\obstacle\\wood00.x",		// �_�炩����
	};
}

//========================================
//�R���X�g���N�^
//========================================
CObstacle::CObstacle() : CStageObj(),
m_type(TYPE_TREE)
{//�l���N���A
}

//========================================
//�f�X�g���N�^
//========================================
CObstacle::~CObstacle()
{
}

//========================================
// ������
//========================================
HRESULT CObstacle::Init(void)
{
	if (FAILED(CStageObj::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ���f������
	m_pModel = CModel::Create(MODEL[m_type]);
	m_pModel->SetType(CModel::TYPE_NOT_HIERARCHY);
	m_pModel->SetPosition(GetPos());

	return S_OK;
}

//========================================
// �I��
//========================================
void CObstacle::Uninit(void)
{
	// �I��
	CStageObj::Uninit();
}

//========================================
// �X�V
//========================================
void CObstacle::Update(void)
{
	// �X�V
	CStageObj::Update();
}

//========================================
// �v���C���[�Ƃ̓����蔻��
//========================================
bool CObstacle::Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return true;
}

//========================================
// �`��
//========================================
void CObstacle::Draw(void)
{
	// �`��
	CStageObj::Draw();
}

//========================================
// ��������
//========================================
CObstacle* CObstacle::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	CObstacle* pObstacle = nullptr;

	switch (type)
	{
	case CObstacle::TYPE_TREE:

		pObstacle = new CObstacleTree;

		break;

	case CObstacle::TYPE_RIVER:

		pObstacle = new CObstacleRiver;

		break;

	case CObstacle::TYPE_STONE:

		pObstacle = new CObstacleStone;

		break;

	case CObstacle::TYPE_HOLE:

		pObstacle = new CObstacleHole;

		break;

	case CObstacle::TYPE_SOFTROCK:

		pObstacle = new CObstacleSoftRock;

		break;

	default:
		assert(false);
		break;
	}

	// �ʒu�E�����E��ސݒ�
	pObstacle->m_type = type;
	pObstacle->SetPos(rPos);
	pObstacle->SetRot(rRot);

	// �|�C���^��Ԃ�
	return pObstacle;
}
