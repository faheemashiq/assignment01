#include<stdlib.h>

int main()
{
	int SIZE = 1000;
	int arr[SIZE];
	int fd[2];
	int totalSumArray[10];
	for(int i=0;i<SIZE;i++)
		arr[i]=i;		
	
	for (int i = 0; i < 10; i++)
	{
		if(pipe(fd)==-1)
			printf("child not created\n");
		int cpid=fork();
		if(cpid==0){
			close(fd[0]);		
			int sum=0;
			for(int j=i*100;j<i*100+100;j++)
				sum=sum+arr[j];	

			write(fd[1],&sum,sizeof(sum));
			close(fd[1]);	
			exit(0);
		}
		else{
			wait(NULL);
			close(fd[1]);
			totalSumArray[i]=0;
			read(fd[0],&totalSumArray[i],sizeof(totalSumArray[i]));
			//printf("%d\n",totalSumArray[i]);
		}
	}
	int totalSum=0;
	for(int i=0;i<10;i++){
		totalSum+=totalSumArray[i];
	}
	printf("Sum of 1000 numbers is: %d", totalSum);
	return 0;
}
