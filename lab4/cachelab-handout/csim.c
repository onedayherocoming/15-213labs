#include "cache.h"
#include "cachelab.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void PrintHelpInfo() {
  printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
  printf("Options:\n");
  printf("  -h         Print this help message.\n");
  printf("  -v         Optional verbose flag.\n");
  printf("  -s <num>   Number of set index flag.\n");
  printf("  -E <num>   Number of lines per set.\n");
  printf("  -b <num>   Number of block offset bits.\n");
  printf("  -t <num>   Trace file.\n");
}

int ParseOption(int argc, char *const *argv, int *s, int *e, int *b,
                char **tracePath, int *printFlag) {
  // return 0 if ok
  // return 1 if just print help
  // return 2 if error usage
  int result;
  *printFlag = 0;
  while ((result = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
    switch (result) {
    case 's':
      *s = atoi(optarg);
      break;
    case 'E':
      *e = atoi(optarg);
      break;
    case 'b':
      *b = atoi(optarg);
      break;
    case 't':
      *tracePath = optarg;
      break;
    case 'v':
      *printFlag = 1;
      break;
    case 'h':
      return 1;
    default:
      return 2;
    }
  }
  return 0;
}

int ParseInstruction(char *line, char *type, Address *addr, int *bytes) {
  while (line && *line == ' ') {
    line++;
  }
  if (!line) {
    return 1;
  }
  *type = *line;
  line++;
  *addr = strtoll(line, NULL, 16);
  while (line && *line != ',') {
    line++;
  }
  if (!line) {
    return 1;
  }
  line++;
  *bytes = atoi(line);
  return 0;
}

void SimTrace(int s, int e, int b, char *tracePath, int printFlag) {
  FILE *fp;
  char buffer[100];
  fp = fopen(tracePath, "r");
  if (fp == NULL) {
    return;
  }
  char *resWord[3] = {"hit", "miss", "miss eviction"};
  Cache *c = NewCache(s, e, b);
  while (!feof(fp)) {
    fgets(buffer, 100, fp);
    if (feof(fp)) {
      break;
    }
    int enterIndex = strlen(buffer) - 1;
    buffer[enterIndex] = 0;

    char type;
    Address addr;
    int bytes;
    int parseRes = ParseInstruction(buffer, &type, &addr, &bytes);
    if (parseRes == 1) {
      printf("%s parse failed\n", buffer);
      exit(-1);
    } else {
      switch (type) {
      case 'L':
      case 'S':
        int res = VisitCache(c, addr);
        if (printFlag) {
          printf("%s %s\n", buffer, resWord[res]);
        }
        break;
      case 'M':
        int res1 = VisitCache(c, addr);
        int res2 = VisitCache(c, addr);
        if (printFlag) {
          printf("%s %s %s\n", buffer, resWord[res1], resWord[res2]);
        }
        break;
      default:
        break;
      }
    }
  }
  printSummary(c->hitNum, c->missNum, c->evictNum);
}

int main(int argc, char **argv) {
  int s, e, b;
  char *tracePath = NULL;
  int printFlag;
  int parseRes = ParseOption(argc, argv, &s, &e, &b, &tracePath, &printFlag);
  switch (parseRes) {
  case 0:
    SimTrace(s, e, b, tracePath, printFlag);
    break;
  case 1:
    PrintHelpInfo();
    break;
  case 2:
    printf("Your args is wrong.\n");
    PrintHelpInfo();
    break;
  }
  return 0;
}
