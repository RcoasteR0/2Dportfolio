#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
	//변수 초기화
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * desc, const UINT & count, ID3DBlob * blob)
{
	//매개변수가 0이면 오류 발생
	if (!desc || !count || !blob)
		assert(false);

	//인풋 레이아웃 생성
	HRESULT hr = DEVICE->CreateInputLayout
	(
		desc,						//GPU가 읽을 정점 정보 배열
		count,						//정점 데이터의 수
		blob->GetBufferPointer(),	//정점 셰이더의 주소
		blob->GetBufferSize(),		//정점 셰이더의 크기
		&inputLayout				//인풋 레이아웃의 주소
	);
	ASSERT(hr);
}

void InputLayout::SetIA()
{
	//인풋 레이아웃을 IA 단계에 사용
	DC->IASetInputLayout(inputLayout);
}
