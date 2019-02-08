#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct node {
    int age;
    char * name;
    struct node *next;
};
typedef struct node node_t;

int sizeOf(  node_t * theList ) {
  int i = 0;
  node_t * temp = theList;

  while(temp != NULL ){
    temp = temp->next;
    i++;
  }
    
  return i;
}

void add(int age, char * name, node_t **theList ) {
  node_t *newS = (node_t *) malloc(sizeof(node_t));

  newS -> age = age;
  newS -> name = name;
  newS -> next = NULL;

  if(*theList == NULL){
    *theList = newS;
  }else{
    node_t * temp = *theList;
    while(temp -> next != NULL ){
      temp = temp -> next;
    }
    temp -> next = newS;
  }
}

void iterate(node_t * pointerToList) {
  node_t * temp = pointerToList;
  printf("\n [");
  while(  temp != NULL ){
    printf("%d %s", temp->age, temp->name);
    temp = temp->next;
    if(temp != NULL){
      printf(", ");
    }
  }
  printf("] \n");
}

void average(node_t * pointerToList){
  node_t * temp = pointerToList;

  int ageSum = 0;

  while(temp != NULL){
    ageSum+=temp->age;
    temp = temp->next;
  }

  printf("\nThe average is: %lf\n", (double) ageSum/sizeOf(pointerToList));
}

void print(  node_t * pointerToList ) {
  node_t * temp = pointerToList;
  printf("\n [");
  while(  temp != NULL ){
    printf("%d %s", temp->age, temp->name);
    temp = temp->next;
    if(temp != NULL){
      printf(", ");
    }
  }
  printf("] \n");
}

void addAtStart(int age, char * name, node_t **theList ) {
  node_t *newS = (node_t *) malloc(sizeof(node_t));
  newS -> age = age;
  newS -> name = name;
  if(theList != NULL){
    newS -> next = *theList;
  }else{
    newS -> next = NULL;
  }
  *theList=newS;
}

void removeAtStart(node_t **theList){
  
  if(sizeOf(*theList)==0){
    return;
  }

  node_t *temp = *theList;
  *theList = temp->next;
  free(temp);
}

void removeAtEnd(node_t **theList){
  
  if(sizeOf(*theList)==0){
    return;
  }else if(sizeOf(*theList)==1){
    *theList = NULL;
    return;
  }

  node_t *temp = *theList;
  node_t *tempBefore = temp;

  while(temp -> next!=NULL){
    tempBefore = temp;
    temp = temp -> next;
  }

  tempBefore -> next = NULL;
  free(temp);
}

void removeItem(node_t **theList, int index){
  
  if(sizeOf(*theList)-1<index || index <0){
    printf("\nThat index doesn't exist in the list\n");
    return;
  }

  if(index==0){
    removeAtStart(theList);
    return;
  }

  if(index==sizeOf(*theList)-1){
    removeAtEnd(theList);
    return;
  }

  int counter = 0;
  node_t *temp = *theList;
  node_t *tempBefore = temp;

  while(counter < index){
    tempBefore = temp;
    temp = temp -> next;
    counter++;
  }

  tempBefore -> next = temp -> next;

  free(temp);
}

void getItem(node_t **theList, int index){

  if(sizeOf(*theList)-1<index || index <0){
    printf("\nThat index doesn't exist in the list\n");
    return;
  }

  int counter = 0;
  node_t *temp = *theList;

  while(counter < index){
    temp = temp -> next;
    counter++;
  }

  printf("\n%d %s\n", temp->age, temp->name);
}

void clear(node_t **theList) {
  node_t * temp = *theList;

  if(temp == NULL){
    return;
  }
  
  if(temp->next == NULL){
    free(temp);
    return;
  }

  clear(&temp->next);
  free(temp);
  *theList = NULL;
}

void oldest(node_t * pointerToList) {
  node_t * temp = pointerToList;
  int oldest = temp->age;
  char * oldestName = temp->name;
  while(  temp != NULL ){
    if(oldest<temp->age){
      oldest = temp->age;
      oldestName = temp->name;
    } 
    temp = temp->next;
    if(temp != NULL){
    }
  }
  printf("\nThe oldest one is: %s with %d years\n", oldestName, oldest);
}


void youngest(node_t * pointerToList) {
  node_t * temp = pointerToList;
  int youngest = temp->age;
  char * youngestName = temp->name;
  while(  temp != NULL ){
    if(youngest>temp->age){
      youngest = temp->age;
      youngestName = temp->name;

    } 
    temp = temp->next;
    if(temp != NULL){
    }
  }
  printf("\nThe younges one is: %s with %d years\n", youngestName, youngest);
}

void allNames(node_t * pointerToList, char c) {
  printf("\n");
  node_t * temp = pointerToList;
  while(temp != NULL){
    if(temp->name[0] == toupper(c)){
      printf("%s is %d years old\n", temp->name, temp->age);
    }
    temp = temp->next;
  }
}

void loadFile(node_t **theList){
  FILE* stream = fopen("dataC.csv", "r");

  char line[1024];

  while (fgets(line, 1024, stream)){
    char *name = (char *) malloc(10* sizeof(char));
    strcpy(name, strtok(line, ","));

    int age;
    age = atoi(strtok(NULL, ""));

    add(age, name, theList);
  }

  free(stream);
}

int main(void) {
  node_t * list = NULL;

  loadFile(&list);
  removeAtStart(&list);

  int end = 0;

  while(!end){
    char c;
    int option;

    printf("\n1. Print linked list\n");
    printf("\n2. Print the oldest person\n");
    printf("\n3. Print the youngest person\n");
    printf("\n4. Print the average of the ages\n");
    printf("\n5. Print all names that start with _\n");
    printf("\n6. Exit\n");

    printf("\nGive me your choice: ");
    scanf("%d", &option);

    switch(option){
      case 1:
        print(list);
      break;

      case 2:
        oldest(list);
      break;

      case 3:
        youngest(list);
      break;

      case 4:
        average(list);
      break;

      case 5:
        printf("\nGive me the letter: ");
        scanf("%s", &c);

        allNames(list, c);
      break;

      case 6:
        end = 1;
      break;
    }

  }

  return 0;
}