#include "stdafx.h"
#include "String.h"

void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();

	int cutAt = 0;
	//find_first_of: 토큰 값 중 하나라도 맞는 부분을 반환
	//npos: 포지션 없음(= -1)
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));	//잘래낼 값 푸시백

		origin = origin.substr(cutAt + 1);	//origin에 잘라낸 것 대입
	}

	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));	//자르고 남은부분 푸시백
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0;
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));
}

bool String::StartsWith(string str, string comp)
{
	string::size_type index = str.find(comp);	//comp 위치 반환

	if (index != string::npos && (int)index == 0)	//index가 npos가 아니고 값이 0일때
		return true;

	return false;
}

bool String::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != string::npos;	//found의 값 존재여부
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != string::npos;
}

void String::Replace(string * str, string comp, string rep)
{
	string temp = *str;	//temp에 문자열 저장

	size_t start_pos = 0;	//대체할 문자의 시작 위치
	while ((start_pos = temp.find(comp, start_pos)) != string::npos)	//대체할 문자가 없을때까지 반복
	{
		temp.replace(start_pos, comp.length(), rep);	//문자 대체
		start_pos += rep.length();
	}

	*str = temp;	//대체된 문자열 저장
}

void String::Replace(wstring * str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}
	*str = temp;
}

string String::ToString(Vector3 vec3)
{
	wstring temp;
	temp = to_wstring(vec3.x) + to_wstring(vec3.y) + to_wstring(vec3.z);
	string str = ToString(temp);
	return str;
}

wstring String::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());
	
	return temp;
}

string String::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
