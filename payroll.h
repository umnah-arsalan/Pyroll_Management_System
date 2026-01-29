#ifndef PAYROLL_H
#define PAYROLL_H

#define EMP_FILE "employee.dat"
#define PAY_FILE "payroll.dat"
#define SLIP_FILE "payslip.txt"

struct Employee {
    int id;
    char name[30];
    float basicpay;
};

struct Payroll {
    int id;
    float basic;
    float allowance;
    float deduction;
    float netsalary;
    char month[10];
    int year;
};

int id_check(int id);
void add_employee(void);
void calculate_payroll(void);
void generate_slip(void);
void monthly_report(void);

#endif