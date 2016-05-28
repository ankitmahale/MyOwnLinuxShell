#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	
	
	int i=0,j=0, temp=0;
	int array[5]={12, 3, 1, 5 ,8};
	int n=5;
	
	int c = 1, d = 1;
 
   for ( c = 1 ; c <= 180000 ; c++ )
       for ( d = 1 ; d <= 32767 ; d++ )
       {}
	
	
	
	
	for (i = 2 ; i <= n; i++)
	{
   		for(j=i-1;j > 0 && array[j] < array[j-1]; j--) 
   		{
      		temp = array[j];
      		array[j]   = array[j-1];
      		array[j-1] = temp;
 			
    	}
  	}
	for(i=0;i<n;i++)
	{
		printf("%d\t", array[i]);
	}
	return 0;	
}
