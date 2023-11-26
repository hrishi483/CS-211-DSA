#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int v) {
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void insert(struct node*arr[],int x, int y)
{
    struct node* node_x = createNode(x);
    struct node* node_y = createNode(y);
    if (arr[x]->next == NULL){
        arr[x]->next = node_y;
    }
    else {
        node_y->next=arr[x]->next;
        arr[x]->next=node_y;
    }

    if (arr[y]->next == NULL){
        arr[y]->next = node_x;
    }
    else {
        node_x->next=arr[y]->next;
        arr[y]->next=node_x;
    }
}
//  ****************************Imoplementation of queue*****************************:
struct Queue {
    int front, rear, size;
    int capacity;
    int* array;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(struct Queue* queue) {
    if (isEmpty(queue)) return -1;
    return queue->array[queue->front];
}

//*******************************Driver Code for BFS********************************************

void BFS(struct node*arr[],int startvertex,int size,FILE*f2){    //size is the number of vertices here
     struct Queue*q=createQueue(size);
     int visited[size],shortdist[size];
     struct node*predecessor[size];
     int distance=0;
          
     for(int i=0;i<size;i++){
      visited[i]=0;
      shortdist[i]=-1;
       predecessor[i]=NULL;
     }

     enqueue(q,startvertex);
     visited[startvertex]=1;
     shortdist[startvertex]=0;
     

     while(!isEmpty(q)){
        int start=front(q);
        dequeue(q);
       struct node*temp=arr[start];
       while(temp!=NULL){
            if(visited[temp->vertex]==0){
              enqueue(q,temp->vertex);
              visited[temp->vertex]=1;
              shortdist[temp->vertex]=shortdist[start]+1;
            }
            temp=temp->next;
       }
     }


    for (int i=0;i<size;i++){
          fprintf(f2,"%d\n",shortdist[i]);
    }


}


int main(int argc , char*argv[]) {
    FILE*f1=fopen(argv[1],"r");
    FILE*f2=fopen("sd.txt","w");

    int vertices, edges;
    fscanf(f1,"%d %d",&vertices,&edges);
    struct node * arr[vertices];
    for(int i=0;i<vertices;i++){
        arr[i]=createNode(i);
        arr[i]->vertex = i;
        arr[i]->next =NULL;
    }
    int dest,src;

    while(fscanf(f1,"%d %d",&src, &dest)!=EOF){
        insert(arr, dest, src);
    }
    
    BFS(arr,0,vertices,f2);

    return 0;
}