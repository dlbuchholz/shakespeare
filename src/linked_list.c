////////////////////////////////////////////////////////////////////////////////
// linked_list.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation einer verketteten Liste,    //
// welche Namen enthält.                                                      //
//                                                                            //
// Erstellt am: 19.10.2022                                                    //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    char* content;
    Node* next_element;
};

struct List {
    Node* nodes;
    size_t length;
    long head;
    long tail;
} typedef List;

List* new_list(long list_size) {
    List* list = (List *) malloc(sizeof(List));
    // Reserves memory for the whole array of nodes
    // Note: Calloc initializes all memory after allocating it
    list->nodes = (Node *) calloc (list_size, sizeof(Node));
    list->length = list_size;
    list->head = 0;
    list->tail = 0;

    return list;
}

void destroy_list(List* list) {
    free(list);
    free(list->nodes);
}

void debug_print(List* list) {
    for(int i = list->head; i < list->length; i++) {
        printf("%d", i);
        printf("%s -> *%s\n", list->nodes[i].content, list->nodes[i].next_element);
    }
}

void print_list(List* list) {
    Node* node = &list->nodes[list->head];

    while (node != NULL) {
        printf("[%s] -> *%s\n", node->content, node->next_element->content);
        node = node->next_element;
    }
}

// To insert a new node, the list has to be cut at the position
// and spliced back together again.
void insert_node(List* list, Node node, long index) {

    // Iterate the list backwords and all push elements (starting from the
    // position at `index`) one step forward
    for (int i = list->length - 1; i > index; i--)
        list->nodes[i] = list->nodes[i-1];

    // After the position has been freed, insert the new element
    list->nodes[index] = node;

    // Update pointer to next item in list after node has been inserted
    list->nodes[index].next_element = &list->nodes[index+1];

    // Update pointer of every item after the inserted item
    for(int i = index + 1; i < list->length - 1; i++) {
        if (list->nodes[i].next_element != NULL)
            list->nodes[i].next_element = &list->nodes[i+1];
    }
}

// Insert a new node at the end of the list
Node* append_node(List* list, char* name) {
    Node new_node;
    new_node.content = name;
    new_node.next_element = NULL;

    int index = list->tail;
    list->nodes[index] = new_node;
    list->nodes[index].next_element = &list->nodes[index+1];
    
    list->tail++;
    return &list->nodes[index];
}
/*
int main(int argc, char **argv) {
    List* list = new_list(21);
    
    append_node(list, "Test");
    append_node(list, "Hans");
    append_node(list, "Dennis");
    append_node(list, "Angela");

    Node new_node;
    new_node.content = "Dieter";
    insert_node(list, new_node, 1);
    append_node(list, "Werner");

    print_list(list);
    destroy_list(list);
    return 0;
}*/