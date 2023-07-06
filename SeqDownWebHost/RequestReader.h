#pragma once
#include<atomic>
#include<chrono>
#include"Spike/Request.h"

class RequestReader
{
private:
	std::atomic_bool completed;
private:
	Request& request;
public:
	RequestReader(Request& request);
public:
	int ReadBody(std::span<char> buffer);
	void WaitTillFinished();
};

