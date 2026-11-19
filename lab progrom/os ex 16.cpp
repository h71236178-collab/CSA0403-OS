
#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;
    int choice, id;

    filePtr = fopen("employee.dat", "rb+");

    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");

        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            fclose(filePtr);
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);

                if (id <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                emp.empId = id;

                printf("Enter Employee Name: ");
                scanf("%49s", emp.empName);

                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(filePtr,
                      (long)(id - 1) * sizeof(struct Employee),
                      SEEK_SET);

                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                fflush(filePtr);

                printf("Employee details added successfully.\n");
                break;

            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &id);

                if (id <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                fseek(filePtr,
                      (long)(id - 1) * sizeof(struct Employee),
                      SEEK_SET);

                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1
                    && emp.empId == id) {
                    printf("\nEmployee Details:\n");
                    printf("Employee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                } else {
                    printf("Employee record not found.\n");
                }
                break;

            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);

                if (id <= 0) {
                    printf("Invalid Employee ID.\n");
                    break;
                }

                fseek(filePtr,
                      (long)(id - 1) * sizeof(struct Employee),
                      SEEK_SET);

                if (fread(&emp, sizeof(struct Employee), 1, filePtr) != 1
                    || emp.empId != id) {
                    printf("Employee record not found.\n");
                    break;
                }

                printf("Enter Employee Name: ");
                scanf("%49s", emp.empName);

                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                emp.empId = id;

                fseek(filePtr,
                      (long)(id - 1) * sizeof(struct Employee),
                      SEEK_SET);

                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                fflush(filePtr);

                printf("Employee details updated successfully.\n");
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    fclose(filePtr);

    return 0;
}
