#pragma once
#include <stdlib.h>
typedef unsigned int Address;

typedef struct line {
  Address tag;
  long long timestamp;
  char vaild;
} Line;

typedef struct Cache {
  char *cachePool;
  int e, s, b;
  int hitNum, missNum, evictNum;
} Cache;

Cache *NewCache(int s, int e, int b);

void FreeCache(Cache *c);

Line *GetLine(Cache *c, Address setIndex, int bIndex);

void AddressSplit(int s, int b, Address addr, Address *tag, Address *setIndex,
                  Address *offset);

int FindOldestLine(Cache *c, Address setIndex);

void UpdateLine(Cache *c, Address setIndex, int bIndex);

int VisitCache(Cache *c, Address addr);
