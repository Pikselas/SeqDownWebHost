#pragma once
#include"pch.h"
#include<functional>
#include<memory>
#include"Spike/HttpServer.h"

// HttpServer instance
HttpServer server(3456);

extern "C" {
	__declspec(dllexport) void OnRequestPath(const char* path , void(*callback)( void * request ));
	__declspec(dllexport) int RequestBodyReader(void * request , char* buffer , unsigned int size);
	__declspec(dllexport) void StartServer();
}