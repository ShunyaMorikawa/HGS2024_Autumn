////========================================
////
//// ��Q���̏���[obstacle.cpp]
//// Author�F�X��x��
////
////========================================
//#include "obstacle.h"
//
////========================================
////���O���
////========================================
//namespace
//{
//
//}
//
////========================================
////�R���X�g���N�^
////========================================
//CObstacle::CObstacle() :
//	m_nLife(0),
//	m_fRadius(0.0f),
//	m_nState(STATE_NORMAL),
//	m_bWalk(false),
//	m_bAttack(false),
//	m_pGauge(nullptr)
//{//�l���N���A
//}
//
////========================================
////�f�X�g���N�^
////========================================
//CObstacle::~CObstacle()
//{
//}
//
////========================================
//// ����
////========================================
//CObstacle* CObstacle::Create(std::string pfile)
//{
//	if (m_pEnemy == nullptr)
//	{//	�C���X�^���X����
//		m_pEnemy = new CObstacle;
//
//		m_pEnemy->Init(pfile);
//	}
//
//	return m_pEnemy;
//}
//
////========================================
//// ������
////========================================
//HRESULT CObstacle::Init(std::string pfile)
//{
//	//�e�N�X�`���̃|�C���^
//	CTexture* pTexture = CManager::GetInstance()->GetTexture();
//
//	// �L�����̏�����
//	CCharacter::Init(pfile);
//
//	// �ʒu�ݒ�
//	SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f));
//
//	// �����ݒ�
//	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//	// �̗�
//	m_nLife = LIFE;
//
//	// ���a
//	m_fRadius = RADIUS;
//
//	// �Q�[�W����
//	m_pGauge = CGauge::Create(m_nLife);
//
//	// �ʒu�ݒ�
//	m_pGauge->SetPos(D3DXVECTOR3(600.0f, 25.0f, 0.0f));
//
//	// �T�C�Y�ݒ�
//	m_pGauge->SetSize(50.0f, 50.0f);
//
//	return S_OK;
//}
//
////========================================
//// �I��
////========================================
//void CObstacle::Uninit(void)
//{
//	// �I��
//	CCharacter::Uninit();
//
//	m_pEnemy = nullptr;
//
//	m_pGauge->Uninit();
//	m_pGauge = nullptr;
//}
//
////========================================
//// �X�V
////========================================
//void CObstacle::Update(void)
//{
//	// �ړI�̌���
//	D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	// �X�V
//	CCharacter::Update();
//
//	// �ʒu�擾
//	D3DXVECTOR3 pos = GetPos();
//
//	// �ړ��ʎ擾
//	D3DXVECTOR3 move = GetMove();
//
//	// �����擾
//	D3DXVECTOR3 rot = GetRot();
//
//	// �ړI�̌����擾
//	D3DXVECTOR3 RotDest = GetRotDest();
//
//	// �v���C���[���̎擾
//	CPlayer* pPlayer = CPlayer::GetInstance();
//
//	// �L�[�{�[�h�̏��擾
//	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
//
//	if (pPlayer != nullptr)
//	{
//		// �ʒu�擾
//		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
//
//		// �v���C���[�Ƃ̊p�x
//		RotDest.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);
//	}
//
//	// �v���C���[�����Ɉړ�
//	move.x += sinf(rot.y + D3DX_PI) * SPEED;
//	move.z += cosf(rot.y + D3DX_PI) * SPEED;
//
//	// �ʒu���X�V
//	pos += move;
//
//	// �ړ��ʂ��X�V(����������)
//	move.x += (0.0f - move.x) * INERTIA;
//	move.z += (0.0f - move.z) * INERTIA;
//
//	//�ړI�̌���
//	DiffRot.y = RotDest.y - rot.y;
//
//	// �����̐��K��
//	USEFUL::NormalizeRotAngle(DiffRot.y);
//
//	//Diff�ɕ␳�W����������
//	rot.y += DiffRot.y * 0.1f;
//
//	// �p�x�̐��K��
//	USEFUL::NormalizeRotAngle(rot.y);
//
//	// �d��
//	move.y -= GRAVITY;
//
//	if (pos.y <= 0.0f)
//	{// �ʒu�ƈړ��ʂ̍X�V��~
//		pos.y = 0.0f;
//		move.y = 0.0f;
//	}
//
//	// �J�E���g���Z
//	m_nCnt++;
//
//	if (m_nCnt >= ATTACKCOUNTER)
//	{// �U������܂ł̎���
//		m_bAttack = true;
//
//		for (int n = 0; n < MAXDIRECTION; n++)
//		{// �e��8�����ɔ�΂�
//			float fAngle = D3DX_PI * 2.0f / MAXDIRECTION;
//
//			// ���ˊp�x�����炷
//			fAngle *= n;
//			D3DXVECTOR3 bulletmove;
//			bulletmove.x = sinf(fAngle) * BULLETMOVE;
//			bulletmove.y = 0.0f;
//			bulletmove.z = cosf(fAngle) * BULLETMOVE;
//
//			// �e�̐���
//			CBullet::Create(pos, bulletmove, BULLETLIFE);
//		}
//
//		// �T�E���h���擾
//		CSound* pSound = CManager::GetInstance()->GetSound();
//
//		// �T�E���h�Đ�
//		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BULLET);
//
//		m_nCnt = 0;
//	}
//
//	// �Q�[�W�ɑ̗͐ݒ�
//	m_pGauge->SetLife(m_nLife);
//
//	// �ʒu�ݒ�
//	SetPos(pos);
//
//	// �ړ��ʐݒ�
//	SetMove(move);
//
//	// �����ݒ�
//	SetRot(rot);
//
//	// �ړI�̌����ݒ�
//	SetRotDest(RotDest);
//
//	// ���[�V�����Ǘ�
//	Motion();
//
//	// ���Z��Ƃ̓����蔻��
//	CollisionCircle();
//
//	switch (m_nState)
//	{
//	case STATE_NORMAL:
//		break;
//	default:
//		break;
//	}
//
//#ifdef _DEBUG
//	if (pInputKeyboard->GetPress(DIK_F4))
//	{// �̗͌��Z
//		Hit(LIFE);
//	}
//#endif
//
//	// �f�o�b�O�\��
//	DebugProc::Print(DebugProc::POINT_LEFT, "\n�G�̈ʒu�F%f�A%f�A%f\n", pos.x, pos.y, pos.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "�G�̌����F%f�A%f�A%f\n", rot.x, rot.y, rot.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "�G�̈ړ��ʁF%f�A%f�A%f\n", move.x, move.y, move.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "�G�̗̑́F%d\n", m_nLife);
//	DebugProc::Print(DebugProc::POINT_LEFT, "F4�œG�̗̑�0\n");
//}
//
////========================================
//// �`��
////========================================
//void CObstacle::Draw(void)
//{
//	// �`��
//	CCharacter::Draw();
//}
//
////========================================
//// �q�b�g����
////========================================
//void CObstacle::Hit(int nLife)
//{
//	//CInputKeyboard���擾
//	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
//
//	//CInputPad���擾
//	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();
//
//	D3DXVECTOR3 pos = GetPos();
//
//	//�e�N�X�`���̃|�C���^
//	CTexture* pTexture = CManager::GetInstance()->GetTexture();
//
//	// ��Ԏ擾
//	int nState = GetState();
//
//	// �̗͌��炷
//	m_nLife -= nLife;
//
//	if (m_pGauge != nullptr)
//	{
//		// �Q�[�W�ɑ̗͐ݒ�
//		m_pGauge->SetLife(m_nLife);
//	}
//
//	if (m_nLife <= 0)
//	{
//		// ���S���
//		nState = STATE_DEATH;
//
//		// �p�[�e�B�N������
//		Myparticle::Create(Myparticle::TYPE_DEATH, pos);
//
//		// �I��
//		Uninit();
//
//		// ����
//		CObject2D* pObje2D = CObject2D::Create();
//
//		// �ʒu�ݒ�
//		pObje2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 00.0f));
//
//		// �T�C�Y�ݒ�
//		pObje2D->SetSize(SCREEN_WIDTH, 200.0f);
//
//		// �����e�N�X�`��
//		pObje2D->BindTexture(pTexture->Regist("data\\texture\\win.png"));
//
//		// �T�E���h���擾
//		CSound* pSound = CManager::GetInstance()->GetSound();
//
//		// �T�E���h��~
//		pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
//
//		// �T�E���h�Đ�
//		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_WIN);
//	}
//}
//
////========================================
//// �m�b�N�o�b�N
////========================================
//void CObstacle::NockBack()
//{
//	// �G�̏��擾
//	CPlayer* pPlayer = CPlayer::GetInstance();
//
//	if (pPlayer != nullptr)
//	{
//		// �ʒu�擾
//		D3DXVECTOR3 posEnemy = GetPos();
//
//		// �v���C���[�̈ʒu�ƈړ���
//		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
//		D3DXVECTOR3 movePlayer = pPlayer->GetMove();
//
//		// ��΂����p�x
//		float angle = atan2f(posEnemy.x - posEnemy.x, posPlayer.z - posEnemy.z);
//
//		// �ʒu�X�V
//		movePlayer.x = sinf(angle) * -NOCKBACK;
//		movePlayer.z = cosf(angle) * -NOCKBACK;
//		movePlayer.y = 25.0f;
//
//		// �ړ��ʐݒ�
//		pPlayer->SetMove(movePlayer);
//	}
//}
//
////========================================
//// ���[�V�����Ǘ�
////========================================
//void CObstacle::Motion()
//{
//	// ���[�V�������擾
//	CMotion* pMotion = GetMotion();
//
//	// �ʒu�擾
//	D3DXVECTOR3 pos = GetPos();
//
//	// �ړ��ʎ擾
//	D3DXVECTOR3 move = GetMove();
//
//	if (m_bWalk)
//	{// �������[�V����
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_WALK);
//	}
//	else if (m_bAttack)
//	{// �؂艺�낵���[�V����
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_ATTACK);
//
//		m_bWalk = false;
//
//		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		if (pMotion->IsFinish() && m_bAttack == true)
//		{// ���[�V�����I��
//			m_bAttack = false;
//		}
//	}
//	else
//	{
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_WALK);
//	}
//
//	if (pMotion != nullptr)
//	{// ���[�V�����X�V
//		pMotion->Update();
//	}
//
//	SetMove(move);
//}
