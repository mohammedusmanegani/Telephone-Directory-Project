/*
 * To implement Telophone Directory Maintenance System using Files (As Relational Database) in C.
 * Date: 08-09-2020
 * Authors:
 *          Mohammed Usman E Gani (2SD18CS059)
 *                  (AND)
 *          S Varun (2SD18CS130)
*/

//Pre-Processor Directives
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

//Function Prototyping
void printLine();
long int findSize(char file_name[]);
char *tail(FILE *, int);
int userAuthentation(char[], char[]);
void mainMenu();
void departmentMaintenanceMenu();
void employeeMaintenanceMenu();
void telephoneMaintenanceMenu();
void addAnEmployee();
void addDepartment();
void addTelephoneNumber();
void printDepartmentDetails();
void printEmployeeDetails();
int returnDepartmentCodeOnDepartmentName(char[]);
int checkForExistenceOfEmpInTelePhoneData(int);
void telephoneEnquiryMenu();
void enquironTelephoneNumber();
void enquiryonEmployeeName();
void printEnquiryonEmployeeName(char[]);
void developerInfo();

/*
 * Structure Name: Employee
 * Structure Members: int, char[]
 * Author: Mohammed Usman E Gani
*/
typedef struct employee
{
    char employeeName[25], departmentName[15], employeeLocation[5];
    int employeeId, departmentCode;
} employee;

/*
 * Structure Name: Department
 * Structure Members: int, char[]
 * Author: Mohammed Usman E Gani
*/
typedef struct department
{
    int departmentCode;
    char departmentName[15];
} department;

/*
 * Structure Name: Telephone
 * Structure Members: int, char[]
 * Author: S Varun
*/
typedef struct telephone
{
    int employeeId, departmentCode, telephoneNumber;
    char location[15], departmentName[15], employeeName[25];
} telephone;

/*
 * This Function Prints Line
 * Author: Mohammed Usman E Gani
*/
void printLine()
{
    for (int i = 0; i < 100; ++i)
    {
        printf("=");
    }
    printf("\n");
}

/*
 * Returns the Last Line Of the File
 * Author: Mohammed Usman E Gani
 * Source: Geeksforgeeks.com
*/
char *tail(FILE *in, int n)
{
    int count = 0; // To count '\n' characters
    // unsigned long long pos (stores upto 2^64 – 1
    // chars) assuming that long long int takes 8
    // bytes
    unsigned long long pos;
    char str[2 * 100];
    char temp[100];
    // Go to End of file
    if (fseek(in, 0, SEEK_END))
        perror("fseek() failed");
    else
    {
        // pos will contain no. of chars in
        // input file.
        pos = ftell(in);
        // search for '\n' characters
        while (pos)
        {
            // Move 'pos' away from end of file.
            if (!fseek(in, --pos, SEEK_SET))
            {
                if (fgetc(in) == '\n')
                    // stop reading when n newlines
                    // is found
                    if (count++ == n)
                        break;
            }
            else
                perror("fseek() failed");
        }
        while (fgets(str, sizeof(str), in))
            return strcpy(temp, str);
    }
}

/*
 * This Function returns the File Size
 * Author: Mohammed Usman E Gani
*/
long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE *fp = fopen(file_name, "r");
    fseek(fp, 0L, SEEK_END);
    // calculating the size of the file
    long int res = ftell(fp);
    // closing the file
    fclose(fp);
    return res;
}

/*
 * This function if For authentation, It allows maximum 3 trails
 * Author: mohammed Usman E Gani
*/
int userAuthentation(char userName[], char password[])
{
    char ch;
    char currentUserName[20];
    char currentPassword[20];
    int i, attempts = 1, userNameCorrect = 1;
    int maxTry = 3;
    while (attempts <= maxTry)
    {
        ch = '\0';
        if (userNameCorrect)
        {
            system("CLS");
            printf("\n User Name : ");
            gets(currentUserName);
        }
        if (strcmp(currentUserName, userName) == 0)
        {
            userNameCorrect = 0;
            system("CLS");
            printf("\n User Name : %s\n", currentUserName);
            printf(" Password  : ");
            i = 0;
            while (ch != 13)
            {
                ch = getch();
                if (ch != 13 && ch != 8)
                {
                    putch('*');
                    currentPassword[i] = ch;
                    i++;
                }
            }
            currentPassword[i] = '\0';
            if (strcmp(currentPassword, password) == 0)
            {
                // Authentication is successfull;
                return 1;
            }
            else
            {
                printf("\n\n Password incorrect ! ");
                getch();
                attempts++;
            }
        }
        else
        {
            attempts++;
            printf("\n User Name incorrect ! ");
            getch();
        }
    }
    return 0;
}

