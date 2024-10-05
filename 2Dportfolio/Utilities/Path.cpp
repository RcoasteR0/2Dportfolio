#include "stdafx.h"
#include "Path.h"

bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(wstring path)
{
	DWORD fileValue = GetFileAttributes(path.c_str());
	return fileValue < 0xFFFFFFFF;	//fileValue의 언더플로우 여부(=파일의 존재 여부)
}

bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	//파일이 존재하고 디렉토리일때
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && (attribute & FILE_ATTRIBUTE_DIRECTORY));

	return temp == TRUE;
}

string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

//파일 경로
string Path::GetDirectory(string path)
{
	String::Replace(&path, "\\", "/");	//\\를 /로 대체
	size_t index = path.find_last_of('/');

	//처음부터 마지막 / 까지
	return path.substr(0, index + 1);
}

wstring Path::getDirectory(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

//확장자
string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	//마지막. 부터 끝까지
	return path.substr(index + 1, path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

//파일 이름
string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	//마지막 / 부터 끝까지
	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

//확장자를 제외한 파일이름
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	//파일이름 처음부터 . 까지
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";		//이미지 파일형식
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";				//셰이더 파일형식
const WCHAR* Path::TextFilter = L"Text file\0*.txt";				//텍스트 파일형식
const WCHAR* Path::SoundFilter = L"sound file\0*.wav;*.mp3;*.flac";	//사운드 파일형식
const WCHAR* Path::TileMapFilter = L"TileMapData\0*.data";

void Path::OpenFileDialog(wstring file, const WCHAR * filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	//파일열기 대화상자
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);		//구조체 크기
	ofn.hwndOwner = hwnd;						//대화상자 소유자
	ofn.lpstrFilter = filter;					//파일형식 필터
	ofn.lpstrFile = name;						//파일 이름
	ofn.lpstrTitle = L"불러오기";				//대화상자 이름
	ofn.nMaxFile = 255;							//최대 파일이름 크기
	ofn.lpstrInitialDir = tempFolder.c_str();	//초기 디렉토리
	ofn.Flags = OFN_NOCHANGEDIR;				//플래그(디렉토리를 변경하지 않음)

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;	//불러올 파일 이름
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);	//기능(파일 열기)
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR * filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;
	if (filter == TextFilter)
		ofn.lpstrDefExt = L".txt";
	else if (filter == ShaderFilter)
		ofn.lpstrDefExt = L".hlsl";
	else if (filter == TileMapFilter)
		ofn.lpstrDefExt = L".data";

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring saveName = name;
			String::Replace(&saveName, L"\\", L"/");

			func(saveName);	//기능(파일 저장)
		}
	}
}

//해당 경로의 모든 파일의 이름을 가져온다
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)	//속성이 폴더일때
			{
				if (bFindSubFolder == true && findData.cFileName[0] != '.')		//현재 폴더 제외
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";
					GetFiles(files, folder, filter, bFindSubFolder);	//하위 폴더로 계속 들어간다(재귀함수)
				}
			}
			else	//속성이 파일일때
			{
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));	//다음 데이터가 존재할때까지 반복

		FindClose(handle);
	}
}

//폴더 생성
void Path::CreateFolder(string path)
{
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(wstring path)
{
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);
}

//하위폴더까지 생성
void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/"); //'/'기준으로 폴더를 나눈다

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";

		CreateFolder(temp);
	}
}
