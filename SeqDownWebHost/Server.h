#pragma once
#include"pch.h"
#include<functional>
#include<memory>
#include<atomic>
#include<iostream>
#include<random>
#include<map>
#include"Spike/HttpServer.h"

// HttpServer instance
HttpServer server(3456);

class RequestReadLocker
{
private:
	std::atomic_bool finished = false;
private:
	Request& request;
public:
	RequestReadLocker(Request& request);
public:
	int ReadBody(std::span<char> buffer);
	void WaitTillFinished();
};

std::map<unsigned int, RequestReadLocker> requests;

extern "C" {
	__declspec(dllexport) void OnRequestPath(const char* path , void(*callback)( unsigned int request_id ));
	__declspec(dllexport) int RequestBodyReader(unsigned int request_id , char* buffer , unsigned int size);
	__declspec(dllexport) void StartServer();
}