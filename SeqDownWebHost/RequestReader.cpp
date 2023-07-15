#include "RequestReader.h"

RequestReader::RequestReader(Request& request) : request(request) , completed(false)
{}

int RequestReader::ReadBody(std::span<char> buffer)
{
	if (auto read_size = request.ReadBody(buffer))
		return *read_size;
	return -1;
}

void RequestReader::Close()
{
	completed = true;
}

void RequestReader::WaitTillFinished()
{
	while (!completed)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
