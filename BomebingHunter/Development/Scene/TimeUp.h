#pragma once
class TimeUp
{
private:
	int image[5];
	int draw;
	int count;

public:
	TimeUp();
	~TimeUp();

	void Initialize();
	void Update(int sco);
	void Draw() const;
	void Finalize();
};

