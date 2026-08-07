<div align="center">
  <h1>Daffodil International University (DIU)</h1>
  <h3>Capstone Project: Daffodil Employee Management System</h3>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="Language">
  <img src="https://img.shields.io/badge/DIU-Capstone--Project-00A859?style=for-the-badge" alt="Institution">
  <img src="https://img.shields.io/badge/Academic-Evaluation-orange?style=for-the-badge" alt="License">
</div>



A console-based Employee / Attendance / Payroll management system for
Daffodil International University, written in C.

Repository: [https://github.com/dhrubojawad26/Capstone-Projects-DIU-EMP](https://github.com/dhrubojawad26/Capstone-Projects_DIU-EMP

## Files

```
project.h        Struct, constants, and function prototypes
project.c        All function implementations + main()
employees.txt    Sample employee records
attendance.txt   Sample attendance records
payroll.txt      Sample payroll records
```
## Team Responsibilities

| Role | Responsibilities | Team Member |
|------|------------------|-------------|
| **HR / Admin & Finance** | Employee CRUD, attendance management, payroll generation, payroll viewing | Zuvin Zawad<br>**ID:** 252-35-052 |
| **Manager** | View all employees, view employees by role, view attendance records, view payroll information | Jannatul Ferdousi Soptorshi<br>**ID:** 252-35-101 |
| **Employee** | View own profile, check attendance history, view own payroll/payslip information | Afia Fahmida Atoshi<br>**ID:** 252-35-276 |

## Features

### HR / Admin & Finance Portal

- Add new employee records
- Update existing employee details
- Delete or deactivate employee records
- Search for employees by ID
- View all employees (grouped by role)
- View employees filtered by specific role
- Record daily attendance
- View attendance records (all or by employee)
- Update attendance records
- Generate payroll for any employee
- View payroll information (all or by employee)
- Role-based login (Username = Employee ID, Password = Phone Number)

### Manager Portal (VC / Dean)

- View all employees with inline search by ID
- View employees filtered by specific role
- View attendance records (all or by employee)
- View payroll information (all or by employee)

### Employee Portal

- View own profile and information
- View own attendance history
- View own payroll and payslip information

## Authentication

- **Master Password:** `1234` (MD5 hashed in source)
- **Portal Login:**
  - **Username:** Employee ID
  - **Password:** Phone Number
- **Role Categories:**
  - **HR / Admin & Finance Portal:** HR Officer, Accountant, CFO, Finance Director
  - **Manager Portal:** Vice Chancellor (VC), Dean
  - **Employee Portal:** All other employee roles
## Requirements

- `gcc` (or any C compiler)
- OpenSSL development headers (used for MD5 password hashing)

On Ubuntu/Debian, install OpenSSL dev headers if you don't have them:

```bash
sudo apt-get update
sudo apt-get install -y libssl-dev
```

## How to run

1. Clone the repository:

```bash
git clone [https://github.com/dhrubojawad26/Capstone-Projects_-DIU-EMP](https://github.com/dhrubojawad26/Capstone-Projects_DIU-EMP.git
cd Capstone-Projects_-DIU-EMP
```

2. Compile the project (must link against `ssl` and `crypto`):

```bash
gcc -o employee_portal project.c -lssl -lcrypto
```

3. Run it:

```bash
./employee_portal
```

The program reads/writes `employees.txt`, `attendance.txt`, and
`payroll.txt` in the current working directory, so run it from the
folder that contains those three files (or copy them in first).

## Master password

The portal is locked behind a master password before showing the
main menu. The default hash in `project.c` corresponds to:

```
1234
```

## Quick rebuild after editing

```bash
gcc -Wall -Wextra -o employee_portal project.c -lssl -lcrypto
```

`-Wall -Wextra` isn't required, just recommended while developing —
it will flag most typos and unused-variable mistakes.
