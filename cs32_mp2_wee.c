//Wee, Filbert Heinrich T.	201701042	WFQR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 53

typedef struct node{				// node
	char data;
	int frequency;
	struct node *left;
	struct node *right;
	int queued;
}Node;

Node* pQueue[MAX];								//make queue
int n;
int fifo = 0;

void HEAPIFY(int r){					// make min heap
	Node* key = pQueue[r];
	int i = r;
	int j = 2*i;
	while(j<=n){													// same frequency arrangment if ASCII
		if(j<n && (pQueue[j+1]->frequency < pQueue[j]->frequency || (pQueue[j+1]->frequency == pQueue[j]->frequency && pQueue[j+1]->queued < pQueue[j]->queued)))
			j+=1;
		if(pQueue[j]->frequency < key->frequency || (pQueue[j]->frequency == key->frequency && pQueue[j]->queued < key->queued)){
			pQueue[i] = pQueue[j];
			i = j;
			j = 2*i;
		}
		else
			break;
	}
	pQueue[i] = key;
}

void P_insert(Node* node){					// priority enqueue
	if(n==MAX)
		printf("KILL ME NOW\n");
	else{
		n++;		
		int i = n;
		int j = i/2;
		while(i>1 && (pQueue[j]->frequency > node->frequency/*)){//*/|| (pQueue[j]->frequency==node->frequency&&pQueue[j]->queued<node->queued))){
			pQueue[i] = pQueue[j];
			i = j;
			j = i/2;
		}
		pQueue[i] = node;
		pQueue[i]->queued = fifo++;
	}
}

Node* P_extract(){				// priority dequeue
	if(n==0){
		printf("I just wanted to sleep\n");
		return NULL;
	}else{
		Node* temp = (Node*)malloc(sizeof(Node));
		temp = pQueue[1];
		pQueue[1] = pQueue[n--];
		HEAPIFY(1);
		return temp;
	}
}

int isEmpty(){						// is queue empty
	return (n==0);
}

int isLeaf(Node* node){					// is leaf  / end of tree
	return (node->left==NULL && node->right==NULL);
}

Node* huffman(char *carr, int *farr, int sz){		// do huffman
	n = 0;		// init q
    Node* temp;
    int arrsize = sz;
    int c;
    for(c = 0; c < arrsize; c++){					//pqueue all values
    	temp = (Node*)malloc(sizeof(Node));
		temp->data = carr[c];
		temp->frequency = farr[c];
		temp->left = NULL;
		temp->right = NULL;
    	P_insert(temp);
    }
	while(n>1){										// analysis of for loop and changing to while loop
		// printf("%d %d\n", c,n);					// pair the 2 least frequencies and put back to queue
		temp = (Node*)malloc(sizeof(Node));
		temp->data = '{';	// just to make sure it is last
		temp->left = P_extract();
		temp->right = P_extract();
		temp->frequency = temp->left->frequency + temp->right->frequency;

		// printf("%d\t%c%d\t%c%d\n", temp->frequency,temp->left->data,temp->left->frequency , temp->right->data,temp->right->frequency);
		P_insert(temp);
	}
	Node* root = P_extract();
	return root;
}

char output[256][100];				// store output since alphabetical order needed

void traverse(Node* node, char s[]){		// traversal of nodes
	// printf("%c\t%s\n", node->data, s);	
	if(isLeaf(node)){
		int temp = node->data;
		strcpy(output[node->data],s);
		return;
	}
	if(node->left!=NULL){
		char strleft[100];
		strcpy(strleft,s);
		strcat(strleft,"0");
		traverse(node->left, strleft);
	}
	if(node->right){
		char strright[100];
		strcpy(strright,s);
		strcat(strright,"1");
		traverse(node->right, strright);
	}
}

int main() 
{ 
	char charArray[256];
	int charfreq[256];
	int i;
	for(i=0;i<256;i++){			// init frequency to 0
		charfreq[i]=0;
		charArray[i]=i;
	}
	char c = getchar();			// get frequencies
	while(c!=EOF){
		if(isalpha(c))
			charfreq[c]++;
		c = getchar();
	}


    char new_charArray[100];
    int new_charfreq[100];
    int new_stuff = 0;
    for(i = 60; i<130; i++){
    	if(charfreq[i]==0) continue;
    	new_charArray[new_stuff] = charArray[i];	// only use char w/ non-0 frequencies
    	new_charfreq[new_stuff++] = charfreq[i];
    }
    // printarray(new_charArray,new_charfreq,new_stuff);
    Node* root = huffman(new_charArray, new_charfreq, new_stuff);		//huffman
    
    char s[100] = "";				// init of a string to print
    traverse(root, s);				// traversal

    int ctr=0;
    for(i = 60; i<130; i++){			// alphabetize
    	if(isalpha(i)&&charfreq[i]!=0){
    		printf("%c %s\n", i, output[i]);	// print final
    	}
    }
	
	return 0; 
}
