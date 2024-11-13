#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>

#define NUM_INTERVALS 5

using namespace std;
using namespace std::chrono;

long long int total_number;
int thread_count = NUM_INTERVALS;
vector<int> countArray(NUM_INTERVALS, 0);

pthread_mutex_t mutex;

struct ThreadArgs{
    int start;
    int end;
    vector<float>* data;
};

void* classifyNumbers(void* arg) {
    ThreadArgs* threadArgs = (ThreadArgs*)arg;
    int start = threadArgs->start;
    int end = threadArgs->end;
    vector<float>& data = *(threadArgs->data);
    
    for (int i = start; i < end; i++) {
        double num = data[i];
        int interval = (int)num; 
        if (interval >= 0 && interval < NUM_INTERVALS) {
            pthread_mutex_lock(&mutex);
            countArray[interval]++;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}


int main(int argc, char* argv[]) {
    random_device rd;
    mt19937 gen(rd()); 

    uniform_real_distribution<> dis(0.0, 5.0);

    double random_number = dis(gen);
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number of dates>" << endl;
        return -1;
    }

    total_number = atoll(argv[1]);
    vector<float> numbers(total_number); 
    for (auto &p:numbers){
        p = dis(gen);
        //Generate float randoms between 0, 5;
        //cout<<p<<endl;
    }
    
    pthread_t* threads = new pthread_t[thread_count];
    int segment_size = total_number / thread_count;
    ThreadArgs* threadData = new ThreadArgs[thread_count];

    for (int i = 0; i < NUM_INTERVALS; i++) {
        threadData[i].start = i * segment_size;
        threadData[i].end = (i + 1) * segment_size;
        threadData[i].data = &numbers;
        pthread_create(&threads[i], NULL, classifyNumbers, (void*)&threadData[i]);
    }

    for (int i = 0; i < NUM_INTERVALS; i++) {
        pthread_join(threads[i], NULL);
    }

    cout << "Results of number classification into intervals:" << std::endl;
    for (int i = 0; i < NUM_INTERVALS; i++) {
    cout << "Interval [" << i << ", " << (i + 1) << "): " << countArray[i] << " numbers" << endl;
    }

    return 0;
}
