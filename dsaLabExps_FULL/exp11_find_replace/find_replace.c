#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find and replace all occurrences of a substring
char* findAndReplace(const char* source, const char* find, const char* replace) {
    char* result;
    int i, count = 0;
    int find_len = strlen(find);
    int replace_len = strlen(replace);

    // Count occurrences of 'find' to determine new string size
    for (i = 0; source[i] != '\0'; i++) {
        if (strstr(&source[i], find) == &source[i]) {
            count++;
            i += find_len - 1;
        }
    }

    // Allocate memory for result string
    result = (char*)malloc(i + count * (replace_len - find_len) + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (*source) {
        // Compare the substring with the find string
        if (strstr(source, find) == source) {
            strcpy(&result[i], replace);
            i += replace_len;
            source += find_len;
        } else {
            result[i++] = *source++;
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    char text[] = "This is a test string. This string is for testing.";
    char* find_str = "string";
    char* replace_str = "text";

    printf("Original text: %s\n", text);
    printf("Find: %s, Replace: %s\n", find_str, replace_str);

    char* new_text = findAndReplace(text, find_str, replace_str);
    printf("Modified text: %s\n", new_text);

    free(new_text); // Free dynamically allocated memory

    char text2[] = "aaaaa";
    char* find_str2 = "aa";
    char* replace_str2 = "b";
    printf("\nOriginal text: %s\n", text2);
    printf("Find: %s, Replace: %s\n", find_str2, replace_str2);
    char* new_text2 = findAndReplace(text2, find_str2, replace_str2);
    printf("Modified text: %s\n", new_text2);
    free(new_text2);

    return 0;
}
