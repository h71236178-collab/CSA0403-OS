
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, seek_time = 0;
    int disk_size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of requests!\n");
        return 1;
    }

    int request_queue[n];

    printf("Enter the disk request queue:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the disk size (number of cylinders): ");
    scanf("%d", &disk_size);

    if (disk_size <= 0 || head < 0 || head >= disk_size)
    {
        printf("Invalid disk size or head position!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (request_queue[i] < 0 ||
            request_queue[i] >= disk_size)
        {
            printf("Invalid request position!\n");
            return 1;
        }
    }

    // Sort the request queue
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (request_queue[i] > request_queue[j])
            {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    int i = 0;

    // Find the first request at or above the head
    while (i < n && request_queue[i] < head)
        i++;

    // Move toward the higher cylinders
    for (int j = i; j < n; j++)
    {
        seek_time += abs(head - request_queue[j]);
        head = request_queue[j];
        printf(" -> %d", head);
    }

    // Wrap around to cylinder 0
    if (i > 0)
    {
        if (head != disk_size - 1)
        {
            seek_time += abs((disk_size - 1) - head);
            head = disk_size - 1;
            printf(" -> %d", head);
        }

        seek_time += disk_size - 1;
        head = 0;
        printf(" -> %d", head);

        // Service remaining requests
        for (int j = 0; j < i; j++)
        {
            seek_time += abs(head - request_queue[j]);
            head = request_queue[j];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n",
           (float)seek_time / n);

    return 0;
}
