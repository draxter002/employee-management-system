#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define Username "Admin" 
#define Password "Admin" 

struct employee
{
    char name[20];
    int ID;
    int age;
    int phone_number;
    char address[20];
    double salary;
    struct employee *next;
} ; 

bool loginCheck(char name[15], char pass[15])
{
    if (strcmp(name, Username) == 0)
    {
        if (strcmp(pass, Password) == 0) 
        {
            return true; 
        }
    }
    else
    {
        return false; 
    }
}

void PrintFromFile()
{
    int i = 1;
    struct employee *temp_node;
    FILE *fp;
    temp_node = (struct employee *)malloc(sizeof(struct employee));
    if ((fp = fopen("Database.bin","rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    printf("\n\n                                         All Employee Details                                     \n\n");
    printf("| SL No  | Name         | ID       | Age    | Phone Number  | Address            | Salary       |\n\n");
    while (fread(temp_node, sizeof(*temp_node), 1, fp) == 1)
    {
        printf(" %d\t", i);
        printf(" %s\t", temp_node->name);
        printf(" %d\t\t", temp_node->ID);
        printf(" %d\t", temp_node->age);
        printf(" 0%d\t\t", temp_node->phone_number);
        printf(" %s\t\t", temp_node->address);
        printf(" %lf\t", temp_node->salary);
        i++;
    }
    fclose(fp);
}

void create_linked_list()
{
    FILE *fp;
    if ((fp = fopen("Database.bin", "ab")) == NULL)
    {
        printf("\nCan't open file\n");
        exit(1);
    }
    int n, i = 1;
    char name[20], address[20];
    int age, pnumber, id;
    double salary;
    printf("\nEnter number of Employee: ");
    scanf("%d", &n); 
    while (n--)
    {
        printf("\nEnter Details for Employee %d\n", i);
        printf("Enter Name: ");
        getchar();
        gets(name);
        printf("Enter ID: ");
        scanf("%d", &id);
        printf("Enter Age: ");
        scanf("%d", &age);
        printf("Enter Phone number: ");
        scanf("%d", &pnumber);
        printf("Enter Address: ");
        getchar();
        gets(address);
        printf("Enter Salary: ");
        scanf("%lf", &salary);
        struct employee *temp_node;
        temp_node = (struct employee *)malloc(sizeof(struct employee)); 
        strcpy(temp_node->name, name);
        temp_node->age = age;
        temp_node->ID = id;
        temp_node->phone_number = pnumber;
        strcpy(temp_node->address, address);
        temp_node->salary = salary;
        temp_node->next = NULL;
        fwrite(temp_node, sizeof(*temp_node), 1, fp);
        i++;
    }
    fclose(fp);
}

void insert_at_last()
{
    FILE *fp;
    if ((fp = fopen("Database.bin", "ab")) == NULL)
    {
        printf("\nCan't open file\n");
        exit(1);
    }
    char name[20], address[20];
    int age, pnumber, id;
    double salary;
    printf("Enter Details for Employee.\n");
    printf("Enter Name: ");
    getchar();
    gets(name);
    printf("Enter ID: ");
    scanf("%d", &id);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter Phone number: ");
    scanf("%d", &pnumber);
    printf("Enter Address: ");
    getchar();
    gets(address);
    printf("Enter Salary: ");
    scanf("%lf", &salary);
    struct employee *temp_node;
    temp_node = (struct employee *)malloc(sizeof(struct employee));
    strcpy(temp_node->name, name);
    temp_node->ID = id;
    temp_node->age = age;
    temp_node->phone_number = pnumber;
    strcpy(temp_node->address, address);
    temp_node->salary = salary;
    temp_node->next = NULL;
    fwrite(temp_node, sizeof(*temp_node), 1, fp);
    fclose(fp);
}

void delete_Employee_Record_by_name()
{
    char value[20];
    FILE *fp, *temp;
    int key;
    struct employee *myNode = (struct employee *)malloc(sizeof(struct employee));
    int flag = 0;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    if ((temp = fopen("Temp.bin", "wb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    printf("Enter Name: ");
    getchar();
    gets(value);
    while (fread(myNode, sizeof(*myNode), 1, fp) == 1)
    {
        if (strcmp(strlwr(myNode->name), strlwr(value)) == 0)
        {
            printf("\nDo you Really delete this Employee Record\n\n");
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n\n");
            printf("| \t%s", myNode->name);
            printf("| \t%d", myNode->ID);
            printf("| \t%d", myNode->age);
            printf("| \t0%d", myNode->phone_number);
            printf("| \t%s", myNode->address);
            printf("| \t%lf|\n", myNode->salary);
            printf("\n\nFor Delete this record (type 1): ");
            scanf("%d", &key);
            if (key == 1)
            {
                flag = 1;
            }
            else
            {
                fwrite(myNode, 1, sizeof(struct employee), temp);
                flag = 1;
            }
        }
        else
        {
            fwrite(myNode, 1, sizeof(struct employee), temp);
        }
    }
    if (flag == 0)
    { 

        printf("\nThis Name not found!\n");
    }
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}

void delete_Employee_Record_by_ID()
{
    int value, key;
    FILE *fp, *temp;
    struct employee *myNode = (struct employee *)malloc(sizeof(struct employee));
    int flag = 0;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    if ((temp = fopen("Temp.bin", "wb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    printf("Enter ID: ");
    scanf("%d", &value);
    while (fread(myNode, sizeof(*myNode), 1, fp) == 1)
    {
        if (myNode->ID == value)
        {
            printf("\nDo you Really delete this Employee Record\n\n");
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n\n");
            printf("| \t%s", myNode->name);
            printf("| \t%d", myNode->ID);
            printf("| \t%d", myNode->age);
            printf("| \t0%d", myNode->phone_number);
            printf("| \t%s", myNode->address);
            printf("| \t%lf|\n", myNode->salary);
            printf("\n\nFor Delete this record (type 1): ");
            scanf("%d", &key);
            if (key == 1)
            {
                flag = 1;
            }
            else
            {
                fwrite(myNode, 1, sizeof(struct employee), temp);
                flag = 1;
            }
        }
        else
        {
            fwrite(myNode, 1, sizeof(struct employee), temp);
        }
    }
    if (flag == 0) 
        printf("\nThis ID not found!\n");
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}

void search_Employee_By_Name()
{
    char value[20];
    struct employee *searchNode = (struct employee *)malloc(sizeof(struct employee));
    FILE *fp;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    int flag = 0; 
    printf("\nEnter name for search.\n");
    printf("----------------------\n");
    printf("\nSearch>> ");
    getchar();
    gets(value);
    system("CLS");
    printf("\n\n                                               Search Result.\n");
    printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n\n");
    while (fread(searchNode, sizeof(*searchNode), 1, fp) == 1)
    {
        if (strcmp(strlwr(searchNode->name), strlwr(value)) == 0)
        {
            printf("| \t%s", searchNode->name);
            printf("| \t%d", searchNode->ID);
            printf("| \t%d", searchNode->age);
            printf("| \t0%d", searchNode->phone_number);
            printf("| \t%s", searchNode->address);
            printf("| \t%lf|\n", searchNode->salary);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nEmployee not found for this (%s) name\n", value);
    }
}

void search_Employee_By_ID()
{
    int value;
    struct employee *searchNode = (struct employee *)malloc(sizeof(struct employee));
    FILE *fp;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    int flag = 0;
    printf("\nEnter ID for search.\n");
    printf("----------------------\n");
    printf("\nSearch>> ");
    scanf("%d", &value);
    system("CLS");
    printf("\n\n                                      Search Result.\n\n");
    printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
    while (fread(searchNode, sizeof(*searchNode), 1, fp) == 1)
    {
        if (searchNode->ID == value)
        {

            printf("| \t%s", searchNode->name);
            printf("| \t%d", searchNode->ID);
            printf("| \t%d", searchNode->age);
            printf("| \t0%d", searchNode->phone_number);
            printf("| \t%s", searchNode->address);
            printf("| \t%lf|\n", searchNode->salary);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nEmployee not found for this (%d) ID\n", value);
    }
}

void search_Employee_By_Age()
{
    struct employee *searchNode = (struct employee *)malloc(sizeof(struct employee));
    FILE *fp;
    int value;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    int flag = 0; 
    printf("\nEnter age for search.\n");
    printf("-----------------------\n");
    printf("\nSearch>> ");
    scanf("%d", &value);
    system("CLS");
    printf("\n\n                                      Search Result.\n\n");
    printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
    while (fread(searchNode, sizeof(*searchNode), 1, fp) == 1)
    {
        if (searchNode->age == value)
        {
            printf("| \t%s", searchNode->name);
            printf("| \t%d", searchNode->ID);
            printf("| \t%d", searchNode->age);
            printf("| \t0%d", searchNode->phone_number);
            printf("| \t%s", searchNode->address);
            printf("| \t%lf|\n", searchNode->salary);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nEmployee not found for this (%d) Age\n", value);
    }
}

void search_Employee_By_phone()
{
    struct employee *searchNode = (struct employee *)malloc(sizeof(struct employee));
    FILE *fp;
    int value;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    int flag = 0;
    printf("\nEnter phone number for search.\n");
    printf("\nEnter value: ");
    scanf("%d", &value);
    printf("\n\n                                      Search Result.\n\n");
    printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
    while (fread(searchNode, sizeof(*searchNode), 1, fp) == 1)
    {
        if (searchNode->phone_number == value)
        {

            printf("| \t%s", searchNode->name);
            printf("| \t%d", searchNode->ID);
            printf("| \t%d", searchNode->age);
            printf("| \t0%d", searchNode->phone_number);
            printf("| \t%s", searchNode->address);
            printf("| \t%lf|\n", searchNode->salary);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nEmployee not found for this (0%d) Phone number\n", value);
    }
}

void search_Employee_By_Place()
{
    char value[20]; 
    struct employee *searchNode = (struct employee *)malloc(sizeof(struct employee));
    FILE *fp;
    if ((fp = fopen("Database.bin", "rb")) == NULL)
    {
        printf("No such file\n");
        exit(1);
    }
    int flag = 0; 
    printf("\nEnter address for search.\n");
    printf("----------------------\n");
    printf("\nEnter value: ");
    getchar();
    gets(value);
    printf("\n\n                                      Search Result.\n\n");
    printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
    while (fread(searchNode, sizeof(*searchNode), 1, fp) == 1)
    {
        if (strcmp(strlwr(searchNode->address), strlwr(value)) == 0)
        {

            printf("| \t%s", searchNode->name);
            printf("| \t%d", searchNode->ID);
            printf("| \t%d", searchNode->age);
            printf("| \t0%d", searchNode->phone_number);
            printf("| \t%s", searchNode->address);
            printf("| \t%lf|\n", searchNode->salary);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("\nEmployee not found for this (%s) Place\n", value);
    }
}

void modify_Employee_Name()
{
    char name[20], Address[20];
    int age, pnumber, id, option;
    double salary;

    FILE *fp, *temp;
    fp = fopen("Database.bin", "rb");
    temp = fopen("Temp.bin", "wb");
    char old[20];     
    int pos = 0, key; 
    printf("\nEnter Name for modify: ");
    getchar();
    gets(old);
    struct employee *current = (struct employee *)malloc(sizeof(struct employee));
    struct employee *temp1 = (struct employee *)malloc(sizeof(struct employee));
    while (fread(current, sizeof(*current), 1, fp) == 1)
    {

        if (strcmp(current->name, old) == 0)
        {
            printf("\n%d this Name found employee.\n\n", old);
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
            printf("| \t%s", current->name);
            printf("| \t%d", current->ID);
            printf("| \t%d", current->age);
            printf("| \t0%d", current->phone_number);
            printf("| \t%s", current->address);
            printf("| \t%lf|\n", current->salary);
            printf("\nDo You want to Modify this Records?(1 = Yes, 2 = No)\n");
            printf("--------------------------------------------------------\n");
            scanf(" %d", &key);

            while (key == 1)
            {
                printf("\nChoose option for modify\n\n");
                printf("1. Name change.\n");
                printf("2. ID change\n");
                printf("3. Age change\n");
                printf("4. Phone Number change\n");
                printf("5. Salary change\n");
                printf("6. Address change\n");
                printf("7. Exit\n");
                printf("\nChange>> ");
                scanf(" %d", &option);
                if (option == 7)
                {
                    break;
                }

                switch (option)
                {
                case 1:
                    printf("Enter new Name: ");
                    getchar();
                    gets(name);
                    strcpy(current->name, name);
                    break;
                case 2:
                    printf("Enter new ID: ");
                    scanf("%d", &id);
                    current->ID = id;
                    break;
                case 3:
                    printf("Enter new Age: ");
                    scanf("%d", &age);
                    current->age = age;
                    break;
                case 4:
                    printf("Enter new Phone number: ");
                    scanf("%d", &pnumber);
                    current->phone_number = pnumber;
                    break;
                case 5:
                    printf("Enter new Salary: ");
                    scanf("%lf", &salary);
                    current->salary = salary;
                    break;
                case 6:
                    printf("Enter new Address: ");
                    getchar();
                    gets(Address);
                    strcpy(current->address, Address);
                    break;
                default:
                    printf("\nYou have to choose right option\n");
                    break;
                }
            }
            fwrite(current, 1, sizeof(*current), temp);
        }
        else
        {
            fwrite(current, 1, sizeof(*current), temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}

void modify_Employee_ID()
{
    char name[20], Address[20];
    int age, pnumber, id, option;
    double salary;
    FILE *fp, *temp;
    fp = fopen("Database.bin", "rb");
    temp = fopen("Temp.bin", "wb");
    int old;         
    int pos = 0, key; 
    printf("\nEnter ID for modify: ");
    scanf("%d", &old);
    struct employee *current = (struct employee *)malloc(sizeof(struct employee));
    struct employee *temp1 = (struct employee *)malloc(sizeof(struct employee));
    while (fread(current, sizeof(*current), 1, fp) == 1)
    {
        if (current->ID == old)
        {
            printf("\n%d this ID found employee.\n\n", old);
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
            printf("| \t%s", current->name);
            printf("| \t%d", current->ID);
            printf("| \t%d", current->age);
            printf("| \t0%d", current->phone_number);
            printf("| \t%s", current->address);
            printf("| \t%lf|\n", current->salary);
            printf("\nDo You want to Modify this Records?(1 = Yes, 2 = No)\n\n");

            scanf(" %d", &key);
            while (key == 1)
            {
                printf("\nChoose option for modify\n");
                printf("--------------------------\n");
                printf("1. Name change.\n");
                printf("2. ID change\n");
                printf("3. Age change\n");
                printf("4. Phone Number change\n");
                printf("5. Salary change\n");
                printf("6. Address change\n");
                printf("7. Exit\n");
                printf("\nChange>> ");
                scanf(" %d", &option);
                if (option == 7)
                {
                    break;
                }
                switch (option)
                {
                case 1:
                    printf("Enter new Name: ");
                    getchar();
                    gets(name);
                    strcpy(current->name, name);
                    break;
                case 2:
                    printf("Enter new ID: ");
                    scanf("%d", &id);
                    current->ID = id;
                    break;
                case 3:
                    printf("Enter new Age: ");
                    scanf("%d", &age);
                    current->age = age;
                    break;
                case 4:
                    printf("Enter new Phone number: ");
                    scanf("%d", &pnumber);
                    current->phone_number = pnumber;
                    break;
                case 5:
                    printf("Enter new Salary: ");
                    scanf("%lf", &salary);
                    current->salary = salary;
                    break;
                case 6:
                    printf("Enter new Address: ");
                    getchar();
                    gets(Address);
                    strcpy(current->address, Address);
                    break;
                default:
                    printf("\nYou have to choose right option\n");
                    break;
                }
            }
            fwrite(current, 1, sizeof(*current), temp);
        }
        else
        {
            fwrite(current, 1, sizeof(*current), temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}

void modify_Employee_Age()
{
    char name[20], Address[20];
    int age, pnumber, id, option;
    double salary;
    FILE *fp, *temp;
    fp = fopen("Database.bin", "rb");
    temp = fopen("Temp.bin", "wb");
    int old;  
    int pos = 0, key; 
    printf("\nEnter Age for modify: ");
    scanf("%d", &old);
    struct employee *current = (struct employee *)malloc(sizeof(struct employee));
    struct employee *temp1 = (struct employee *)malloc(sizeof(struct employee));
    while (fread(current, sizeof(*current), 1, fp) == 1)
    {
        if (current->age == old)
        {
            printf("\n%d this Age found employee.\n\n", old);
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
            printf("| \t%s", current->name);
            printf("| \t%d", current->ID);
            printf("| \t%d", current->age);
            printf("| \t0%d", current->phone_number);
            printf("| \t%s", current->address);
            printf("| \t%lf|\n", current->salary);
            printf("\nDo You want to Modify this Records?(1 = Yes, 2 = No)\n\n");
            scanf(" %d", &key);
            while (key == 1)
            {
                printf("\nChoose option for modify\n");
                printf("--------------------------\n");
                printf("1. Name change.\n");
                printf("2. ID change\n");
                printf("3. Age change\n");
                printf("4. Phone Number change\n");
                printf("5. Salary change\n");
                printf("6. Address change\n");
                printf("7. Exit\n");
                printf("\nChange>> ");
                scanf(" %d", &option);
                if (option == 7)
                {
                    break;
                }
                switch (option)
                {
                case 1:
                    printf("Enter new Name: ");
                    getchar();
                    gets(name);
                    strcpy(current->name, name);
                    break;
                case 2:
                    printf("Enter new ID: ");
                    scanf("%d", &id);
                    current->ID = id;
                    break;
                case 3:
                    printf("Enter new Age: ");
                    scanf("%d", &age);
                    current->age = age;
                    break;
                case 4:
                    printf("Enter new Phone number: ");
                    scanf("%d", &pnumber);
                    current->phone_number = pnumber;
                    break;
                case 5:
                    printf("Enter new Salary: ");
                    scanf("%lf", &salary);
                    current->salary = salary;
                    break;
                case 6:
                    printf("Enter new Address: ");
                    getchar();
                    gets(Address);
                    strcpy(current->address, Address);
                    break;
                default:
                    printf("\nYou have to choose right option\n");
                    break;
                }
            }
            fwrite(current, 1, sizeof(*current), temp);
        }
        else
        {
            fwrite(current, 1, sizeof(*current), temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}

void modify_Employee_pnumber()
{
    char name[20], Address[20];
    int age, pnumber, id, option;
    double salary;
    FILE *fp, *temp;
    fp = fopen("Database.bin", "rb");
    temp = fopen("Temp.bin", "wb");
    int old;    
    int pos = 0, key; 
    printf("\nEnter Phone Number for modify: ");
    scanf("%d", &old);
    struct employee *current = (struct employee *)malloc(sizeof(struct employee));
    struct employee *temp1 = (struct employee *)malloc(sizeof(struct employee));
    while (fread(current, sizeof(*current), 1, fp) == 1)
    {
        if (current->phone_number == old)
        {
            printf("\n%d this Phone Number found employee.\n\n", old);
            printf("| Name               | ID       | Age    | Phone Number  | Address            | Salary       |\n");
            printf("| \t%s", current->name);
            printf("| \t%d", current->ID);
            printf("| \t%d", current->age);
            printf("| \t0%d", current->phone_number);
            printf("| \t%s", current->address);
            printf("| \t%lf|\n", current->salary);
            printf("\nDo You want to Modify this Records?(1 = Yes, 2 = No)\n");
            scanf(" %d", &key);
            while (key == 1)
            {
                printf("\nChoose option for modify\n");
                printf("--------------------------\n");
                printf("1. Name change.\n");
                printf("2. ID change\n");
                printf("3. Age change\n");
                printf("4. Phone Number change\n");
                printf("5. Salary change\n");
                printf("6. Address change\n");
                printf("7. Exit\n");
                printf("\nChange>> ");
                scanf(" %d", &option);
                if (option == 7)
                {
                    break;
                }
                switch (option)
                {
                case 1:
                    printf("Enter new Name: ");
                    getchar();
                    gets(name);
                    strcpy(current->name, name);
                    break;
                case 2:
                    printf("Enter new ID: ");
                    scanf("%d", &id);
                    current->ID = id;
                    break;
                case 3:
                    printf("Enter new Age: ");
                    scanf("%d", &age);
                    current->age = age;
                    break;
                case 4:
                    printf("Enter new Phone number: ");
                    scanf("%d", &pnumber);
                    current->phone_number = pnumber;
                    break;
                case 5:
                    printf("Enter new Salary: ");
                    scanf("%lf", &salary);
                    current->salary = salary;
                    break;
                case 6:
                    printf("Enter new Address: ");
                    getchar();
                    gets(Address);
                    strcpy(current->address, Address);
                    break;
                default:
                    printf("\nYou have to choose right option\n");
                    break;
                }
            }
            fwrite(current, 1, sizeof(*current), temp);
        }
        else
        {
            fwrite(current, 1, sizeof(*current), temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Database.bin");
    rename("Temp.bin", "Database.bin");
}
void printLogo()
{
    printf("  EMPLOYMENT MANAGEMNET SYSTEM   \n");
    printf("CREATED BY:-----------------");
    printf("\nNAME              ENROLLMENT NUMBER");
    printf("\nAGNIK PAUL        23103170");
    printf("\nAYUSH JINDAL      23103162");
    printf("\nAMAN SINGH        23103153");
    printf("\n\n");
}

int main()
{
    int option, option1, option2, option3, option4; 
    char name[15], pass[15], name1[20];
    double salary;
    system("CLS");
    printLogo(); 
    while (1)
    {
        printf("You need to login first.\n");
        printf("Username: ");
        gets(name); 
        printf("Password: ");
        gets(pass);             
        if (loginCheck(name, pass))
        {
            while (1)
            {
                printf("\nSelect Your Option From Menu.\n\n");
                printf("1.Add New\n2.List\n3.Exit\n4.Modify\n5.Search\n6.Delete\n");
                scanf("%d", &option); 
                switch (option)
                {
                case 1:
                    system("cls");
                    printf("\nChoose Option.\n");
                    printf("--------------\n");
                    printf("1.Add Many Employee\n");
                    printf("2.Add Employee\n");
                    printf("3.Back\n");
                    printf("\nAdd New>> ");
                    scanf("%d", &option1); 
                    switch (option1)
                    {
                    case 1:
                        create_linked_list();
                        break;
                    case 2:
                        insert_at_last();
                        break;
                    case 3:
                        break;
                    default:
                        printf("You Need to select valid option\n");
                        break;
                    }
                    break;
                case 2:
                    system("cls");
                    PrintFromFile();
                    break;
                case 3:
                    exit(0);
                    break;
                case 4:
                    system("cls");
                    printf("\nChoose Option.\n");
                    printf("--------------\n");
                    printf("1.Modify by Name.\n");
                    printf("2.Modify by ID.\n");
                    printf("3.Modify by Age.\n");
                    printf("4.Modify by Phone Number.\n");
                    printf("5.Back\n");
                    printf("\nModify>> ");
                    scanf("%d", &option3);
                    if (option3 == 5)
                    {
                        break;
                    }
                    switch (option3)
                    {
                    case 1:
                        system("CLS");
                        modify_Employee_Name();
                        break;
                    case 2:
                        modify_Employee_ID();
                        break;
                    case 3:
                        modify_Employee_Age();
                        break;
                    case 4:
                        modify_Employee_pnumber();
                        break;
                    case 5:
                        break;
                    default:
                        printf("\nYou need to choose currect option.\n");
                        break;
                    }
                    break;
                case 5:
                    system("cls");
                    printf("\nChoose your Searching Option.\n");
                    printf("1.Search by Name\n");
                    printf("2.Search by ID\n");
                    printf("3.Search by Age\n");
                    printf("4.Search by Phone Number\n");
                    printf("5.Search by Place\n");
                    printf("6.Back\n");
                    printf("\nInput ");
                    scanf("%d", &option2);
                    switch (option2) 
                    {
                    case 1:
                        search_Employee_By_Name();
                        break;
                    case 2:
                        search_Employee_By_ID();
                        break;
                    case 3:
                        search_Employee_By_Age();
                        break;
                    case 4:
                        search_Employee_By_phone();
                        break;
                    case 5:
                        search_Employee_By_Place();
                        break;
                    case 6:
                        break;
                    default:
                        printf("You have to choose right option\n");
                        break;
                    }
                    break;
                case 6:
                    system("cls");
                    printf("\nChoose your Delete Option.\n");
                    printf("1.Delete by Name\n");
                    printf("2.Delete by ID\n");
                    printf("3.Back\n");
                    printf("\nDelete>> ");
                    scanf("%d", &option4);
                    switch (option4)
                    {
                    case 1:
                        delete_Employee_Record_by_name();
                        break;
                    case 2:
                        delete_Employee_Record_by_ID();
                        break;
                    case 3:
                        break;
                    default:
                        printf("You have to choose right option\n");
                        break;
                    }
                    break;
                default:
                    printf("You Need to choose option into 1-6\n");
                    break;
                }
            }
            break;
        }
    }
    return 0;
}