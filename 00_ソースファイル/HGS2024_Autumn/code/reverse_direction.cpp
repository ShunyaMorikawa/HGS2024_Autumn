//=============================================================================
// 
//  ���]���o���� [reverse_direction.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "reverse_direction.h"
#include "manager.h"
#include "texture.h"
#include "calculation.h"
#include "input.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const std::string TEXTURE_SAMPLE = "data\\TEXTURE\\reverse.png";	// �e�N�X�`���̃t�@�C��
}

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CReverse_Direction::CReverse_Direction(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CReverse_Direction::~CReverse_Direction()
{

}

//==========================================================================
// ��������
//==========================================================================
CReverse_Direction* CReverse_Direction::Create()
{
	// �������̊m��
	CReverse_Direction* pObj = new CReverse_Direction;

	if (pObj != nullptr)
	{
		// ����������
		pObj->Init();
	}

	return pObj;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CReverse_Direction::Init()
{

	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	// �e�N�X�`���ݒ�
	int texID = CTexture::GetInstance()->Regist(TEXTURE_SAMPLE);
	BindTexture(texID);

	// �T�C�Y�ݒ�
	D3DXVECTOR2 size = CTexture::GetInstance()->GetImageSize(texID);

#if 0	// ���������ɃT�C�Y�ݒ�
	size = UtilFunc::Transformation::AdjustSizeByWidth(size, 240.0f);

#else	// �c�������ɃT�C�Y�ݒ�
	size = UtilFunc::Transformation::AdjustSizeByWidth(size, 240.0f);
#endif
	SetSize(size.x, size.y);
	SetSizeOrigin(size);


	// �ʒu�A�����ݒ�͕K�v������Βǉ�


	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CReverse_Direction::Uninit()
{
	// �I������
	CObject2D::Uninit();
}

//==========================================================================
// �X�V����
//==========================================================================
void CReverse_Direction::Update()
{
	// �X�V����
	CObject2D::Update();
}

//==========================================================================
// �`�揈��
//==========================================================================
void CReverse_Direction::Draw()
{
	// �`�揈��
	CObject2D::Draw();
}
