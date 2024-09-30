#pragma once
//==========================================
//
//  �^�C�}�[�N���X(timer.h)
//  Author : Tomoya Kanazaki
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
class CTimer : public CObject
{
public:

	CTimer();
	~CTimer();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CTimer* Create();

private:

	// �����o�֐�
	void CalcNum(); // �v�Z

	// �����o�ϐ�
	float m_fTimer; // ���݂̎���
	CNumber* m_pNumber[2]; // ����

};
