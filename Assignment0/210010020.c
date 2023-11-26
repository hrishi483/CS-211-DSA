/**************ACKNOWLEGDEMENT****************
Cebajel Tanan 210010057 
stackoverflow : https://stackoverflow.com/
*/
#include <stdio.h>
#include <stdlib.h>

int min(int a,int b){
    if(a<=b)
    return a;
    else return b;
}
int max(int a,int b){
    if(a<=b)
    return b;
    else return a;
}
int main(int args,char*argc[]){
   
   FILE *Pointer;
   
   int n,i=1,counter=0,SUM=0,mini=0,maxi=0;
   float avg;
   printf("Enter the file to be opened");
    Pointer=fopen(argc[1],"r");
    if(Pointer==NULL){
        printf("file can not be opened");
        exit(0);
    }
    else{
        printf("file is now open\n");
    }
   fscanf(Pointer,"%d",&n);
   mini=n;
   maxi=mini;
    rewind(Pointer);  //takes pointer to the start of the file again
   
   while(fscanf(Pointer,"%d", &n)!=EOF){
    maxi=max(maxi,n);  //function to find the maximum of the numbers
   mini=min(mini,n);   //function to find the minimum  of the numbers
   counter++;
   }
   avg=SUM*1.0/counter;
  fclose(Pointer);
  FILE* Pointer2;
  Pointer2=fopen("output.txt","w");   //writing in output file;
  
  fprintf(Pointer2,"%d\n",counter);      //The number of digits in the file are 
  fprintf(Pointer2,"%d\n",mini);        //minimum of numbers 
  fprintf(Pointer2,"%d\n",maxi);    //  fprintf(Pointer2,"maximum of numbers is %d\n",maxi);

  fprintf(Pointer2,"%d\n",SUM);     //The sum is 
 float SUM2=SUM;
  fprintf(Pointer2,"%.2f\n" , avg);  //The average is 
  
   printf("Chreck file output.txt for the output\n");
   
}