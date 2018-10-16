#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	int frequency;
	struct node *left;
	struct node *right;
}Node;

Node* pQueue(char d, int p){

	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = d;
	temp->priority = p;
	temp->next = NULL;

	return temp;
}

int isEmpty(Node** head){
	return (*head) == NULL;
}

int peek(Node** head){
	return ((*head)->data);
}

int dequeue(Node** head){
	Node* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void enqueue(Node** head, int d, int p){
	Node* s = *head;

	Node* temp = pQueue(d,p);

	if((*head)->priority < p){
		temp->next = (*head);
		(*head) = temp;
	}else{
		while(s->next != NULL && s->next->priority > p)
			s = s->next;
		temp->next = s->next;
		s->next = temp;
	}

}

int main() 
{ 
    // Create a Priority Queue 
    // 7->4->5->6 
	char charArray[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    int charfreq[] = { 5, 9, 12, 13, 16, 1 };

    int letters = sizeof(charArray)/sizeof(charArray[0]);

    Node* pq = pQueue(charArray[0], charfreq[0]); 

    int i;
    for(i = 1; i < letters; i++){
    	enqueue(&pq, charArray[i], charfreq[i]);
    }
  
    while (!isEmpty(&pq)) { 
        printf("%c ", peek(&pq)); 
        dequeue(&pq); 
    } 
  
    return 0; 
}