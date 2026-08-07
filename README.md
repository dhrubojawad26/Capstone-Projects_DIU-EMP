# DIU Employee Management System (Capstone Project)

A console-based Employee / Attendance / Payroll management system for
Daffodil International University, written in C.

Repository: https://github.com/dhrubojawad26/Capstone-Projects_-DIU-EMP

## Files

```
project.h        Struct, constants, and function prototypes
project.c        All function implementations + main()
employees.txt    Sample employee records
attendance.txt   Sample attendance records
payroll.txt      Sample payroll records
```

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
git clone https://github.com/dhrubojawad26/Capstone-Projects_-DIU-EMP.git
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
