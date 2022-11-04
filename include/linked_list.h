#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct ListNode ListNode;
typedef struct List List;

struct ListNode {
    char character;
    int frequency;
    double probability;
    ListNode* next_element;
};

struct List {
    ListNode* head;
    int sum_of_frequencies;
};

List* list_new(void);
void list_destroy(List* list);
void list_print(List* list);
ListNode* list_node_new(char content);
void list_node_destroy(ListNode* head);
ListNode* list_node_lookup(ListNode* head, char content);
ListNode* list_node_append(List* list, char content);

#endif