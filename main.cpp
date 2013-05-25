#include "meta_info.h"
#include "array_size.h"
#include "moving_average.h"
#include <cstdio>

struct data
{
  int x1;
  double x2;
  char x3;
  float x4;
  int* x5;
};
META(data, 5, x1, x2, x3, x4, x5);

int main(int argc, char* argv[])
{
  class_meta<data> info;
  printf("%d members\n", info.num_members);
  for (int i = 0;i < info.num_members; ++i) {
    printf("member %d: type %s name %s size %d offset %d\n", i, info.members[i].type, info.members[i].name, info.members[i].size, info.members[i].offset);
  }
  
  moving_average<double> mv_double(5);
  mv_double.add_val(1.0);
  mv_double.add_val(2.0);
  mv_double.add_val(3.0);
  mv_double.add_val(4.0);
  mv_double.add_val(5.0);
  printf("%f %f\n", mv_double.get_average(), mv_double.get_linear_weighted_avgerage());
  
  int a[12];
  double b[20];
  const int sz1 = sz(a);
  const int sz2 = sz(b);
  int c[sz1];
  int d[sz2];
  printf("%d %d\n", sizeof(c)/sizeof(int), sizeof(d)/sizeof(int));
  return 0;
}
