#pragma once
//==========================================
//
//  �^�C�}�[�N���X(resultscore.h)
//  Author : ���n�Ή�
//
//==========================================
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �N���X��`
//==========================================
class CResultScore : public CObject
{
public:

	CResultScore();
	~CResultScore();

	HRESULT Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CResultScore* Create(const MyLib::Vector3& pos, float time);

private:

	// �����o�֐�
	void CalcNum(); // �v�Z

	// �����o�ϐ�
	float m_fTimer; // ���݂̎���
	CNumber* m_pNumber[2]; // ����

};
