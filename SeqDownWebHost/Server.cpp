#include "pch.h"
#include "Server.h"


void OnRequestPath(const char* path, void(*callback)(unsigned int request_id))
{
	server.OnPath(path, [&](Request& req, Response& res) {
		
		unsigned int locker_id = std::random_device{}();
		std::cout << "ID_GENERATED: " << locker_id << std::endl;
		requests.emplace(locker_id, req);
		callback(locker_id);

		std::cout << "Callback exited" << std::endl;

		requests.at(locker_id).WaitTillFinished();

		std::cout << "Waited till finished" << std::endl;

		res.SendString("Ooh!! Imouto janai desu?");
	});
}

int RequestBodyReader(unsigned int request_id, char* buffer, unsigned int size)
{
	std::cout << "Reading body-1" << std::endl;
	std::cout << "Request id: " << request_id << std::endl;
	return requests.at(request_id).ReadBody(std::span<char>(buffer, size));
}

void StartServer()
{
	try
	{
		server.Serve();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

RequestReadLocker::RequestReadLocker(Request& request) : request(request)
{
	
}

int RequestReadLocker::ReadBody(std::span<char> buffer)
{
	std::cout << "Reading body-2" << buffer.size() << std::endl;
	if (auto read_size = request.ReadBody(buffer))
		return *read_size;
	std::cout << "Finished reading body" << std::endl;
	finished = true;
	return -1;
}

void RequestReadLocker::WaitTillFinished()
{
	while (!finished)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	};
}
