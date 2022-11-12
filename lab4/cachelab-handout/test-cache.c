#include "cache.h"
#include <assert.h>
#include <stdio.h>

void TEST_AddressSplit() {
  printf("TEST_AddressSplit...\n");
  int s[2] = {2, 1};
  int b[2] = {1, 1};
  Address addrs[2][5] = {{0, 1, 7, 8, 0}, {0, 1, 7, 8, 0}};
  Address res[2][5][3] = {
      {{0, 0, 0}, {0, 0, 1}, {0, 3, 1}, {1, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 1}, {1, 1, 1}, {2, 0, 0}, {0, 0, 0}}};
  Address splitRes[3];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      AddressSplit(s[i], b[i], addrs[i][j], &splitRes[0], &splitRes[1],
                   &splitRes[2]);
      for (int k = 0; k < 3; k++) {
        assert(splitRes[k] == res[i][j][k]);
      }
    }
  }

  printf("PASS TEST_AddressSplit\n");
}

void TEST_CacheVisit() {
  printf("TEST_CacheVisit...\n");
  int s[2] = {2, 1};
  int e[2] = {1, 2};
  int b[2] = {1, 1};
  Address addrs[2][5] = {{0, 1, 7, 8, 0}, {0, 1, 7, 8, 0}};
  int res[2][5] = {{1, 0, 1, 2, 2}, {1, 0, 1, 1, 0}};
  for (int i = 0; i < 2; i++) {
    Cache *c = NewCache(s[i], e[i], b[i]);
    //    printf("( s e b ) : ( %d %d %d )\n", s[i], e[i], b[i]);
    for (int j = 0; j < 5; j++) {
      int hitRes = VisitCache(c, addrs[i][j]);
      //      printf("%d %d %d\n", j + 1, res[i][j], hitRes);
      assert(hitRes == res[i][j]);
    }
  }
  printf("PASS TEST_CacheVisit\n");
}
int main() {
  TEST_AddressSplit();
  TEST_CacheVisit();
  return 0;
}
