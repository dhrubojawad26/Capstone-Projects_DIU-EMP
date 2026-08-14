#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

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
    300000, 220000, 180000, 150000,
    120000, 90000, 60000, 40000,
    45000, 45000, 25000, 22000,
    18000, 20000, 250000, 200000
};

struct Employee
{
    int id;
    char name[MAX];
    char role[MAX];
    char phone[MAX];
    float baseSalary;
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

    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("\nPress Enter to continue...");
    fflush(stdout);
    getchar();

    refreshScreen();
}

void printRoleMenu(void)
{
    int i;

    printf("\n----- SELECT ROLE -----\n");

    for (i = 0; i < ROLE_COUNT; i++)
        printf("%d. %s (Base Salary: %.2f)\n",
               i + 1, roles[i], roleSalaries[i]);
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
            *out = e;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int employeeExists(int id)
{
    struct Employee e;
    return findEmployeeById(id, &e);
}

int getBaseSalary(int empId, float *baseSalary)
{
    struct Employee e;

    if (findEmployeeById(empId, &e))
    {
        *baseSalary = e.baseSalary;
        return 1;
    }

    return 0;
}


void addEmployee(void)
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
    printf("Username: %d\n", e.id);
    printf("Password: %s (phone number)\n", e.phone);
    printf("Assigned Base Salary: %.2f\n", e.baseSalary);
}

void updateEmployee(void)
{
    FILE *fp, *temp;
    struct Employee e;
    int targetId, found = 0;

    printf("Enter Employee ID to update: ");
    scanf("%d", &targetId);

    fp = fopen("employees.txt", "r");

    if (fp == NULL)
    {
        printf("No employee records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d", &e.id) != EOF)
    {
        fscanf(fp, " %[^\n]", e.name);
        fscanf(fp, " %[^\n]", e.role);
        fscanf(fp, " %[^\n]", e.phone);
        fscanf(fp, "%f", &e.baseSalary);

        if (e.id == targetId)
        {
            found = 1;

            printf("Current Name: %s\n", e.name);
            printf("Enter New Name: ");
            scanf(" %[^\n]", e.name);

            printf("Current Role: %s (Salary: %.2f)\n",
                   e.role, e.baseSalary);
            printf("Update Role? (1 = Yes, 0 = No): ");

            {
                int updateRole;
                scanf("%d", &updateRole);

                if (updateRole == 1)
                    getRoleChoice(e.role, &e.baseSalary);
            }

            printf("Current Phone: %s\n", e.phone);
            printf("Enter New Phone Number: ");
            scanf(" %[^\n]", e.phone);
        }

        fprintf(temp, "%d\n", e.id);
        fprintf(temp, "%s\n", e.name);
        fprintf(temp, "%s\n", e.role);
        fprintf(temp, "%s\n", e.phone);
        fprintf(temp, "%.2f\n", e.baseSalary);
    }

    fclose(fp);
    fclose(temp);

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found)
        printf("Employee updated successfully.\n");
    else
        printf("Employee ID not found.\n");
}

void deleteEmployee(void)
{
    FILE *fp, *temp;
    struct Employee e;
    int targetId, found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &targetId);

    fp = fopen("employees.txt", "r");

    if (fp == NULL)
    {
        printf("No employee records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d", &e.id) != EOF)
    {
        fscanf(fp, " %[^\n]", e.name);
        fscanf(fp, " %[^\n]", e.role);
        fscanf(fp, " %[^\n]", e.phone);
        fscanf(fp, "%f", &e.baseSalary);

        if (e.id == targetId)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d\n", e.id);
            fprintf(temp, "%s\n", e.name);
            fprintf(temp, "%s\n", e.role);
            fprintf(temp, "%s\n", e.phone);
            fprintf(temp, "%.2f\n", e.baseSalary);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found)
        printf("Employee deleted successfully.\n");
    else
        printf("Employee ID not found.\n");
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
    {
        printf("Employee ID not found.\n");
    }
}

void searchEmployee(void)
{
    int id;

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    searchEmployeeById(id);
}

void viewEmployees(void)
{
    FILE *fp;
    struct Employee e;
    int i, found, total = 0;
    int choice, id;

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

    if (choice != 0)
    {
        printf("Invalid choice.\n");
        return;
    }

    printf("\n===== EMPLOYEE LIST =====\n");

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
    int roleChoice, total = 0;

    printRoleMenu();

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

    printf("\n===== EMPLOYEES - %s =====\n",
           roles[roleChoice - 1]);

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

void recordAttendance(void)
{
    FILE *fp;
    int empId, day, month, year;
    char status[MAX];

    printf("Enter Employee ID: ");
    scanf("%d", &empId);

    if (!employeeExists(empId))
    {
        printf("Employee ID not found.\n");
        return;
    }

    printf("Enter Day: ");
    scanf("%d", &day);

    printf("Enter Month: ");
    scanf("%d", &month);

    printf("Enter Year: ");
    scanf("%d", &year);

    printf("Enter Status (Present/Absent): ");
    scanf(" %[^\n]", status);

    fp = fopen("attendance.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening attendance file.\n");
        return;
    }

    fprintf(fp, "%d %d %d %d %s\n",
            empId, day, month, year, status);

    fclose(fp);

    printf("Attendance recorded successfully.\n");
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

    if (!found)
        printf("No matching attendance records found.\n");
}

