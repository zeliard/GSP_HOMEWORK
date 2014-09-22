#pragma once
#include "ContentsConfig.h"
#include "SyncExecutable.h"

class ClientSession;


class Player : public SyncExecutable
{
public:
	Player(ClientSession* session);
	~Player();

	bool IsValid() { return mPlayerId > 0; }
	
	void RequestLoad(int pid);
	void ResponseLoad(int pid, float x, float y, float z, bool valid, wchar_t* name, wchar_t* comment);

	void RequestUpdatePosition(float x, float y, float z);
	void ResponseUpdatePosition(float x, float y, float z);

	void RequestUpdateComment(const wchar_t* comment);
	void ResponseUpdateComment(const wchar_t* comment);

	void RequestUpdateValidation(bool isValid);
	void ResponseUpdateValidation(bool isValid);

	void OnTick(); ///< 로그인후 1초마다 불리는 기능

private:

	void PlayerReset();

	//TODO: 테스트용, 요놈들은 사실상 외부로 빼야 함
	void TestCreatePlayerData(const wchar_t* newName);
	void TestDeletePlayerData(int playerId);

private:

	int		mPlayerId;
	float	mPosX;
	float	mPosY;
	float	mPosZ;
	bool	mIsValid;
	wchar_t	mPlayerName[MAX_NAME_LEN];
	wchar_t	mComment[MAX_COMMENT_LEN];

	ClientSession* const mSession;
	friend class ClientSession;
};