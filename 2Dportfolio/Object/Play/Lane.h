#pragma once

#define Lane1Pos -103.5f
#define Lane2Pos -64.0f
#define Lane3Pos -23.5f
#define Lane4Pos 23.5f
#define Lane5Pos 64.0f
#define Lane6Pos 103.5f

#define WhlteLaneSize 42.5f
#define BlackLaneSize 33.5f

class Lane : public TextureRect
{
public:
	Lane();
	~Lane();

	virtual void Update();

private:

};