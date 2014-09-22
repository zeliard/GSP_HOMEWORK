#pragma once

#include "MemoryPool.h"
#include "Session.h"
#include "Player.h"
#include "PacketInterface.h"

class ClientSessionManager;

class ClientSession : public Session, public PooledAllocatable
{
public:
	ClientSession();
	virtual ~ClientSession();

	void SessionReset();

	bool PostAccept();
	void AcceptCompletion();

	bool SendRequest(short packetType, const protobuf::MessageLite& payload);

	virtual void OnReceive(size_t len);
	virtual void OnDisconnect(DisconnectReason dr);
	virtual void OnRelease();

public:
	enum { CLIENT_BUFSIZE = 65536 };

	std::shared_ptr<Player> mPlayer;

private:
	
	SOCKADDR_IN		mClientAddr ;

	
	friend class ClientSessionManager;
} ;



