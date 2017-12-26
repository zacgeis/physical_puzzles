#include <stdio.h>
#include <stdlib.h>

int llen = 16;
int l0b[16] = { 6, -1,  8, -1,  8, -1, 16, -1, 19, -1, 8, -1,  17, -1,  6, -1};
int l1a[16] = {10,  5,  6, 18,  8, 17,  4, 20,  4, 14, 4,  5,  1,  14, 10, 17};
int l1b[16] = { 8, -1, 10, -1, 14, -1, 11, -1,  8, -1, 12, -1, 11, -1,  3, -1};
int l2a[16] = {13, 13,  0, 22, 19, 10,  0,  5, 20,  8, 19, 10, 15, 20, 12, 20};
int l2b[16] = { 8, -1, 10, -1, 11, -1, 10, -1,  0, -1, 11, -1, 8,  -1,  8, -1};
int l3a[16] = { 5,  8,  5,  1, 24,  8, 10, 20,  7, 20, 12,  1, 10, 12, 22,  0};
int l3b[16] = { 9, -1,  6, -1, 10, -1,  8, -1, 10, -1, 9,  -1, 8,  -1,  8, -1};
int l4a[16] = { 2,  9, 27, 13, 11, 13, 10, 18, 10, 10, 10, 10, 15,  7, 19, 18};
int l4b[16] = { 16, 4,  7,  0, 16,  8,  4, 15, 7,  10, 1,  10, 4,   5,  3, 15};

int read(int *a, int *b, int i, int r, int len) {
  int v = a[(i + r) % len];
  if(v == -1) {
    return b[i % len];
  }
  return v;
}

int *solve() {
  int *solution = (int *)malloc(4 * sizeof(int));

  for(int r0 = 0; r0 < llen; r0++) {
    for(int r1 = 0; r1 < llen; r1++) {
      for(int r2 = 0; r2 < llen; r2++) {
        for(int r3 = 0; r3 < llen; r3++) {
          int solved = 1;
          for(int i = 0; i < llen; i++) {
            int sum = 0;
            sum += read(l0b, l1a, i + r1 + r2 + r3, r0, llen);
            sum += read(l1b, l2a, i + r2 + r3, r1, llen);
            sum += read(l2b, l3a, i + r3, r2, llen);
            sum += read(l3b, l4a, i, r3, llen);
            sum += read(l4b, NULL, i, 0, llen);
            if(sum != 50) {
              solved = 0;
              break;
            }
          }
          if(solved) {
            solution[0] = r0;
            solution[1] = r1;
            solution[2] = r2;
            solution[3] = r3;
            return solution;
          }
        }
      }
    }
  }

  return NULL;
}

void print_reads(int *a, int *b, int offset, int rotation, int len) {
  for(int i = 0; i < len; i++) {
    int v = read(a, b, i + offset, rotation, llen);
    if(v < 10) {
      printf("%i   ", v);
    } else {
      printf("%i  ", v);
    }
  }
  printf("\n");
}

int main(void) {
  printf("Start State:\n");
  print_reads(l0b, l1a, 0, 0, llen);
  print_reads(l1b, l2a, 0, 0, llen);
  print_reads(l2b, l3a, 0, 0, llen);
  print_reads(l3b, l4a, 0, 0, llen);
  print_reads(l4b, NULL, 0, 0, llen);
  int *solution = solve();
  printf("\n");
  if(solution == NULL) {
    printf("Solution not found.\n");
    return 1;
  }
  printf("Solution found.\n");
  printf("Rotations: ");
  for(int i = 0; i < 4; i++) {
    printf("%i ", solution[i]);
  }
  printf("\nEnd State:\n");
  print_reads(l0b, l1a, solution[1] + solution[2] + solution[3], solution[0], llen);
  print_reads(l1b, l2a, solution[2] + solution[3], solution[1], llen);
  print_reads(l2b, l3a, solution[3], solution[2], llen);
  print_reads(l3b, l4a, 0, solution[3], llen);
  print_reads(l4b, NULL, 0, 0, llen);
}
