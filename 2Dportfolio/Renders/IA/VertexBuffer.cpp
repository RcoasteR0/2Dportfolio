#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	//�Ҹ��ڿ��� ���� �ʱ�ȭ
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);	//���� ���� IA�ܰ迡 ���
}
