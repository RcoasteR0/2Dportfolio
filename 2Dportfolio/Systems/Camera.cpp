#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	VPBuffer = new ViewProjectionBuffer();
	D3DXMatrixLookAtLH(&view, &Vector3(0, 0, 0), &Vector3(0, 0, 1), &Vector3(0, 1, 0));
	D3DXMatrixOrthoLH(&proj, WinMaxWidth, WinMaxHeight, 0, 1);
	VPBuffer->SetView(view);
	VPBuffer->setProjection(proj);
}

Camera::~Camera()
{
	SAFE_DELETE(VPBuffer)
}

void Camera::Update()
{
	Move(position);
}

void Camera::Render()
{
	VPBuffer->SetVSBuffer(1);
}

void Camera::Move(Vector3 position)
{
	this->position = position;
	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Vector3(0, 0, 1)), &Vector3(0, 1, 0));
	VPBuffer->SetView(view);
}

void Camera::unProjection(Vector3 * out, Vector3 source, Matrix world)
{
	Vector3 position = source;

	out->x = (position.x * 2.0f / WinMaxWidth) - 1.0f;
	out->y = (position.x * 2.0f / WinMaxHeight) - 1.0f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);

	D3DXVec3TransformCoord(out, out, &wvp);
}

