
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, seek_time = 0;

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

    // SCAN Disk Scheduling
    printf("\nSCAN (Elevator) Disk Scheduling:\n");
    printf("Enter initial direction (1 = right, -1 = left): ");

    int current_direction;
    scanf("%d", &current_direction);

    if (current_direction != 1 && current_direction != -1)
    {
        printf("Invalid direction!\n");
        return 1;
    }

    printf("Head Movement Sequence: %d", head);

    if (current_direction == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (request_queue[i] >= head)
            {
                seek_time += abs(head - request_queue[i]);
                head = request_queue[i];
                printf(" -> %d", head);
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            if (request_queue[i] < head)
            {
                seek_time += abs(head - request_queue[i]);
                head = request_queue[i];
                printf(" -> %d", head);
            }
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i--)
        {
            if (request_queue[i] <= head)
            {
                seek_time += abs(head - request_queue[i]);
                head = request_queue[i];
                printf(" -> %d", head);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (request_queue[i] > head)
            {
                seek_time += abs(head - request_queue[i]);
                head = request_queue[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n",
           (float)seek_time / n);

    return 0;
}
