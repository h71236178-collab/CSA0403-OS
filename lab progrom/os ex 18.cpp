
#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE] = {0};
int produced_items = 0;
int consumed_items = 0;

HANDLE empty, full;
CRITICAL_SECTION cs;

DWORD WINAPI producer(LPVOID arg) {
    while (1) {
        WaitForSingleObject(empty, INFINITE);

        EnterCriticalSection(&cs);

        if (produced_items >= MAX_ITEMS) {
            LeaveCriticalSection(&cs);
            ReleaseSemaphore(empty, 1, NULL);
            break;
        }

        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                buffer[i] = ++produced_items;
                printf("Produced: %d\n", buffer[i]);
                break;
            }
        }

        LeaveCriticalSection(&cs);

        ReleaseSemaphore(full, 1, NULL);
        Sleep(100);
    }

    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    while (1) {
        WaitForSingleObject(full, INFINITE);

        EnterCriticalSection(&cs);

        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }

        int done = (consumed_items >= MAX_ITEMS);

        LeaveCriticalSection(&cs);

        ReleaseSemaphore(empty, 1, NULL);

        if (done) {
            break;
        }

        Sleep(200);
    }

    return 0;
}

int main(void) {
    HANDLE producer_thread, consumer_thread;

    InitializeCriticalSection(&cs);

    empty = CreateSemaphore(NULL, BUFFER_SIZE,
                            BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    if (empty == NULL || full == NULL) {
        printf("Error creating semaphores.\n");

        if (empty != NULL)
            CloseHandle(empty);

        if (full != NULL)
            CloseHandle(full);

        DeleteCriticalSection(&cs);
        return 1;
    }

    producer_thread = CreateThread(
        NULL, 0, producer, NULL, 0, NULL
    );

    consumer_thread = CreateThread(
        NULL, 0, consumer, NULL, 0, NULL
    );

    if (producer_thread == NULL || consumer_thread == NULL) {
        printf("Error creating threads.\n");

        if (producer_thread != NULL)
            CloseHandle(producer_thread);

        if (consumer_thread != NULL)
            CloseHandle(consumer_thread);

        CloseHandle(empty);
        CloseHandle(full);
        DeleteCriticalSection(&cs);
        return 1;
    }

    WaitForSingleObject(producer_thread, INFINITE);
    WaitForSingleObject(consumer_thread, INFINITE);

    CloseHandle(producer_thread);
    CloseHandle(consumer_thread);
    CloseHandle(empty);
    CloseHandle(full);

    DeleteCriticalSection(&cs);

    printf("\nAll items produced and consumed successfully.\n");

    return 0;
}
