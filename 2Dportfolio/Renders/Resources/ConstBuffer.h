#pragma once

class InvisibleBuffer : public ShaderBuffer
{
public:
	InvisibleBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{}

	//void SetSelection(int selection)
	//{
	//	data.selection = selection;
	//}

	//void SetOutline(bool bOutline)
	//{
	//	data.bOutline = bOutline;
	//}

	void SetInvisible(bool bInvisible)
	{
		data.bInvisible = bInvisible;
	}

	struct Struct
	{
		bool bInvisible = false;
		bool dummy1[3];
		Vector3 dummy2;
	};

private:
	Struct data;
};