#include<stdio.h>
#include<stdlib.h>
#include "payroll.h"

int main() {
    int choice;

    while (1) {
        printf("1. Add Employee");
        printf("\n2. Calculate Payroll");
        printf("\n3. Generate Payslip");
        printf("\n4. Monthly Report");
        printf("\n5. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee(); break;
            case 2: calculate_payroll(); break;
            case 3: generate_slip(); break;
            case 4: monthly_report(); break;
            case 5: exit(0);
            default: printf("\nInvalid choice!\n\n");
        }
    }
    return 0;
}
