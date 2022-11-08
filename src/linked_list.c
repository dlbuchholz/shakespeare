#include <linked_list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* list_new() {
    List* list = malloc(sizeof(List));
    list->sum_of_frequencies = 0;
    list->head = NULL;

    return list;
}

void list_destroy(List* list) {
    list_node_destroy(list->head);
    free(list);
}

void list_print(List* list) {
    ListNode* node = list->head;

    while (node != NULL) {
        printf("{%c: frequency: %d, probability: %f}", node->character,
               node->frequency,
               node->probability);
        node = node->next_element;
    }
}

ListNode* list_node_new(char character) {
    ListNode* new_node = malloc(sizeof(ListNode));
    new_node->character = character;
    new_node->frequency = 1;
    new_node->probability = 0;
    new_node->next_element = NULL;
    return new_node;
}

void list_node_destroy(ListNode* head) {
    if(head) {
        list_node_destroy(head->next_element);
        free(head);
    }
}

ListNode* list_node_lookup(ListNode* head, char character) {
    if(head) {
        if(head->character == character)
            return head;
        else {
            if(head->next_element)
                return list_node_lookup(head->next_element, character);
        }
    }
    return NULL;
}

/* Insert a new node at the end of the list, if a node with a specific character
 * doesn't already exist. */
ListNode* list_node_append(List* list, char character) {
    list->sum_of_frequencies++;
    if(!list->head) {
        list->head = list_node_new(character);
        return list->head;
    }

    ListNode* current = list_node_lookup(list->head, character);

    if(current == NULL) {
        current = list->head;
        while(current->next_element != NULL)
            current = current->next_element;

        current->next_element = list_node_new(character);
        return current->next_element;
    } else {
        current->frequency++;
        return current;
    }
}