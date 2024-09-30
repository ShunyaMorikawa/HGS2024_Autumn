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
bool CReverse::Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	bool bHit = false;

	// �ʒu�擾
	MyLib::Vector3 pos = GetPos();

	if (UtilFunc::Collision::CircleRange3D(pos, rPos, COLLISIONRANGE, rSize.x))
	{
		Kill();
		bHit = true;
	}

	return bHit;

}
