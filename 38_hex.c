#include <stdio.h>
#include <stdlib.h>

int len = 19;

void print_row(int *board, int *r, int l, char* p) {
  printf("%s", p);
  for(int i = 0; i < l; i++) {
    int v = board[r[i]];
    if(v < 10) {
      printf("%i  ", v);
    } else {
      printf("%i ", v);
    }
  }
  printf("\n");
}

void print_board(int *board) {
  int r1[] = {0, 1, 2};
  int r2[] = {3, 4, 5, 6};
  int r3[] = {7, 8, 9, 10, 11};
  int r4[] = {12, 13, 14, 15};
  int r5[] = {16, 17, 18};
  print_row(board, r1, 3, "    ");
  print_row(board, r2, 4, "  ");
  print_row(board, r3, 5, "");
  print_row(board, r4, 4, "  ");
  print_row(board, r5, 3, "    ");
  printf("\n");
}

void shuffle(int *arr) {
  for(int i = len - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int t = arr[j];
    arr[j] = arr[i];
    arr[i] = t;
  }
}

int *copy(int *arr) {
  int *c_arr = (int *)malloc(len * sizeof(int));
  for(int i = 0; i < len; i++) {
    c_arr[i] = arr[i];
  }
  return c_arr;
}

int *make_vals() {
  int* vals = (int *)malloc(len * sizeof(int));
  for(int i = 0; i < len; i++) {
    vals[i] = len - i;
  }
  return vals;
}

int *make_board() {
  int* board = (int *)malloc(len * sizeof(int));
  for(int i = 0; i < len; i++) {
    board[i] = 0;
  }
  return board;
}

int check_range(int *arr, int *r, int l) {
  int num = 38;
  int res = 0;
  int rem = 0;
  for(int i = 0; i < l; i++) {
    res += arr[r[i]];
    if(arr[r[i]] == 0) {
      rem = 1;
    }
  }
  if(rem && res < 38) {
    return 1;
  }
  if(!rem && res == 38) {
    return 1;
  }
  return 0;
}

int check(int *board) {
  int a1[] = {0, 1, 2};
  if(!check_range(board, a1, 3)) return 0;
  int a2[] = {3, 4, 5, 6};
  if(!check_range(board, a2, 4)) return 0;
  int a3[] = {7, 8, 9, 10, 11};
  if(!check_range(board, a3, 5)) return 0;
  int a4[] = {12, 13, 14, 15};
  if(!check_range(board, a4, 4)) return 0;
  int a5[] = {16, 17, 18};
  if(!check_range(board, a5, 3)) return 0;

  int b1[] = {2, 6, 11};
  if(!check_range(board, b1, 3)) return 0;
  int b2[] = {1, 5, 10, 15};
  if(!check_range(board, b2, 4)) return 0;
  int b3[] = {0, 4, 9, 14, 18};
  if(!check_range(board, b3, 5)) return 0;
  int b4[] = {3, 8, 13, 17};
  if(!check_range(board, b4, 4)) return 0;
  int b5[] = {7, 12, 16};
  if(!check_range(board, b5, 3)) return 0;

  int c1[] = {0, 3, 7};
  if(!check_range(board, c1, 3)) return 0;
  int c2[] = {1, 4, 8, 12};
  if(!check_range(board, c2, 4)) return 0;
  int c3[] = {2, 5, 9, 13, 16};
  if(!check_range(board, c3, 5)) return 0;
  int c4[] = {6, 10, 14, 17};
  if(!check_range(board, c4, 4)) return 0;
  int c5[] = {11, 15, 18};
  if(!check_range(board, c5, 3)) return 0;

  return 1;
}

int *fill(int *board, int i, int *vals) {
  if(!check(board)) {
    return NULL;
  }
  if(i == 19) {
    return board;
  }
  for(int j = 0; j < len; j++) {
    if(vals[j] != -1) {
      int *new_board = copy(board);
      int *new_vals = copy(vals);
      new_board[i] = vals[j];
      new_vals[j] = -1;
      shuffle(new_vals);
      int *res = fill(new_board, i + 1, new_vals);
      if(res != NULL) {
        return res;
      }
      free(new_board);
      free(new_vals);
    }
  }
  return NULL;
}

int main(void) {
  int *start_vals = make_vals();
  shuffle(start_vals);
  int *start_board = make_board();
  printf("Starting board:\n");
  print_board(start_board);
  int *solution = fill(start_board, 0, start_vals);
  printf("Solution found:\n");
  print_board(solution);
}
