#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct path_node {
    char *directory;
    struct path_node *next;
} path_node_t;

path_node_t *build_path_list() {
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        return NULL;
    }

    path_node_t *head = NULL;
    path_node_t *current = NULL;
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        path_node_t *new_node = malloc(sizeof(path_node_t));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            // Clean up previously allocated nodes
            while (head != NULL) {
                path_node_t *temp = head;
                head = head->next;
                free(temp->directory);
                free(temp);
            }
            free(path_copy);
            return NULL;
        }

        new_node->directory = strdup(dir);
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return head;
}

// Function to free the linked list
void free_path_list(path_node_t *head) {
    while (head != NULL) {
        path_node_t *temp = head;
        head = head->next;
        free(temp->directory);
        free(temp);
    }
}

// Function to print the linked list (for testing)
void print_path_list(path_node_t *head) {
    path_node_t *current = head;
    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }
}

