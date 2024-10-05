#pragma once

class Accurate : public TextureRect
{
public:
	Accurate();
	~Accurate();

	void DisplayJudge(Judge recentJudgement);

	virtual void Update();

private:
	float display;
	Judge judgement;
	Vector3 tsize;

	const Vector3 position { 0, 0, 0 };
	const Vector3 size { 150, 50, 1 };
};