#include <stdio.h>
#include <stdlib.h>

//********************************DOUBLY lINKED lIST******************************
struct DLL
{
    int data;
    struct DLL *next;
    struct DLL *prev;
};

struct DLL *createNode(int val)
{
    struct DLL *newNode = (struct DLL*)malloc(sizeof(struct DLL));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data= val;
    return newNode;
}

void DLL_insert(struct DLL**head, int val,FILE*fdll)
{
    struct DLL *new_Node = createNode(val);  
    if ((*head) == NULL)
    {
        (*head) = new_Node;
        fprintf(fdll,"inserted %d\n", val);
        return;
    }
    else{
    new_Node->next =(*head);
    (*head)->prev = new_Node;
    (*head) = new_Node;
    new_Node->prev = NULL;

    fprintf(fdll,"inserted %d\n", val);
    }
}

void DLL_deleteNode(struct DLL**head,int val,FILE*fdll){
    struct DLL*temp=*head;
    if((*head)==NULL){
        fprintf(fdll,"cannot delete %d\n",val); 
        return;
    }
    else{
        while( temp!=NULL){
            if(temp->data==val){
                break;
            }
            temp=temp->next;
        }
        if(temp==NULL){
            fprintf(fdll,"cannot delete %d\n",val); //printf("checkpoint 1\n");
            free(temp);
            return;
        }
        else if(temp->next==NULL){
            //printf("checkpoint 2\n");
             temp->prev->next=NULL;
        }                                    
        else if((*head)->data==val){
            //printf("checkpoint 3\n");
            (*head)=(*head)->next;
            (*head)->prev=NULL;
        }
        else{
            //printf("checkpoint 4\n");
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
        }
        
    }
    fprintf(fdll,"deleted %d\n",val);
}
void DLL_find(struct DLL*head,int val,FILE*fdll){
    if(head==NULL){
        fprintf(fdll,"not found %d\n",val);
        return;
    }
    struct DLL *temp = head;
    do{
        if(temp->data==val){
        fprintf(fdll,"found %d\n",val);
        break;
    }
    temp=temp->next;
    }   while(temp!=NULL);
    if(temp==NULL){
        fprintf(fdll,"not found %d\n",val);
        
    }
}
void DLL_print(struct DLL *head,FILE*fdll)
{
    struct DLL *temp = head;
    while (temp != NULL)
    {
        fprintf(fdll,"%d ", temp->data);
        temp = temp->next;
    }
    fprintf(fdll,"\n");
}

//*******************************STACK IMPLEMENTATION*******************************


struct Node{
int data;
struct Node*next;
};
int Stack_isFull(struct Node*top,int size){    //function to check if the stack is full
    int count=1;
    if(top==NULL) //stack empty;
    return 0;
    
     struct Node*temp=top;
     while(temp!=NULL){    //count elementsin stack;
        count++;
        temp=temp->next;
     }
     if(size<count){
        return 1;    //stack is full
     }
    
     return 0;
}
struct Node*Stack_createNode(int val){   //function to create the new node 
    struct Node*newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->data=val;
    newnode->next=NULL;

    return newnode;
}
void Stack_push(struct Node**top,int val,int size,FILE*fstack){  //function to insert the node in the stack

     struct Node*newnode=Stack_createNode(val);
    if(Stack_isFull(*top,size)){
        fprintf(fstack,"overflow\n");
        return ;   
    }
    else if(*top==NULL){
        *top=newnode;
        fprintf(fstack,"pushed %d\n",(*top)->data); 
        return;
    }
    else {
    newnode->next=(*top);
    (*top)=newnode;
    fprintf(fstack,"pushed %d\n",(*top)->data); 
    return ;
    }
   
}

void Stack_find(struct Node*top,int y,FILE*fstack){   //function to search for a given node in the satck
  
    if(top==NULL){
         fprintf(fstack,"not found %d\n",y);
         return;
    }
    struct Node*temp=top;
    while(temp!=NULL){
        if (temp->data==y)
        {
           fprintf(fstack,"found %d\n",y);
           return;
        }
        else{
            temp=temp->next;
        }     
    }
    fprintf(fstack,"not found %d\n",y);
    
}

void Stack_pop(struct Node**top,FILE*fstack){
      

    if((*top)==NULL){
        fprintf(fstack,"underflow");
        return;
    }
    
    fprintf(fstack,"popped %d\n",(*top)->data);
    (*top)=(*top)->next;
    return ;
}

