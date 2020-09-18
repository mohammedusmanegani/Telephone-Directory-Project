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
void userAuthentation();
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
void userAuthentation()
{
    int i = 0, uid, maxLimit = 0;
    char password[10], c;
    system("CLS");
    printLine();
    printf(" Welcome - Telephone Directory Maintenance System \n");
    printLine();
    while (1)
    {
        printf("\n User ID  : ");
        scanf("%d", &uid);
        printf("\n Password : ");
        while ((c = getch()) != '\r')
        {
            password[i] = c;
            printf("*");
            i++;
        }
        char finalPass[50] = {password[0], password[1], password[2], '\0'};
        if (strcmp(finalPass, "abc") != 0 || uid != 123)
        {
            printf("\n\n Authentation Failed !\n");
            printf("\n Try Again\n");
            maxLimit++;
        }
        else if (strcmp(finalPass, "abc") == 0 && uid == 123)
        {
            return;
        }
        if (maxLimit >= 3)
        {
            system("CLS");
            printf("\n\n Authentation Failed !\n");
            printf("\n You Have Reached Maximum Trails Limit.\n");
            printf("\n Hit Enter to Terminate ...");
            getch();
            system("CLS");
            exit(0);
        }
    }
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
    printf("\n Enter Employee Name: ");
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
    printf("\n Employee ID: %d\n", emp.employeeId);
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
    printf("\n Enter Department Code: ");
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
        }
    }
    fclose(fp_departmentData);
    if (totrec == 0)
    {
        system("CLS");
        printf("\n Department with code %d Dose not Exists.\n\n", departmentCode);
        printDepartmentDetails();
    }
    printf("\n Enter The Location: ");
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
    printf("\n Enter Department Name: ");
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
        printf("\n Department Code: %d\n", dep.departmentCode);
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
            printf("\n Department Code: %d\n", dep.departmentCode);
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

    printf("\n Enter Employee ID: ");
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
            addTelephoneNumber();
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
            // system("CLS");
            // enquiryonEmployeeName();
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

    long int tempTelephoneNumber;
    int linesCount = 0;
    char ch;
    printLine();
    printf(" Telephone Number Enquiry\n");
    printLine();
    printf("\n Enter Telephone Number: ");
    scanf("%d", tempTelephoneNumber);

    while ((ch = fgetc(fp_telephoneData)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }

    fclose(fp_telephoneData);
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
    userAuthentation(); //Authentation
    system("CLS");
    printf("\n Logged In\n\n");
    mainMenu();
}