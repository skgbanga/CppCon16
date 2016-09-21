#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
#include <algorithm>
#include <random>
#include <atomic>

using namespace std;
using namespace std::chrono;

struct Message {};
ostream& operator<<(ostream &os, const Message &) {
   return os << '.';
}

class transit_zone {
   mutex m;
   vector<Message> v;
public:

   template <class It>
      void add(It b, It e) {
         // The class lock_guard is a mutex wrapper that provides a convenient RAII-style
         // mechanism for owning a mutex or several mutexes (since C++17) for the duration
         // of a scoped block.
         lock_guard<mutex> _{ m };

         // std::vector's insert overload taking a position and being/end iterators
         v.insert(end(v), b, e);
      }

   template <int N>
      int bounded_extract(Message (&arr)[N]) { // precondition : n>=0
         lock_guard<mutex> _{ m };

         // takes the min between size of array and size of vector
         auto n = min<int>(N, v.size()); // passing the template T yoursef

         // find the iterator pointing to min
         auto e = next(begin(v), n);

         // copy contents from vector to array
         copy(begin(v), e, begin(arr));

         // erase stuff which we have already copied
         v.erase(begin(v), e);

         // return the number of elements we moved
         return n;
      }
};

//
// Polling under consumer control
//
int main() {
   atomic<bool> done {false};

   transit_zone tz;

   // create two threads - consumer and producer
   thread producer {
      [&tz, &done] {
      random_device rd;
      mt19937 prng{ rd() };
      uniform_int_distribution<> distrib{ 1, 400 };
      int doses[] = { 4,11,0,0,20,0,0,0,0,0,0,27,3,0,0 };
      Message data[20];
      for (auto p = begin(doses); !done; ) {
         // sleep for some time
         this_thread::sleep_for(milliseconds{ distrib(prng) });

         // add some data to your time zone
         tz.add(begin(data), next(begin(data), *p));
         ++p;

         if (p == end(doses))
            p = begin(doses);
      }
   } };

   thread consumer { [&tz, &done] {
      enum { N = 10 };
      auto period = 500ms;
      while (!done) {
         auto next_period = system_clock::now() + period;
         Message buf[N];
         auto n = tz.bounded_extract(buf);
         for_each(begin(buf), next(begin(buf), n), [](const Message &m) {
            cout << m;
         });
         cout << endl;
         if (next_period < system_clock::now()) {
            cerr << "Overrun!" << endl;
         } else {
            this_thread::sleep_until(next_period);
         }
      }
   } };

   char c;
   cin.get(c);
   done = true;

   producer.join();
   consumer.join();
}

