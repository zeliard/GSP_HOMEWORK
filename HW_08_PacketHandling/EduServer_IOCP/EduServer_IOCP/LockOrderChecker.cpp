#include "stdafx.h"
#include "Exception.h"
#include "ThreadLocal.h"
#include "FastSpinlock.h"
#include "LockOrderChecker.h"

LockOrderChecker::LockOrderChecker(int tid) : mWorkerThreadId(tid), mStackTopPos(0)
{
	memset(mLockStack, 0, sizeof(mLockStack));
}

void LockOrderChecker::Push(FastSpinlock* lock)
{
	CRASH_ASSERT(mStackTopPos < MAX_LOCK_DEPTH);

	if (mStackTopPos > 0)
	{
		/// 현재 락이 걸려 있는 상태에 진입한경우는 반드시 이전 락의 우선순위가 높아야 한다.
		CRASH_ASSERT(mLockStack[mStackTopPos-1]->mLockOrder < lock->mLockOrder);
	}

	mLockStack[mStackTopPos++] = lock;
}

void LockOrderChecker::Pop(FastSpinlock* lock)
{

	/// 최소한 락이 잡혀 있는 상태여야 할 것이고
	CRASH_ASSERT(mStackTopPos > 0);
	
	/// 당연히 최근에 push했던 녀석이랑 같아야겠지..
	CRASH_ASSERT(mLockStack[mStackTopPos - 1] == lock);

	mLockStack[--mStackTopPos] = nullptr;

}