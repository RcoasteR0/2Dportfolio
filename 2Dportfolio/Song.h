#pragma once

#include "stdafx.h"

struct Info
{
	string Song;
	string Chart;
	string Name;
	string Artist;
	float BPM;
	float SongDelay;
	float NoteDelay;
	int Level;
};

static Info test
{
	".\\_Sounds\\test.mp3",
	".\\_Chart\\test.txt",
	"test",
	"N/A",
	120,
	2,
	2,
	1
};

static Info So_Happy
{
	".\\_Sounds\\So Happy.mp3",
	".\\_Chart\\So Happy.txt",
	"So Happy",
	"Raven & Kreyn",
	126,
	2.1f,
	3.057f,
	4
};

static Info Alone
{
	".\\_Sound\\Alone.mp3",
	".\\_Chart\\Alone.txt",
	"Alone",
	"Marshmello",
	142,
	1.9f,
	1.9f,
	5
};

static Info MilK
{
	".\\_Sounds\\MilK.mp3",
	".\\_Chart\\MilK.txt",
	"MilK",
	"Morimori Atsushi",
	150,
	1.0f,
	2.605f,
	6
};

static Info Infinity
{
	".\\_Sounds\\INFINITY.mp3",
	".\\_Chart\\INFINITY.txt",
	"INFINITY",
	"Lunatic Sounds",
	175,
	1.5f,
	1.5f,
	7
};

static Info IWantYou
{
	".\\_Sounds\\I Want You.mp3",
	".\\_Chart\\I Want You.txt",
	"I Want You ~¹ÝÂ¦ ¹ÝÂ¦ Sunshine~",
	"Mycin.T x GOTH x jam - jam",
	165,
	1.7f,
	1.7f,
	8
};

static Info BrainPower
{
	".\\_Sounds\\Brain Power.mp3",
	".\\_Chart\\Brain Power.txt",
	"Brain Power",
	"NOMA",
	170,
	1.6f,
	1.786f,
	10
};
