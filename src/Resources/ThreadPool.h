#pragma once

#include <thread>
#include <vector>
#include <functional>
#include <list>
#include <memory>

class Unit;
class Vision;

class ThreadPool
{
public:
	static ThreadPool& GetInstance();
	~ThreadPool();
	void start(Vision& vision);
	unsigned int max_thread_count;
private:	
	ThreadPool();

	unsigned int thread_count;
	std::vector<std::shared_ptr<std::thread>> threads;
};