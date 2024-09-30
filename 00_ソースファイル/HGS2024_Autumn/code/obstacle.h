//========================================
//
// αQ¨Μ[obstacle.h]
// AuthorFXμxν
//
//========================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "model.h"

//========================================
// αQ¨NX
//========================================
class CObstacle : public CModel
{
public:

	// νή
	enum EType
	{
		TYPE_TREE = 0,	// Ψ
		TYPE_RIVER,		// μ
		TYPE_STONE,		// Ξ
		TYPE_MAX		// ρ^Μ
	};

	CObstacle();		//RXgN^
	~CObstacle();		//fXgN^

	// oΦ
	HRESULT Init(void) { return S_OK; }	// Όz
	HRESULT Init(const EType type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual bool Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize) = 0;	// vC[ΖΜ½θ»θ

	// ΓIoΦ
	static CObstacle* Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);

private:


};

#endif
