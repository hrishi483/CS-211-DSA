#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int length=0;
int k=0;
struct BST{
 int data;
 struct BST*right;
 struct BST*left;
};
struct BST*createNode(int value){
 struct BST*newNode=(struct BST*)malloc(sizeof(struct BST));
 newNode->data=value;
 newNode->right=NULL;
 newNode->left=NULL;
 return newNode;
}
void insert(struct BST**root,int val,FILE* fptr2){
 struct BST*newNode=createNode(val);
 if(*root==NULL){
 *root=newNode;
 fprintf(fptr2,"%d inserted \n",val);
 length++;
 return;
 }
 else {
 struct BST*current= (*root);
 struct BST*temp=current;
 while(current!=NULL){
 temp=current;
 if(current->data>val){
 current=current->left;
 }
 else
 current=current->right;
 }
 if(temp->data>val){
 temp->left=newNode;
 fprintf(fptr2,"%d inserted \n",val);
 }
 else{
 temp->right=newNode;
 fprintf(fptr2,"%d inserted \n",val);
 }
 length++;
 return;
 }
}
int minimum(struct BST*root){
 if(root->left==NULL){ //if the tree is empty 
 return root->data; 
 }
 while (root->left!=NULL)
 {
 root=root->left;
 }
 return root->data; //the leftmost element in the subtree
 
}

int maximum(struct BST*root){
 if (root==NULL){
 return -1;
 }
 while (root->right!=NULL){
 root=root->right;
 }
 return root->data;
}

int search(struct BST*root,int val){
 while(root!=NULL){
 if(root->data==val){
 return 1;
 }
 else if(val<root->data){
 root=root->left;
 }
 else{
 root=root->right;
 }
 }
 return 0;
}

void inorder(struct BST*root,FILE*fptr2){
 if(root==NULL){
 return;
 } 
 else{
 inorder(root->left,fptr2);
 fprintf(fptr2,"%d ",root->data);
 inorder(root->right,fptr2);
 return;
 }
}
void storeinorder(struct BST*root,int arr[]){ 
 if(root != NULL){
 storeinorder(root->left ,arr);
 arr[k] = root->data;
 k=k+1;
 storeinorder(root->right ,arr);
 }
 return; 
}
void pred(struct BST*root,int val,FILE*fptr2){
 if(search(root,val)==0){
 fprintf(fptr2,"%d does not exist\n",val);
 return;
 }
 int array[length];
 k=0;
 storeinorder(root,array);
 int i=0;
 for(;i<length;i++){
 if(array[i]==val){
 break;
 }
 }
 if(i==0){
 fprintf(fptr2,"predecessor of %d does not exist\n",val);
 return;
 }
 fprintf(fptr2,"%d\n",array[i-1]); 
} 

void preorder(struct BST*root,FILE*fptr2){
 if(root==NULL){
 return;
 }
 else {
 fprintf(fptr2,"%d ",root->data);
 preorder(root->left,fptr2);
 preorder(root->right,fptr2);
 }
}

void postorder(struct BST*root,FILE*fptr2){
 if(root==NULL){
 return;
 }
 else{
 postorder(root->left,fptr2);
 postorder(root->right,fptr2);
 fprintf(fptr2,"%d ",root->data);
 }
}

void succ(struct BST*root,int val,FILE*fptr2){
 if(search(root,val)==0){
 fprintf(fptr2,"%d does not exist\n",val);
 return;
 }
 int array[length];
 k=0; 
 storeinorder(root,array);
 int i=0;
 for(;i<length;i++){
 if(array[i]==val){
 break;
 }
 }
 if(i==(length-1)){
 fprintf(fptr2,"successor of %d does not exist\n",val);
 return;
 } 
 fprintf(fptr2,"%d\n",array[i+1]); 
}

int main(int argc ,char*argv[]){
 struct BST*root=NULL;
 
 FILE* fptr=fopen(argv[1],"r");
 FILE* fptr2=fopen("bst.txt","w");
 char *command; int n;
 command=(char*)malloc(20*sizeof(char));
 while (fscanf(fptr,"%s",command)!=EOF)
 { 
 if(strcmp(command,"insert")==0){
 fscanf(fptr," %d",&n);
 insert(&root,n,fptr2);
 }
 else if(strcmp(command,"inorder")==0){
 inorder(root,fptr2);
 fprintf(fptr2,"\n");
 }
 else if(strcmp(command,"preorder")==0){
 preorder(root,fptr2);
 fprintf(fptr2,"\n");
 }
 else if(strcmp(command,"postorder")==0){
 postorder(root,fptr2);
 fprintf(fptr2,"\n");
 }
 else if(strcmp(command,"search")==0){
 fscanf(fptr,"%d",&n);
 int x=search(root,n);
 if(x==0){
 fprintf(fptr2,"%d not found\n",n);
 }
 else{
 fprintf(fptr2,"%d found\n",n);
 }
 }
 else if(strcmp(command,"minimum")==0){
 fprintf(fptr2,"%d\n",minimum(root));
 }
 else if(strcmp(command,"maximum")==0){
 fprintf(fptr2,"%d\n",maximum(root));
 }
 else if(strcmp(command,"successor")==0){
 fscanf(fptr,"%d",&n);
 succ(root,n,fptr2); 
 }
 else if(strcmp(command,"predecessor")==0){
 fscanf(fptr,"%d",&n);
 pred(root,n,fptr2);
 }
 }
 return 0;
}