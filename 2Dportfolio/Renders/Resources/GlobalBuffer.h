#pragma once

#include "stdafx.h"

//���� ��Ĺ���
class WorldBuffer : public ShaderBuffer
{
public:
	//������
	WorldBuffer()
		:ShaderBuffer(&data, sizeof(WorldStruct))
	{
		D3DXMatrixIdentity(&data.world);
	}

	//���� ��� �Է�
	void SetWorld(Matrix world)
	{
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct WorldStruct
	{
		Matrix world;
	};

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ShaderBuffer
{
public:
	//������
	ViewProjectionBuffer()
		: ShaderBuffer(&data, sizeof(ViewProjStruct))
	{
		D3DXMatrixIdentity(&data.View);
		D3DXMatrixIdentity(&data.Projection);
	}
	
	//�� ��� �Է�
	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.View, &view);
	}

	//������� �Է�
	void setProjection(Matrix projection)
	{
		D3DXMatrixTranspose(&data.Projection, &projection);
	}

	struct ViewProjStruct
	{
		Matrix View;
		Matrix Projection;
	};

private:
	ViewProjStruct data;
};

//���� ����
class ColorBuffer : public ShaderBuffer	
{
public:
	//������
	ColorBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{
		data.color = Color(0, 0, 0, 1);
	}
	 
	//���� �Է�
	void SetColor(Color color)
	{
		data.color = color;
	}

	struct Struct
	{
		Color color;
	};

private:
	Struct data;
};