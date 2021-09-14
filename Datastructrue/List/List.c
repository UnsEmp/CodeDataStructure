#include <stdio.h>
#include <stdlib.h>
#define STOP -1

typedef struct LNode* List;

struct LNode {
	int Data;
	List next;
};

List CreatList();
void PintList(List L);
int main() {
	List L;
	L = CreatList();
	PintList(L);	
	return 0;
}

List CreatList() {
	List head, L, L1;
	L = (List)malloc(sizeof(struct LNode));
	L->next = NULL;
	head = L;
	int num;
	scanf("%d", &num);
	L->Data = num;
	while(num != STOP) {
		scanf("%d", &num);
		L1 = (List)malloc(sizeof(struct LNode));
		L1->Data = num;
		L1->next = NULL;
		L->next = L1;
		L = L1;
	}
	return head;
}

void PintList(List L) {
	while( L->Data != -1 ) {
		printf("%d ", L->Data);
		L = L->next;
	}
}
