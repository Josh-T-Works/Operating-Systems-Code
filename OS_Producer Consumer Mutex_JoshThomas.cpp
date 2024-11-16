#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdio.h>

#define MAX 10
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

using namespace std;

void *producer(void *ptr)
{
	for (int i = 1; i <= MAX; i++)
	{
		pthread_mutex_lock(&the_mutex); // Locks the mutex for producer
		while (buffer != 0) { pthread_cond_wait(&condp, &the_mutex); } 
		buffer = i;
		cout << "In Producer: Buffer = " << buffer << endl;
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&the_mutex); // Unlocks the mutex
	}
	pthread_exit(0);
}

void *consumer(void *ptr)
{
	for (int j = 1; j <= MAX; j++)
	{
		pthread_mutex_lock(&the_mutex); // Locks the mutex for consumer
		while (buffer == 0) { pthread_cond_wait(&condc, &the_mutex); }
		cout << "In Consumer: Buffer = " << buffer << endl;
		buffer = 0;
		pthread_cond_signal(&condp);
		pthread_mutex_unlock(&the_mutex); // Unlocks the mutex
	}
	pthread_exit(0);
}


int main() 
{
	pthread_t pro, con;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	cout << "Threads have been started..." << endl;
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
	cout << "Ending main() : Buffer = " << buffer << endl;
}

