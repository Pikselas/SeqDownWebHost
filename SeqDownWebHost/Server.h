#pragma once
#include"pch.h"
#include<functional>
#include<memory>

#include"Spike/HttpServer.h"
#include"RequestReader.h"

// HttpServer instance
HttpServer server("3456");

extern "C" {
	__declspec(dllexport) void OnRequestPath(const char* path , void* user_ptr , void(*callback)( void* user_ptr , void* reader ));
	__declspec(dllexport) int ReadRequestBody(void * request , char* buffer , unsigned int size);
	__declspec(dllexport) void CloseRequest(void* request_id);
	__declspec(dllexport) void StartServer();
}