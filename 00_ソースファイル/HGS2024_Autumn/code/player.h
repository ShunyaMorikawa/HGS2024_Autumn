//========================================
//
//�v���C���[����[player.h]
//Author�F�X��x��
//
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

//========================================
// �O���錾
//========================================
class CModel;
class CMotion;
class CEffect;
class CGauge;
class CLockonMarker;

//========================================
//�v���C���[�N���X
//========================================
class CPlayer : public CCharacter
{
public:
	// ���
	enum PLAYERSTATE
	{// �v���C���[�̏��
		STATE_NONE = 0,
		STATE_NORMAL,		// �ʏ�
		STATE_DAMAGE,		// �_���[�W
		STATE_DETAH,		// ���S
		STATE_MAX
	};

	CPlayer(int nPriority = 4);		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	// �����o�֐�
	static CPlayer* Create(std::string pfile);

	HRESULT Init() { return S_OK; }		//�������z
	HRESULT Init(std::string pfile);
	void Uninit();
	void Update();
	void Draw();

	float GetRadius() { return m_fRadius; }		// ���a�擾
	int GetLife() { return m_nLife; }			// �̗͎擾
	int GetState() { return m_State; }			// ��Ԏ擾

	// �ÓI�����o�֐�
	static CPlayer* GetInstance() { return m_pPlayer; }

private:

	// �����o�֐�
	void Motion();
	void Move(D3DXVECTOR3& pos, const float fDeltaTime);

	// �����o�ϐ�
	int m_apNumModel;		// ���f��(�p�[�c)�̑���
	int m_nLife;			// �̗�
	int m_nOldMotion;		// �O��̃��[�V����
	int m_WalkCounter;		// ���s���̃J�E���^�[
	int m_State;			// ���
	float m_fRadius;		// ���a
	bool m_bJump;			// �W�����v
	CEffect* m_pEffect;				// �G�t�F�N�g�̃|�C���^
	CGauge* m_pGauge;				// �Q�[�W�̃|�C���^
	CModel* m_apModel[MAX_PARTS];	// ���f���̃_�u���|�C���^
	CLockonMarker* m_pMarker;		// ���b�N�I���}�[�J�[�̃|�C���^

	// �ÓI�����o�ϐ�
	static CPlayer* m_pPlayer;		// ���g�̃|�C���^
};

#endif
