#include<stdio.h>
#include<stdlib.h>

FILE *fptr;
struct stack{
char name;         //create a stack
int size1,top;
int* arr;
};
struct stack* createstack(int size1,char Name ){
    struct stack* st=(struct stack*)malloc(sizeof(struct stack));
    st->top=-1;
    st->size1 = size1 ;
    st->arr=(int*)malloc(size1*sizeof(int));
    st->name=Name;
    return st;
}
int isFull(struct stack*st){  //Function to check if the stack is full 
if (st->top==st->size1-1)     //if number of elements of the stack becomes equal to size-1 then its full 
return 1;
return 0;
}
int isEmpty(struct stack*st){  //Function to check if the stack is empty
if (st->top==-1)  //if the top of the stack is equal to -1 then full
return 1;
return 0;
}
void push(struct stack * st,int val){
if(isFull(st)){                 //if the stack is already full then it displays the error satck overflow
    printf("Stack Overflow\n");
    return ;
}
st->top=st->top+1;   //increments the top
st->arr[st->top]=val;      // adds the passed value at the top of the stack
}

int  pop(struct stack*st){  //function to delete the top element of the stack
if(isEmpty(st)){
    printf("Stack Underflow\n");   //if stack is Empty there is no element to be popped from the stack
    return 0;
}
int r=st->arr[st->top];
st->top=st->top-1;    //decrements the top of the stack by 1
return r;
}

int peek(struct stack*st){ //Function to return the top element in the stack
return st->arr[st->top];
}
void print(struct stack*st){  //function to print the stack 
    while(!isEmpty(st)){      
        printf("%d",peek(st));  //prints the top of the stack ans then pops out the top element
        pop(st);
    }

}
void AddtoA(struct stack*A,int n){   //Functiom to add all the disk to the POLE A in reverse order depending on the radius of the disk
       
    for(int i=n;i>0;i--){
        fprintf(fptr,"Push disk %d to Stack A\n",i);
        push(A,i);
    }
}

void TOH(struct stack* A,struct stack* B,struct stack* C,int n)
 {  
    if(n==1){
        fprintf(fptr,"Pop disk %d from Stack %c\n",1,A->name); int i=peek(A); pop(A);
        fprintf(fptr,"Push disk %d to Stack %c\n",n,C->name); push(C,i);
        return;
    }
    // TO store the final output of the file in toh.txt
    else{
     TOH(A,C,B,n-1);
      int i=peek(A); pop(A);
     fprintf(fptr,"Pop disk %d from Stack %c\n",n,A->name);
     push(C,i);
     fprintf(fptr,"Push disk %d to Stack %c\n",n,C->name);
     TOH(B,A,C,n-1);
 }

}
int main(int args,char*argc[]){
    fptr=fopen("toh.txt","w+"); 
    int n=atoi(argc[1]);
    //scanf("%d",&sizeOfStack);
    struct stack*A=createstack(n,'A');  //User defined size
    struct stack*B=createstack(n,'B');
    struct stack*C=createstack(n,'C');

    //scanf("%d/n",&n);//Enter the value of n
    AddtoA(A,n);
    char a='A',b='B',c='C';
    TOH(A,B,C,n);
    fclose(fptr);
    
}