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
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ΓIoΦ
	static CObstacle* Create(std::string pfile);

private:


};

#endif
