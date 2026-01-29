#include<stdio.h>
#include<string.h>
#include "payroll.h"

int id_check(int id) {
    struct Employee e;
    FILE *fp = fopen(EMP_FILE, "rb");
    if (!fp)
        return 0;

    while (fread(&e, sizeof(e), 1, fp)) {
        if (id == e.id) {
            printf("\nProduct already exists!\n\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void add_employee() {
    FILE *fp = fopen(EMP_FILE, "ab");
    struct Employee e;

    printf("\nEmployee ID: ");
    scanf("%d", &e.id);

    printf("Employee Name: ");
    scanf(" %[^\n]", e.name);

    printf("Basic Salary: ");
    scanf("%f", &e.basicpay);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("\nEmployee added successfully!\n\n");
}

void calculate_payroll() {
    FILE *fp = fopen(PAY_FILE, "ab");
    FILE *fpe = fopen(EMP_FILE, "rb");
    struct Payroll p;
    struct Employee e;

    if (!fpe) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter month: ");
    scanf("%s", p.month);

    printf("Enter year: ");
    scanf("%d", &p.year);

    while (fread(&e, sizeof(e), 1, fpe)) {
        p.id = e.id;
        p.basic = e.basicpay;

        p.allowance = p.basic * 0.20;
        p.deduction = p.basic * 0.10;

        p.netsalary = p.basic + p.allowance - p.deduction;

        fwrite(&p, sizeof(p), 1, fp);
    }
    fclose(fp);
    fclose(fpe);

    printf("\nPayroll calculated for %s %d!\n\n", p.month, p.year);
}

void generate_slip() {
    FILE *fp = fopen(PAY_FILE, "rb");
    FILE *fpe = fopen(EMP_FILE, "rb");
    FILE *fpp = fopen(SLIP_FILE, "w");

    struct Payroll p;
    struct Employee e;
    int id;

    if (!fp || !fpe) {
        printf("\nFile doesn't exist!\n\n");
        return;
    }

    printf("\nEnter employee ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {

            rewind(fpe);
            while (fread(&e, sizeof(e), 1, fpe)) {
                if (e.id == id)
                    break;
            }

            fprintf(fpp, "====== PAYSLIP ======\n");
            fprintf(fpp, "Employee ID: %d\n", e.id);
            fprintf(fpp, "Name: %s\n", e.name);
            fprintf(fpp, "Month: %s %d\n\n", p.month, p.year);

            fprintf(fpp, "Basic Salary: %.2f\n", p.basic);
            fprintf(fpp, "Allowance: %.2f\n", p.allowance);
            fprintf(fpp, "Deduction: %.2f\n", p.deduction);
            fprintf(fpp, "----------------------\n");
            fprintf(fpp, "Net Salary: %.2f\n", p.netsalary);

            break;
        }
    }

    fclose(fp);
    fclose(fpe);
    fclose(fpp);

    printf("\nPayroll generated! File: %s\n\n", SLIP_FILE);
}

void monthly_report() {
    FILE *fp = fopen(PAY_FILE, "rb");
    struct Payroll p;
    float total = 0.0;
    char month[10];
    int year;

    if (!fp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter month: ");
    scanf("%s", month);

    printf("Enter year: ");
    scanf("%d", &year);

    printf("\nPayroll Report – %s %d\n", month, year);
    printf("---------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        if (strcmp(p.month, month) == 0 && p.year == year) {
            printf("Employee ID: %d  Net salary: %.2f\n", p.id, p.netsalary);
            total += p.netsalary;
        }
    }

    printf("\n---------------------------------\n");
    printf("Total Payout: %.2f\n\n", total);

    fclose(fp);
}