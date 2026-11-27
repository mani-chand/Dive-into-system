/*
gcc -std=c17 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined employees.c -o employees

./employees
*/
#include <stdio.h>
#include <stdlib.h>

int *init_employees(void);
int add_employees(int **employees, int count, int capacity,int emp_id);
int resize_employees(int **employees,int capacity);
void update_employee(int *employee,int emp_id);
void display(int *employee,int count);
int *create_backup_employees(int *employee,int count);
void clear_employees(int *employee,int *backup_employees);


int main()
{
    int choice = -1;
    int count = 0;
    int capacity = 0;
    int* employees = init_employees();
    int* backup_employees = NULL;
    int backup_employees_count = 0;
    int emp_id,idx;
    if(employees == NULL){
        printf("Couldn't initialize the employees due memory allocation issue");
        return 1;
    }
    capacity += 2;
    while(choice != 6){
        printf("\n---------------------------Please select a option-------------------------------------\n");
        printf("1. Add employee\n");
        printf("2. Update employee\n");
        printf("3. Display employees\n");
        printf("4. Create backup\n");
        printf("5. Display backup\n");
        printf("6. Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Employee ID: ");
                scanf("%d",&emp_id);
                int temp_capcity = add_employees(&employees,count,capacity,emp_id); // Assuming User enters vaild emp_id.
                if(!temp_capcity){
                    printf("Couldn't add Employee due memory allocation issue!");
                    break;
                }
                capacity = temp_capcity;
                count++;
                break;
            case 2:
                printf("Index: ");
                scanf("%d",&idx);
                printf("Employee ID: ");
                scanf("%d",&emp_id);
                if(idx >= count || idx < 0){
                    printf("Please give a valid Index");
                    break;
                }
                update_employee(&employees[idx],emp_id);
                break;
            case 3:
                display(employees,count);
                break;
            case 4:
                int *temp = create_backup_employees(employees, count);
                if (temp == NULL) {
                    printf("Backup creation failed!");
                    break;
                }
                free(backup_employees);
                backup_employees = temp;
                backup_employees_count = count;
                break;
            case 5:
                display(backup_employees,backup_employees_count);
                break;
            case 6:
                clear_employees(employees,backup_employees);
                break;
        }
        
    }
    return 0;
}

int *init_employees(void){
    int *employees = malloc(sizeof(int)*2);
    if(employees == NULL){
        return NULL;
    }
    return employees;
}

int add_employees(int **employees, int count, int capacity,int emp_id){
    int new_cap = capacity;
    if(count >= capacity){
        new_cap = resize_employees(employees,capacity);
        if(!new_cap){
            printf("Memory could not allocate! Please try again");
            return 0;
        }
    }
    (*employees)[count] = emp_id;
    return new_cap;// return  capacity
}

int resize_employees(int **employees,int capacity){
    int new_cap = capacity ? capacity * 2 : 2; // if zero increase to 2.
    int *temp = realloc(*employees,sizeof(int)*(size_t)new_cap);
    if(temp == NULL){
        return 0;
    }
    *employees = temp;
    return new_cap; // return new capacity
}

void update_employee(int *employee,int emp_id){
    *employee = emp_id;
}

void display(int *employee,int count){
    if(employee == NULL){
        printf("There are no Employees to show");
        return;
    }
    for(int i = 0; i < count; i++){
        printf("Employee %d is %d\n",i+1,employee[i]);
    }
}

int *create_backup_employees(int *employee,int count){
    int *backup_employees = malloc(sizeof(int)*count);
    if(backup_employees == NULL){
        return NULL;
    }
    for(int i = 0;i<count;i++){
        backup_employees[i] = employee[i];
    }
    return backup_employees;
}

void clear_employees(int *employee,int *backup_employees){
    free(employee);
    free(backup_employees);
}