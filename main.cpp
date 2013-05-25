#include "meta_info.h"
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
  return 0;
}