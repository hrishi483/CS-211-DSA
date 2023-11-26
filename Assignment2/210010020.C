#include<stdio.h>
#include<stdlib.h>

void merge(int arr[],int l,int r){ //Function to merge the two arrays
    
    int mid=(l+r)/2;
    int n1=mid-l+1,n2=r-mid;
    int L[n1],R[n2];
    
    int i=0,j=0,k=l;
    for(i=0;i<n1;i++)
    L[i]=arr[k++];   //copying the elements to the first temp array
    
    for(j=0;j<n2;j++)
    R[j]=arr[k++];   //copying the elements to the first temp array
    
    k=l,i=0,j=0;
    while(i<n1 && j<n2){
        if(L[i]<R[j])
        arr[k++]=L[i++];  //if the first element of left array is less than right then fill the  
                          //left into the ans array;
        else
        arr[k++]=R[j++];  //else fill the last into the answer array
    }
    
    while(i<n1){          //if the right array elements are over
        arr[k++]=L[i++];
    }
    
    while(j<n2){          //if left array elements are over
        arr[k++]=R[j++];
    }
}

void mergeSort(int arr[],int l,int r){   //Function to recursively sort the array
    if(l>=r){  //base case of recursion
        return;
    }
    else{
        int mid=(l+r)/2;
        
        mergeSort(arr,l,mid);
        
        mergeSort(arr,mid+1,r);
        
        merge(arr,l,r);
    }
    
    
}


int main(int argc,char* argv[]){
    argc=2;

    FILE*fptr;
    fptr=fopen(argv[1],"r");   //Taking input from the file
    int n,counter=0;
    while (fscanf(fptr,"%d ",&n)!=EOF)
    {
        counter++;                  //count the total number of elements in the array
    }
    fclose(fptr);

int k;
    FILE*fileptr;
    fileptr=fopen(argv[1],"r");
    int arr[counter],i=0;           //counter is the total number of elemnts in the inpute file
    while(fscanf(fileptr,"%d",&k)!=EOF){  
        arr[i]=k;                  //copy the elements in the array
        i++;
    }
    FILE*pptr;
    pptr=fopen("mergesort.txt","w+");
    
    
    mergeSort(arr,0,counter-1); //Call the Function mergeSort


    for(int i=0;i<counter;i++){
    fprintf(pptr,"%d\n",arr[i]);    //print the final sorted array in the output.txt file '
    }

    fclose(pptr);
    
}