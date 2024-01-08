#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define max 5
int city;
char industries[50][500];
struct machineries *head = NULL;
struct machineries *arr[100];
int arrIndex = 0;
int clarr[max];

//Setting up information
void getstarted()
{
    FILE *ptr;
    ptr = fopen("G:\\DSA_UUU\\city.txt","w");
    printf("\n \n");
    printf("\t\t\t############################################################################");
    printf("\n\t\t\t############              DSA Project:      Made by :           ############");
    printf("\n\t\t\t############              Shalin Patel      21bce215            ############");
    printf("\n\t\t\t############              Shreya Patel      21bce216            ############");
    printf("\n\t\t\t############              Smit   Patel      21bce217            ############");
    printf("\n\t\t\t############################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\n");
    printf("\n\t\t\t  *------------------*\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =                 DSA Project               =");
    printf("\n\t\t\t        =                  Made by:                 =");
    printf("\n\t\t\t        =                  215,216,217              =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  *------------------*\n\n\n");

    printf("In how many cities do you have your Industries?\n");
    scanf("%d",&city);
    for (int i = 0; i < city; i++)
    {
        printf("Enter %d City name: ",(i+1));
        scanf("%s",&industries[i]);
        fputs(industries,ptr);
        fputs("\n",ptr);
    }
    fclose(ptr);
}

//Structure for employee management
struct Employees
{
    struct Employees *lchild;
    struct Employees *rchild;
    long long int id;
    char name[25];
    long int salary;
    long long int phone_number;
    char city[30];
}*firstem,*tempem;

//To insert details of the new employee
struct Employees *Insert(struct Employees *p,long int salary, char *names, long long int id, long long int phonenumber, char *city)
{
    if(p==NULL)
    {
        struct Employees* t=(struct Employees *)malloc(sizeof(struct Employees));
        t->salary=salary;
        strcpy(t->name,names);
        t->id=id;
        t->phone_number=phonenumber;
        strcpy(t->city,city);
        t->lchild=t->rchild=NULL;
        p=t;
    }
    if(id < p->id)
    {
        p->lchild=Insert(p->lchild,salary,names,id,phonenumber,city);
    }
    else if(id > p->id)
    {
        p->rchild=Insert(p->rchild,salary,names,id,phonenumber,city);
    }
    return p;
}


//Height of employee stucture
int Height(struct Employees *p)
{
    int x,y;
    if(p==NULL)
    {
        return 0;
    }
    x=Height(p->lchild);
    y=Height(p->rchild);
    return x>y?x+1:y+1;
}

//Precedessor of employee structure
struct Employees *InPre(struct Employees *p)
{
    while(p && p->rchild!=NULL)
    {
        p=p->rchild;
    }
    return p;
}

//Successor of employee structure
struct Employees *InSucc(struct Employees *p)
{
    while(p && p->lchild!=NULL)
    {
        p=p->lchild;
    }
    return p;
}

//Display all employees
void displayem(struct Employees *p)
{
    if(p)
    {
        displayem(p->lchild);
        printf("%s\t%lld\t\t%lld\t%ld\t%s",p->name,p->phone_number,p->id,p->salary,p->city);
        printf("\n");
        displayem(p->rchild);
    }
}


//Searching employee
struct Employees * searchem(long long int id)
{
    struct Employees *t=firstem;
    printf("Name\tPhonenumber\tid\tsalary\tcity\n");
    while(t!=NULL)
    {
        // printf("0");
        if(id==t->id)
        {
            // printf("3");
            return t;
        }
        else if(id<(t->id))
        {
            // printf("1");
            t=t->lchild;
        }
        else
        {
            // printf("2");
            t=t->rchild;
        }
    }
    return NULL;
}

//Remove an employee
struct Employees *deleteem(struct Employees *p,long int salary, char *names, long long int id, long long int phonenumber, char *city)
{
    struct Employees *q=(struct Employees *) malloc (sizeof(struct Employees));
    if(p==NULL)
    {
        return NULL;
    }
    if(p->lchild==NULL && p->rchild==NULL)
    {
        if(p==firstem)
        {
            firstem=NULL;
        }
        free(p);
        return NULL;
    }
    if(id < p->id)
    {
        p->lchild=deleteem(p->lchild,salary,names,id,phonenumber,city);
    }
    else if(id > p->id)
    {
        p->rchild=deleteem(p->rchild,salary,names,id,phonenumber,city);
    }
    else
    {
        if(Height(p->lchild)>Height(p->rchild))
        {
            q=InPre(p->lchild);
            p->phone_number=q->phone_number;
            strcpy(p->name,q->name);
            p->id=q->id;
            p->salary=q->salary;
            strcpy(p->city,q->city);
            p->lchild=deleteem(p->lchild,q->salary,q->name,q->id,q->phone_number,q->city);
        }
        else
        {
            q=InSucc(p->rchild);
            p->phone_number=q->phone_number;
            strcpy(p->name,q->name);
            p->id=q->id;
            p->salary=q->salary;
            strcpy(p->city,q->city);
            p->rchild=deleteem(p->rchild,q->salary,q->name,q->id,q->phone_number,q->city);
        }
    }
    return p;
}



