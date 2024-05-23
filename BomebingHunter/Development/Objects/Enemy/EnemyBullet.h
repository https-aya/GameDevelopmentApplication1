#pragma on

#include "../GameObject.h"

class EnemyBullet : public GameObject
{
private:
	int animation[4];
	Vector2D direction;

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	virtual void Movement() ;
 
};

