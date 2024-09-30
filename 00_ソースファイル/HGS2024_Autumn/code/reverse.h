//========================================
//
// ��Q���̏���[reverse.h]
// Author�F���n�Ή�
//
//========================================
#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "stageobj.h"

//========================================
// ��Q���N���X
//========================================
class CReverse : public CStageObj
{
public:

	CReverse();		//�R���X�g���N�^
	~CReverse();	//�f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	virtual bool Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize) override;	// �v���C���[�Ƃ̓����蔻��
	static CListManager<CReverse> GetList() { return m_List; }	// ���X�g�擾

private:

	static CListManager<CReverse> m_List;	// ���X�g
};

#endif
