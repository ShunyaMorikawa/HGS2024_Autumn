//========================================
//
//  ���U���g [ranking.h]
//  Author�F���n�Ή�
//
//========================================
#include "ranking.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "sound.h"
#include "timer.h"

namespace
{
	const int NUM = 3;
}

//=======================================
//�R���X�g���N�^
//=======================================
CRanking::CRanking() : 
m_bNewRecord(false)		// �j���[���R�[�h
{
}

//=======================================
//�f�X�g���N�^
//=======================================
CRanking::~CRanking()
{
}

//=======================================
//����
//=======================================
CRanking* CRanking::Create(float nowScore)
{
	//�^�C�g���̃|�C���^
	CRanking* pTutorial = nullptr;

	//�C���X�^���X����
	pTutorial = new CRanking;

	if (pTutorial != nullptr)
	{
		// ����̃X�R�A
		pTutorial->m_fNowScore = nowScore;
		pTutorial->Init();
	}

	//�|�C���^��Ԃ�
	return pTutorial;
}

//=======================================
//������
//=======================================
HRESULT CRanking::Init(void)
{
	
	Load();
	Sort();
	Save();


	//������Ԃ�
	return S_OK;
}

//=======================================
// �I��
//=======================================
void CRanking::Uninit(void)
{
}

//=======================================
// �X�V
//=======================================
void CRanking::Update(void)
{
	//CInputKeyboard���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//CInputPad���擾
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) ||
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		// ��ʑJ��(�t�F�[�h)
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
	}
}

//=======================================
// �`��
//=======================================
void CRanking::Draw(void)
{
}

//=======================================
// �`��
//=======================================
void CRanking::Sort()
{
	// �~������
	for (int nCntData = 0; nCntData < NUM - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < NUM; nCntSort++)
		{
			if (m_fRanking[nCntData] < m_fRanking[nCntSort])
			{// �v�f1���v�f2���傫��������

				int nTemp = m_fRanking[nCntData];
				m_fRanking[nCntData] = m_fRanking[nCntSort];
				m_fRanking[nCntSort] = nTemp;
			}
		}
	}

	// �����L���O�ő�l��������̂�������������
	if (m_fRanking[NUM - 1] < m_fNowScore)
	{// ����ւ�

		m_fRanking[NUM - 1] = m_fNowScore;	// �ŏ��l�ƍ���̃f�[�^����ւ�
		m_bNewRecord = true;	// �t���OON
	}

	// �~������
	for (int nCntData = 0; nCntData < NUM - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < NUM; nCntSort++)
		{
			if (m_fRanking[nCntData] < m_fRanking[nCntSort])
			{// �v�f1���v�f2���傫��������

				int nTemp = m_fRanking[nCntData];
				m_fRanking[nCntData] = m_fRanking[nCntSort];
				m_fRanking[nCntSort] = nTemp;
			}
		}
	}
}

//=======================================
// �Z�[�u
//=======================================
void CRanking::Save()
{
	// �t�@�C�����J��
	std::ofstream File("data\\FILE\\ranking.bin", std::ios::binary);
	if (!File.is_open()) {
		return;
	}

	// ��������
	File.write(reinterpret_cast<char*>(m_fRanking), sizeof(m_fRanking));

	// �t�@�C�������
	File.close();
}

//=======================================
// ���[�h
//=======================================
void CRanking::Load()
{
	// �t�@�C�����J��
	std::ifstream File("data\\FILE\\ranking.bin", std::ios::binary);
	if (!File.is_open()) {
		
		m_fRanking[0] = 20.0f;	// �����L���O
		m_fRanking[1] = 15.0f;	// �����L���O
		m_fRanking[2] = 10.0f;	// �����L���O

		return;
	}

	// ��������
	File.read(reinterpret_cast<char*>(m_fRanking), sizeof(m_fRanking));

	// �t�@�C�������
	File.close();
}

