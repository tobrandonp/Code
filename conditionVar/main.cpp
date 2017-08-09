#include <iostream>
#include <boost/thread.hpp>

void Log(const std::string& str)
{
	std::cout << str << std::endl;
}

boost::mutex mutex;
boost::condition_variable condVar;

bool someVariable = false;

void waitForIt()
{
	boost::unique_lock<boost::mutex> lock(mutex);
	while(someVariable == false)
	{
		Log("inside loop again...");
		condVar.wait(lock);
	}
	Log("done");
}

void notifyIt()
{
	sleep(3);
	someVariable = true;
	condVar.notify_one();
}

int main()
{
	Log("notifying first...");
	boost::thread t1(notifyIt);
	Log("sleeping 6 before waiting for it...");
	sleep(6);
	boost::thread t2(waitForIt);

	t1.join();
	t2.join();
}

