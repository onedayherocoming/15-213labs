#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DisplayAllLines(Cache *c) {
  int n = 1 << c->s;
  for (int i = 0; i < n; i++) {
    printf("| ");
    for (int j = 0; j < c->e; j++) {
      Line *t = GetLine(c, i, j);
      printf("%d %x %lld |", t->vaild, t->tag, t->timestamp);
    }
    printf("\n");
  }
}

Cache *NewCache(int s, int e, int b) {
  Cache *c = (Cache *)malloc(sizeof(Cache));
  if (!c) {
    return NULL;
  }
  c->e = e;
  c->s = s;
  c->b = b;
  c->hitNum = 0;
  c->evictNum = 0;
  c->missNum = 0;
  int setNum = 1 << s;
  c->cachePool = (char *)malloc(setNum * e * sizeof(Line));
  if (!c->cachePool) {
    FreeCache(c);
    return NULL;
  }
  memset(c->cachePool, 0, setNum * e * sizeof(Line));
  return c;
}

void FreeCache(Cache *c) {
  if (!c) {
    return;
  }
  if (c->cachePool) {
    free(c->cachePool);
    c->cachePool = NULL;
  }
  free(c);
}

Line *GetLine(Cache *c, Address setIndex, int bIndex) {
  int offset = (bIndex + setIndex * c->e) * sizeof(Line);
  return (Line *)(&(c->cachePool[offset]));
}

void AddressSplit(int s, int b, Address addr, Address *tag, Address *setIndex,
                  Address *offset) {
  Address mask = ~(-1 << b);
  *offset = addr & mask;
  addr >>= b;

  mask = ~(-1 << s);
  *setIndex = addr & mask;
  addr >>= s;

  *tag = addr;
}

int FindOldestLine(Cache *c, Address setIndex) {
  int bIndex = -1;
  long long timeMin = 100000000l;
  for (int i = 0; i < c->e; i++) {
    Line *line = GetLine(c, setIndex, i);
    if (line->timestamp < timeMin) {
      bIndex = i;
      timeMin = line->timestamp;
    }
  }
  return bIndex;
}

void UpdateLine(Cache *c, Address setIndex, int bIndex) {
  static long long time = 1;
  Line *line = GetLine(c, setIndex, bIndex);
  line->timestamp = time++;
}

int VisitCache(Cache *c, Address addr) {
  // if hit , return 0
  // else if miss but not evict ,return 1
  // else return 2
  // DisplayAllLines(c);
  Address tag, setIndex, offset;
  AddressSplit(c->s, c->b, addr, &tag, &setIndex, &offset);
  // printf("setIndex: %d\n", setIndex);
  for (int i = 0; i < c->e; i++) {
    Line *temp = GetLine(c, setIndex, i);
    if (temp->vaild && temp->tag == tag) {
      UpdateLine(c, setIndex, i);
      c->hitNum++;
      // DisplayAllLines(c);
      return 0;
    }
  }
  for (int i = 0; i < c->e; i++) {
    Line *temp = GetLine(c, setIndex, i);
    if (temp->vaild == 0) {
      temp->vaild = 1;
      temp->tag = tag;
      UpdateLine(c, setIndex, i);
      c->missNum++;
      // DisplayAllLines(c);
      return 1;
    }
  }
  int evictIndex = FindOldestLine(c, setIndex);
  Line *line = GetLine(c, setIndex, evictIndex);
  line->tag = tag;
  UpdateLine(c, setIndex, evictIndex);
  c->missNum++;
  c->evictNum++;
  // DisplayAllLines(c);
  return 2;
}
