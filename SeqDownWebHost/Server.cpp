#include "pch.h"
#include "Server.h"


void OnRequestPath(const char* path, void(*callback)(void* request))
{
	server.OnPath(path, [&](Request& req, Response& res) {
		
		callback(&req);

	});
}

int RequestBodyReader(void* request, char* buffer, unsigned int size)
{
	auto req = static_cast<Request*>(request);
	if(auto read_size = req->ReadBody(std::span<char>(buffer , size)))
		return *read_size;
	return -1;
}

void StartServer()
{
	server.Serve();
}
