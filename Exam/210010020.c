#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *next;
    int parent;
};

int l = 0;

struct node*createNode(int val){
    struct node*newNode = (struct node*)malloc(sizeof(struct node));
    newNode->next =NULL;
   newNode->parent = -1;
    newNode->data = val;
    return newNode;
}
void insert(struct node*adjList[],int src,int dest) {
    struct node*newNode = createNode(dest);
    if(adjList[src]->next == NULL){
        adjList[src]->next = newNode;
    }
    else{
        newNode->next=adjList[src]->next;
        adjList[src]->next=newNode;
    }
    return ;
}

struct node* push(struct node* head,int data){
    struct node* newNode = createNode(data);
     if(head==NULL){
         head=newNode;
      }
      else{
        newNode->next=head;
        head=newNode;
      }
      return head;
}

void DFS_visit(struct node *adjlist[], int visited[], int size,int s[], int start)
{
	visited[start] = 1;
	struct node *temp = adjlist[start];

	while(temp != NULL)
	{
		// int k = temp->data;
		if(visited[temp->data] == 0)
		{
			temp->parent = start;
			DFS_visit(adjlist, visited, n, s, temp->data);
		}
		temp = temp->next;
	}

	s[l] = start;
	l++;
}
void print(int s[],int size,FILE *f2){
    for(int i = size-1; i >= 0; i--)
		fprintf(f2, "%d\n", s[i]);

}
void DFS(struct node *adjlist[], int visited[], int s[], int size)
{
	for(int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}

	for(int i = 0; i < size; i++)
		if(visited[i] == 0)
			DFS_visit(adjlist, visited,  size, s, i);
}

int main(int argc, char *argv[])
{

int vertices=0,edges=0 ;

	FILE *f1 = fopen(argv[1],"r");
	FILE *f2 = fopen("ts.txt", "w");
	
	fscanf(f1, "%d %d", &vertices, &edges);
	
	int a[edges], b[edges], visited[vertices], pre[vertices], s[vertices];
	struct node *adjlist[vertices], *p;
	
	for(int i = 0; i < vertices; i++){
		adjlist[i] = createNode(i);
    }
	
	for(int i = 0; i < edges; i++)
	{
		fscanf(f1, "%d %d", &a[i], &b[i]);
	    	
		insert(adjlist,a[i],b[i]);
    }

	DFS(adjlist, visited,s, vertices);

	for(int i = vertices-1; i >= 0; i--)
		fprintf(f2, "%d\n", s[i]);

	fclose(f2);
	fclose(f1);
 
   print(s,vertices,f2);
   return 0;
  }



