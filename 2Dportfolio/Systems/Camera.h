#pragma once

class Camera : public Singleton<Camera>
{
public:
	friend class Singleton<Camera>;

	void Update();
	void Render();

	void Move(Vector3 position);
	void UpdateView();

	void unProjection(Vector3* out, Vector3 source, Matrix world);

	Vector3 GetPosition() { return position; }

private:
	Camera();
	~Camera();

	ViewProjectionBuffer* VPBuffer = nullptr;
	Matrix view, proj;

	Vector3 position = Vector3(0, 0, 0);
};