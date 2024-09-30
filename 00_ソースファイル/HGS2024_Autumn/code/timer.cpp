//==========================================
//
//  �^�C�}�[�N���X(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "number.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float INIT_TIME = 30.0f; // �����l
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(50.0f, 50.0f); // �T�C�Y
	const D3DXVECTOR3 NUMBER_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f); // ���W
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTimer::CTimer() :
	m_fTimer(0.0f)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTimer::~CTimer()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CTimer::Init()
{
	// �����l��ݒ�
	m_fTimer = INIT_TIME;

	// �����𐶐�
	for (int i = 0; i < 2; ++i)
	{
		m_pNumber[i] = CNumber::Create();
		m_pNumber[i]->SetSizeOrigin(NUMBER_SIZE);
		D3DXVECTOR3 pos = NUMBER_POS;
		if (i == 0)
		{
			pos.x -= 40.0f;
		}
		else
		{
			pos.x += 40.0f;
		}
		m_pNumber[i]->SetPos(pos);
		m_pNumber[i]->SetPosVertex();
	}

	// �v�Z
	CalcNum();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTimer::Uninit()
{
	// �����̏I��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pNumber[i] != nullptr)
		{
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}
}

//==========================================
//  �X�V����
//==========================================
void CTimer::Update()
{
#ifndef _DEBUG

	// �^�C�}�[������
	m_fTimer -= CManager::GetInstance()->GetDeltaTime();

#else

	if (CManager::GetInstance()->GetInputKeyboard()->GetPress(DIK_RSHIFT))
	{
		// �^�C�}�[������
		m_fTimer -= CManager::GetInstance()->GetDeltaTime();
	}

#endif
	// �l��␳
	if (m_fTimer < 0.0f)
	{
		m_fTimer = 0.0f;
	}

	// �v�Z
	CalcNum();
}

//==========================================
//  �`�揈��
//==========================================
void CTimer::Draw()
{
}

//==========================================
//  �^�C���A�b�v���Ă锻��
//==========================================
bool CTimer::GetTimeZero()
{
	return m_fTimer <= 0.0f;
}

//==========================================
//  ��������
//==========================================
CTimer* CTimer::Create()
{
	// �|�C���^���m��
	CTimer* pTime = new CTimer;

	// null�`�F�b�N
	if (pTime == nullptr) { assert(false); return nullptr; }

	// ����������
	pTime->Init();

	return pTime;
}

//==========================================
//  �v�Z
//==========================================
void CTimer::CalcNum()
{
	// �^�C�}�[�𐮐��l�ɕϊ�
	int nTime = (float)m_fTimer;

	// �������X�V
	for (int i = 0; i < 2; ++i)
	{
		if (m_pNumber[i] != nullptr)
		{
			// ���ɍ��킹�����l���Z�o
			int nNum = nTime / 10;

			// ���l��ݒ�
			m_pNumber[i]->SetNumber(nNum);

			// ���l��ύX
			nTime %= 10;
			nTime *= 10;
		}
	}
}
