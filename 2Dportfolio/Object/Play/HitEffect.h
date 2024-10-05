#pragma once

class HitEffect : public AnimationRect
{
public:
	HitEffect(int line);
	~HitEffect();

	void ShortEffect();
	void LongEffect(bool on);
	void EndEffect();

	virtual void Update();

private:

};
