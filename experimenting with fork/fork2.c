#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
void forkexample() 
{ 
    int x=1;
    // child process because return value zero 
    if (fork() == 0) {
        printf("Hello from Child!\n"); 
        x++;
    // parent process because return value non-zero. 
    }else{
        printf("Hello from Parent!\n"); 
        x=5;
    }
    printf("\n%d\n",x);

} 
int main() 
{ 
    forkexample(); 
    return 0; 
} 