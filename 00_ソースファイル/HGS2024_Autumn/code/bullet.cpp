//=======================================
//
//�e[bullet.cpp]
//Author : MORIKAWA SHUNYA
//
//=======================================

#include "bullet.h"
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "particle.h"
#include "useful.h"

//===========================================
//�R���X�g���N�^
//===========================================
CBullet::CBullet()
{
}

//===========================================
//�f�X�g���N�^
//===========================================
CBullet::~CBullet()
{
}

//===========================================
//����
//===========================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//CBullet�^�̃|�C���^
	CBullet* pEffect = nullptr;

	if (pEffect == nullptr)
	{//nullptr�̎�
		//�C���X�^���X����
		pEffect = new CBullet;

		pEffect->SetPos(pos);
		pEffect->SetMove(move);
		pEffect->m_nLife = nLife;

		//������
		pEffect->Init();
	}

	//�|�C���^��Ԃ�
	return pEffect;
}

//===========================================
//����������
//===========================================
HRESULT CBullet::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//������
	CBillboard::Init();

	// �T�C�Y�ݒ�
	SetSize(150.0f, 150.0f);

	BindTexture(pTexture->Regist("data\\texture\\effect000.png"));

	//������Ԃ�
	return S_OK;
}

//===========================================
//�I������
//===========================================
void CBullet::Uninit(void)
{
	//�I��
	CBillboard::Uninit();
}

//===========================================
//�X�V����
//===========================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	D3DXCOLOR col = GetCol();

	// �X�V
	CBillboard::Update();

	// �ʒu�X�V
	pos += move;

	if (m_nLife % 2 == 0)
	{
		Myparticle::Create(Myparticle::TYPE::TYPE_BULLET, pos);
	}

	// �ʒu�ݒ�
	SetPos(pos);

	// �̗͌��Z
	m_nLife--;

	if (m_nLife < 0)
	{
		//�j������
		Uninit();
	}

	// �v���C���[�Ƃ̓����蔻��
	CollisionPlayer(pos);

	// ���Z��Ƃ̓����蔻��
	CollisionCircle();
}

//===========================================
//�`�揈��
//===========================================
void CBullet::Draw(void)
{
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//CRenderer�^�̃|�C���^
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//===========================================
// �G�Ƃ̓����蔻��
//===========================================
void CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	// ����
	float fLength;

	float fRadius = GetSize();

	// �G�̏��擾
	CEnemy *pEnemy = CEnemy::GetInstance();

	// �v���C���[�̈ʒu
	D3DXVECTOR3 posEnemy = pEnemy->GetPos();

	// ���a
	float radiusEnemy = pEnemy->GetRadius();

	// �x�N�g�������߂�
	D3DXVECTOR3 vec = posEnemy - pos;

	//�x�N�g�����
	fLength = D3DXVec3Length(&vec);

	if (fLength <= radiusEnemy + fRadius)
	{
		Uninit();

		pEnemy->Hit(1);
	}
}

//===========================================
// �v���C���[�Ƃ̓����蔻��
//===========================================
void CBullet::CollisionPlayer(D3DXVECTOR3 pos)
{
	// ����
	float fLength;

	float fRadius = GetSize();

	// �v���C���[�̏��擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	// �v���C���[�̈ʒu
	D3DXVECTOR3 posPlayer = pPlayer->GetPos();

	// ���a
	float radiusPlayer = pPlayer->GetRadius();

	// �x�N�g�������߂�
	D3DXVECTOR3 vec = posPlayer - pos;

	//�x�N�g�����
	fLength = D3DXVec3Length(&vec);

	if (fLength <= radiusPlayer + fRadius)
	{// �v���C���[�ɓ�������
		Uninit();

		// �̗͏���
		pPlayer->Hit(1);
	}
}

//===========================================
// ���Z��Ƃ̓����蔻��
//===========================================
void CBullet::CollisionCircle()
{
	// �v���C���[�ʒu
	D3DXVECTOR3 posBullet = GetPos();
	D3DXVECTOR3 vec;
	D3DXVec3Normalize(&vec, &posBullet);

	if (USEFUL::CollisionCircle(posBullet, Constance::ARENA_SIZE))
	{// ���Z��ɓ���������
		Uninit();

		// �p�[�e�B�N������
		Myparticle::Create(Myparticle::TYPE_DEATH, posBullet);
	}

	// �ʒu�ݒ�
	SetPos(posBullet);
}
