#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
time_t cTime;

int main()
{
	int pid = fork(); // FORK FOR CHILD AND PARENT PROCESSES
	if (pid != 0)
	{ 
		waitpid(-1, NULL, 0);
		cTime = time(NULL); //UPDATES TIME 
		char *t = ctime(&cTime); // MAKES THE TIME READABLE
		cout << "I am a parent process. Child pid = " << pid << ". Time = " << t << endl;
		exit(0);
	}
	else
	{
		cTime = time(NULL);
		char *t = ctime(&cTime);
		cout << "I am a child process. My pid = " << pid << ". Time = " << t << endl;
		sleep(3); // WAITS 3 SECONDS
		cTime = time(NULL);
		t = ctime(&cTime);
		cout << "I am a child process. My pid = " << pid << ". Time = " << t << endl;
		exit(0);
	}
}

