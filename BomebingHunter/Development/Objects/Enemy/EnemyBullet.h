#pragma on

#include "../GameObject.h"

class EnemyBullet : public GameObject
{
private:
	int animation[4];
	bool anime_flag;
	int anime_count;
	int anime_num;

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
	void AnimeControl();

};

