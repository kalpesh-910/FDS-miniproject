#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int d;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

struct node *createmenu(struct node *head, int d, char foodname[25], float price);
struct node *createorder(struct node *head, int d, int quantity);
void displayMenu(struct node *head);
void displayOrder(struct node *head);
struct node *totalsales(int d, int quantity);
void calculatetotsales();
struct node *delete (int dt, struct node *head, struct node *tail);
struct node *deleteM(int dt, struct node *head, struct node *tail);
int deleteMenu();
int deleteOrder();
void displaybill();
struct node *deleteList(struct node *head);
void Manager();
void customer();

int main()
{
    heada = createmenu(heada, 101, "Cheese-Pizza", 330);
    heada = createmenu(heada, 102, "Special-Pav-Bhaji", 210);
    heada = createmenu(heada, 103, "Manchurian-Noodles", 400);
    heada = createmenu(heada, 104, "Cheese-Burger", 250);
    heada = createmenu(heada, 105, "Cherry-Pineapple", 350);

    struct node *temp = heada;

    FILE *fp;
    fp = fopen("Menu.txt", "w");
    if (fp == NULL)
        printf("\nError");
    else
    {
        while (temp != NULL)
        {
            fprintf(fp, "%d \t%s \t%f\n", temp->d, temp->foodname, temp->price);
            temp = temp->next;
        }
    }
    fclose(fp);
    int choice;
    do
    {
        printf("\n=========================================================\n");
        printf("           WELCOME TO TAJ HOTEL\n");
        printf("==========================================================\n\n\n");
        printf("          1. MANAGER SECTION   \n");
        printf("          2. CUSTOMER SECTION \n");
        printf("          3. Exit \n\n");
        printf("          Enter Your Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Manager();
            break;

        case 2:
            customer();
            break;

        case 3:
            printf("          *THANK YOU FOR VISITING*\n");
            break;

        default:
            printf("          Wrong Input, Choose valid option\n");
            break;
        }
    } while (choice != 3);
}

struct node *createmenu(struct node *head, int d, char foodname[25], float price)
{

    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->d = d;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->foodname, foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = heada;

    if (temp == NULL)
        heada = taila = newnode;
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node *createorder(struct node *head, int d, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->d == d)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newnode->d = d;
        newnode->price = quantity * (temp1->price);
        newnode->quantity = quantity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if (temp == NULL)
            headc = tailc = newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        printf("          This item is not present in the menu!\n");
    }

    return headc;
}

void displayMenu(struct node *head)
{
    int da;
    float price;
    char name[100];
    FILE *fp;
    fp = fopen("Menu.txt", "r");
    int n = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %f", &da, name, &price);
        n++;
    }
    rewind(fp);

    printf("\n");
    printf("        Sr.no.\t    FoodName  \t       Rate\n");
    printf("     -----------------------------------------------------\n");
    if (fp == NULL)
        printf("\nError");
    else
        for (int i = 0; i < n - 1; i++)
        {
            fscanf(fp, "%d %s %f", &da, name, &price);
            printf("          %d\t%s     \t%0.2f\n", da, name, price);
        }
    fclose(fp);
}

