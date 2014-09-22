#include "stdafx.h"
#include "SQLStatement.h"
#include "Log.h"
#include "PlayerDBContext.h"
#include "DBHelper.h"
#include "ClientSession.h"

void CreatePlayerDataContext::SetNewName(const wchar_t* name)
{
	wcscpy_s(mPlayerName, name);
}

bool CreatePlayerDataContext::OnSQLExecute()
{
	DBHelper dbHelper;
	int result = 0;

	dbHelper.BindParamText(mPlayerName);
	dbHelper.BindResultColumnInt(&result);

	if (dbHelper.Execute(SQL_CreatePlayer))
	{
		if (dbHelper.FetchRow())
		{
			/// 적용받은 행이 하나도 없다면, 실패라고 간주하자
			return result != 0;
		}
	}

	return false;
}

void CreatePlayerDataContext::OnFail()
{
	std::stringstream dbfail;
	dbfail << "LOG: DB_FAIL at " << typeid(this).name() << std::endl;
	std::string logErr = dbfail.str();

	EVENT_LOG(logErr.c_str(), 0);
	std::cout << logErr;

}

bool DeletePlayerDataContext::OnSQLExecute()
{
	DBHelper dbHelper;

	int result = 0;

	dbHelper.BindParamInt(&mPlayerId);
	dbHelper.BindResultColumnInt(&result);

	if (dbHelper.Execute(SQL_DeletePlayer))
	{
		if (dbHelper.FetchRow())
		{
			/// 적용받은 행이 하나도 없다면, 실패라고 간주하자
			return result != 0;
		}
	}

	return false;
}

void DeletePlayerDataContext::OnFail()
{
	std::stringstream dbfail;
	dbfail << "LOG: DB_FAIL at " << typeid(this).name() << std::endl;
	std::string logErr = dbfail.str();

	EVENT_LOG(logErr.c_str(), 0);
	std::cout << logErr;

}


bool LoadPlayerDataContext::OnSQLExecute()
{
	DBHelper dbHelper;

	dbHelper.BindParamInt(&mPlayerId);

	dbHelper.BindResultColumnText(mPlayerName, MAX_NAME_LEN);
	dbHelper.BindResultColumnFloat(&mPosX);
	dbHelper.BindResultColumnFloat(&mPosY);
	dbHelper.BindResultColumnFloat(&mPosZ);
	dbHelper.BindResultColumnBool(&mIsValid);
	dbHelper.BindResultColumnText(mComment, MAX_COMMENT_LEN);

	if (dbHelper.Execute(SQL_LoadPlayer))
	{
		if (dbHelper.FetchRow())
		{
			return true;
		}
	}

	return false;
}

void LoadPlayerDataContext::OnSuccess()
{
	//mSessionObject->mPlayer->ResponseLoad(mPlayerId, mPosX, mPosY, mPosZ, mIsValid, mPlayerName, mComment);
	mSessionObject->mPlayer->DoSync(&Player::ResponseLoad, mPlayerId, mPosX, mPosY, mPosZ, mIsValid, mPlayerName, mComment);
}

void LoadPlayerDataContext::OnFail()
{
	EVENT_LOG("LoadPlayerDataContext fail", mPlayerId);
}


bool UpdatePlayerPositionContext::OnSQLExecute()
{
	DBHelper dbHelper;
	int result = 0;

	dbHelper.BindParamInt(&mPlayerId);
	dbHelper.BindParamFloat(&mPosX);
	dbHelper.BindParamFloat(&mPosY);
	dbHelper.BindParamFloat(&mPosZ);

	dbHelper.BindResultColumnInt(&result);

	if (dbHelper.Execute(SQL_UpdatePlayerPosition))
	{
		if (dbHelper.FetchRow())
		{
			return result != 0;
		}
	}

	return false;
}

void UpdatePlayerPositionContext::OnSuccess()
{
	//mSessionObject->mPlayer->ResponseUpdatePosition(mPosX, mPosY, mPosZ);
	mSessionObject->mPlayer->DoSync(&Player::RequestUpdatePosition, mPosX, mPosY, mPosZ);
}




bool UpdatePlayerCommentContext::OnSQLExecute()
{
	DBHelper dbHelper;
	int result = 0;
	dbHelper.BindParamInt(&mPlayerId);
	dbHelper.BindParamText(mComment);

	dbHelper.BindResultColumnInt(&result);

	if (dbHelper.Execute(SQL_UpdatePlayerComment))
	{
		if (dbHelper.FetchRow())
		{
			return result != 0;
		}
	}

	return false;
}

void UpdatePlayerCommentContext::SetNewComment(const wchar_t* comment)
{
	wcscpy_s(mComment, comment);
}

void UpdatePlayerCommentContext::OnSuccess()
{
	//mSessionObject->mPlayer->ResponseUpdateComment(mComment);
	mSessionObject->mPlayer->DoSync(&Player::ResponseUpdateComment, const_cast<const wchar_t*>(mComment));
}



bool UpdatePlayerValidContext::OnSQLExecute()
{
	DBHelper dbHelper;
	int result = 0;

	dbHelper.BindParamInt(&mPlayerId);
	dbHelper.BindParamBool(&mIsValid);

	dbHelper.BindResultColumnInt(&result);

	if (dbHelper.Execute(SQL_UpdatePlayerValid))
	{
		if (dbHelper.FetchRow())
		{
			return result !=0 ;
		}
	}

	return false;
}

void UpdatePlayerValidContext::OnSuccess()
{
	//mSessionObject->mPlayer->ResponseUpdateValidation(mIsValid);
	mSessionObject->mPlayer->DoSync(&Player::ResponseUpdateValidation, mIsValid);
}


