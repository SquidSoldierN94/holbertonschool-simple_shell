#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *str, const char *delim, int *count) {
    char **result = NULL;
    char *token;
    int i = 0;

    // First call to strtok
    token = strtok(str, delim);

    while (token != NULL) {
        result = realloc(result, sizeof(char *) * (i + 1));
        result[i] = strdup(token);
        i++;
        
        // Subsequent calls to strtok
        token = strtok(NULL, delim);
    }

    *count = i;
    return result;
}

// Function to free the allocated memory
void free_words(char **words, int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

// Example usage
int main() {
    char str[] = "This is a sample string";
    int count;
    char **words = split_string(str, " ", &count);

    printf("Words in the string:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return 0;
}

