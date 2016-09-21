#include "util/timings.h"

#include <iostream>
#include <thread>
#include <pthread.h>
#include <mutex>

#include <cpuid.h>

using namespace std;
using namespace std::chrono;

class MyMutex
{
private:
    pthread_mutex_t _mutex;

public:
    MyMutex()
    {
        pthread_mutex_init(&_mutex, NULL);
    }

    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
};

int main(int argc, char* argv[])
{
    /* MyMutex m; */
    std::mutex m;
    auto lamda = [](std::mutex& m)
    {
        const int LOOP {1000};
        for (int i=0; i<LOOP; ++i)
        {
            std::lock_guard<std::mutex> lock(m);
            /* m.lock(); */
            /* m.unlock(); */
        }
        return LOOP;
    };
    auto res = test(lamda, m);
    cout << "Function ran for " << duration_cast<nanoseconds>( res.second ).count()/res.first << " ns " << endl;
    std::cout << sizeof(MyMutex) << std::endl;
    std::cout << sizeof(std::mutex) << std::endl;

    return 0;
}