void viewAttendance(void)
{
    int empId;

    printf("Enter Employee ID (0 for all): ");
    scanf("%d", &empId);

    viewAttendanceById(empId);
}

void updateAttendance(void)
{
    FILE *fp, *temp;
    int empId, day, month, year;
    int targetId, targetDay, targetMonth, targetYear;
    char status[MAX];
    int found = 0;

    printf("Enter Employee ID: ");
    scanf("%d", &targetId);

    printf("Enter Day: ");
    scanf("%d", &targetDay);

    printf("Enter Month: ");
    scanf("%d", &targetMonth);

    printf("Enter Year: ");
    scanf("%d", &targetYear);

    fp = fopen("attendance.txt", "r");

    if (fp == NULL)
    {
        printf("No attendance records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d", &empId) != EOF)
    {
        fscanf(fp, "%d", &day);
        fscanf(fp, "%d", &month);
        fscanf(fp, "%d", &year);
        fscanf(fp, " %[^\n]", status);

        if (empId == targetId &&
            day == targetDay &&
            month == targetMonth &&
            year == targetYear)
        {
            found = 1;

            printf("Current Status: %s\n", status);
            printf("Enter New Status (Present/Absent): ");
            scanf(" %[^\n]", status);
        }

        fprintf(temp, "%d %d %d %d %s\n",
                empId, day, month, year, status);
    }

    fclose(fp);
    fclose(temp);

    remove("attendance.txt");
    rename("temp.txt", "attendance.txt");

    if (found)
        printf("Attendance updated successfully.\n");
    else
        printf("Matching attendance record not found.\n");
}


float computeSalaryForMonth(int empId, int month, int year)
{
    FILE *fp;
    int recEmpId, day, recMonth, recYear;
    char status[MAX];
    float baseSalary = 0;
    int presentDays = 0;
    float perDaySalary, salary;

    if (!getBaseSalary(empId, &baseSalary))
    {
        printf("Employee not found.\n");
        return -1;
    }

    fp = fopen("attendance.txt", "r");

    if (fp == NULL)
    {
        printf("No attendance records found. Salary computed as 0.\n");
        return 0;
    }

    while (fscanf(fp, "%d", &recEmpId) != EOF)
    {
        fscanf(fp, "%d", &day);
        fscanf(fp, "%d", &recMonth);
        fscanf(fp, "%d", &recYear);
        fscanf(fp, " %[^\n]", status);

        if (recEmpId == empId &&
            recMonth == month &&
            recYear == year &&
            strcmp(status, "Present") == 0)
        {
            presentDays++;
        }
    }

    fclose(fp);

    perDaySalary = baseSalary / WORKING_DAYS;
    salary = perDaySalary * presentDays;

    return salary;
}

void calculateSalaryMenu(void)
{
    int empId, month, year;
    float salary;

    printf("Enter Employee ID: ");
    scanf("%d", &empId);

    printf("Enter Month (1-12): ");
    scanf("%d", &month);

    printf("Enter Year: ");
    scanf("%d", &year);

    salary = computeSalaryForMonth(empId, month, year);

    if (salary >= 0)
    {
        printf("Calculated Salary for Employee %d (%d/%d): %.2f\n",
               empId, month, year, salary);
    }
}

void generatePayroll(void)
{
    FILE *fp;
    int empId, month, year;
    float basicSalary, bonus, deduction, netSalary;

    printf("Enter Employee ID: ");
    scanf("%d", &empId);

    if (!employeeExists(empId))
    {
        printf("Employee ID not found.\n");
        return;
    }

    printf("Enter Month (1-12): ");
    scanf("%d", &month);

    printf("Enter Year: ");
    scanf("%d", &year);

    basicSalary = computeSalaryForMonth(empId, month, year);

    if (basicSalary < 0)
        return;

    printf("Enter Bonus Amount: ");
    scanf("%f", &bonus);

    printf("Enter Deduction Amount: ");
    scanf("%f", &deduction);

    netSalary = basicSalary + bonus - deduction;

    fp = fopen("payroll.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening payroll file.\n");
        return;
    }

    fprintf(fp, "%d %d %d %.2f %.2f %.2f %.2f\n",
            empId, month, year,
            basicSalary, bonus, deduction, netSalary);

    fclose(fp);

    printf("Payroll generated successfully.\n");
    printf("Net Salary: %.2f\n", netSalary);
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
            printf("ID: %d | Period: %d/%d | Basic: %.2f | "
                   "Bonus: %.2f | Deduct: %.2f | Net: %.2f\n",
                   empId, month, year, basicSalary,
                   bonus, deduction, netSalary);

            found = 1;
        }
    }

    fclose(fp);

    if (!found)
        printf("No matching payroll records found.\n");
}

