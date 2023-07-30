#include<stdio.h>
#include<process.h>
#include<string.h>

int main(){
    FILE *fp;
    struct record{
        char number[10];
        char name[15];
        char status;
        int hoursWorked;
        float deductions;
    };

    struct record employee;
    // Open file for writing
    fp = fopen("Records.dat", "wb");
    

    // Check if file can be created
    if (fp==NULL){
        printf("File cannot be created!");
        exit(1);
    }

    int i, num;
    printf("Enter the number of employee: ");
    scanf("%d", &num);

    int basicSalary[num], basicRate[num], overtimeRate[num], overtimePay[num], netPay[num], overtimeHours[num]; // Naka-array ito para ma-store n'ya lahat ng value na ii-input per employee.

    // Enter data and write to file
    printf("\n\nEnter the following\n");
    for (i=1; i<=num; i++){ //
        overtimePay[i] = 0; // Initialize the value of overtimePay to 0. Every maglo-loop 0 ang unang value ni overtimePay.
        printf("\nEMPLOYEE %d\n", i);
        printf("Employee Number: ");
        scanf("%s", &employee.number);
        while (strlen(employee.number) > 9){   // Maglo-loop dito hanggat ang characters na ininput ay mas mataas sa 9.
            printf("!!! Maximun of 9 characters only !!!\n");
            printf("Employee Number: ");
            scanf("\n");
            scanf("%s", &employee.number);
        }
        printf("Employee Name: ");
        scanf("\n");
        gets(employee.name);
        while (strlen(employee.name) > 14){ // Maglo-loop dito hanggat ang characters na ininput ay mas mataas sa 14
            printf("!!! Maximun of 14 characters only !!!\n");
            printf("Employee Name: ");
            scanf("\n");
            gets(employee.name);
        }

        printf("Status Code: ");
        scanf("%c", &employee.status);
        while (((employee.status != 'R') && (employee.status != 'r')) && ((employee.status != 'C') && (employee.status != 'c'))){   // Maglo-loop dito hanggat hindi R, C, r, c ang ininput ni user
            printf("!!!You must enter R for Regular or C for Casual!!!\nStatus Code: ");
            scanf("\n");
            scanf("%c", &employee.status);
        }

        printf("Hours Worked: ");
        scanf("%d", &employee.hoursWorked);

        if ((employee.status == 'R') || (employee.status == 'r')){  // papasok dito kapag R or r ang status ni employee.
            printf("Basic Salary: ");
            scanf("%d", &basicSalary[i]);
            if (employee.hoursWorked > 160){    // Computation. Pasok dito kapag exceed ang number of hours sa 160. Entitled din si employee sa overtimapay.
                overtimeHours[i] = employee.hoursWorked - 160;
                basicRate[i] = basicSalary[i]/160;
                overtimeRate[i] = basicRate[i] * 1.5;
                overtimePay[i] = overtimeRate[i] * overtimeHours[i];
            }   // End
        }   // End of the if statement.
        else {  // Papasok dito kapag C or c ang status ni employee.
            printf("Basic Rate: ");
            scanf("%d", &basicRate[i]); //
            basicSalary[i] = employee.hoursWorked*basicRate[i];
            if (employee.hoursWorked > 160){    // Computation. Pasok dito kapag exceed ang number of hours sa 160. Entitled din si employee sa overtimapay.
                overtimeHours[i] = employee.hoursWorked - 160;
                overtimeRate[i] = basicRate[i] * 1.5;
                overtimePay[i] = overtimeRate[i] * overtimeHours[i];
            }   // End
        }   // End

        printf("Deductions: ");
        scanf("%f", &employee.deductions);

        netPay[i] = basicSalary[i] + overtimePay[i] - employee.deductions;

        fwrite(&employee, sizeof(struct record), 1, fp);
    }

    // Close file
    fclose(fp);

    // Open file for reading
    fp=fopen("Records.dat", "rb");
    //Check if file can be opened for reading
    if (fp==NULL){
        printf("File cannot be opened for reading!");
        exit(1);
    }


    // Display
    printf("--------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\tABC COMPANY\n\t\t\t\t\t\tMakati City\n");
    printf("--------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t  Payroll\n");
    printf("--------------------------------------------------------------------------------------------------------------");
    printf("\n\nEmployee\tEmployee\tStatus\t\tBasic\t\tOvertime\tDeductions\tNet");
    printf("\nNumber\t\tName\t\t\t\tSalary\t\t\t\tPay\t\tPay\n\n");
    i=0;    // Initialize variable i to 0 because we will print the records of employee 1.
    while (fread(&employee,sizeof(struct record),1,fp) == 1){
        i++;    // increment to access or print the records of the employee. (employee 1, 2, 3...)
        printf("%-10s\t%-15s\t", employee.number, strupr(employee.name)); // -10 and -15 specify the width of the field
        if ((employee.status == 'R') || (employee.status == 'r'))
            printf("REGULAR\t\t");
        else
            printf("CASUAL\t\t");
        printf("%-10d\t%-10d\t%-10.2f\t%-10d\n", basicSalary[i], overtimePay[i], employee.deductions, netPay[i]);
    }

    fclose(fp);
}