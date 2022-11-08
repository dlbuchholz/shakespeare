#include <markov/model.h>
#include <utest.h>

UTEST(markov_model, shift_string) {
    char test_string[6] = "Hello";

    shift_string(&test_string, 6);
    ASSERT_STREQ(test_string, "ello");
}

UTEST(markov_probability, calculate_probabilities) {
    Node* root = new_node("", 0);
    List* list = list_new();

    root->list_char = list;

    list_node_append(list, 'a');
    list_node_append(list, 'a');
    list_node_append(list, 'b');

    calculate_probabilities(root);

    ASSERT_NEAR(root->list_char->head->probability, 0.666, 0.001f);
    ASSERT_NEAR(root->list_char->head->next_element->probability, 0.333, 0.001f);

    node_destroy(root);
}

UTEST(linked_list, list_node_append) {
    List* list = list_new();

    list_node_append(list, 'x');
    ASSERT_NE(list->head, NULL);
    ASSERT_EQ(list->head->character, 'x');
    ASSERT_EQ(list->head->frequency, 1);
    ASSERT_EQ(list->sum_of_frequencies, 1);

    /* Duplicates shall not get inserted into the linked list */
    list_node_append(list, 'x');
    ASSERT_EQ(list->head->next_element, NULL);
    ASSERT_EQ(list->head->frequency, 2);
    ASSERT_EQ(list->sum_of_frequencies, 2);

    Node* next = list_node_append(list, 'y');
    ASSERT_EQ(list->head->next_element, next);
    ASSERT_EQ(list->head->next_element->frequency, 1);
    ASSERT_EQ(list->sum_of_frequencies, 3);

    list_destroy(list);
}

UTEST(linked_list, list_node_lookup) {
    List* list = list_new();

    Node* node_a = list_node_append(list, 'a');
    Node* node_f = list_node_append(list, 'f');
    Node* node_z = list_node_append(list, 'z');

    ASSERT_EQ(node_a, list_node_lookup(list->head, 'a'));
    ASSERT_EQ(node_f, list_node_lookup(list->head, 'f'));
    ASSERT_EQ(node_z, list_node_lookup(list->head, 'z'));

    list_destroy(list);
}

UTEST(bst_analysis, lookup) {
    Tree* tree = tree_new();
    Node* a = node_insert(NULL, "Hello", 5, tree);
    node_insert(a, "Friedrich", 9, tree);
    node_insert(a, "Weser", 5, tree);

    Node* x = lookup(a, "Hell", 4);
    Node* y = lookup(a, "Friedric", 8);
    Node* z = lookup(a, "Wese", 4);

    ASSERT_NE(NULL, x);
    ASSERT_NE(NULL, y);
    ASSERT_NE(NULL, z);
    ASSERT_STREQ("Hell", x->content);
    ASSERT_STREQ("Friedric", y->content);
    ASSERT_STREQ("Wese", z->content);

    tree_destroy(tree);
}

UTEST(bst_core, node_insert) {
    Tree* tree = tree_new();

    Node* node = node_insert(NULL, "Hello", 5, tree);
    ASSERT_EQ(node, tree->root);
    ASSERT_EQ(1, tree->node_len);
    ASSERT_STREQ("Hell", tree->root->content);
    ASSERT_EQ('o', tree->root->list_char->head->character);

    node_insert(tree->root, "Hallo", 5, tree);
    ASSERT_NE(NULL, tree->root->left);
    ASSERT_EQ(NULL, tree->root->right);
    ASSERT_STREQ("Hall", tree->root->left->content);

    node_insert(tree->root, "Weser", 5, tree);
    ASSERT_NE(NULL, tree->root->right);
    ASSERT_STREQ("Wese", tree->root->right->content);

    tree_destroy(tree);
}

UTEST_MAIN()