void Stack_print(struct Node*top,FILE*fstack){ //function to print the elements in the stack

    if(top==NULL){
        fprintf(fstack,"\n");
    return;
    }
   struct Node*temp=top;
   while(temp->next!=NULL){
   fprintf(fstack,"%d ",temp->data);
   temp=temp->next;
   }
   fprintf(fstack,"%d ",temp->data);
   fprintf(fstack,"\n");
}

//****************************************CIRCULAR QUEUE****************************************
struct Queue{
  struct Node*front,*rear;
};

int CQueue_isFull(struct Queue*q,int size){
    struct Node*temp=q->front;
    if(q->front==NULL){
        return 0;
    }
    int count=0;
    do{
        count++;
        temp=temp->next;
    }while(temp!=q->front);
    if(count==size)
    return 1;

    return 0;
}

void CQueue_Enqueue(struct Queue**q,int val,int size,FILE*fqueue){
  struct Node*new_Node=(struct Node*)malloc(sizeof(struct Node));
  new_Node->data=val;
  new_Node->next=NULL;  //creating a new Node

  if(CQueue_isFull(*q,size)==1){    //check if the queue is full
    fprintf(fqueue,"overflow\n");
    return;
  }
  
  else if((*q)->rear==NULL){
    (*q)->front=new_Node;
    (*q)->rear=new_Node;
    (*q)->rear->next=(*q)->front;
   } 
   else{
       (*q)->rear->next=new_Node;
       (*q)->rear=new_Node;
       (*q)->rear->next=(*q)->front;
       
   }
   fprintf(fqueue,"enqueued %d\n",val);
   return;

  
}

void CQueue_Dequeue(struct Queue**q,FILE*fqueue){
    struct Node*temp=(*q)->front;
    int val=(*q)->front->data;
    if((*q)->front==NULL && (*q)->rear==NULL){ //empty queue
        fprintf(fqueue,"underflow\n");
        return;
    }
    else if((*q)->front==(*q)->rear){  //only one node present
        (*q)->front=(*q)->rear=NULL;
    }
    else{                             //more than one node present
        (*q)->front=(*q)->front->next;
        (*q)->rear->next=(*q)->front;
    }
    fprintf(fqueue,"dequeued %d\n",val);
    free(temp);
}
void CQueue_find(struct Queue*q,int val,FILE*fqueue){
    if(q->front==NULL&&q->rear==NULL){
        fprintf(fqueue,"\n");
        return;
    }
    else{
        struct Node*temp= q->front;
        do{
           if(temp->data==val){
           fprintf(fqueue,"found %d\n",val);
           return;
           }
           temp=temp->next;
        }while(temp!=q->front);
    }
   fprintf(fqueue,"not found %d\n",val);
    return;
}

void CQueue_print(struct Queue*q,FILE*fqueue){
    struct Node*temp=q->front;
    if(q->front==NULL){
        fprintf(fqueue,"\n");
        return;
    }
    do{
        fprintf(fqueue,"%d ",temp->data);
        temp=temp->next;
    }while(temp!=q->front);
    fprintf(fqueue,"\n");
    return;
}
int main(int argc,char*argv[])
{   
struct Node*top=NULL;
struct Queue*q=(struct Queue*)malloc(sizeof(struct Queue));
q->front=NULL;
q->rear=NULL;
struct DLL *head = NULL;

int size=atoi(argv[2]);
FILE*fptr1=fopen(argv[1],"r");   //to read the input from the file
FILE*fstack=fopen("stack.txt","w");
FILE*fqueue=fopen("queue.txt","w");
FILE*fdll=fopen("dll.txt","w");

char op;
while(fscanf(fptr1," %c",&op)!=EOF){
// printf("%c\n",op);
 if(op=='+'){
    int n;
     fscanf(fptr1,"%d",&n);
    DLL_insert(&head,n,fdll);
    Stack_push(&top,n,size,fstack);
    CQueue_Enqueue(&q,n,size,fqueue);
 }
 if(op=='-'){
    int n;
     fscanf(fptr1,"%d",&n);
    DLL_deleteNode(&head,n,fdll);
    Stack_pop(&top,fstack);
    CQueue_Dequeue(&q,fqueue);
 }
 if(op=='?'){
    int n;
    fscanf(fptr1,"%d",&n);
    DLL_find(head,n,fdll);
    Stack_find(top,n,fstack);
    CQueue_find(q,n,fqueue);
 }
if(op=='!'){
    DLL_print(head,fdll);
    Stack_print(top,fstack);
    CQueue_print(q,fqueue);
 }

}
}