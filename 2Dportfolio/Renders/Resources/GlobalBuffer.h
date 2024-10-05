#pragma once

#include "stdafx.h"

//월드 행렬버퍼
class WorldBuffer : public ShaderBuffer
{
public:
	//생성자
	WorldBuffer()
		:ShaderBuffer(&data, sizeof(WorldStruct))
	{
		D3DXMatrixIdentity(&data.world);
	}

	//월드 행렬 입력
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
	//생성자
	ViewProjectionBuffer()
		: ShaderBuffer(&data, sizeof(ViewProjStruct))
	{
		D3DXMatrixIdentity(&data.View);
		D3DXMatrixIdentity(&data.Projection);
	}
	
	//뷰 행렬 입력
	void SetView(Matrix view)
	{
		D3DXMatrixTranspose(&data.View, &view);
	}

	//투영행렬 입력
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

//색상 버퍼
class ColorBuffer : public ShaderBuffer	
{
public:
	//생성자
	ColorBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{
		data.color = Color(0, 0, 0, 1);
	}
	 
	//색상값 입력
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