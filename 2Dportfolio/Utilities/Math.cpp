#include "stdafx.h"
#include "Math.h"

#include "Geometry/Line.h"
#include "Geometry/Square.h"
#include "Geometry/Circle.h"
#include "Geometry/FilledCircle.h"
#include "Geometry/TextureRect.h"

bool Math::Intersect(Square * rect1, Square * rect2)
{
	RectEdges edge1 = rect1->GetTransformedCoord();
	RectEdges edge2 = rect2->GetTransformedCoord();
	
	if (edge1.RB.x >= edge2.LT.x && edge1.LT.x <= edge2.RB.x
		&& edge1.LT.y >= edge2.RB.y && edge1.RB.y <= edge2.LT.y)
		return true;
	else
		return false;
}

bool Math::Intersect(Square * rect, Vector3 position)
{
	RectEdges e1 = rect->GetTransformedCoord();
	if (e1.RB.x >= position.x && e1.LT.x <= position.x && e1.LT.y >= position.y && e1.RB.y <= position.y)
		return true;
	else
		return false;
}

bool Math::Intersect(TextureRect * rect, Vector3 position)
{
	RectEdges e1 = rect->GetTransformedCoord();
	if (e1.RB.x >= position.x && e1.LT.x <= position.x && e1.LT.y >= position.y && e1.RB.y <= position.y)
		return true;
	else
		return false;
}

bool Math::IntersectOriented(Square * rect1, Square * rect2)
{
	Vector3 dist = rect1->GetPosition() - rect2->GetPosition();

	Vector3 r1Up = rect1->Up() * rect1->GetScale().y * 0.5f;
	Vector3 r1Right = rect1->Right() * rect1->GetScale().x * 0.5f;

	Vector3 r2Up = rect2->Up() * rect2->GetScale().y * 0.5f;
	Vector3 r2Right = rect2->Right() * rect2->GetScale().x * 0.5f;

	float c = fabs(Dot(dist, rect1->Right()));
	float a = fabs(Dot(r2Up, rect1->Right())) + fabs((Dot(r2Right, rect1->Right())));
	float b = rect1->GetScale().y * 0.5f;
	if (c > a + b)
		return false;

	c = fabs(Dot(dist, rect1->Up()));
	a = fabs(Dot(r2Up, rect1->Up())) + fabs((Dot(r2Right, rect1->Up())));
	b = rect1->GetScale().x * 0.5f;
	if (c > a + b)
		return false;

	c = fabs(Dot(dist, rect2->Right()));
	a = fabs(Dot(r1Up, rect2->Right())) + fabs((Dot(r1Right, rect2->Right())));
	b = rect2->GetScale().y * 0.5f;
	if (c > a + b)
		return false;

	c = fabs(Dot(dist, rect2->Up()));
	a = fabs(Dot(r1Up, rect2->Up())) + fabs((Dot(r1Right, rect2->Right())));
	b = rect2->GetScale().x * 0.5f;
	if (c > a + b)
		return false;


	return true;
}

Vector2 Math::absVec2(Vector2 val)
{
	float x = abs(val.x);
	float y = abs(val.y);
	return Vector2(x, y);
}

Vector3 Math::absVec3(Vector3 val)
{
	float x = abs(val.x);
	float y = abs(val.y);
	float z = abs(val.z);
	return Vector3(x,y,z);
}

float Math::GetDistance(Vector3 vec1, Vector3 vec2)
{
	return sqrt(pow((vec1.x - vec2.x), 2) + pow((vec1.y - vec2.y), 2));
}

float Math::Dot(Vector3 vec1, Vector3 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
