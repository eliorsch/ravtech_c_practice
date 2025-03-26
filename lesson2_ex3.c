#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee_struct {
	int id;
	char name[10];
	float salary;
	struct Employee_struct*  next;
} Employee;

typedef struct  {
	int id;
	char name[10];
	float salary;
	int age;
} NewEmployee;

void Efill(Employee*  e)
{
	printf("enter id: ");
	scanf("%d", &(e->id));
	printf("enter name: ");
	scanf("%s", &(e->name));
	printf("enter salary: ");
	scanf("%f", &(e->salary));
	e->next = NULL;
}

void Eprint(Employee*  e)
{
	printf("id: %d\n", e->id);
	printf("name: %s\n", e->name);
	printf("salary: %.2f\n", e->salary);
}

Employee*  EmaxSalaryArr(Employee*  arr, int n)
{
	Employee*  max = arr;

	for (int i = 1; i < n; ++i)
	{
		if ((arr + i)->salary > max->salary) max = arr + i;
	}
	return max;
}

Employee*  EmaxSalaryList(Employee*  head)
{
	Employee*  max = head;

	for (Employee*  ptr = head->next; ptr ; ptr = ptr->next)
	{
		if (ptr->salary > max->salary) max = ptr;
	}
	return max;
}

Employee* addEmp(Employee*  head, int id, const char* name, float salary)
{
	Employee*  ptr = head;
	
	if (head)
	{
		while (ptr->next) ptr = ptr->next;
		ptr = ptr->next= malloc(sizeof(Employee));
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

void EfreeList(Employee*  head)
{
	if (head)
	{
		EfreeList(head->next);
		free(head);
	}
}

Employee*  findTopEmp(Employee*  head)
{
	return EmaxSalaryList(head);
}

void EListSaveToFile(Employee*  head, const char* filename)
{
	FILE* fp = fopen(filename, "wb");

	if (fp == NULL) {

		perror("Cannot open file");

		return;

	}

	for (Employee* ptr = head; ptr; ptr = ptr->next) {

		fwrite(ptr, sizeof(Employee), 1, fp);

	}

	fclose(fp);
}

Employee* EListLoadFromFile(const char* filename)
{
	FILE* fp = fopen(filename, "rb");

	if (fp == NULL) {

		perror("Cannot open file");

		return NULL;

	}

	Employee* head = NULL, input = { 0, " ", 0 };

	while (fread(&input, sizeof(Employee), 1, fp))
	{
		head = addEmp(head, input.id, input.name, input.salary);
	}

	fclose(fp);
	
	return head;
}

Employee* EEmployeeLoadFromFile(const char* filename, int index)
{
	FILE* fp = fopen(filename, "rb");

	if (fp == NULL) {

		perror("Cannot open file");

		return NULL;

	}

	if (fseek(fp, index * sizeof(Employee), SEEK_SET))
	{
		printf("error seeking employee!\n");
		return NULL;
	}

	Employee* item = malloc(sizeof(Employee));
	
	fread(item, sizeof(Employee) - sizeof(Employee*), 1, fp);
	item->next = NULL;

	fclose(fp);
	
	return item;
}


void Q1()
{
	Employee* head = NULL, input = { 0, " ", 0 };
	char* filename = "employees.bin";

	while (1)
	{
		printf("enter id: ");
		scanf("%d", &(input.id));
		printf("enter name: ");
		scanf("%s", &(input.name));
		if (input.name[0] == 'Q') break;
		printf("enter salary: ");
		scanf("%f", &(input.salary));

		head = addEmp(head, input.id, input.name, input.salary);
		EListSaveToFile(head, filename);
	}

	EfreeList(head);
}

void Q2()
{
	Employee* head = NULL;
	char* filename = "employees.bin";


	head = EListLoadFromFile(filename);
	for (Employee* ptr = head; ptr; ptr = ptr->next) Eprint(ptr);

	EfreeList(head);
}

void Q3()
{
	char* filename = "employees.bin";

	printf("please enter employee index: ");
	int index;
	scanf("%d", &index);

	Employee* item = EEmployeeLoadFromFile(filename, index);
	if (item)
	{
		Eprint(item);

		free(item);
	}
	else
	{
		printf("error fetching employee!\n");
	}
}

void Q4()
{
	char* old_filename = "employees.bin", *new_filename = "employees_new.bin";
	Employee* head = EListLoadFromFile(old_filename);
	NewEmployee newE;	
	FILE* fp = fopen(new_filename, "wb");

	if (fp == NULL) {

		perror("Cannot open file");

		return;

	}

	for (Employee* ptr = head; ptr; ptr = ptr->next)
	{
		newE.id =  ptr->id;
		strcpy(newE.name, ptr->name);
		newE.salary = ptr->salary;
		
		printf("enter age for employee: \n");
		Eprint(ptr);
		scanf("%d", &newE.age);
		
		fwrite(&newE, sizeof(newE), 1, fp);
	}

	EfreeList(head);
	
	fclose(fp);

	fp = fopen(new_filename, "rb");

	while (fread(&newE, sizeof(NewEmployee), 1, fp)) 
	{
		printf("ID: %d | Name: %s | Salary: %.2f | Age: %d.\n", newE.id, newE.name, newE.salary, newE.age);
	}

	fclose(fp);
 }

int main()
{
	Q1();
	Q2();
	Q3();
	Q4();

	return 0;
}