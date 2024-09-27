//========================================
//
// �G�̏���[enemy.h]
// Author�F�X��x��
//
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"

//========================================
// �O���錾
//========================================
class CModel;
class CMotion;
class CEffect;
class CGauge;

//========================================
//�G�l�~�[�N���X
//========================================
class CEnemy : public CCharacter
{
public:
	CEnemy();		//�R���X�g���N�^
	~CEnemy();		//�f�X�g���N�^

	// �����o�֐�
	static CEnemy* Create(std::string pfile);
	HRESULT Init(void) { return S_OK; }		// �������z
	HRESULT Init(std::string pfile);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nLife);
	void NockBack();
	void Motion();
	void CollisionPlayer(int nDamage);
	void CollisionCircle();

	int GetLife() { return m_nLife; }			// �̗͎擾

	float GetRadius() { return m_fRadius; }		// ���a�擾

	static CEnemy* GetInstance() { return m_pEnemy; }	// �G�̏��擾

private:
	//�����o�ϐ�
	int m_nLife;		// �̗�
	int m_nCnt;			// �J�E���g
	int m_nState;		// ���

	float m_fRadius;	// ���a

	bool m_bWalk;		// �ړ�����
	bool m_bAttack;		// �U������

	CGauge* m_pGauge;	// �Q�[�W�̃|�C���^

	static CEnemy* m_pEnemy;	// ���g�̃|�C���^
};

#endif
