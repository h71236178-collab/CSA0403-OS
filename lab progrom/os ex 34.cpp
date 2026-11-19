
#include <stdio.h>
#include <stdlib.h>

struct Record
{
    int recordNumber;
    char data[256];
};

int main()
{
    FILE *file;
    struct Record record;
    int recordNumber;
    int found;

    // Open file for writing records
    file = fopen("sequential_file.txt", "wb");

    if (file == NULL)
    {
        perror("Error opening the file");
        return 1;
    }

    printf("Enter records (Enter 0 to exit):\n");

    while (1)
    {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);

        if (record.recordNumber == 0)
            break;

        printf("Data: ");
        scanf(" %255[^\n]", record.data);

        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file);

    // Open file for reading records
    file = fopen("sequential_file.txt", "rb");

    if (file == NULL)
    {
        perror("Error opening the file");
        return 1;
    }

    // Search for a specific record
    while (1)
    {
        printf("\nEnter record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0)
            break;

        rewind(file);
        found = 0;

        while (fread(&record, sizeof(struct Record), 1, file) == 1)
        {
            if (record.recordNumber == recordNumber)
            {
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("Record not found!\n");
    }

    fclose(file);

    return 0;
}
