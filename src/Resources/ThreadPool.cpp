#include "ThreadPool.h"
#include "../GameClasses/Unit.h"
#include "../Components/Vision.h"

ThreadPool& ThreadPool::GetInstance()
{
	static ThreadPool instance;
	return instance;
}

ThreadPool::ThreadPool()
{
	thread_count = std::thread::hardware_concurrency();
	max_thread_count = std::thread::hardware_concurrency();
	threads.resize(128);
}

ThreadPool::~ThreadPool()
{
	for (auto thread : threads)
	{
		if(thread)
			thread->join();
	}

	threads.clear();
}

void ThreadPool::start(Vision& vision)
{
	static size_t i = 0;

	--thread_count;
	if (!threads[i % (max_thread_count - 1)])
	{
		//threads[i % (max_thread_count - 1)] = std::move(std::make_shared<std::thread>(&Vision::Update, std::move(vision)));
	}
	else
	{
		/*threads[i % (max_thread_count - 1)]->join();
		threads[i % (max_thread_count - 1)] = std::move(std::make_shared<std::thread>(&Vision::Update, std::move(vision)));*/
	}
	++thread_count;
	++i;
}

