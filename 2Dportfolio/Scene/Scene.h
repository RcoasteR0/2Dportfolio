#pragma once

#include "Utilities/RenderTexture.h"
#include "Utilities/SoundSystem.h"

#include "Geometry/Line.h"
#include "Geometry/Square.h"
#include "Geometry/Circle.h"
#include "Geometry/FilledCircle.h"
#include "Geometry/TextureRect.h"
#include "Geometry/AnimationRect.h"

#include"Object/BackMain.h"
#include"Object/Main/SettingUI.h"
#include"Object/Main/Songlist.h"
#include"Object/Main/SongInfo.h"
#include"Object/Main/StartButton.h"
#include"Object/Play/Accurate.h"
#include"Object/Play/BeatLine.h"
#include"Object/Play/Combo.h"
#include"Object/Play/Frame.h"
#include"Object/Play/HitEffect.h"
#include"Object/Play/JudgementLine.h"
#include"Object/Play/Key.h"
#include"Object/Play/Lane.h"
#include"Object/Play/Light.h"
#include"Object/Play/LongNote.h"
#include"Object/Play/Note.h"
#include"Object/Result/ResultUI.h"

class Scene
{
public:
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	bool ChangeScene = false;
	bool BacktoMain = false;
};