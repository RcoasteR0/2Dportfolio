#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D * srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReverse)
	:clipName(clipName)
	, frameCount(frameCount)
	, bReverse(bReverse)
{
	srv = srcTex->GetSRV();

	float imageWidth = (float)srcTex->GetWidth();
	float imageHeight = (float)srcTex->GetHeight();
	Vector2 clipSize = Math::absVec2(endPos - startPos);
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;	//Ŭ�� x�� ũ��
	frameSize.y = clipSize.y;				//Ŭ�� y�� ũ��

	Vector2 texelSize = Vector2(1.0f / imageWidth, 1.0f / imageHeight);	//�ؼ� ũ��

	Vector2 texelStartPos = Vector2(startPos.x * texelSize.x, startPos.y * texelSize.y);	//��������
	texelFrameSize = Vector2(frameSize.x * texelSize.x, frameSize.y * texelSize.y);			//������ ũ��

	//������ ������
	for (UINT i = 0; i < frameCount; i++)
	{
		Vector2 keyframe;
		keyframe.x = texelStartPos.x + texelFrameSize.x * i;
		keyframe.y = texelStartPos.y;
		keyframes.push_back(keyframe);
	}
}

AnimationClip::~AnimationClip()
{
}

Animator::Animator(AnimationClip * animClip)
	: currentAnimClip(animClip)
{
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

Animator::Animator(vector<AnimationClip*> animClips)
	: currentAnimClip(animClips[0])
{
	for (AnimationClip* animClip : animClips)
		this->animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

Animator::~Animator()
{

}

void Animator::Update()
{
	if (bStop) return;

	if (deltaTime > playRate)
	{
		//������ ����
		if (currentAnimClip->GetIsReverse() == false)
		{
			currentFrameIndex++;
			if (currentFrameIndex >= currentAnimClip->GetFrameCount())
			{
				if (bLoop)
				{
					currentFrameIndex = 0;
				}
				else
				{
					currentFrameIndex--;
					if (playonce)
					{
						bStop = true;
						playonce = false;
					}
				}
			}
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}
		else
		{
			currentFrameIndex--;
			if (currentFrameIndex <= 0 && bLoop)
			{
				if (bLoop)
				{
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
				}
				else
				{
					currentFrameIndex++;
					if (playonce)
					{
						bStop = true;
						playonce = false;
					}
				}
			}
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}

		deltaTime = 0.0f;
	}
	else
		deltaTime += Time::Delta();	//+����ð�
}

void Animator::Render(UINT slotIndex)
{
}

void Animator::AddAnimClip(AnimationClip * animClip)
{
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (clipName == currentAnimClip->GetClipName()) return;	//���� Ŭ���� ������(��ȭ����)

	if (animClips.find(clipName) != animClips.end())	//Ŭ�� ã��
	{
		currentAnimClip = animClips.find(clipName)->second;	//Ŭ�� ����
		deltaTime = 0.0f;	//�ð� �ʱ�ȭ
		//�ε��� �ʱ�ȭ
		if (currentAnimClip->GetIsReverse())
			currentFrameIndex = currentAnimClip->GetLastFrameIndex();
		else
			currentFrameIndex = 0;
		currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);	//������ �ʱ�ȭ
	}
}
