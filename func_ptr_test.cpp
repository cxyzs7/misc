//! test the performance of function pointer and functor

#include <vector>
#include <algorithm>
#include <cstdio>
#include <windows.h>

template<typename T>
struct less_str
{
  bool operator()(const T& a, const T& b) const {
    return a < b;
  }
};

template <typename T>
bool less_fun(const T& a, const T& b)
{
  return a < b;
}

struct gen_rand_double
{
  double scaled_range;
  gen_rand_double(const double range) : scaled_range(range/static_cast<double>(RAND_MAX)) {}
  double operator()() { 
    return rand() * scaled_range;
  }
};

double singleRunTestLessFun(int vec_size, int rand_seed)
{
  std::vector<int> rand_vec(vec_size);
  srand(rand_seed);
  std::generate(rand_vec.begin(), rand_vec.end(), gen_rand_double(100.0));
  
  LARGE_INTEGER frequency;        // ticks per second
  LARGE_INTEGER t1, t2;           // ticks

  // get ticks per second
  QueryPerformanceFrequency(&frequency);

  // start timer
  QueryPerformanceCounter(&t1);
  std::sort(rand_vec.begin(), rand_vec.end(), less_fun<double>);
  // stop timer
  QueryPerformanceCounter(&t2);
  // compute and print the elapsed time in millisec
  return (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
}

double singleRunTestLessStr(int vec_size, int rand_seed)
{
  std::vector<int> rand_vec(vec_size);
  srand(rand_seed);
  std::generate(rand_vec.begin(), rand_vec.end(), gen_rand_double(100.0));
  
  LARGE_INTEGER frequency;        // ticks per second
  LARGE_INTEGER t1, t2;           // ticks

  // get ticks per second
  QueryPerformanceFrequency(&frequency);

  // start timer
  QueryPerformanceCounter(&t1);
  std::sort(rand_vec.begin(), rand_vec.end(), less_str<double>());
  // stop timer
  QueryPerformanceCounter(&t2);
  // compute and print the elapsed time in millisec
  return (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
}

int main(int argc, char* argv[])
{
  int num_test_runs = 10;
  double total_elapsed_time = 0.0;
  for (int i = 0;i < num_test_runs; ++i) {
    total_elapsed_time += singleRunTestLessStr(1000000, i*10);
  }
  printf("Average execution Time for %d runs using less functor: %f milliseconds\n", num_test_runs, total_elapsed_time/num_test_runs);
  
  total_elapsed_time = 0.0;
  for (int i = 0;i < num_test_runs; ++i) {
    total_elapsed_time += singleRunTestLessFun(1000000, i*10);
  }
  printf("Average execution Time for %d runs using less function pointer: %f milliseconds\n", num_test_runs, total_elapsed_time/num_test_runs);
  
  return 0;
}
