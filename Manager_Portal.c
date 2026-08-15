#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define ROLE_COUNT 16

struct Employee
{
    int id;
    char name[MAX];
    char role[MAX];
    char phone[MAX];
    float baseSalary;
};

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

void refreshScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseAndRefresh(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("\nPress Enter to continue...");
    fflush(stdout);
    getchar();

    refreshScreen();
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

void viewEmployees(void)
{
    FILE *fp;
    struct Employee e;
    int i, found;
    int total = 0;
    int choice = -1;
    int id;

    printf("\n----- VIEW EMPLOYEES -----\n");
    printf("0. View All Employees\n");
    printf("1. Search by Employee ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Employee ID to search: ");
        scanf("%d", &id);
        searchEmployeeById(id);
        return;
    }
    else if (choice != 0)
    {
        printf("Invalid choice.\n");
        return;
    }

    printf("\n===== EMPLOYEE LIST (DAFFODIL INTERNATIONAL UNIVERSITY) =====\n");

    for (i = 0; i < ROLE_COUNT; i++)
    {
        fp = fopen("employees.txt", "r");

        if (fp == NULL)
        {
            printf("No employee records found.\n");
            return;
        }

        found = 0;

        while (fscanf(fp, "%d", &e.id) != EOF)
        {
            fscanf(fp, " %[^\n]", e.name);
            fscanf(fp, " %[^\n]", e.role);
            fscanf(fp, " %[^\n]", e.phone);
            fscanf(fp, "%f", &e.baseSalary);

            if (strcmp(e.role, roles[i]) == 0)
            {
                if (found == 0)
                {
                    printf("\n====================================\n");
                    printf("Role: %s\n", roles[i]);
                    printf("====================================\n");
                    found = 1;
                }

                printf("ID: %d\n", e.id);
                printf("Name: %s\n", e.name);
                printf("Phone: %s\n", e.phone);
                printf("Salary: %.2f\n\n", e.baseSalary);

                total++;
            }
        }

        fclose(fp);
    }

    if (total == 0)
        printf("No employee records found.\n");
}

void viewEmployeesByRole(void)
{
    FILE *fp;
    struct Employee e;
    int roleChoice;
    int total = 0;
    int i;

    printf("\n----- SELECT ROLE -----\n");

    for (i = 0; i < ROLE_COUNT; i++)
        printf("%d. %s\n", i + 1, roles[i]);

    printf("Enter role number to filter by: ");
    scanf("%d", &roleChoice);

    while (roleChoice < 1 || roleChoice > ROLE_COUNT)
    {
        printf("Invalid role number. Try again: ");
        scanf("%d", &roleChoice);
    }

    fp = fopen("employees.txt", "r");

    if (fp == NULL)
    {
        printf("No employee records found.\n");
        return;
    }

    printf("\n===== EMPLOYEES - %s =====\n", roles[roleChoice - 1]);

    while (fscanf(fp, "%d", &e.id) != EOF)
    {
        fscanf(fp, " %[^\n]", e.name);
        fscanf(fp, " %[^\n]", e.role);
        fscanf(fp, " %[^\n]", e.phone);
        fscanf(fp, "%f", &e.baseSalary);

        if (strcmp(e.role, roles[roleChoice - 1]) == 0)
        {
            printf("ID: %d\n", e.id);
            printf("Name: %s\n", e.name);
            printf("Phone: %s\n", e.phone);
            printf("Salary: %.2f\n\n", e.baseSalary);
            total++;
        }
    }

    fclose(fp);

    if (total == 0)
        printf("No employees found for this role.\n");
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
            printf("ID: %d | Date: %d/%d/%d | Status: %s\n",
                   empId, day, month, year, status);
            found = 1;
        }
    }

    fclose(fp);

    if (found == 0)
        printf("No matching attendance records found.\n");
}

void viewAttendance(void)
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

void viewPayrollInfo(void)
{
    int empId;

    printf("Enter Employee ID (0 for all): ");
    scanf("%d", &empId);

    viewPayrollById(empId);
}

int authenticateManager(int *outId, char outRole[])
{
    int id;
    char password[MAX];
    struct Employee e;

    printf("Enter Employee ID (Username): ");
    scanf("%d", &id);

    printf("Enter Password: ");
    scanf(" %[^\n]", password);

    if (!findEmployeeById(id, &e))
    {
        printf("Employee ID not found.\n");
        return 0;
    }

    if (strcmp(password, e.phone) != 0)
    {
        printf("Incorrect password.\n");
        return 0;
    }

    if (strcmp(e.role, "Vice Chancellor (VC)") != 0 &&
        strcmp(e.role, "Dean") != 0)
    {
        printf("Access denied. Manager Portal is only for VC / Dean.\n");
        return 0;
    }

    printf("\nLogin successful. Welcome, %s (%s)\n", e.name, e.role);

    *outId = e.id;
    strcpy(outRole, e.role);

    return 1;
}

void managerMenu(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n----- MANAGER PORTAL (VC / DEAN) -----\n");
        printf("1. View Employees\n");
        printf("2. View Employees by Role\n");
        printf("3. View Attendance\n");
        printf("4. View Payroll Information\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewEmployees();
                pauseAndRefresh();
                break;

            case 2:
                viewEmployeesByRole();
                pauseAndRefresh();
                break;

            case 3:
                viewAttendance();
                pauseAndRefresh();
                break;

            case 4:
                viewPayrollInfo();
                pauseAndRefresh();
                break;

            case 0:
                printf("Logging out...\n");
                refreshScreen();
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}

int main(void)
{
    int id;
    char role[MAX];

    refreshScreen();

    printf("===== DAFFODIL INTERNATIONAL UNIVERSITY =====\n");
    printf("=====        MANAGER PORTAL LOGIN        =====\n\n");

    if (authenticateManager(&id, role))
    {
        managerMenu();
    }

    return 0;
}
