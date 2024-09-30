//========================================
//
// ��Q��(��)�̏���[obstacleTree.h]
// Author�F��������
//
//========================================
#ifndef _OBSTACLE_TREE_H_
#define _OBSTACLE_TREE_H_

#include "obstacle.h"

//========================================
// ��Q��(��)�N���X
//========================================
class CObstacleTree : public CObstacle
{
public:

	CObstacleTree();		// �R���X�g���N�^
	~CObstacleTree();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(const EType type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize) override;	// �v���C���[�Ƃ̓����蔻��

private:


};

#endif
