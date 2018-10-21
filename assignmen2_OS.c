#include <pthread.h>
#include <stdio.h>

#define SIZE 1000
#define tSIZE 10

int arr[SIZE];
int chunks = 0;
int sum = 0;
void * arraySum(void *arg)
{
    if(chunks <tSIZE)
    {
      for (int i = chunks * (SIZE /tSIZE); i < chunks * (SIZE /tSIZE)+100; i++)
	        sum = sum + arr[i];
    }
  chunks++;
}

int main ()
{
  for (int i = 0; i < SIZE; i++)
    arr[i] = i;

  pthread_t threads[tSIZE];
  for (int i = 0; i < tSIZE; i++)
    pthread_create (&threads[i], NULL,arraySum, NULL);
  for (int i = 0; i < tSIZE; i++)
    pthread_join (threads[i], NULL);

  printf ("Sum of 1000 numbers = %d", sum);
  return 0;
}
