#include "stdafx.h"
#include "Time.h"

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);
	/* 실행 카운터의 빈도
	프로세서 간의 빈도를 일정하게 하기 위해 사용
	시간을 일관되게 측정 */
	fpsUpdateInterval = ticksPerSecond >> 1;
}

Time::~Time(void)
{
}

void Time::Update()
{
	if (isTimerStopped) return;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;

	//fps
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;
}

void Time::Start()
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}

