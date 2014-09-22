
IOCP Echo Server for educational purposes only.

# Student Homework

-- done

*echo (성능 테스트 가능한 수준)
*ref count 사용 (ClientSession*)
*AcceptEx/DisconnectEx로 바꾸는거 
*Aggregated Send
*ConnectEx 기능 (Server to Server를 위한 기능)
*DbHelper
*trace + call history + logger + perf checker
*db context
*memory pool
*timer + dosync + lock order checker
*전역작업처리기: GrandCentralExecutor (플레이어끼리 DoSync하면 문제가 생기기 때문.)

-- todo

*packet handling 및 더미 클라 연동 (protobuf)
-- MOVE 패킷 구현


*더미 클라이언트를 통한 성능 테스트
*DB Cache 서버 따로 구현하고 게임서버와 연동

--- extra work ---------------------- 
*half-open connection (유령세션) 감지기능 추가
*graceful server shutdown (+command line tool)
