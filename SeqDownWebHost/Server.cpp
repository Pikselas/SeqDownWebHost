#include "pch.h"
#include "Server.h"


void OnRequestPath(const char* path, void * user_ptr ,void(*callback)(void* user_ptr,void * reader))
{
	server.OnPath(path, [=](Request& req, Response& res) {
		
		auto request_reader = std::make_unique<RequestReader>(req);
		callback(user_ptr , request_reader.get());
		request_reader->WaitTillFinished();
		res.SendString("OK");
	});
}

int ReadRequestBody(void* request_reader, char* buffer, unsigned int size)
{
	return reinterpret_cast<RequestReader*>(request_reader)->ReadBody(std::span<char>(buffer, size));
}

void CloseRequest(void* request_id)
{
	reinterpret_cast<RequestReader*>(request_id)->Close();
}

void StartServer()
{
	server.Serve();
}
