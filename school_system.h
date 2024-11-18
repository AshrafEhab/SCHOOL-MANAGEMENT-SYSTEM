#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "STD_Types.h"

typedef struct node
{
	student_t student;
	struct node* node_link;

}node_t;

void MAIN_MENU		(void);
void NEW_STUDENT    (node_t** list_head);
void STUDENT_LIST   (node_t** list_head);
void STUDENT_SCORE  (node_t** node);
void RANK_STUDENT	(node_t** list_head);
void DELETE_STUDENT (node_t** list_head, uint32_t position);
void STUDENT_EDIT	(node_t** list_head, uint32_t position); 	
#endif




