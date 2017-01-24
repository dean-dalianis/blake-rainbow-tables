#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include "Pthreads\pthread.h"
#include "passwordGenerator\password_generator.h"
#include "chainGenerator\chain_generator.h"

using namespace std;

pthread_mutex_t mtx;
PasswordGen *passwords;


void *task(void *);
void merge();

int main(int argc, char** argv) {
	srand((unsigned int) time(NULL));

	clock_t begin = clock();

	/**************** PASSWORD GENERATION ****************/
	passwords = new PasswordGen();
	std::cout << "Generating passwords..." << endl;
	passwords->password_generator("");
	std::cout << passwords->passwords.size() << " unique passwords generated.\n" << endl; 
	/********************************************************/

	/**************** THREAD INITIALIZATION ****************/
	int rc;
	pthread_t threads[threads_num];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void *status;
	pthread_mutex_init(&mtx, NULL);
	/********************************************************/

	/**************** THREAD CREATION ****************/
	std::cout << "Generating Rainbow Table with chain length: " << chainLen
		<< " and chain count: " << chainCount << "\n" << endl;
	for (int i = 0; i < threads_num; i++) {
		printf("main(): creating thread, %d\n", i);
		rc = pthread_create(&threads[i], NULL, task, (void *)i);
	}
	/************************************************/

	/**************** JOIN AND DESTROY ****************/
	pthread_attr_destroy(&attr);
	for (int i = 0; i < threads_num; i++) {
		rc = pthread_join(threads[i], &status);
		printf("main(): completed thread id:%d\n", i);
	}
	pthread_mutex_destroy(&mtx);
	/********************************************************/

	/******** MERGE RAINBOW TABLES ********/
	cout << "\nMerging..." << endl;
	merge();
	/****************************************/
	
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Seconds elapsed: " << elapsed_secs << endl;
	pthread_exit(NULL);
}

void *task(void *threadid) {
	long tid;
	tid = (long)threadid;
	pthread_mutex_lock(&mtx);
	printf("Starting thread: %ld\n", tid);
	pthread_mutex_unlock(&mtx);
	string out = outputPath;
	out.append("rb_tid");
	out.append(to_string(tid));
	ofstream write(out);
	for (int i = 0; i < (chainCount / threads_num); i++) {
		pthread_mutex_lock(&mtx);
		char *password = passwords->get_password();
		pthread_mutex_unlock(&mtx);
		Chain *c = generate_chain(password);
		write << c->head;
		write << " ";
		string tail;
		char temp[2];
		for (int i = 0; i < 32; i++) {
			sprintf(temp, "%02x", c->tail[i]);
			tail.append(temp);
		}
		write << tail;
		write << "\n";
		delete c;
	}
	write.close();
	pthread_exit(NULL);
	return NULL;
}

void merge() {
	ifstream read;
	string out = outputPath;
	out.append(fileName);
	out.append("_tmp");
	ofstream write(out);

	for (int i = 0; i < threads_num; i++){
		string in = outputPath;
		in.append("rb_tid");
		in.append(to_string(i));
		string line;
		read.open(in);
		while (getline(read, line, '\n'))
			write << line << endl;
		read.close();
		remove(in.c_str());
	}
	write.close();
}