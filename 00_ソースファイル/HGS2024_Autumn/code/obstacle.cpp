//========================================
//
// ��Q���̏���[obstacle.cpp]
// Author�F�X��x��
//
//========================================
#include "obstacle.h"

//========================================
//���O���
//========================================
namespace
{

}

//========================================
//�R���X�g���N�^
//========================================
CObstacle::CObstacle() : CModel()
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
// �v���C���[�Ƃ̓����蔻��
//========================================
bool CObstacle::Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return false;
}

//========================================
// ��������
//========================================
CObstacle* CObstacle::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	//CObstacle* pObstacle = new ;

	//if (m_pEnemy == nullptr)
	//{//	�C���X�^���X����
	//	m_pEnemy = new CEnemy;

	//	m_pEnemy->Init(pfile);
	//}

	//return m_pEnemy;

	return nullptr;
}
