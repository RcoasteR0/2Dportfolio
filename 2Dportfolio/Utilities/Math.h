#pragma once

#define VK_00 48
#define VK_01 49
#define VK_02 50
#define VK_03 51
#define VK_04 52
#define VK_05 53
#define VK_06 54
#define VK_07 55
#define VK_08 56
#define VK_09 57

class Square;

class Math
{
public:
	static bool Intersect(Square* rect1, Square* rect2);
	static bool Intersect(Square* rect, Vector3 position);
	static bool Intersect(TextureRect* rect, Vector3 position);

	static bool IntersectOriented(Square* rect1, Square* rect2);

	static Vector2 absVec2(Vector2 val);
	static Vector3 absVec3(Vector3 val);

	static float GetDistance(Vector3 vec1, Vector3 vec2);
	static float Dot(Vector3 vec1, Vector3 vec2);
};
