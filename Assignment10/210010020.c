#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  int weight;
  struct node *next;
};

struct node* createNode(int d,int w){
    struct node*newNode=(struct node*)malloc(sizeof(newNode));
    newNode->data=d;
    newNode->weight=w;
    newNode->next=NULL;
    
    return newNode;
} 

int isPresent(struct node* head,int key){
    if(head==NULL){
      return 0;
    }
    else{
        struct node* temp = head;
        while(temp!=NULL){
            if(temp->data==key){
              return 1;
              break;
             }
          temp =temp->next;
        }
    }
    return 0;
}
struct node *SLL(struct node *start,int value){
    struct node*newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data =value;
    newNode->next =NULL;

   if(start==NULL){
      start = newNode;
      return start;
   }
   else{
    newNode->next =start;
    start=newNode;
   }
   return start;
}

//*******************************************Driver Code for Dijikstra********************************
void dijkstra(int vertices,int **G,int startnode,FILE *f)   //dynamic memory allocation to avoid seg-fault
{
int distance[vertices],pred[vertices];
int visited[vertices],count,mindistance,nextnode,i,j;
int **cost = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        cost[i] = (int *)malloc(vertices* sizeof(int));
    }

for(i=0;i<vertices;i++)
for(j=0;j<vertices;j++)
if(G[i][j]==0)
cost[i][j]=__INT16_MAX__;
else
cost[i][j]=G[i][j];
//initialize pred[],distance[] and visited[]

for(i=0;i<vertices;i++)
{
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}

distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count<vertices-1)
{
mindistance=__INT16_MAX__;
//nextnode gives the node at minimum distance
for(i=0;i<vertices;i++)
if(distance[i]<mindistance && !visited[i])
{
mindistance=distance[i];
nextnode=i;
}

//find the shortest path
visited[nextnode]=1;
for(i=0;i<vertices;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
 
for(i=0;i<vertices;i++)
if(i!=startnode)
{
    if(distance[i]==__INT16_MAX__)
       distance[i]=-1;

   fprintf(f,"%d %d\n",i,distance[i]);
}
else{
    fprintf(f,"%d %d\n",i,0);
}
}

//***********INT MAIN ********************************
int main(int argc, char*argv[]) {
FILE*fptr1=fopen(argv[1],"r");
// FILE*ftemp=fopen("sample.txt", "w");
FILE*fptr2=fopen("dijkstra.txt", "w");

int vertices =0;
struct node *start=NULL;

int n1,n2,w;
while(fscanf(fptr1, "%d %d %d", &n1, &n2,&w) != EOF){
    if(isPresent(start,n1)==0){
        start=SLL(start,n1);
        vertices++;
    }
 
    if(isPresent(start,n2)==0){
        start=SLL(start,n2);
         vertices++;
    }
}
printf("TOtal number of vertices: %d\n", vertices);
rewind(fptr1);

//int G[vertices][vertices];
 int **G = (int **)malloc(vertices * sizeof(int *));    //dynamic memory allocation to avoid segmentation issues
    for (int i = 0; i < vertices; i++)
    {
        G[i] = (int *)malloc(vertices* sizeof(int));
    }
for(int i = 0; i < vertices; i++)
for(int j = 0; j < vertices; j++)
   G[i][j]=0;


while (fscanf(fptr1, "%d %d %d",&n1,&n2,&w)!=EOF)
{
     G[n1][n2]=w;
}

// To print the adjacency matrix 
// for(int i=0;i<vertices;i++){
// for(int j=0;j<vertices;j++){
// fprintf(ftemp, "%d ",G[i][j]);
// }
// fprintf(ftemp,"\n");
// }

int source = atoi(argv[2]);
 //int source=442;
  dijkstra(vertices,G,source,fptr2);

 fclose(fptr1);
//  fclose(ftemp);
 fclose(fptr2);
return 0;
}
 
