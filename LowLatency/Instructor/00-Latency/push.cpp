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
   condition_variable &cv;
   mutex m;
   vector<Message> v;
   atomic<bool> &done;
public:
   transit_zone(atomic<bool> &done, condition_variable &cv) : done{ done }, cv{ cv } {
   }
   template <class It>
      void add(It b, It e) {
         lock_guard<mutex> _{ m };
         v.insert(end(v), b, e);
         cv.notify_one();
      }

   template <int N>
      int bounded_extract(Message (&arr)[N]) { // precondition : n>=0
         unique_lock<mutex> _{ m };
         if (v.empty())
            cv.wait(_, [&] { return !v.empty() || done; });
         auto n = min<int>(N, v.size());
         auto e = next(begin(v), n);
         copy(begin(v), e, begin(arr));
         v.erase(begin(v), e);
         return n;
      }
};

//
// Polling under consumer control
//
int main() {
   atomic<bool> done {false};
   condition_variable cv;

   transit_zone tz{ done, cv };
   thread producer{ [&tz, &done] {
      random_device rd;
      mt19937 prng{ rd() };
      uniform_int_distribution<> distrib{ 1, 400 };
      int doses[] = { 4,11,0,0,20,0,0,0,0,0,0,27,3,0,0 };
      Message data[20];
      for (auto p = begin(doses); !done; ) {
         this_thread::sleep_for(milliseconds{ distrib(prng) });
         tz.add(begin(data), next(begin(data), *p));
         ++p;
         if (p == end(doses)) p = begin(doses);
      }
   } };

   thread consumer{ [&tz, &done] {
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
         }
      }
   } };
   char c;
   cin.get(c);
   done = true;
   cv.notify_all();

   producer.join();
   consumer.join();
}

