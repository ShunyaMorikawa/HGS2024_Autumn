//========================================
//
// ��Q���̏���[obstacle.cpp]
// Author�F��������
//
//========================================
#include "obstacle.h"

#include "obstacleTree.h"
#include "obstacleRiver.h"
#include "obstacleStone.h"
#include "obstacleHole.h"

//========================================
//���O���
//========================================
namespace
{

}

//========================================
//�R���X�g���N�^
//========================================
CObstacle::CObstacle() : CModel(),
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
HRESULT CObstacle::Init(const EType type)
{
	//if (FAILED(CModel::Init()))
	//{ // �������Ɏ��s�����ꍇ

	//	// ���s��Ԃ�
	//	return E_FAIL;
	//}

	// �l�̐ݒ�
	SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f));	// �ʒu
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ����

	return S_OK;
}

//========================================
// �I��
//========================================
void CObstacle::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

//========================================
// �X�V
//========================================
void CObstacle::Update(void)
{
	// �X�V
	CModel::Update();
}

//========================================
// �`��
//========================================
void CObstacle::Draw(void)
{
	// �`��
	CModel::Draw();
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

	default:
		assert(false);
		break;
	}

	// �����������Ɏ��s������A��~
	if (FAILED(pObstacle->Init(type))) { assert(false); return nullptr; }

	// �|�C���^��Ԃ�
	return pObstacle;
}
