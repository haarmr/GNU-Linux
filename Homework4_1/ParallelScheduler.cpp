#include "ParallelScheduler.h"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
 * Ininitialize out class and create threads of count
 */
ParallelScheduler::ParallelScheduler(int threadsCount) 
{
	this->count = threadsCount;
	this->cond = new pthread_cond_t();
	this->mutex = new pthread_mutex_t();

	// create an array of threads
	this->threads = new pthread_t[this->count];

    // create threads to execute in parallel
	for(int i = 0; i < this->count; i++){
		
		// create a thread to execute
		int result = pthread_create(&this->threads[i], NULL, thread_start, this);
		
		// something went wrong, exiting
		if(result != 0){
			std::cout << "Error making thread, exit" << std::endl;
			exit(result);
		}
	}
}

/*
 * Add method with args to queue 
 */
void ParallelScheduler::run(void (*start_routine) (void*), void* arg) 
{
	// create task with for function and arguments
    struct Task task;
	task.arg = arg;
	task.func = start_routine;
	
	// lock the mutex to add task to queue
	pthread_mutex_lock(this->get_mutex());

	// add function to queue
	this->myFunctions.push(task);

	// unlock the mutex
	pthread_mutex_unlock(this->get_mutex());

	// broadcast to all threads that task has been added
	pthread_cond_signal(this->get_cond());
}

/*
 * Join all threads
 */
void ParallelScheduler::wait_for_threads() 
{
	// wait for all the threads to complete
	for(int i = 0; i < this->count; ++i){
		
		// the return value of thread
		void* retVal;
		
		// join the tread
		pthread_join(this->threads[i], &retVal);
	}
}

/*
 * Retrieve mutex
 */
pthread_mutex_t* ParallelScheduler::get_mutex()
{
	return this->mutex;
}

/*
 * Retrieve conditional variable
 */
pthread_cond_t* ParallelScheduler::get_cond()
{
	return this->cond;
}

/*
 * Run thread
 */
void* ParallelScheduler::thread_start(void* args) 
{
	// get instance from argument
    ParallelScheduler *pThis = (ParallelScheduler*) args;

    while (true) {

		// lock mutex before accessing queue
		pthread_mutex_lock(pThis->get_mutex());

		// wait for tasks to be added to queue
		while(pThis->myFunctions.empty()) {

			// queue empty unlock mutex for a while
			pthread_cond_wait(pThis->get_cond(), pThis->get_mutex());
		}

		// condition took place
		struct Task mytask = pThis->myFunctions.front();
		
		// remove exeutinh task from queue
		pThis->myFunctions.pop();
		
		// unlocking mutex after execution
		pthread_mutex_unlock(pThis->get_mutex());

		// executing function with arg
		mytask.func(mytask.arg);
    }
	
	return NULL;
}


