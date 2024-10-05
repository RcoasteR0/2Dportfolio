#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	//소멸자에서 변수 초기화
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);	//정점 버퍼 IA단계에 사용
}