//Management of employees
void employees(struct Employees *firstem)
{
    long long int id;
    char name[25];
    long int salary;
    long long int phone_number;
    char city[30];
    int option;
    bool flag=true;
    while (flag)
    {
        printf("Enter 1---> to insert details of new employee\n");
        printf("Enter 2---> to display all employee\n");
        printf("Enter 3---> to search an employee\n");
        printf("Enter 4---> to Remove an employee\n");
        printf("Enter 5---> to exit employee management:\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            printf("Enter name: ");
            scanf("%s",&name);
            printf("Enter id: ");
            scanf("%lld",&id);
            printf("Enter salary: ");
            scanf("%ld",&salary);
            printf("Enter phone_number: ");
            scanf("%lld",&phone_number);
            printf("Enter city:");
            scanf("%s",&city);
            firstem = Insert(firstem,salary,name,id,phone_number,city);
            break;
        case 2:
            printf("Name\tPhonenumber\tid\tsalary\tcity\n");
            displayem(firstem);
            break;
        case 3:
            printf("Enter id: ");
            scanf("%lld",&id);
            // for (int i=0)
            tempem=searchem(id);
            if (tempem==NULL){
                printf("Not Found!");
                break;
            }
            printf("%s\t%lld\t\t%lld\t%ld\t%s",tempem->name,tempem->phone_number,tempem->id,tempem->salary,tempem->city);
            printf("\n");
            break;
        case 4:
            printf("Enter id: ");
            scanf("%lld",&id);
            tempem=searchem(id);
            deleteem(firstem,tempem->salary,tempem->name,tempem->id,tempem->phone_number,tempem->city);
            printf("Employee removed succesfully!!");
            printf("\n");
            break;
        case 5:
            flag=false;
            break;
        default: employees(firstem);
            break;
        }
    }
    
}

//Structure for machinery management
struct machineries
{
    char typefor[50];
    char thecity[50];
    long int billNo;
    struct machineries *next;
};


//To insert details of the new machine
void insert(long int billNo, char *typefor, char *thecity)
{
    if(head==NULL)
    {
        head = (struct machineries *)malloc(sizeof(struct machineries));
        head->billNo = billNo;
        strcpy(head->typefor,typefor);
        strcpy(head->thecity,thecity);
        head->next = NULL;
        arr[0] = head;
        arrIndex++;
    }
    else
    {
        struct machineries *newNode = (struct machineries *)malloc(sizeof(struct machineries));
        struct machineries *temp = head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        newNode->billNo = billNo;
        strcpy(newNode->typefor,typefor);
        strcpy(newNode->thecity,thecity);
        newNode->next = NULL;
        temp->next = newNode;
        arr[arrIndex] = newNode;
        arrIndex++;
    }
}

//Display all machineries
void displaymach(struct machineries *temp)
{
    printf("bill No ,It's type, City\n");
    while(temp!=NULL)
    {
        printf("%ld\t%s\t%s\n",temp->billNo,temp->typefor,temp->thecity);
        temp = temp->next;
    }
    printf("\n");
}

//Display machineries of specific industry
void displaycity(struct machineries *temp)
{
    char thecity[50];
    printf("Enter the city:");
    scanf("%s",&thecity);
    bool flag=true;
    while(temp!=NULL)
    {
        if (strcmp(temp->thecity,thecity)==0)
        {
            printf("%ld\t%s\n",temp->billNo,temp->typefor);
            flag=false;
            break;
        }
        temp = temp->next;
    }
    if (flag) printf("Machinery not found...");
    printf("\n\n");

}


//Management of machineries
void machineries()
{
    int option;
    long int billnumber;
    char typefor[50],thecity[50];
    bool flag=true;
    while (flag)
    {
        printf("Enter 1---> to insert new machine\n");
        printf("Enter 2---> view all machines\n");
        printf("Enter 3---> to view machines of particular industry\n"); 
        printf("Enter 4---> to exit: \n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            printf("Enter the bill number: ");
            scanf("%ld",&billnumber);
            printf("Enter it's type: ");
            scanf("%s",&typefor);
            printf("Enter the city: ");
            scanf("%s",&thecity);
            insert(billnumber,typefor,thecity);
            break;
        case 2:
            displaymach(head);
            break;
        case 3:
            displaycity(head);
            break;
        case 4:
            flag=false;
            break;
        default:
            break;
        }
    }
}

//Industry Management main function
int main()
{
    getstarted();
    firstem=(struct Employees *)malloc(sizeof(struct Employees));
    firstem->lchild = NULL;
    firstem->rchild = NULL;
    printf("Enter the name of the employee (Root): ");
    scanf("%s",&firstem->name);
    printf("Enter id : ");
    scanf("%lld",&firstem->id);
    printf("Enter salary: ");
    scanf("%ld",&firstem->salary);
    printf("Enter phone_number: ");
    scanf("%lld",&firstem->phone_number);
    printf("Enter city:  ");
    scanf("%s",&firstem->city);
    int option;
    bool flag=true;
    label:
    while (flag)
    {
        printf("Enter 1---> to manage employees\n");
        printf("Enter 2---> to manage machineries\n");
        printf("Enter 3---> to exit\n");
        scanf("%d",&option);
        switch (option)
        {
            case 1:
            employees(firstem);
            break;
            case 2:
            machineries();
            break;
            case 3:
            flag = false;
            return 0;
            break;
            default:
            break;
        }
    }
    goto label;
    return 0;
}