#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int add_vector(int v[]);
void error_exit(char *s);

int main()
{
  int a[3][3] = {{1, 1, 1},
		 {2, 2, 2},
		 {3, 3, 3}},
    i, row_sum = 0, sum = 0, pd[2];

  // create a pipe
  if(pipe(pd) == -1) {
    error_exit("pipe() failed");
  }

  // N = 3
  for(i = 0; i < 3; ++i) {
    if(fork() == 0) {
      row_sum = add_vector(a[i]);
      if(write(pd[1], &row_sum, sizeof(int)) == -1) {
	error_exit("write() failed");
      }
      return;
    }
  }
  
  for(i = 0; i < 3; ++i) {
    if(read(pd[0], &row_sum, sizeof(int)) == -1) {
      error_exit("read() failed");
    }    
    sum += row_sum;
  }
  printf("Sum of the array = %d\n", sum);

  return 0;
}

int add_vector(int v[])
{
  int i, vector_sum = 0;
  
  for(i = 0; i < 3; ++i) {
    vector_sum += v[i];
  }
  return vector_sum;
}

void error_exit(char *s)
{
  fprintf(stderr, "\nERROR: %s - bye!\n", s);
  exit(1);
}