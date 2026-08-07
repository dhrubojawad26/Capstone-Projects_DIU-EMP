#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <openssl/md5.h>

#define MAX 100
#define WORKING_DAYS 30
#define ROLE_COUNT 16

extern const char *roles[ROLE_COUNT];
extern float roleSalaries[ROLE_COUNT];

struct Employee
{
    int id;
    char name[MAX];
    char role[MAX];
    char phone[MAX];
    float baseSalary;
};


void refreshScreen();
void pauseAndRefresh();


void printRoleMenu();
void getRoleChoice(char role[], float *salary);
int getRoleCategory(const char *role);


int findEmployeeById(int id, struct Employee *out);
int employeeExists(int id);
int getBaseSalary(int empId, float *baseSalary);
void addEmployee();
void updateEmployee();
void deleteEmployee();
void searchEmployeeById(int id);
void searchEmployee();
void viewEmployees();
void viewEmployeesByRole();

void recordAttendance();
void viewAttendanceById(int id);
void viewAttendance();
void updateAttendance();


float computeSalaryForMonth(int empId, int month, int year);
void calculateSalaryMenu();
void generatePayroll();
void viewPayrollById(int id);
void viewPayrollInfo();


int authenticate(int *outId, char outRole[]);
void hrMenu();
void managerMenu(void);
void employeeMenu(int selfId);
void financeMenu(int selfId);
void loginPortal(void);
int checkPortalPassword();

#endif
