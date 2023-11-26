#include<stdio.h>
#include<stdlib.h>

struct SetList{
    int data;              //   _  
    struct SetList*next; //        // |
    int parent; //  parent                 

};    

struct SetList*create(int val){
    struct SetList*node=(struct SetList*)malloc(sizeof(struct SetList));
    node->next=NULL;
    node->data=val;
    node->parent=val;     //Intialize the parent as the value only
    return node;
}

int belongsto(struct SetList*head,int key){
    struct SetList*temp=head;
    while(temp!=NULL){
        if(temp->data==key){
            return 1;
            break;
        }
        else{
            temp=temp->next;
        }
    }
    return 0;
}

struct SetList*insert(struct SetList*head,int val){   //Insert at the head of the Linked List
    struct SetList*newNode=create(val);   
  if(belongsto(head,val)==0){     
    if(head==NULL){
        head=newNode;
    }
    else{
        newNode->next=head;
        head=newNode;
    }
  }
return head;
}

int FindInSet(struct SetList*head,int key){
    struct SetList*temp=head;
    while(temp->data!=key){
        temp=temp->next;
    }
    return temp->parent;
}


struct SetList* Union(struct SetList*head,int key1,int key2){
    struct SetList*temp1=head;
    
    while(temp1->data!=key1 && temp1!=NULL){
        // printf(" temp1->data=%d ",temp1->data);
        temp1=temp1->next;
    }
    // printf("\n Hi");
    int p1=temp1->parent;   
    struct SetList*temp2=head;
    
    //Not printing temp2->data
    // printf("Hi");
    while(temp2->data!=key2 && temp2!=NULL){
        // printf(" temp2->data=%d ",temp2->data);
        temp2=temp2->next;
    }
    int p2=temp2->parent;   
    //For all those nodes which have parent as p2 we need to make their parent as p1
    struct SetList*temp3=head;
    while (temp3!=NULL)
    {
        if(temp3->parent==p2){
            temp3->parent=p1;
        }
        temp3=temp3->next;
    }
    return head;
}

int main(int argc, char *argv[]){

FILE *f1=fopen(argv[1],"r");
FILE *f3=fopen("mst.txt","w");

int V1,V2,W,counter=0,i=0,j=0,k=0;

// Loop to count the total number of elements in the array
 while(fscanf(f1,"%d\n",&V1)!=EOF){
    fscanf(f1,"%d",&V2);
    fscanf(f1,"%d",&W);
        counter++;
 }
 printf("%d\n",counter);  //to count the total number of edges in the input graph
    int arrV1[counter];
    int arrV2[counter];
    int arrW[counter];

rewind(f1);

//Loop to take the input of the array
while(fscanf(f1,"%d",&V1)!=EOF){
    fscanf(f1,"%d",&V2);
    fscanf(f1,"%d",&W);
    arrV1[i]=V1;i++;
    arrV2[j]=V2;j++;
    arrW[k] =W;k++;
}

//Loop for sorting the weights array
for(int m=0;m<counter;m++){
    for(int n=m;n<counter;n++){
        if(arrW[m]>arrW[n]){
            int temp1=arrW[m];
            arrW[m]=arrW[n];    //swap
            arrW[n]=temp1;

            int temp2=arrV1[m];
            arrV1[m]=arrV1[n]; //swap
            arrV1[n]=temp2;

            int temp3=arrV2[m];
            arrV2[m]=arrV2[n]; //swap
            arrV2[n]=temp3;
        }
    }
}

//krushkals algorithm starts here
struct SetList*head=NULL;

//Print the sorted vertices and edges by comparing the weights 
// for(int m=0;m<counter;m++){
//     fprintf(f2,"%d %d %d\n",arrV1[m],arrV2[m],arrW[m]);

// }

for(int m=0;m<counter;m++){
      if(belongsto(head,arrV1[m])==0){
        head=insert(head,arrV1[m]);
      }
      if(belongsto(head,arrV2[m])==0){
        head=insert(head,arrV2[m]);
      }
    }

int m=0;
    //for(int m=0;m<counter;m++){
  while(m<counter){
    //   printf("%d %d %d\n",m,arrV1[m],arrV2[m]);
      if(FindInSet(head,arrV1[m])!=FindInSet(head,arrV2[m])){  //If the parents are not the same then take the union
        head=Union(head,arrV1[m],arrV2[m]);
        fprintf(f3,"%d %d %d\n",arrV1[m],arrV2[m],arrW[m]);
      }
      m++;
  }
//Obtained a Linkd List which stores the distinct values 
    // struct SetList*temp=head;
    //  while(temp!=NULL){
    //     printf("%d(%d)->",temp->data,temp->parent);
    //     temp=temp->next;
    // }

}
