//========================================
//
// ��Q���̏���[reverse.cpp]
// Author�F���n�Ή�
//
//========================================
#include "reverse.h"
#include "model.h"
#include "calculation.h"

//========================================
//���O���
//========================================
namespace
{
	const char* MODEL = "data\\MODEL\\obstacle\\wood00.x";	// ���f���̃p�X
	const float COLLISIONRANGE = 200.0f;	// �L���͈�
}
CListManager<CReverse> CReverse::m_List = {};	// ���X�g

//========================================
//�R���X�g���N�^
//========================================
CReverse::CReverse() : CStageObj()
{

}

//========================================
//�f�X�g���N�^
//========================================
CReverse::~CReverse()
{

}

//========================================
// ������
//========================================
HRESULT CReverse::Init(void)
{
	// ���X�g�ɒǉ�
	m_List.Regist(this);

	// ���f������
	m_pModel = CModel::Create(MODEL);

	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CReverse::Uninit(void)
{
	// ���X�g����폜
	m_List.Delete(this);

	// �I��
	CStageObj::Uninit();
}

//========================================
// �X�V
//========================================
void CReverse::Update(void)
{
	// �X�V
	CStageObj::Update();
}

//========================================
// �v���C���[�Ƃ̓����蔻��
//========================================
bool CReverse::Collision(const D3DXMATRIX& rMtx, const D3DXVECTOR3& rSize)
{
	bool bHit = false;

	// �ʒu�擾
	MyLib::Vector3 pos = GetPos();
	MyLib::Vector3 posTarget = UtilFunc::Transformation::WorldMtxChangeToPosition(rMtx);

	if (UtilFunc::Collision::CircleRange3D(pos, posTarget, COLLISIONRANGE, rSize.x))
	{
		Uninit();
		bHit = true;
	}

	return bHit;

}
