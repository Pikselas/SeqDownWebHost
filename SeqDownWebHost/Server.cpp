#include "pch.h"
#include "Server.h"


void OnRequestPath(const char* path, void(*callback)(void * reader))
{
	server.OnPath(path, [&](Request& req, Response& res) {
		
		auto request_reader = std::make_unique<RequestReader>(req);
		callback(request_reader.get());
		request_reader->WaitTillFinished();
		res.SendString("Ooh!! Imouto janai desu?");
	});
}

int ReadRequestBody(void* request_reader, char* buffer, unsigned int size)
{
	return reinterpret_cast<RequestReader*>(request_reader)->ReadBody(std::span<char>(buffer, size));
}

void StartServer()
{
	server.Serve();
}
