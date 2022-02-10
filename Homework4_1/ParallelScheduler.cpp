#include "ParallelScheduler.h"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

ParallelScheduler::ParallelScheduler(int threadsCount) 
{
	this->count = threadsCount;
	int condSt = pthread_cond_init(&this->cond, NULL);
	int mutexSt = pthread_mutex_init(&this->mutex, NULL);

	if (condSt != 0 || mutexSt != 0) {
		std::cout << "Error initalizin conditional variable or mutex" << std::endl;
		exit(0);
	}	

	// create an array of threads
	this->threads = new pthread_t[this->count];

    // create threads to execute in parallel
	for(int i = 0; i <= this->count; i++){
		
		// create a thread to execute
		int result = pthread_create(&this->threads[i], NULL, thread_start, this);
		
		// something went wrong, exiting
		if(result != 0){
			exit(result);
		}
	}

	 


    // remove allocated array from heap
	//delete [] threads;
}


void ParallelScheduler::run(void (*start_routine) (void*), void* arg) 
{
    struct Task task;
	task.arg = arg;
	task.func = start_routine;
	
	//std::cout << "Lock mutex to add function" << std::endl;

	// lock the mutex to add to queue
	pthread_mutex_lock(this->get_mutex());

	//std::cout << "Pushing function" << std::endl;

	// add function to queue
	this->myFunctions.push(task);

	//std::cout << "Broadcas cond to all" << std::endl;

	// broadcast all threads
	pthread_cond_broadcast(this->get_cond());

	//std::cout << "Unlock mutex after broadcast" << std::endl;

	// unlock the mutex
	pthread_mutex_unlock(this->get_mutex());
}

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

pthread_mutex_t* ParallelScheduler::get_mutex()
{
	return &this->mutex;
}

pthread_cond_t* ParallelScheduler::get_cond()
{
	return &this->cond;
}

void* ParallelScheduler::thread_start(void* args) 
{
    ParallelScheduler *pThis = (ParallelScheduler*) args;

    while (true) {

		//std::cout << "Unlocking befor thread execution" << std::endl;

		pthread_mutex_lock(pThis->get_mutex());

		while(pThis->myFunctions.size() == 0){

			//std::cout << "Queue empty unlock mutex for a while" << std::endl;
			pthread_cond_wait(pThis->get_cond(), pThis->get_mutex());
		}

		//std::cout << "Condition took place" << std::endl;
		struct Task mytask = pThis->myFunctions.front();
			
		//std::cout << "Executing function with arg" << std::endl;
			
		mytask.func(mytask.arg);

		pThis->myFunctions.pop();
		//std::cout << "Unlocking mutex after execution" << std::endl;

		pthread_mutex_unlock(pThis->get_mutex());

		//std::cout<< "Thread executed, rest for a while and then start again" << std::endl;
	    //sleep(1);

    }
	
	return NULL;
}


