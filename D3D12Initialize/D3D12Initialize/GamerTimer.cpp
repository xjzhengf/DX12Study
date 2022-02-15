#include "GamerTimer.h"
#include <windows.h>

GamerTimer::GamerTimer() :mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0), mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
	mSecondsPerCount = 1.0 / (double)countPerSec;
}

float GamerTimer::TotalTime() const
{
	if (mStopped) {
		return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
	else
	{
		return(float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
}

float GamerTimer::DeltaTime() const
{
	return (float)mDeltaTime;
}

void GamerTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);
	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GamerTimer::Start()
{
	__int64 startTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&startTime);
	if (mStopped) {
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GamerTimer::Stop()
{
	if (!mStopped) {
		__int64 currTime;
		QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void GamerTimer::Tick()
{
	if (mStopped) {
		mDeltaTime = 0.0;
		return;
	}
	__int64 currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0) {
		mDeltaTime = 0.0;
	}
}