/*
 * Main Menu Function
 * Author: Mohammed Usman E Gani
*/
void mainMenu()
{
    int choice, invalidStatus;
    do
    {
        invalidStatus = 0;
        printLine();
        printf(" Main Menu\n");
        printLine();
        printf("\n 1. Department Maintenance\n 2. Employee Maintenance\n 3. Telephone Directory Maintenance\n 4. Exit\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("CLS");
            departmentMaintenanceMenu();
            break;
        case 2:
            system("CLS");
            employeeMaintenanceMenu();
            break;
        case 3:
            system("CLS");
            telephoneMaintenanceMenu();
            break;
        case 4:
            printf("\n");
            developerInfo();
            exit(0);
        default:
            system("CLS");
            printf("\n Invalid Choice\n\n");
            invalidStatus = 1;
        }
    } while (invalidStatus == 1);
}

/*
 * This Function prints the Department Details
 * Author: S Varun
*/
void printDepartmentDetails()
{
    FILE *f;
    char deptname[15], ch, deptcode[15];
    int linesCount = 0;
    f = fopen("DepartmentData.txt", "r");
    long int res = findSize("DepartmentData.txt");
    if (res == 0)
    {
        system("CLS");
        printf("\n Department List Is Empty. Please Add the Department.\n\n");
        departmentMaintenanceMenu();
    }
    // Counting the number of lines in the file
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(f);
    f = fopen("DepartmentData.txt", "r");
    // printing all the departments
    printf(" -----------------------------------------------");
    printf("\n Department Name\t\t Department Code\n");
    printf(" -----------------------------------------------\n");
    while (!(feof(f)) && linesCount > 0)
    {
        fscanf(f, "%s", deptname);
        strcpy(deptcode, deptname);
        strrev(deptcode);
        strrev(strtok(deptcode, ","));
        printf(" %s \t\t\t\t %s\n", strtok(deptname, ","), deptcode);
        linesCount--;
    }
    printf(" -----------------------------------------------\n");
    fclose(f);
    printf("\n Press Enter To Continue... ");
    getch();
    system("CLS");
    departmentMaintenanceMenu();
}

