#include "stdafx.h"
#include "SoundSystem.h"
#include <FMod/fmod.h>

//������
SoundSystem::SoundSystem()
{
	result = FMOD_System_Create(&system);
	if (result != FMOD_OK)
		ASSERT(false);
	FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, nullptr);
}

//�Ҹ���
SoundSystem::~SoundSystem()
{
	FMOD_Sound_Release(sound);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
}

//�Ҹ� ����
void SoundSystem::CreateSound(const string & fileName)
{
	FMOD_RESULT result = FMOD_System_CreateSound(system, fileName.data(), FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK)
		ASSERT(false);

	bLoop = false;	//���� ����
}

void SoundSystem::CreateBGSound(const string & fileName)
{
	this->fileName = Path::GetFileName(fileName) + " (BGSound)";
	CreateSound(fileName);
}

void SoundSystem::CreateEffSound(const string & fileName)
{
	this->fileName = Path::GetFileName(fileName) + " (EffSound)";
	CreateSound(fileName);
}

//�Ҹ� ���
void SoundSystem::Play()
{
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

//�Ҹ� ����
void SoundSystem::Stop()
{
	FMOD_Channel_Stop(channel);
}

void SoundSystem::Update()
{
	FMOD_Channel_IsPlaying(channel, &bPlaying);

	if (system)
		FMOD_System_Update(system);

	FMOD_MODE mode = bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	FMOD_Channel_SetMode(channel, mode);
	SetVolume(volume);
}

//���� ����
void SoundSystem::SetVolume(float val)
{
	volume = val;
	FMOD_Channel_SetVolume(channel, volume);
}

//���Ұ�
void SoundSystem::SetMute(bool val)
{
	bMute = val;
	FMOD_Channel_SetMute(channel, bMute);
}

//���� ����
void SoundSystem::SetLoop(bool val)
{
	bLoop = val;
}

//GUI
void SoundSystem::GUI(int ordinal)
{
	string objName = "Sound" + to_string(ordinal);
	string GUIFileName = "File Name : " + fileName;
	if (ImGui::BeginMenu(objName.c_str()))
	{
		ImGui::Text(objName.c_str());
		ImGui::Text(GUIFileName.c_str());

		//�Ҹ� ���� ��ư
		if (ImGui::Button("ChangeSound", ImVec2(100, 30)))
		{
			//������̾����� �ٽ����
			ChangeSoundFunc();
			if (bPlaying)
				Play();
		}

		//���� ���� �����̵�
		ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f, "%.2f");
		SetVolume(volume);

		//���Ұ� üũ�ڽ�
		ImGui::Checkbox("Mute", &bMute);
		SetMute(bMute);

		ImGui::EndMenu();
	}
}

//�Ҹ� ����
void SoundSystem::ChangeSoundFunc(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&SoundSystem::ChangeSoundFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::SoundFilter, L"./_Sounds/", func, handle);
	}
	else
	{
		size_t index = fileName.find_last_of('(');

		fileName = Path::GetFileName(String::ToString(path)) + " " + fileName.substr(index, fileName.length());
		
		//������̾����� ���� �� �ٽ����
		if (bPlaying)
		{
			Stop();
		}

		//�������̾����� ����
		if (bLoop)
		{
			CreateSound(String::ToString(path));
			bLoop = true;
		}
		else
		{
			CreateSound(String::ToString(path));
		}
	}
}
