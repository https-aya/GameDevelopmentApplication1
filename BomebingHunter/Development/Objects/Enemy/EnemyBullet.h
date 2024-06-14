

#include "../GameObject.h"

class EnemyBullet : public GameObject
{
private:
	int animation[4];		//�A�j���[�V�����摜
	bool anime_flag;		//�A�j���[�V�������邩�ǂ���
	int anime_count;		//�A�j���[�V��������
	int anime_num;			//�A�j���[�V�����ԍ�

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V�����Ǘ�
	void AnimeControl();

};
