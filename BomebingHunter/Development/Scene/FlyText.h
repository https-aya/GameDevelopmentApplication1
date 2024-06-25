#pragma once

#include "../Utility/Vector2D.h"
class FlyText
{
private:
	int number_image[11];
	int fly_text[3];
	int size;

public:
	FlyText();
	~FlyText();

	void Initialize();

	void Draw(Vector2D location, int sco) const;
	void Finalize();
	void SetFlyText(int ft);

};

