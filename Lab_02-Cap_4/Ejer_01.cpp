#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>
using namespace std;
using namespace std::chrono;

long long int total_number;
int thread_count;
pthread_mutex_t mutex;

struct ThreadArgs{
    int rank;
    vector<float> dates;
};

void* rate_bind(void* args){
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
}

int main(int argc, char* argv[]) {
    random_device rd;
    mt19937 gen(rd()); 

    uniform_real_distribution<> dis(0.0, 5.0);

    double random_number = dis(gen);
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <number of threads> <number of dates>" << endl;
        return -1;
    }

    thread_count = atoi(argv[1]);
    total_number = atoll(argv[2]);
    vector<float> numbers(total_number); 
    for (auto &p:numbers){
        //Generate float randoms between 0, 5;
        p = dis(gen); 
        cout<<p<<endl;
    }
    return 0;
    //pthread_t* threads = new pthread_t[thread_count];
    //pthread_mutex_init(&mutex, nullptr);
//
    //// Start measuring time
    //auto start = high_resolution_clock::now();
//
    //// Create threads
    //for (int i = 0; i < thread_count; i++) {
    //    pthread_create(&threads[i], nullptr, perform_tosses, (void*)(long)i);
    //}
//
    //// Join threads
    //for (int i = 0; i < thread_count; i++) {
    //    pthread_join(threads[i], nullptr);
    //}
//
    //// Stop measuring time
    //auto end = high_resolution_clock::now();
    //duration<double> elapsed = end - start;
//
    //// Calculate and print pi estimate
    ////double pi_estimate = 4 * static_cast<double>(circle_hits) / total_tosses;
    ////cout << "Estimated Pi = " << pi_estimate << endl;
    //cout << "Execution Time: " << elapsed.count() << " seconds" << endl;
//
    //// Cleanup
    //pthread_mutex_destroy(&mutex);
    //delete[] threads;
//
    //return 0;
}
