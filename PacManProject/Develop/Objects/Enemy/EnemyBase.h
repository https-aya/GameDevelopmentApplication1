#pragma once

#include "../GameObject.h"
#include "Enemy.h"

enum eEnemyState 
{
	eIDLE,
	eATTACK,
	ePATROL,
	eIZIKE,
	eESCAPE,
};

enum eEnemyType
{
	AKABE,
	AOSUKE,
	PINKY,
	GUZUTA,
};


class EnemyBase : public GameObject
{
private:
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

protected:
	std::vector<int> animation;
	std::vector<int> eyeanimation;
	eEnemyType enemy_type;
	eEnemyState enemy_state;
	eEnemyDirectionState now_direction;
	eEnemyDirectionState next_direction;
	int animation_count;
	float animation_time;


private:
	std::vector<Enemy*> enemy;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	virtual void AnimationControl(float delta_second);

	template <class T>
	T* CreateObject()
	{
		//指定したクラスを生成する
		T* new_instance = new T();

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();

		//オブジェクトリストに追加
		enemy.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};