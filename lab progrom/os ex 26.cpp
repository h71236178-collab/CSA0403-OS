#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char buffer[100];

    file = fopen("example.txt", "w");

    if (file == NULL)
    {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a C file management example.\n");

    fclose(file);

    file = fopen("example.txt", "r");

    if (file == NULL)
    {
        perror("Error opening file for reading");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}