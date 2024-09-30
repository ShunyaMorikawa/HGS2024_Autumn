//=============================================================================
// 
//  �X�e�[�W�̔z�u������ [transferBeacon.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "stageobj.h"
#include "manager.h"
#include "calculation.h"
#include "model.h"
#include "input.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const char* MODEL = "data\\MODEL\\box.x";
}

namespace StateTime
{
	const float APPEARANCE = 1.0f;	// �o��
	const float LEAVE = 1.0f;		// �ޏ�
}

//==========================================================================
// �֐��|�C���^
//==========================================================================
CStageObj::SAMPLE_FUNC CStageObj::m_SampleFuncList[] =
{
	&CStageObj::StateNone,			// �Ȃ�
	&CStageObj::StateAppearance,	// �o��
	&CStageObj::StateLeave,			// �ޏ�
};

//==========================================================================
// �ÓI�����o�ϐ�
//==========================================================================
CListManager<CStageObj> CStageObj::m_List = {};	// ���X�g

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CStageObj::CStageObj(int nPriority) : CObject(nPriority),
m_fStateTime(0.0f),		// ��ԃ^�C�}�[
m_state(State::STATE_NONE),	// ���
m_pModel(nullptr)		// ���f��
{

}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CStageObj::~CStageObj()
{
	
}

//==========================================================================
// ��������
//==========================================================================
CStageObj *CStageObj::Create(const Type& type, const MyLib::Vector3& pos)
{
	// �������̊m��
	CStageObj* pObj = new CStageObj;

	if (pObj != nullptr)
	{
		// �����ݒ�
		pObj->SetPos(pos);
		pObj->SetOriginPosition(pos);

		// ����������
		pObj->Init();
	}

	return pObj;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CStageObj::Init()
{
	// ���X�g�ɒǉ�
	m_List.Regist(this);

	// ���f������
	m_pModel = CModel::Create(MODEL);
	m_pModel->SetType(CModel::TYPE_NOT_HIERARCHY);
	m_pModel->SetPosition(GetPos());

	// �o��
	SetState(State::STATE_APPEARANCE);
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CStageObj::Uninit()
{
	if (m_pModel != nullptr)
	{// ���f���̍폜
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// ���X�g����폜
	m_List.Delete(this);

	// �I��
	Release();
}

//==========================================================================
// �폜
//==========================================================================
void CStageObj::Kill()
{
	if (m_pModel != nullptr)
	{// ���f���̍폜
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// ���X�g����폜
	m_List.Delete(this);

	// �I��
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CStageObj::Update()
{
	// ��ԍX�V
	UpdateState();

	if (m_pModel != nullptr)
	{// ���f���̍X�V
		m_pModel->SetPosition(GetPos());
		m_pModel->Update();
	}
}

//==========================================================================
// ��ԍX�V
//==========================================================================
void CStageObj::UpdateState()
{
	// ��ԃJ�E���^�[���Z
	m_fStateTime += CManager::GetInstance()->GetDeltaTime();

	// ��ԕʏ���
	(this->*(m_SampleFuncList[m_state]))();
}

//==========================================================================
// �Ȃ�
//==========================================================================
void CStageObj::StateNone()
{
	m_fStateTime = 0.0f;
}

//==========================================================================
// �o��
//==========================================================================
void CStageObj::StateAppearance()
{
	MyLib::Vector3 posOrigin = GetOriginPosition();	// �����ʒu
	MyLib::Vector3 posDest = GetOriginPosition();	// �ڕW�ʒu
	posDest.y = 0.0f;

	// ���`���
	MyLib::Vector3 pos = posOrigin;
	pos.y = UtilFunc::Correction::EaseOutBack(posOrigin.y, posDest.y, 0.0f, StateTime::APPEARANCE, m_fStateTime);

	// �ʒu�ݒ�
	SetPos(pos);
}

//==========================================================================
// �ޏ�
//==========================================================================
void CStageObj::StateLeave()
{
	MyLib::Vector3 posOrigin = GetOriginPosition();	// �����ʒu
	MyLib::Vector3 posDest = GetOriginPosition();	// �ڕW�ʒu
	posDest.y = 0.0f;

	// ���`���
	MyLib::Vector3 pos = posOrigin;
	pos.y = UtilFunc::Correction::EaseInBack(0.0f, posOrigin.y, 0.0f, StateTime::APPEARANCE, m_fStateTime);

	// �ʒu�ݒ�
	SetPos(pos);
}

//==========================================================================
// ��Ԑݒ�
//==========================================================================
void CStageObj::SetState(const State& state)
{
	m_fStateTime = 0.0f;	// ��ԃJ�E���^�[
	m_state = state;		// ���
}

//==========================================================================
// �`�揈��
//==========================================================================
void CStageObj::Draw()
{
	if (m_pModel != nullptr)
	{// ���f���̕`��
		m_pModel->Draw();
	}
}

