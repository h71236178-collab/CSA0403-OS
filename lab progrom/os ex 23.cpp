
#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

// Function to initialize memory
void initializeMemory(void) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1;
    }
}

// Function to display memory status
void displayMemory(void) {
    int i = 0;
    int count = 0;

    printf("\nMemory Status:\n");

    while (i < MAX_MEMORY) {
        if (memory[i] == -1) {
            int start = i;

            while (i < MAX_MEMORY && memory[i] == -1) {
                count++;
                i++;
            }

            printf("Free memory block %d-%d\n", start, i - 1);
        } else {
            i++;
        }
    }

    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using First-Fit
void allocateMemory(int processId, int size) {
    int start = -1;
    int blockSize = 0;

    if (size <= 0 || size > MAX_MEMORY) {
        printf("Invalid memory size.\n");
        return;
    }

    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (blockSize == 0) {
                start = i;
            }

            blockSize++;

            if (blockSize >= size) {
                break;
            }
        } else {
            blockSize = 0;
        }
    }

    if (blockSize >= size) {
        for (int i = start; i < start + size; i++) {
            memory[i] = processId;
        }

        printf("Allocated memory block %d-%d to Process %d\n",
               start, start + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed "
               "(not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    int found = 0;

    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            found = 1;
        }
    }

    if (found) {
        printf("Memory released by Process %d\n", processId);
    } else {
        printf("Process %d not found in memory.\n", processId);
    }
}

// Main function
int main(void) {
    initializeMemory();

    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}
