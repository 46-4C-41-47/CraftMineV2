#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>



class CMThreadPool 
{
private:
	const unsigned threadCount;
	bool shouldStop = false;
	std::mutex queue_mutex;
	std::condition_variable mutex_condition;
	std::vector<std::thread> threads;

public:
	CMThreadPool(unsigned tCount = std::thread::hardware_concurrency());
	
	~CMThreadPool();

	CMThreadPool(const CMThreadPool&) = delete;

	CMThreadPool& operator = (const CMThreadPool&) = delete;

	void start();
	void stop();
};
