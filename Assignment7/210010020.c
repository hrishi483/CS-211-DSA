#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hash{
  char data[100];
  struct hash*next;
};

int hashfunction(char word[],int m){  //function to calculate the hashvalue 
    int sum=0;
    for (int i=0;word[i]!='\0';i++)
       sum=sum+word[i]; 
    return sum%m;
}

struct hash*insert(struct hash*head,char word[]){  //Function to insert the values in the hashtable
      struct hash*newNode=(struct hash*)malloc(sizeof(struct hash));   
      strcpy(newNode->data,word);
      newNode->next=NULL;

      if(head==NULL){  //If the head is NULL then insert at the head
        head=newNode;
        return head;
      }
      else{
        newNode->next=head;    //if the head is not null then insert at  the node afte head
        head=newNode;
      }
      return head;
}

void sort(char string[]){   //function to sort the given  string used during comaparing 
  char temp;
   int i, j;
   int n = strlen(string);

   for (i = 0; i < n-1; i++) {
      for (j = i+1; j < n; j++) {
         if (string[i] > string[j]) {
            temp = string[i];
            string[i] = string[j];
            string[j] = temp;
         }
      }
   }

   return ;
}


int isAnagram(char word1[],char word2[]){  //FUnction to check the two strings are anagrams or not
  char str1[60],str2[60];
  strcpy(str1,word1);
  strcpy(str2,word2);
  sort(str1);
  sort(str2);

if(strlen(word1)!=strlen(word2)){
   return 0;
}

int i=0;
  while (str1[i]!='\0' || str2[i]!='\0')
  {
    if(str1[i]==str2[i]){
       i++;
    }
    else{
      return 0;
      break;
    }
  }
  return 1;
}
void printAnagram(struct hash*head,char word[],FILE*f2){  //Funtiion to print the words which are anagrams of the words in the queury file
    struct hash*temp=head;
    while (temp!=NULL)
    {   
      int bool=isAnagram(temp->data,word);
      if(bool==1){         
        fprintf(f2,"%s ",temp->data);
      }
      temp=temp->next;
    }
    fprintf(f2,"\n");

}

int main(int argc,char*argv[]){
    FILE*f1=fopen(argv[1],"r");
    FILE*f2=fopen("anagrams.txt","w");
    FILE*f3=fopen(argv[3],"r");
    int m=atoi(argv[2]),val;

    struct hash*hashtable[m];
    for (int  i = 0; i < m; i++)
    {
      hashtable[i]=NULL;
    }
    
    char word[60];
    
    while (fscanf(f1,"%s",word)!=EOF)
    {
      val=hashfunction(word,m);
      hashtable[val]=insert(hashtable[val],word);
    }
    char word2[60];
    while (fscanf(f3,"%s",word2)!=EOF)
    {
      val=hashfunction(word2,m);
      printAnagram(hashtable[val],word2,f2);
    }

}