void displayOrder(struct node *head)
{
    struct node *temp1 = head;
    if (temp1 == NULL)
    {
        printf("\n          List is empty!!\n\n");
    }
    else
    {
        printf("\n");
        printf("        Sr.no.\t    FoodName  \t    Quantity\tRate\n");
        printf("     -----------------------------------------------------\n");
        

        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                printf("          %d\t%s     \t%0.2f\n", temp1->d, temp1->foodname, temp1->price);
            else
            {
                printf("          %d\t%s     \t%d     \t%0.2f\n", temp1->d, temp1->foodname, temp1->quantity, temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }
}

struct node *totalsales(int d, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while (temp1->d != d)
    {
        temp1 = temp1->next;
    }

    newnode->d = d;
    newnode->price = quantity * (temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->d == d)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalsales(temp->d, temp->quantity);
        temp = temp->next;
    }
}

struct node *delete (int dt, struct node *head, struct node *tail)
{
    int a;
    if (head == NULL)
    {
        printf("\n          List is empty\n");
    }
    else
    {
        struct node *temp;
        if (dt == head->d)
        {
            temp = head;
            if (head != NULL && head->quantity == 1)
            {
                head = head->next;
                head->prev = NULL;
                free(temp);
            }
            (head->quantity)--;
        }
        else if (dt == tail->d)
        {
            temp = tail;
            if (tail->quantity == 1)
            {
                tail = tail->prev;
                tail->next = NULL;
                free(temp);
            }
            (tail->quantity)--;
        }
        else
        {
            temp = head;
            while (dt != temp->d)
            {
                temp = temp->next;
            }
            if (temp->quantity == 1)
            {
                (temp->prev)->next = temp->next;
                (temp->next)->prev = temp->prev;
                free(temp);
            }

            (temp->quantity)--;
        }
    }
    return head;
}

struct node *deleteM(int dt, struct node *head, struct node *tail)
{
    int a;
    if (head == NULL)
    {
        printf("\n          List is empty\n");
    }
    else
    {
        struct node *temp;
        if (dt == head->d)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
            {
                head->prev = NULL;
                free(temp);
            }
        }
        else if (dt == tail->d)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (dt != temp->d)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteMenu()
{
    printf("\n          Enter serial no. of the food item which is to be deleted: ");

    int num;
    int a = 0;
    scanf("%d", &num);
    struct node *temp = heada;
    while (temp != NULL)
    {
        if (temp->d == num)
        {
            heada = deleteM(num, heada, taila);
            a = 1;
            break;
        }
        temp = temp->next;
    }

    char nm[100];
    int t = 0;
    int dat;
    float p;
    FILE *fp, *ft;
    fp = fopen("Menu.txt", "r");
    ft = fopen("data1.txt", "wb+");
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %f", &dat, nm, &p);
        t++;
    }
    rewind(fp);
    for (int i = 0; i < t - 1; i++)
    {
        fscanf(fp, "%d %s %f", &dat, nm, &p);

        if (dat != num)
        {
            fprintf(ft, "%d\t %s\t %f\n", dat, nm, p);
        }
    }

    fclose(fp);
    fclose(ft);
    remove("Menu.txt");
    rename("data1.txt", "Menu.txt");

    if (a == 1)
        return 1;
    return 0;
}

int deleteOrder()
{

    int num, Qty;
    printf("\n          Enter serial no. of the food item which is to be deleted: ");
    scanf("%d", &num);
    printf("\n          Enter quantity want to delete : ");
    scanf("%d", &Qty);

    struct node *temp = headc;
    while (temp != NULL)
    {
        if (temp->d == num)
        {
            if (temp->quantity == Qty)
            {
                headc = delete (num, headc, tailc);
            }
            else
            {
                temp->quantity = temp->quantity - Qty;
                temp->price = temp->price - (temp->price / Qty);
            }
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaybill()
{
    displayOrder(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp != NULL)
    {
        total_price += temp->price;
        temp = temp->next;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("\n          Price :-\t\t %0.02f       \n", total_price);
    float gst = (((105 * total_price) / 100) - total_price);
    printf("          Additional GST :-\t %.2f\n", gst);
    printf("          -------------------------------\n");
    printf("           Total Price :-\t %.2f\n", gst + total_price);
    printf("          -------------------------------\n");
}

struct node *deleteList(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void Manager()
{
    printf("\n----------------------------------------------\n");
    printf("          MANAGER SECTION\n");
    printf("----------------------------------------------\n");
    while (1)
    {
        printf("\n        1. View total sales\n");
        printf("          2. Add new items in the order menu\n");
        printf("          3. Delete items from the order menu\n");
        printf("          4. Display order menu\n");
        printf("          5. Back To Main Menu \n\n");
        printf("          Enter Your Choice : ");

        int opt;
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            printf("\n======================= Total Sales =======================\n");

            displayOrder(head_s);
            break;
        case 2:

            printf("\n          Enter serial no. of the food item: ");
            int num, flag = 0;
            char name[50];
            float price;
            scanf("%d", &num);

            struct node *temp = heada;

            while (temp != NULL)
            {
                if (temp->d == num)
                {
                    printf("\n          Food item with given serial number already exists!!\n\n");
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }

            if (flag == 1)
                break;

            printf("          Enter food item name: ");
            scanf("%s", name);
            printf("          Enter price: ");
            scanf("%f", &price);
            heada = createmenu(heada, num, name, price);

            FILE *fp;
            fp = fopen("Menu.txt", "a");
            if (fp == NULL)
                printf("\nError");
            else
                fprintf(fp, "%d \t%s \t%f\n", num, name, price);
            printf("\n          New food item added to the list!!\n\n");
            fclose(fp);
            break;
        case 3:
            if (deleteMenu())
            {
                printf("\n======================= Updated list of food items menu =======================\n");
                displayMenu(heada);
            }
            else
                printf("\n          Food item with given serial number doesn't exist!\n\n");

            break;
        case 4:
            printf("\n======================== Order menu ========================\n");
            displayMenu(heada);
            break;

        default:
            printf("\n          Wrong Input !! PLease choose valid option\n");
            break;
        }
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch,l;
    printf("\n----------------------------------------------\n");
    printf("              CUSTOMER SECTION\n");
    printf("----------------------------------------------\n");
    int opt;
    do
    {
        printf("\n          1. Place your order\n");
        printf("          2. View your ordered items\n");
        printf("          3. Delete an item from order\n");
        printf("          4. Display final bill\n");
        printf("          5. Back To Main Menu \n\n");
        printf("          Enter Your Choice : ");
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            do{
            displayMenu(heada);
            printf("\n          Enter number corresponding to the item you want to order: ");
            int n;
            scanf("%d", &n);
            printf("          Enter quantity: ");
            int quantity;
            scanf("%d", &quantity);
            headc = createorder(headc, n, quantity);
            printf("          Do you want to continue your order (y/n) : ");
            scanf(" %c",&l);
            }while(l!='n');
            break;
        case 2:
            printf("\n========================== List of ordered items =========================\n");
            displayOrder(headc);
            break;
        case 3:
            if (deleteOrder())
            {
                printf("\n====================== Updated list of your ordered food items ========================\n");
                displayOrder(headc);
            }
            else
                printf("\n          Food item with given serial number doesn't exist!!\n");
            break;
        case 4:
            calculatetotsales();
            printf("\n=========================== Final Bill ================================\n");
            displaybill();
            headc = deleteList(headc);
            printf("\n          Press any key to return to main menu:");
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;
        case 5:
            break;
        default:
            printf("\n          Wrong Input !! PLease choose valid option\n");
            break;
        }
        if (flag == 1)
            break;
    } while (opt != 5);
}