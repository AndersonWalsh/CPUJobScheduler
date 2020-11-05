//File: scheduler.cpp
//Purpose: Simulate cpu processes with priority queue
//Author: Anderson Walsh

#include <iostream>
#include <string>
#include <stdlib.h>
#include "heap.h"

using namespace std;

struct Job
{
	string name;
	int length;
	int priority;
	//overloaded operator for sorting Job trees by priority
	bool operator<(Job other) const
	{
		if (this->priority < other.priority)
			return true;
		else
			return false;
	}
};

void getJob(Job &, string command);
string getData(string, string);
bool userCommand(Min_Heap<Job> &);
void runJob(Min_Heap<Job> &);

int main()
{
	Min_Heap<Job> jobs;
	int slices = 0;
	cout << "\nCPU job simluator\n\n";

	//run job on top of heap if there is one, then get command
	//from user, either adding job, doing nothing or exiting

	do
	{
		cout << "Slice " << slices << endl;
		runJob(jobs);
		slices++;
	} while (userCommand(jobs));
}

//precondition: jobs exists
bool userCommand(Min_Heap<Job> &jobs)
{
	string command;
	Job temp;
	getline(cin, command);

	//ugly conditional statement, but it helps ensure that all 3 necessary values are
	//supplied by user before adding job to heap, keeping things from breaking

	if (command == "exit")
	{
		cout << "\nSimulation terminated.\n\n";
		return false;
	}
	else if (command.find("job") != -1 && command.find("priority") != -1 && command.find("length") != -1)
	{
		getJob(temp, command);
		jobs.add(temp);
		return true;
	}
	else
		return true;
} //postcondition: user io processed, either exiting loop, taking no action, or adding job to heap

//precondition: jobs exists
void runJob(Min_Heap<Job> &jobs)
{
	Job temp;
	if (!jobs.isEmpty())
	{
		temp = jobs.getRoot();
		cout << "Running: " << temp.name << endl
			 << "> ";
		temp.length--;
		if (temp.length < 1)
		{
			jobs.remove();
		}
		else
		{
			jobs.setRoot(temp);
		}
	}
	else
		cout << "Running: none\n> ";
} //postcondition: if jobs has a root, it is processed, decrementing length, removing root if job is done

//precondition: job exists, command contains necessary keywords and data
void getJob(Job &job, string command)
{
	job.name = getData(command, "job");
	job.length = atoi(getData(command, "length").c_str());
	job.priority = atoi(getData(command, "priority").c_str());
} //postcondition: data is extracted from command and put in job based on keyword position

//precondition: command exists and contains keyword
string getData(string command, string keyword)
{
	int pos = command.find(keyword);
	pos += keyword.length() + 1; //set pos to start of name
	int start_pos = pos;
	while (command[pos] != ' ' && pos < command.length())
		pos++;
	return command.substr(start_pos, pos - start_pos);
} //postcondition: keyword is found in command, data following the keyword is extracted
