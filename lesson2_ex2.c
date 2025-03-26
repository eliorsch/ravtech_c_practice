#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee_struct {
	int id;
	char name[10];
	float salary;
	struct Employee_struct* next;
} Employee;

void Efill(Employee* e)
{
	printf("enter id: ");
	scanf("%d", &(e->id));
	printf("enter name: ");
	scanf("%s", &(e->name));
	printf("enter salary: ");
	scanf("%f", &(e->salary));
	e->next = NULL;
}

void Eprint(Employee* e)
{
	printf("id: %d\n", e->id);
	printf("name: %s\n", e->name);
	printf("salary: %f\n", e->salary);
}

Employee* EmaxSalaryArr(Employee* arr, int n)
{
	Employee* max = arr;

	for (int i = 1; i < n; ++i)
	{
		if ((arr + i)->salary > max->salary) max = arr + i;
	}
	return max;
}

Employee* EmaxSalaryList(Employee* head)
{
	Employee* max = head;

	for (Employee* ptr = head->next; ptr; ptr = ptr->next)
	{
		if (ptr->salary > max->salary) max = ptr;
	}
	return max;
}

Employee* addEmp(Employee* head, int id, const char* name, float salary)
{
	Employee* ptr = head;

	if (head)
	{
		while (ptr->next) ptr = ptr->next;
		ptr = ptr->next = malloc(sizeof(Employee));
	}
	else
	{
		ptr = head = malloc(sizeof(Employee));
	}

	ptr->id = id;
	strcpy(ptr->name, name);
	ptr->salary = salary;
	ptr->next = NULL;

	return head;
}

void EfreeList(Employee* head)
{
	if (head)
	{
		EfreeList(head->next);
		free(head);
	}
}

Employee* findTopEmp(Employee* head)
{
	return EmaxSalaryList(head);
}
void Q1()
{
	int n;
	
	printf("number of employees? ");
	scanf("%d", &n);

	Employee* arr = malloc(sizeof(Employee) * n);
	
	for (int i = 0; i < n; ++i)
	{
		Efill(arr + i);
	}
	
	prntf("employees list: \n");
	for (int i = 0; i < n; ++i)
	{
		Eprint(arr + i);
	}

	printf("max salary employee: ");
	Eprint(EmaxSalaryArr(arr, n));

	free(arr);
}

void Q2_Q3()
{
	Employee* head = NULL, input;


	Efill(&input);
	head = addEmp(head, input.id, input.name, input.salary);

	Efill(&input);
	head = addEmp(head, input.id, input.name, input.salary);

	Efill(&input);
	head = addEmp(head, input.id, input.name, input.salary);



	printf("max salary : \n");
	Eprint(EmaxSalaryList(head));

	EfreeList(head);
}

int main()
{
	Q1();
	Q2_Q3();


	return 0;
}