void viewPayrollInfo(void)
{
    int empId;

    printf("Enter Employee ID (0 for all): ");
    scanf("%d", &empId);

    viewPayrollById(empId);
}


int isHRRole(const char *role)
{
    return strcmp(role, "HR Officer") == 0;
}

int isFinanceRole(const char *role)
{
    return strcmp(role, "Accountant") == 0 ||
           strcmp(role, "Finance Director") == 0 ||
           strcmp(role, "Chief Financial Officer (CFO)") == 0;
}

int authenticate(int *outId, char outRole[])
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

    if (!isHRRole(e.role) && !isFinanceRole(e.role))
    {
        printf("\nThis portal is only for HR/Admin and Finance users.\n");
        return 0;
    }

    printf("\nLogin successful. Welcome, %s (%s)\n",
           e.name, e.role);

    *outId = e.id;
    strcpy(outRole, e.role);

    return 1;
}

void hrMenu(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n----- HR / ADMIN PORTAL (DIU) -----\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Search Employee\n");
        printf("5. View Employees\n");
        printf("6. View Employees by Role\n");
        printf("7. Record Attendance\n");
        printf("8. View Attendance\n");
        printf("9. Update Attendance\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addEmployee();
                pauseAndRefresh();
                break;

            case 2:
                updateEmployee();
                pauseAndRefresh();
                break;

            case 3:
                deleteEmployee();
                pauseAndRefresh();
                break;

            case 4:
                searchEmployee();
                pauseAndRefresh();
                break;

            case 5:
                viewEmployees();
                pauseAndRefresh();
                break;

            case 6:
                viewEmployeesByRole();
                pauseAndRefresh();
                break;

            case 7:
                recordAttendance();
                pauseAndRefresh();
                break;

            case 8:
                viewAttendance();
                pauseAndRefresh();
                break;

            case 9:
                updateAttendance();
                pauseAndRefresh();
                break;

            case 0:
                printf("Logging out...\n");
                refreshScreen();
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void financeMenu(int selfId)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("\n----- FINANCE PORTAL -----\n");
        printf("1. View My Information\n");
        printf("2. View My Attendance\n");
        printf("3. View My Payroll Information\n");
        printf("4. Search Employee by ID\n");
        printf("5. Calculate Salary\n");
        printf("6. Generate Payroll\n");
        printf("7. View Payroll Information\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                searchEmployeeById(selfId);
                pauseAndRefresh();
                break;

            case 2:
                viewAttendanceById(selfId);
                pauseAndRefresh();
                break;

            case 3:
                viewPayrollById(selfId);
                pauseAndRefresh();
                break;

            case 4:
                searchEmployee();
                pauseAndRefresh();
                break;

            case 5:
                calculateSalaryMenu();
                pauseAndRefresh();
                break;

            case 6:
                generatePayroll();
                pauseAndRefresh();
                break;

            case 7:
                viewPayrollInfo();
                pauseAndRefresh();
                break;

            case 0:
                printf("Logging out...\n");
                refreshScreen();
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void loginPortal(void)
{
    int id;
    char role[MAX];

    if (!authenticate(&id, role))
        return;

    if (isHRRole(role))
        hrMenu();
    else if (isFinanceRole(role))
        financeMenu(id);
}

int checkPortalPassword(void)
{
    char input[100];
    unsigned char digest[MD5_DIGEST_LENGTH];
    char hex[33];
    const char *correctHash =
        "81dc9bdb52d04dc20036dbd8313ed055";
    int i;

    printf("\n----- PORTAL LOCKED -----\n");
    printf("Enter master password to access the system: ");
    scanf("%99s", input);

    MD5((unsigned char *)input, strlen(input), digest);

    for (i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(hex + i * 2, "%02x", digest[i]);

    hex[32] = '\0';

    if (strcmp(hex, correctHash) == 0)
        return 1;

    printf("Incorrect password. Access denied.\n");
    return 0;
}

int main(void)
{
    int choice = -1;

    if (!checkPortalPassword())
        return 1;

    refreshScreen();

    while (choice != 0)
    {
        printf("\n===== DAFFODIL INTERNATIONAL UNIVERSITY =====\n");
        printf("=====       HR / ADMIN & FINANCE       =====\n");
        printf("1. Login\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                loginPortal();
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
