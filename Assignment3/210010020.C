#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void CountingSort(int arr[], int n, int place)
{
  
  int output[n ];
  int count[10];               // Array to store the occurences of elements
  for (int i = 0; i < 10; i++) // intialize elements of count array as '0'
    count[i] = 0;

  for (int i = 0; i < n; i++)
    count[(arr[i] / place) % 10]++; // loop to count number of distinct elements of the array

  for (int i = 1; i < 10; i++)
    count[i] = count[i] + count[i - 1]; // prefix sum of the count array elements

  for (int i = n - 1; i >= 0; i--)
  {
    output[count[(arr[i] / place) % 10] - 1] = arr[i];
    count[(arr[i] / place) % 10]--;
  }

  for (int i = 0; i < n; i++)
  {
    arr[i] = output[i];
  }
}

void RadixSort(int arr[], int n, int d)
{
  for (int i = 1; i <=pow(10, d); i=i*10)
  {
    CountingSort(arr, n, i);
  }
}
int main(int argc, char *argv[])
{
  
  argc = 3;
  int size=0,n;
  FILE*fptr=fopen(argv[1],"r");

 while (fscanf(fptr,"%d",&n)!=EOF)
 {
  size++;
 }
 rewind(fptr);

int arr[size];


int i=0;

 while (fscanf(fptr,"%d",&n)!=EOF){ 
  arr[i]=n; 
  i++;
 }

 RadixSort(arr,size,atoi(argv[2]));

 fclose(fptr);
 FILE*fout=fopen("radix.txt","w");

 for (int  i = 0; i < size; i++) 
  fprintf(fout,"%d\n",arr[i]);
 
  
fclose(fout);
  return 0;
}