//========================================
//
// ��Q���̏���[obstacle.h]
// Author�F�X��x��
//
//========================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "model.h"

//========================================
// ��Q���N���X
//========================================
class CObstacle : public CModel
{
public:

	// ���
	enum EType
	{
		TYPE_TREE = 0,	// ��
		TYPE_RIVER,		// ��
		TYPE_STONE,		// ��
		TYPE_MAX		// �񋓌^�̑���
	};

	CObstacle();		//�R���X�g���N�^
	~CObstacle();		//�f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CObstacle* Create(std::string pfile);

private:


};

#endif