/*
 * This Function prints the Employee Details
 * Author: Mohammed Usman E Gani
*/
void printEmployeeDetails()
{
    FILE *f;
    f = fopen("employeeData.txt", "r");
    long int res = findSize("employeeData.txt");
    char empData[100], ch;
    int linesCount = 0;
    if (res == 0)
    {
        system("CLS");
        printf("\n Employee List Is Empty. Please Add the Employee.\n\n");
        employeeMaintenanceMenu();
    }
    printf(" ---------------------------------------------------------------------------------------------------------------");
    printf("\n Department \t\t Department Code \t Location \t\t Employee Name \t\t Employee ID\n");
    printf(" ---------------------------------------------------------------------------------------------------------------\n");
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(f);
    f = fopen("employeeData.txt", "r");
    char token1[15], token2[25], token3[25], token4[15];
    while (!(feof(f)) && linesCount > 0)
    {
        fscanf(f, "%s", empData);
        char *token = strtok(empData, ",");
        while (token != NULL)
        {
            printf(" %s\t\t\t", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
        linesCount--;
    }
    printf(" ---------------------------------------------------------------------------------------------------------------\n");
    fclose(f);
    printf("\n Press Enter To Continue... ");
    getch();
    system("CLS");
    employeeMaintenanceMenu();
}

/*
 * Department Maintenance Menu
 * Author: Mohammed Usman E Gani
*/
void departmentMaintenanceMenu()
{
    int choice, invalidStatus;
    do
    {
        invalidStatus = 0;
        printLine();
        printf(" Department Maintenance Menu\n");
        printLine();
        printf("\n 1. Add Department\n 2. Print Department Details\n 3. Goto Main Menu\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("CLS");
            addDepartment();
            break;
        case 2:
            system("CLS");
            printDepartmentDetails();
            break;
        case 3:
            system("CLS");
            mainMenu();
            break;
        default:
            system("CLS");
            printf("\n Invalid Choice\n\n");
            invalidStatus = 1;
        }
    } while (invalidStatus == 1);
}

/*
 * Employee Maintenance Menu
 * Author: Mohammed Usman E Gani
*/
void employeeMaintenanceMenu()
{
    int choice, invalidStatus;
    do
    {
        invalidStatus = 0;
        printLine();
        printf(" Employee Maintenance Menu\n");
        printLine();
        printf("\n 1. Add Employee\n 2. Print Employee Details\n 3. Goto Main Menu\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("CLS");
            addAnEmployee();
            break;
        case 2:
            system("CLS");
            printEmployeeDetails();
            break;
        case 3:
            system("CLS");
            mainMenu();
            break;
        default:
            system("CLS");
            printf("\n Invalid Choice\n\n");
            invalidStatus = 1;
        }
    } while (invalidStatus == 1);
}

/*
 * Telephone Directory Maintenance Menu
 * Author: S. Varun
*/
void telephoneMaintenanceMenu()
{
    int choice, invalidStatus;
    do
    {
        invalidStatus = 0;
        printLine();
        printf(" Telephone Directory Maintenance Menu\n");
        printLine();
        printf("\n 1. Add Telephone Number\n 2. Telephone Enquiry Menu\n 3. Goto Main Menu\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("CLS");
            addTelephoneNumber();
            break;
        case 2:
            system("CLS");
            telephoneEnquiryMenu();
            break;
        case 3:
            system("CLS");
            mainMenu();
            break;
        default:
            system("CLS");
            printf("\n Invalid Choice\n\n");
            invalidStatus = 1;
        }
    } while (invalidStatus == 1);
}

/*
 * Add An Employee Function
 * Author: Mohammed Usman E Gani
*/
void addAnEmployee()
{
    FILE *fp_employeeData = fopen("employeeData.txt", "a");
    FILE *fp_departmentData = fopen("DepartmentData.txt", "r");
    employee emp;
    department dep;
    long int res = findSize("DepartmentData.txt");
    int departmentCode, totrec = 0;
    char foundDepartment[15];
    if (res == 0)
    {
        system("CLS");
        printf("\n----------- No Department Exists ! -----------\n\n");
        departmentMaintenanceMenu();
    }
    printLine();
    printf(" Add an Employee \n");
    printLine();
    printf("\n Enter Employee Name      : ");
    scanf("%s", emp.employeeName);
    res = findSize("employeeData.txt");
    if (res == 0)
    {
        emp.employeeId = 1000;
    }
    else
    {
        char trav[100];
        strcpy(trav, strrev(tail(fopen("employeeData.txt", "r"), 2)));
        char *previousEmployeeId = strtok(trav, ",");
        strcpy(previousEmployeeId, strrev(previousEmployeeId));
        emp.employeeId = atoi(previousEmployeeId) + 1;
        fclose(fp_employeeData);
    }
    printf("\n Employee ID              : %d\n", emp.employeeId);
    char deptname[15], ch, deptcode[15], tempDeptCode[15], tempdeptname[15];
    int linesCount = 0, tempDeptCodeDigits;
    // Counting the number of lines in the file
    while ((ch = fgetc(fp_departmentData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_departmentData);
    fp_departmentData = fopen("DepartmentData.txt", "r");
    // printing all the departments
    printf("\n -----------------------------------------------");
    printf("\n Department Name\t\t Department Code\n");
    printf(" -----------------------------------------------\n");
    while (!(feof(fp_departmentData)) && linesCount > 0)
    {
        fscanf(fp_departmentData, "%s", deptname);
        strcpy(deptcode, deptname);
        strrev(deptcode);
        strrev(strtok(deptcode, ","));
        printf(" %s \t\t\t\t %s\n", strtok(deptname, ","), deptcode);
        linesCount--;
    }
    printf(" -----------------------------------------------\n");
    fclose(fp_departmentData);
    printf("\n Enter Department Code    : ");
    scanf("%d", &departmentCode);
    fp_departmentData = fopen("DepartmentData.txt", "r");
    while (!feof(fp_departmentData))
    {
        fscanf(fp_departmentData, "%s,%d\n", dep.departmentName, &dep.departmentCode);
        strcpy(tempdeptname, dep.departmentName);
        strcpy(tempDeptCode, strrev(dep.departmentName));
        tempDeptCodeDigits = atoi(strrev(strtok(tempDeptCode, ",")));
        if (tempDeptCodeDigits == departmentCode)
        {
            strcpy(emp.departmentName, strtok(tempdeptname, ","));
            emp.departmentCode = tempDeptCodeDigits;
            totrec++;
            strcpy(foundDepartment, dep.departmentName);
            break;
        }
    }
    fclose(fp_departmentData);
    if (totrec == 0)
    {
        system("CLS");
        printf("\n Department with code %d Dose not Exists.\n\n", departmentCode);
        printDepartmentDetails();
    }
    printf("\n Department Name          : %s\n", strtok(strrev(foundDepartment), ","));
    printf("\n Enter The Location       : ");
    scanf("%s", emp.employeeLocation);
    fp_employeeData = fopen("employeeData.txt", "a");
    fprintf(fp_employeeData, "%s,%d,%s,%s,%d\n", emp.departmentName, emp.departmentCode, emp.employeeLocation, emp.employeeName, emp.employeeId);
    printf("\n Employee Added Successfully. Press Enter To Continue... ");
    getch();
    system("CLS");
    fclose(fp_employeeData);
    employeeMaintenanceMenu();
}

/*
 * Function to add the New Department
 * Author: S Varun
*/
void addDepartment()
{
    int i;
    FILE *fp_departmentData = fopen("DepartmentData.txt", "a");
    department dep;
    char tempDepartmentName[15], foundDepartment[15];
    int tempDepartmentCode, totrec = 0, found = 0;
    long int res = findSize("DepartmentData.txt");
    fclose(fp_departmentData);
    printLine();
    printf(" Add Department \n");
    printLine();
    printf("\n Enter Department Name  : ");
    scanf("%s", tempDepartmentName);
    for (i = 0; i <= strlen(tempDepartmentName); i++)
    {
        if (tempDepartmentName[i] >= 97 && tempDepartmentName[i] <= 122)
            tempDepartmentName[i] = tempDepartmentName[i] - 32;
    }
    if (res == 0)
    {
        FILE *fp_departmentData = fopen("DepartmentData.txt", "a");
        dep.departmentCode = 1000;
        fprintf(fp_departmentData, "%s,%d\n", tempDepartmentName, dep.departmentCode);
        fclose(fp_departmentData);
        printf("\n Department Code        : %d\n", dep.departmentCode);
        printf("\n Department Added Successfully. Press Enter To Continue... ");
        getch();
        system("CLS");
        departmentMaintenanceMenu();
    }
    else
    {
        fp_departmentData = fopen("DepartmentData.txt", "r");
        while (!feof(fp_departmentData))
        {
            fscanf(fp_departmentData, "%s,%d\n", dep.departmentName, &dep.departmentCode);
            if (strcmp(strtok(dep.departmentName, ","), tempDepartmentName) == 0)
            {
                totrec++;
                strcpy(foundDepartment, dep.departmentName);
                found = 1;
            }
        }
        if (found == 1)
        {
            system("CLS");
            printf("\n Department of %s Already Exists.\n\n", foundDepartment);
            departmentMaintenanceMenu();
        }
        if (totrec == 0)
        {
            char trav[100];
            strcpy(trav, strrev(tail(fopen("DepartmentData.txt", "r"), 2)));
            char *departmentCode = strtok(trav, ",");
            strcpy(departmentCode, strrev(departmentCode));
            dep.departmentCode = atoi(departmentCode) + 1;
            printf("\n Department Code        : %d\n", dep.departmentCode);
            fp_departmentData = fopen("DepartmentData.txt", "a");
            fprintf(fp_departmentData, "%s,%d\n", tempDepartmentName, dep.departmentCode);
            fclose(fp_departmentData);
            printf("\n Department Added Successfully. Press Enter To Continue... ");
            getch();
            system("CLS");
            departmentMaintenanceMenu();
        }
    }
}

/*
 * Function to Add a telephone Number
 * Author: S.Varun
*/
void addTelephoneNumber()
{
    FILE *fp_employeeData = fopen("employeeData.txt", "r");
    telephone tel;
    int tempEmployeeId, linesCount = 0, found = 0, finalDepCode;
    char empData[100], tempEmpData[100], depName[100], tempEmpId[100], ch;
    long int res = findSize("employeeData.txt");
    if (res == 0)
    {
        system("CLS");
        printf("\n----------- No Employees Exists ! -----------\n\n");
        employeeMaintenanceMenu();
    }
    printLine();
    printf(" Add a Telephone Number \n");
    printLine();
    printf("\n Enter Employee ID        : ");
    scanf("%d", &tempEmployeeId);
    while ((ch = fgetc(fp_employeeData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_employeeData);
    fp_employeeData = fopen("employeeData.txt", "r");
    while (!(feof(fp_employeeData)) && linesCount > 0)
    {
        fscanf(fp_employeeData, "%s", tempEmpData);
        strcpy(tempEmpId, tempEmpData);
        tel.employeeId = atoi(strrev(strtok(strrev(tempEmpId), ",")));
        if (tempEmployeeId == tel.employeeId)
        {
            strcpy(empData, tempEmpData);
            strcpy(depName, tempEmpData);
            strtok(depName, ",");
            found = 1;
        }
        linesCount--;
    }
    fclose(fp_employeeData);
    if (found == 0)
    {
        system("CLS");
        printf("\n Employee with ID %d Dose not Exists.\n\n", tempEmployeeId);
        printEmployeeDetails();
    }
    finalDepCode = returnDepartmentCodeOnDepartmentName(depName);
    res = findSize("telephoneData.txt");
    if (res == 0)
    {
        tel.telephoneNumber = 1000;
    }
    else
    {
        int employeeExistInTelephoneData = 0;
        employeeExistInTelephoneData = checkForExistenceOfEmpInTelePhoneData(tempEmployeeId);
        if (employeeExistInTelephoneData == 1)
        {
            system("CLS");
            printf("\n Telephone Number With Employee ID %d Already Exist.\n\n", tempEmployeeId);
            telephoneMaintenanceMenu();
        }
        char trav[100];
        FILE *fp_telephoneData = fopen("telephoneData.txt", "r");
        strcpy(trav, strrev(tail(fp_telephoneData, 2)));
        strrev(strtok(trav, "-"));
        tel.telephoneNumber = atoi(trav) + 1;
        fclose(fp_telephoneData);
    }
    FILE *fp_telephoneData = fopen("telephoneData.txt", "a");
    fprintf(fp_telephoneData, "%s,%d-%d\n", empData, finalDepCode, tel.telephoneNumber);
    fclose(fp_telephoneData);
    char *token = strtok(empData, ",");
    int i = 0;
    while (token != NULL)
    {
        i++;
        if (i == 3)
        {
            printf("\n Location                 : %s\n", token);
        }
        token = strtok(NULL, ",");
    }
    printf("\n Department Code          : %d\n", finalDepCode);
    printf("\n Telephone Number Alloted : %d%d\n", finalDepCode, tel.telephoneNumber);
    printf("\n Telephone Number Added Successfully. Press Enter To Continue... ");
    getch();
    system("CLS");
    telephoneMaintenanceMenu();
}

/*
 * This functions takes Department Name And Returns Department Code
 * Author: Mohammed Usman E Gani
*/
int returnDepartmentCodeOnDepartmentName(char depName[])
{
    FILE *fp_departmentData = fopen("DepartmentData.txt", "r");
    int linesCount = 0, finalDepCode;
    char tempDepData[100], ch, tempDepName[100], tempDepCode[100];
    while ((ch = fgetc(fp_departmentData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_departmentData);
    fp_departmentData = fopen("DepartmentData.txt", "r");
    while (!(feof(fp_departmentData)) && linesCount > 0)
    {
        fscanf(fp_departmentData, "%s", tempDepData);
        strcpy(tempDepName, tempDepData);
        strtok(tempDepName, ",");
        strcpy(tempDepCode, tempDepData);
        if (strcmp(tempDepName, depName) == 0)
        {
            finalDepCode = atoi(strrev(strtok(strrev(tempDepCode), ",")));
        }
        linesCount--;
    }
    fclose(fp_departmentData);
    return finalDepCode;
}

/*
 * This Function
*/
int checkForExistenceOfEmpInTelePhoneData(int tempEmployeeId)
{
    char ch, tempTeleData[100];
    int linesCount = 0, exist = 0;
    FILE *fp_telephoneData = fopen("telephoneData.txt", "r");
    while ((ch = fgetc(fp_telephoneData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_telephoneData);
    fp_telephoneData = fopen("telephoneData.txt", "r");
    while (!(feof(fp_telephoneData)) && linesCount > 0)
    {
        fscanf(fp_telephoneData, "%s", tempTeleData);

        char *token = strtok(tempTeleData, ",");
        int i = 0;
        while (token != NULL)
        {
            i++;
            if (i == 5)
            {
                break;
            }
            token = strtok(NULL, ",");
        }
        if (atoi(token) == tempEmployeeId)
        {
            exist = 1;
            break;
        }
        linesCount--;
    }
    fclose(fp_telephoneData);
    if (exist == 1)
        return 1;
    else
        return 0;
}

/*
 * Telephone Enquiry Menu
 * Author: Mohammed Usman E Gani
*/
void telephoneEnquiryMenu()
{
    long int res = findSize("telephoneData.txt");
    if (res == 0)
    {
        system("CLS");
        printf("\n----------- Telephone Directory Is Empty ! -----------\n\n");
        telephoneMaintenanceMenu();
    }
    int choice, invalidStatus;
    do
    {
        invalidStatus = 0;
        printLine();
        printf(" Telephone Enquiry Menu\n");
        printLine();
        printf("\n 1. Enquiry on Employee Name\n 2. Enquiry on Telephone Number\n 3. Goto Main Menu\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("CLS");
            enquiryonEmployeeName();
            break;
        case 2:
            system("CLS");
            enquironTelephoneNumber();
            break;
        case 3:
            system("CLS");
            mainMenu();
            break;
        default:
            system("CLS");
            printf("\n Invalid Choice\n\n");
            invalidStatus = 1;
        }
    } while (invalidStatus == 1);
}

/*
 * Function For Telephone Number Enquiry
 * Author: Mohammed Usman E Gani
*/
void enquironTelephoneNumber()
{
    FILE *fp_telephoneData = fopen("telephoneData.txt", "r");
    long int tempTelephoneNumber, finalTelephoneNumber;
    int linesCount = 0, found = 0;
    char ch, tempTelephoneData[125], tempTeleNumber[20], temp1[20], temp2[20], finalTeleNumber[20], telephoneData[125];
    printLine();
    printf(" Telephone Number Enquiry\n");
    printLine();
    printf("\n Enter Telephone Number   : ");
    scanf("%d", &tempTelephoneNumber);
    while ((ch = fgetc(fp_telephoneData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_telephoneData);
    fp_telephoneData = fopen("telephoneData.txt", "r");
    while (!(feof(fp_telephoneData)) && linesCount > 0)
    {
        fscanf(fp_telephoneData, "%s", tempTelephoneData);
        strcpy(telephoneData, tempTelephoneData);
        strcpy(tempTeleNumber, tempTelephoneData);
        strrev(strtok(strrev(tempTeleNumber), ","));
        strcpy(temp1, tempTeleNumber);
        strcpy(temp2, tempTeleNumber);
        strtok(temp1, "-");
        strrev(strtok(strrev(temp2), "-"));
        strcpy(finalTeleNumber, strcat(temp1, temp2));
        finalTelephoneNumber = atoi(finalTeleNumber);
        if (tempTelephoneNumber == finalTelephoneNumber)
        {
            char *token = strtok(telephoneData, ",");
            int i = 0;
            while (token != NULL)
            {
                i++;
                if (i == 4)
                {
                    printf("\n Employee Name            : %s\n", token);
                }
                if (i == 3)
                {
                    printf("\n Location                 : %s\n", token);
                }
                if (i == 1)
                {
                    printf("\n Department Name          : %s\n", token);
                }
                token = strtok(NULL, ",");
            }
            found = 1;
            printf("\n Press Enter To Continue... ");
            getch();
            system("CLS");
            break;
        }
        linesCount--;
    }
    if (found == 0)
    {
        system("CLS");
        printf("\n Employee With Telephone Number %d Dose Not Exist.\n\n", tempTelephoneNumber);
        telephoneEnquiryMenu();
    }
    fclose(fp_telephoneData);
    telephoneEnquiryMenu();
}

/*
 * Function for Telephone Enquiry on name
 * Author: Mohammed Usman E Gani
*/
void enquiryonEmployeeName()
{
    FILE *fp_telephoneData = fopen("telephoneData.txt", "r");
    char tempEmployeeName[25], ch, tempEmployeeTelephoneData[125], foundData[125];
    int linesCount = 0, dataFound = 0, headers = 1;
    printLine();
    printf(" Telephone Number Enquiry By Name\n");
    printLine();
    printf("\n Enter Employee Name : ");
    scanf("%s", tempEmployeeName);
    while ((ch = fgetc(fp_telephoneData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(fp_telephoneData);
    fp_telephoneData = fopen("telephoneData.txt", "r");
    while (!(feof(fp_telephoneData)) && linesCount > 0)
    {
        fscanf(fp_telephoneData, "%s", tempEmployeeTelephoneData);
        strcpy(foundData, tempEmployeeTelephoneData);
        char *token = strtok(tempEmployeeTelephoneData, ",");
        int i = 0;
        while (token != NULL)
        {
            i++;
            if (i == 4)
            {
                for (i = 0; i <= strlen(tempEmployeeName); i++)
                {
                    if (tempEmployeeName[i] >= 97 && tempEmployeeName[i] <= 122)
                        tempEmployeeName[i] = tempEmployeeName[i] - 32;
                }
                for (i = 0; i <= strlen(token); i++)
                {
                    if (token[i] >= 97 && token[i] <= 122)
                        token[i] = token[i] - 32;
                }
                if (strcmp(token, tempEmployeeName) == 0)
                {
                    if (headers == 1)
                    {
                        printf("\n ---------------------------------------------------------------------------------------------------");
                        printf("\n Name \t\t Location \t\t Department Name \t\t Telephone Number\n");
                        printf(" ---------------------------------------------------------------------------------------------------\n");
                        headers = 0;
                    }
                }
                if (strcmp(token, tempEmployeeName) == 0)
                {
                    printEnquiryonEmployeeName(foundData);
                    dataFound = 1;
                }
            }
            token = strtok(NULL, ",");
        }
        linesCount--;
    }
    if (dataFound == 0)
    {
        system("CLS");
        printf("\n Employee With Name %s Dose not Exist In Telephone Directory.\n\n", tempEmployeeName);
        telephoneEnquiryMenu();
    }
    else
    {
        printf(" ---------------------------------------------------------------------------------------------------\n");
        printf("\n Press Enter To Continue... ");
        getch();
        system("CLS");
        telephoneEnquiryMenu();
    }
}

void printEnquiryonEmployeeName(char dataToPrint[])
{
    char *token = strtok(dataToPrint, ","), name[25], location[25], dep[25], tele[25];
    int i = 0;
    while (token != NULL)
    {
        i++;
        if (i == 4)
        {
            strcpy(name, token);
        }
        if (i == 3)
        {
            strcpy(location, token);
        }
        if (i == 1)
        {
            strcpy(dep, token);
        }
        if (i == 6)
        {
            strcpy(tele, token);
        }
        token = strtok(NULL, ",");
    }
    printf(" %s\t\t %s \t\t\t %s \t\t\t\t %s \n", name, location, dep, tele);
}

/*
 * Main Function
 * Authors:
 *          Mohammed Usman E Gani (2SD18CS059)
 *                  (AND)
 *          S Varun (2SD18CS130)
*/
int main()
{
    FILE *fp_employeeData = fopen("employeeData.txt", "a");
    FILE *fp_departmentData = fopen("DepartmentData.txt", "a");
    FILE *fp_telephoneData = fopen("telephoneData.txt", "a");
    fclose(fp_telephoneData);
    char password[20] = "123"; // set password
    char userName[20] = "abc"; // set userName
    system("CLS");
    printLine();
    printf(" Welcome - Telephone Directory Maintenance System \n");
    printLine();
    printf("\n\n Press Enter to Login... ");
    getch();
    if (userAuthentation(userName, password))
    {
        system("CLS");
        printf("\n Logged In\n\n");
        mainMenu();
    }
    else
    {
        printf("\n\n You have reached Maximum Trails Limit !!! \n\n");
        exit(0);
    }
    return 0;
}

void developerInfo()
{
    printf("\n\t\t\t\t\t\t   DEVELOPERS INFO \n");
    printf("=======================================================================================================================\n");
    printf(" SL.NO\t\tName\t\t\t\tUSN\t\t\tPhone Number\t\tE-Mail\n");
    printf("=======================================================================================================================\n");
    printf(" 1\t\tS Varun\t\t\t\t2SD18CS130\t\t+91 94837 12819\t\tvarun3082000@gmail.com\n");
    printf(" 2\t\tMohammed Usman E Gani\t\t2SD18CS059\t\t+91 80886 11415\t\tka.usmanegani@gmail.com\n");
    printf("=======================================================================================================================\n\n");
    return;
}