#include <stdio.h>
#include <string.h>

#define MAX 100
#define WORKING_DAYS 30
#define ROLE_COUNT 16
const char *roles[ROLE_COUNT] = {
    "Vice Chancellor (VC)",
    "Dean",
    "Head of Department (HOD)",
    "Professor",
    "Associate Professor",
    "Assistant Professor",
    "Lecturer",
    "Administrative Officer",
    "Accountant",
    "HR Officer",
    "Office Assistant",
    "Security Officer",
    "Cleaner",
    "Driver",
    "Chief Financial Officer (CFO)",
    "Finance Director"
};

float roleSalaries[ROLE_COUNT] = {
    300000,             /* Vice Chancellor (VC) */
    220000,             /* Dean */
    180000,             /* Head of Department (HOD) */
    150000,             /* Professor */
    120000,             /* Associate Professor */
    90000,              /* Assistant Professor */
    60000,              /* Lecturer */
    40000,              /* Administrative Officer */
    45000,              /* Accountant */
    45000,              /* HR Officer */
    25000,              /* Office Assistant */
    22000,              /* Security Officer */
    18000,              /* Cleaner */
    20000,              /* Driver */
    250000,             /* Chief Financial Officer (CFO) */
    200000              /* Finance Director */
};

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

void printRoleMenu()
{
    int i;

    printf("\n----- SELECT ROLE -----\n");
    for (i = 0; i < ROLE_COUNT; i++)
        printf("%d. %s (Base Salary: %.2f)\n", i + 1, roles[i], roleSalaries[i]);
}

void getRoleChoice(char role[], float *salary)
{
    int choice = -1;

    printRoleMenu();
    printf("Enter role number: ");
    scanf("%d", &choice);

    while (choice < 1 || choice > ROLE_COUNT)
    {
        printf("Invalid role number. Try again: ");
        scanf("%d", &choice);
    }

    strcpy(role, roles[choice - 1]);
    *salary = roleSalaries[choice - 1];
}

int findEmployeeById(int id, struct Employee *out)
{
    FILE *fp;
    struct Employee e;
    int found = 0;

    fp = fopen("employees.txt", "r");
    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d", &e.id) != EOF)
    {
        fscanf(fp, " %[^\n]", e.name);
        fscanf(fp, " %[^\n]", e.role);
        fscanf(fp, " %[^\n]", e.phone);
        fscanf(fp, "%f", &e.baseSalary);

        if (e.id == id)
        {
            found = 1;
            *out = e;
            break;
        }
    }

    fclose(fp);
    return found;
}

int employeeExists(int id)
{
    struct Employee e;
    return findEmployeeById(id, &e);
}

void addEmployee()
{
    FILE *fp;
    struct Employee e;

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);

    if (employeeExists(e.id))
    {
        printf("Employee ID already exists.\n");
        return;
    }

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", e.name);

    getRoleChoice(e.role, &e.baseSalary);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", e.phone);

    fp = fopen("employees.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening employee file.\n");
        return;
    }

    fprintf(fp, "%d\n", e.id);
    fprintf(fp, "%s\n", e.name);
    fprintf(fp, "%s\n", e.role);
    fprintf(fp, "%s\n", e.phone);
    fprintf(fp, "%.2f\n", e.baseSalary);

    fclose(fp);

    printf("\nEmployee registered successfully.\n");
    printf("Username (Portal Login): %d\n", e.id);
    printf("Password (Portal Login): %s (their phone number)\n", e.phone);
    printf("Assigned Base Salary: %.2f\n", e.baseSalary);
}



void searchEmployeeById(int id)
{
    struct Employee e;

    if (findEmployeeById(id, &e))
    {
        printf("\nEmployee ID: %d\n", e.id);
        printf("Name: %s\n", e.name);
        printf("Role: %s\n", e.role);
        printf("Phone: %s\n", e.phone);
        printf("Base Salary: %.2f\n", e.baseSalary);
    }
    else
        printf("Employee ID not found.\n");
}

void searchEmployee()
{
    int id;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    searchEmployeeById(id);
}



void viewAttendanceById(int id)
{
    FILE *fp;
    int empId, day, month, year;
    char status[MAX];
    int found = 0;

    fp = fopen("attendance.txt", "r");
    if (fp == NULL)
    {
        printf("No attendance records found.\n");
        return;
    }

    printf("\n===== ATTENDANCE RECORDS =====\n");

    while (fscanf(fp, "%d", &empId) != EOF)
    {
        fscanf(fp, "%d", &day);
        fscanf(fp, "%d", &month);
        fscanf(fp, "%d", &year);
        fscanf(fp, " %[^\n]", status);

        if (id == 0 || empId == id)
        {
            printf("ID: %d | Date: %d/%d/%d | Status: %s\n", empId, day, month, year, status);
            found = 1;
        }
    }

    fclose(fp);

    if (found == 0)
        printf("No matching attendance records found.\n");
}

void viewAttendance()
{
    int empId;

    printf("Enter Employee ID (0 for all): ");
    scanf("%d", &empId);

    viewAttendanceById(empId);
}


void viewPayrollById(int id)
{
    FILE *fp;
    int empId, month, year;
    float basicSalary, bonus, deduction, netSalary;
    int found = 0;

    fp = fopen("payroll.txt", "r");
    if (fp == NULL)
    {
        printf("No payroll records found.\n");
        return;
    }

    printf("\n===== PAYROLL RECORDS =====\n");

    while (fscanf(fp, "%d", &empId) != EOF)
    {
        fscanf(fp, "%d", &month);
        fscanf(fp, "%d", &year);
        fscanf(fp, "%f", &basicSalary);
        fscanf(fp, "%f", &bonus);
        fscanf(fp, "%f", &deduction);
        fscanf(fp, "%f", &netSalary);

        if (id == 0 || empId == id)
        {
            printf("ID: %d | Period: %d/%d | Basic: %.2f | Bonus: %.2f | Deduct: %.2f | Net: %.2f\n",
                   empId, month, year, basicSalary, bonus, deduction, netSalary);
            found = 1;
        }
    }

    fclose(fp);

    if (found == 0)
        printf("No matching payroll records found.\n");
}

void viewPayrollInfo()
{
    int empId;

    printf("Enter Employee ID (0 for all): ");
    scanf("%d", &empId);

    viewPayrollById(empId);
}

void employeeMenu()
{
    int choice = -1;
    int Id;

    printf("\nEnter your Employee ID: ");
    scanf("%d", &Id);

    while (choice != 0)
    {
        printf("\n----- EMPLOYEE PORTAL -----\n");
        printf("1. View My Information\n");
        printf("2. View My Attendance\n");
        printf("3. View My Payroll Information\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                searchEmployeeById(Id);
                break;

            case 2:
                viewAttendanceById(Id);
                break;

            case 3:
                viewPayrollById(Id);
                break;

            case 0:
                printf("Exiting Employee Portal...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main()
{
    int roleChoice = -1;

    while(roleChoice != 0)
    {
        printf("\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Employee\n");
        printf("2. Employee\n");
        printf("0. Exit\n");
        printf("Select your role: ");

        scanf("%d", &roleChoice);

        switch(roleChoice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                
                employeeMenu();
                break;

            case 0:
                printf("Exiting system. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}