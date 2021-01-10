
//////*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//////*******************************Fundamentals of programming, first semester project*******************************/
////************************************************Mask application**************************************************/
////********************************************Developed and designed by:*******************************************/
//*************************************************~#Alireza Mirzaei#~**********************************************/
//*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define strSize 45
#define true 1
#define false 0
int shopUsercount = 1, normalUsercount = 1;
char username[strSize], pass1[strSize], pass2[strSize];

//Structures (DEFINED GLOBALLY)
struct users
{
    //Shared
    char user_type[strSize];
    char user_name[strSize];
    char passwd[strSize];
    char fname[strSize];
    char lname[strSize];
    char email[strSize];
    long int codeMelli;
    //Admin only!
    char TFAQ01[2 * strSize];
    char TFAA01[2 * strSize];
    char TFAQ02[2 * strSize];
    char TFAA02[2 * strSize];
    //Normal only
    char bloodG[4];
    int age;
    int height;
    int weight;
    int test_score;
    int test_counter;
    int health_code;
    int test_score_history[1000];
    time_t test_time_history[1000];
    //Shop only
    int disinfection;
    int mantaghe;
    char store_name[strSize];
    char cityName[strSize];
};
struct users admin;
struct users normalUser[100];
struct users shopUser[100];

//Function prototypes
void welcome();

//Menus
void main_menu();
void help_mm();
void command_mm();
void signup_menu();
void forgot_passwd();
bool Question1();
bool Question2();

//login
void login();
int findUsernormal(char un[]);
int findUsershop(char un[]);

//Signup
void signupNorm();
void signupShop();
void getPasswd(char pass[]);
int codemelli_check(long int code);

//pages
void admin_page();
void normal_page(int UN);
void shop_page(int UN);
void health_test(int *score);
void healthCode(int user_number);
void choice_check(char choice[]);
void edit_info(char ut, int index);

// Main Driver Program
// Mostly users info
int main()
{
    //Program Start
    //Creating admin account
    strcpy(admin.user_name, "admin");
    strcpy(admin.passwd, "adminadmin");
    strcpy(admin.user_type, "admin");
    strcpy(admin.email, "noneofyourbzness@nobz.com");
    strcpy(admin.fname, "Alireza");
    strcpy(admin.lname, "Mirzaei");
    strcpy(admin.TFAQ01, "Who was your first grade teacher?");
    strcpy(admin.TFAA01, "Mrs."); //Alakia!
    strcpy(admin.TFAQ02, "What is your NEXT laptop?");
    strcpy(admin.TFAA02, "A MBA13.3'");
    admin.codeMelli = 1098273645;

    //Creating the default user
    strcpy(normalUser[0].fname, "alireza");
    strcpy(normalUser[0].lname, "mirzaei");
    strcpy(normalUser[0].email, "alirezamirzaei68@gmail.com");
    strcpy(normalUser[0].bloodG, "A+");
    strcpy(normalUser[0].cityName, "Esfahan");
    strcpy(normalUser[0].user_name, "alirezam68");
    strcpy(normalUser[0].passwd, "alirezaalireza");
    strcpy(normalUser[0].user_type, "normal");
    normalUser[0].age = 18;
    normalUser[0].height = 180;
    normalUser[0].weight = 76;            //??!?!?!?
    normalUser[0].codeMelli = 3648273382; //None of ur business!
    normalUser[0].test_score = 0;
    normalUser[0].health_code = 0;

    //Creating the default seller
    strcpy(shopUser[0].user_type, "shop");
    strcpy(shopUser[0].fname, "reza");
    strcpy(shopUser[0].lname, "karimi");
    strcpy(shopUser[0].user_name, "rezakarimi");
    strcpy(shopUser[0].passwd, "Karimi_1_Reza");
    strcpy(shopUser[0].email, "RK_Shop@gmail.com");
    strcpy(shopUser[0].store_name, "RK_shop");
    strcpy(shopUser[0].cityName, "New York");
    shopUser[0].mantaghe = 2;
    shopUser[0].codeMelli = 1234567890;
    shopUser[0].disinfection = 0; //false
    welcome();
    sleep(2);
    main_menu();
}

//Functions body
//Welcome and main menu section
void welcome()
{

    printf("\t\t\t\t\t\t\t       \e[36;1mWelcome to MASK!\n\n\e[0m");
    sleep(2);
    printf("\t\t\t\t\t    >>>>>>>>    \e[1;32mDeveloped By : Alireza Mirzaei\e[0m     <<<<<<<<\n");
    sleep(2);
}

void main_menu()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    sleep(1);
    puts("\e[21;24;36mMain Menu\e[0m  \n\n\e[31;1mlogin(1)\e[0m || \e[32;1msign up(2)\e[0m || \e[33;1mforgot password(3)\e[0m || \e[34;1mhelp(4)\e[0m || \e[1mexit(0)\e[0m");
    printf("\n>> ");
    command_mm();
}

//Helps
void help_mm()
{
    puts("\e[46;30mHelp for : Main menu\r"); //Help for main menu
    puts("To login to your account, type login\r");
    puts("To sign up, type signup\r");
    puts("If you've forgotten your password, type password recovery/forgot password\r\e[0m");
}

//Commands
void command_mm()
{
    char command[strSize];
    fgets(command, strSize, stdin);
    switch (command[0])
    {
    case 'l':
    case 'L':
    case '1':
        login();
        break;
    case 's':
    case 'S':
    case '2':
        signup_menu();
        break;
    case 'P':
    case 'p':
    case 'f':
    case 'F':
    case '3':
        forgot_passwd();
        break;
    case 'h':
    case 'H':
    case '4':
        help_mm();
        puts("\nPress a key");
        getchar();
        main_menu();
        break;
    case 'e':
    case 'E':
    case '0':
        _exit(0);
    default:
        printf("Enter a valid input please \n>> ");
        command_mm();
    }
}

void getPasswd(char passwd[])
{
    scanf("%s", passwd);
    // int cnt = 0;
    // while (1)
    // {
    //     passwd[cnt] = getch();
    //     if (passwd[cnt] == '\177')
    //     {
    //         printf("\b\b");
    //         cnt--;
    //     }
    //     else if (passwd[cnt] != '\177' || passwd[cnt] != '\n')
    //     {
    //         printf("*");
    //         cnt++;
    //     }
    //     else if (passwd[cnt] == '\10')
    //         break;
    // }
    // passwd[cnt] = '\0';
    // printf("%s", passwd);
}

//Login_section
void login()
{
    sleep(1);
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    puts("\e[33;1mNote that You CANNOT login to a user which is not yet created\e[0m");
    printf("Username(type return/-1 to go back): ");
    scanf("%s", username);
    getchar();
    int uni = findUsernormal(username), ushi = findUsershop(username);
    if (!strcmp(username, "return") || !strcmp(username, "Return") || !strcmp(username, "-1"))
    {
        puts("\nReturning to main menu ...");
        sleep(1);
        main_menu();
    }
    else if ((uni == -1) && (ushi == -1) && strcmp(username, admin.user_name))
    {
        puts("\nUser name not found, Please try again"); //back to login
        sleep(2);
        printf("\e[1;1H\e[2J");
        fflush(stdout);
        login();
    }
    //Admin login
    else if (!strcmp(admin.user_name, username))
    {
        printf("Password: ");
        getPasswd(pass1);
        if (!strcmp(admin.passwd, pass1))
        {
            puts("\n\e[32;1;24mLogin successful, Welcome to your account!\e[0m");
            sleep(1);
            admin_page();
        }
        else
        {
            puts("\nIncorrect password, Please login again!"); //back to admin login
            sleep(2);
            printf("\e[1;1H\e[2J");
            fflush(stdout);
            login();
        }
    }
    //Normal Login
    else if (uni != -1)
    {
        printf("Password: ");
        getPasswd(pass1);
        if (!strcmp(normalUser[uni].passwd, pass1))
        {
            puts("\n\e[32;1;24mLogin successful, Welcome to your account!\e[0m");
            sleep(1);
            normal_page(uni);
        }
        else
        {
            puts("\nIncorrect password, Please login again!"); //back to login
            sleep(2);
            printf("\e[1;1H\e[2J");
            fflush(stdout);
            login();
        }
    }
    else if (ushi != -1)
    {
        printf("Password: ");
        getPasswd(pass1);
        if (!strcmp(shopUser[ushi].passwd, pass1))
        {
            puts("\n\e[32;1;24mLogin successful, Welcome to your account!\e[0m");
            sleep(1);
            shop_page(ushi);
        }
        else
        {
            puts("\nIncorrect password, Please login again!"); //back to login
            sleep(1);
            printf("\e[1;1H\e[2J");
            fflush(stdout);
            login();
        }
    }
}

int findUsernormal(char username[])
{
    for (int i = 0; i < normalUsercount; i++)
        if (!strcmp(normalUser[i].user_name, username))
            return i;
    return -1;
}

int findUsershop(char username[])
{
    for (int i = 0; i < shopUsercount; i++)
        if (!strcmp(shopUser[i].user_name, username))
            return i;
    return -1;
}

//Pages_section
//Admin_page
void admin_page()
{
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t\t\t\t\e[1;32mHi %s %s, Welcome to your account\n\e[0m", admin.fname, admin.lname);
    puts("\e[1mEnter desired command(number only) to proceed.(NA = not yet available)\e[0m");
    puts("\e[34m1. Add a Hospital(NA)");
    puts("2. See statistics(NA)");
    puts("3. Edit users health info(NA)");
    puts("4. See all users(NA)");
    puts("5. Show the list of deaths(NA)");
    puts("6. List of registered shops(NA)");
    puts("7. List of all registered hospitals(NA)");
    puts("8. Edit your information");
    puts("9. Logout");
    puts("0. Exit the program\e[0m");
    printf(">> ");
    int choice;
    scanf("%d", &choice);
    while (choice < 0 || choice > 9)
    {
        printf("\n Wrong choice, Enter again..\n");
        printf(">> ");
        scanf("%d", &choice);
    }
    switch (choice)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        printf("\nCommand not available, enter again.");
        sleep(1);
        getchar();
        admin_page();
        break;
    case 8:
        edit_info('a', 0);
        break;
    case 9:
        printf("\n\e[1mReturning to main menu...\e[0m");
        sleep(1);
        printf("\e[1;1H\e[02J");
        getchar();
        main_menu();
        break;
    case 0:
        exit(0);
    default:
        printf("\nCommand not valid, enter again.");
        sleep(1);
        getchar();
        admin_page();
        break;
    }
}

//normal_page
void normal_page(int index)
{
    int sth = normalUser[index].test_counter;
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t\e[1;32mHi %s %s, Welcome to your account\n\e[0m", normalUser[index].fname, normalUser[index].lname);
    printf("\nHealth Status: ");
    healthCode(index);
    puts("\n");
    puts("\e[1m\nEnter desired command(number only) to proceed.(NA = not yet available)\e[0m");
    puts("\e[34m1. Edit info");
    puts("2. Give health test");
    puts("3. See a history of your tests");
    puts("4. Register a visit to other users");
    puts("5. History of visits");
    puts("6. Register a place you've recently been to");
    puts("7. See history of visited locations");
    puts("8. See covid-19 statistics(NA)");
    puts("9. Find nearby hospitals(NA)");
    puts("10. Logout");
    puts("0. Exit the program\e[0m");
    printf(">> ");
    int choice;
    scanf("%d", &choice);
    while (choice < 0 || choice > 10)
    {
        printf("\n Wrong choice, Enter again..\n");
        printf(">> ");
        scanf("%d", &choice);
    }
    switch (choice)
    {
    case 1:
        edit_info('n', index);
        break;
    case 2:
        health_test(&normalUser[index].test_score);
        normalUser[index].test_score_history[normalUser[index].test_counter] = normalUser[index].test_score;
        normalUser[index].test_time_history[normalUser[index].test_counter] = time(NULL);
        if (normalUser[index].test_score <= 15)
            normalUser[index].health_code = 1;
        else if (normalUser[index].test_score > 15 && normalUser[0].test_score <= 50)
            normalUser[index].health_code = 2;
        else if (normalUser[index].test_score > 50 && normalUser[0].test_score <= 75)
            normalUser[index].health_code = 3;
        else if (normalUser[index].test_score > 75 && normalUser[0].test_score <= 100)
            normalUser[index].health_code = 4;
        sleep(1);
        printf("\e[1;1H\e[2J");
        normalUser[index].test_counter++;
        normal_page(index);
        break;
    case 3:
        if (sth)
        {
            for (int i = 0; i < sth; i++)
                if (i < 10)
                    printf("Test number %d\nTaken at %sresult: %d/100\n~~~~~~~~~~~~~~~~~~~~~\n", i + 1, asctime(localtime(&normalUser[index].test_time_history[i])), normalUser[index].test_score_history[i]);
                else
                    break;
            sleep(4);
            normal_page(index);
        }
        else
        {
            printf("You have not taken the test yet!\n");
            sleep(2);
            normal_page(index);
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        printf("\nCommand not available, enter again.");
        sleep(1);
        getchar();
        normal_page(index);
        break;
    case 10:
        printf("\n\e[1mReturning to main menu...\e[0m");
        sleep(1);
        printf("\e[1;1H\e[02J");
        getchar();
        main_menu();
        break;
    case 0:
        exit(0);
        break;
    default:
        printf("\nCommand not valid, enter again.");
        sleep(1);
        getchar();
        normal_page(index);
        break;
    }
}

//shop_page
void shop_page(int index)
{
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t \e[1;32mHi %s %s, Welcome to your account\n\e[0m", shopUser[index].fname, shopUser[index].lname);
    puts("\e[1mYour Store has not been disinfected, but your store status is white\e[0m");
    puts("\e[1mEnter desired command(number only) to proceed.(NA = not yet available)\e[0m");
    puts("\e[34m1. Your stores status");
    puts("2. Report disinfection");
    puts("3. See the status of the users who've come to your store(NA)");
    puts("4. Logout");
    puts("0. Exit the program\e[0m");
    printf(">> ");
    int choice;
    scanf("%d", &choice);
    while (choice < 0 || choice > 9)
    {
        printf("\n Wrong choice, Enter again..\n");
        printf(">> ");
        scanf("%d", &choice);
    }
    switch (choice)
    {
    case 1:
        puts("\nYour store status is WHITE");
        sleep(2);
        printf("\e[1;1H\e02J");
        shop_page(index);
        break;
    case 2:
        shopUser[index].disinfection = 1;
    case 3:
        printf("\nCommand not available, enter again.");
        sleep(1);
        getchar();
        shop_page(index);
        break;
    case 4:
        printf("\n\e[1mReturning to main menu...\e[0m");
        sleep(1);
        printf("\e[1;1H\e[02J");
        getchar();
        main_menu();
        break;
    case 0:
        exit(0);
    default:
        printf("\nCommand not valid, enter again.");
        sleep(1);
        getchar();
        shop_page(index);
        break;
    }
}

//Sign_up section
void signup_menu()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    printf("Enter usertype (normal/1, shop/2, return(-1)) : \n >> ");
    char UT[20];
    fgets(UT, 20, stdin);
    switch (UT[0])
    {
    case 'r':
    case 'R':
    case '-':
        puts("\nReturning to main menu...");
        sleep(2);
        main_menu();
        break;
    case 'n':
    case 'N':
    case '1':
        signupNorm();
        break;
    case 's':
    case 'S':
    case '2':
        signupShop();
        break;
    default:
        puts("Wrong usertype! Try again.");
        sleep(2);
        signup_menu();
        break;
    }
}

void signupNorm()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    sleep(1);
    puts("");
    strcpy(normalUser[normalUsercount].user_type, "normal");
    puts("Fields marked with * are required");
    printf("Enter your first name* : ");
    scanf("%s", normalUser[normalUsercount].fname);
    puts("");
    printf("Enter your last name* : ");
    scanf("%s", normalUser[normalUsercount].lname);
    puts("");
    printf("Enter your ID code(10 digits)* : ");
    scanf("%ld", &normalUser[normalUsercount].codeMelli);
    while (!codemelli_check(normalUser[normalUsercount].codeMelli))
    {
        printf("your Id code must have 10 digits!, enter again : ");
        scanf("%ld", &normalUser[normalUsercount].codeMelli);
        puts("");
    }
    printf("Enter your username* : ");
    scanf("%s", normalUser[normalUsercount].user_name);
    puts("");
    printf("Enter your Password* : ");
    getPasswd(pass1);
    puts("");
    printf("Enter your Password again* : ");
    getPasswd(pass2);
    while (strcmp(pass1, pass2))
    {
        puts("\nPasswords don't match. Try again");
        printf("Enter your Password* : ");
        getPasswd(pass1);
        puts("");
        printf("Enter your Password again* : ");
        getPasswd(pass2);
    }
    strcpy(normalUser[normalUsercount].passwd, pass1);
    puts("");
    printf("Enter your E-Mail* : ");
    scanf("%s", normalUser[normalUsercount].email);
    puts("");
    printf("Enter your Blood group(null to skip) : ");
    scanf("%s", normalUser[normalUsercount].bloodG);
    puts("");
    printf("Enter your age(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser[normalUsercount].age);
    puts("");
    printf("Enter your height(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser[normalUsercount].height);
    puts("");
    printf("Enter your weight(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser[normalUsercount].weight);
    puts("");
    normalUsercount++;
    printf("\e[1;1H\e[02J");
    login();
}

void signupShop()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    sleep(1);
    puts("");
    strcpy(shopUser[shopUsercount].user_type, "shop");
    puts("All fields are required");
    printf("Enter your first name* : ");
    scanf("%s", shopUser[shopUsercount].fname);
    puts("");
    printf("Enter your last name* : ");
    scanf("%s", shopUser[shopUsercount].lname);
    puts("");
    printf("Enter your ID code(10 digits)* : ");
    scanf("%ld", &shopUser[shopUsercount].codeMelli);
    while (!codemelli_check(shopUser[shopUsercount].codeMelli))
    {
        printf("your Id code must have 10 digits!, enter again : ");
        scanf("%ld", &shopUser[shopUsercount].codeMelli);
        puts("");
    }
    printf("Enter your username* : ");
    scanf("%s", shopUser[shopUsercount].user_name);
    puts("");
    printf("Enter your Password* : ");
    getPasswd(pass1);
    puts("");
    printf("Enter your Password again* : ");
    getPasswd(pass2);
    while (strcmp(pass1, pass2))
    {
        puts("\nPasswords don't match. Try again");
        printf("Enter your Password* : ");
        getPasswd(pass1);
        puts("");
        printf("Enter your Password again* : ");
        getPasswd(pass2);
    }
    strcpy(shopUser[shopUsercount].passwd, pass1);
    puts("");
    printf("Enter your E-Mail* : ");
    scanf("%s", shopUser[shopUsercount].email);
    getchar();
    puts("");
    printf("Enter your store name* : ");
    fgets(shopUser[shopUsercount].store_name, strSize, stdin);
    getchar();
    puts("");
    printf("Enter e your store is in* : ");
    fgets(shopUser[shopUsercount].cityName, strSize, stdin);
    getchar();
    puts("");
    printf("Enter your city district zone* : ");
    scanf("%d", &shopUser[shopUsercount].mantaghe);
    shopUsercount++;
    printf("\e[1;1H\e[02J");
    login();
}

int codemelli_check(long int code)
{
    int cnt = 0;
    while (code > 0)
    {
        code /= 10;
        cnt++;
    }
    return (cnt == 10 ? true : false);
}

//forgot_password_section
void forgot_passwd()
{
    printf("\e[1;1H\e[2J");
    char email[strSize];
    long int codem;
    printf("Enter your username(return/-1 to go back to main menu) : ");
    scanf("%s", username);
    puts("");
    char ans1[strSize], ans2[strSize];
    int uni = findUsernormal(username), ushi = findUsershop(username);
    if (!strcmp("return", username) || !strcmp("-1", username))
    {
        printf("Returning to main menu...");
        sleep(1);
        main_menu();
    }
    printf("Enter your 'code melli'!(return to go back to main menu) : ");
    scanf("%li", &codem);
    puts("");
    printf("Enter your email(return to go back to main menu) : ");
    scanf("%s", email);
    puts("");
    if (strcmp(admin.user_name, username) && (uni == -1) && (ushi == -1))
    {
        printf("\nUsername not found! returning to main menu...");
        sleep(1);
        main_menu();
    }
    //Admin
    else if ((codem == admin.codeMelli) && (!strcmp(admin.user_name, username)) && (!strcmp(admin.email, email)))
    {
        //3 step verification (2 left)
        //Steps 2 & 3
        printf("%s?\n", admin.TFAQ01);
        scanf("%s", ans1);
        printf("%s?\n", admin.TFAQ02);
        scanf("%s", ans2);
        if (!strcmp(ans1, admin.TFAA01) && !strcmp(ans2, admin.TFAA02))
        {
            printf("Enter your Password* : ");
            getPasswd(pass1);
            puts("");
            printf("Enter your Password again* : ");
            getPasswd(pass2);
            while (strcmp(pass1, pass2))
            {
                puts("\nPasswords don't match. Try again");
                printf("Enter your Password* : ");
                getPasswd(pass1);
                puts("");
                printf("Enter your Password again* : ");
                getPasswd(pass2);
            }
            strcpy(admin.passwd, pass1);
            login();
        }
        else
        {
            printf("\n\e[31mYou failed the 2FA test, try again if it's really you.\n");
            sleep(2);
            printf("\e[1;1H\e[2J");
            main_menu();
        }
    }
    //Normal
    else if (uni)
    {
        printf("Enter your Password* : ");
        getPasswd(pass1);
        puts("");
        printf("Enter your Password again* : ");
        getPasswd(pass2);
        while (strcmp(pass1, pass2))
        {
            puts("\nPasswords don't match. Try again");
            printf("Enter your Password* : ");
            getPasswd(pass1);
            puts("");
            printf("Enter your Password again* : ");
            getPasswd(pass2);
        }
        strcpy(normalUser[uni].passwd, pass1);
        login();
    }
    //Shop
    else if (ushi)
    {
        printf("Enter your Password* : ");
        getPasswd(pass1);
        puts("");
        printf("Enter your Password again* : ");
        getPasswd(pass2);
        while (strcmp(pass1, pass2))
        {
            puts("\nPasswords don't match. Try again");
            printf("Enter your Password* : ");
            getPasswd(pass1);
            puts("");
            printf("Enter your Password again* : ");
            getPasswd(pass2);
        }
        strcpy(shopUser[ushi].passwd, pass1);
        login();
    }
    else
    {
        puts("\e[31mThe information you entered didn't match with any user, returning to main menu...\e[0m");
        sleep(2);
        main_menu();
    }
}

void healthCode(int index)
{
    switch (normalUser[index].health_code)
    {
    case 1:
        printf("\e[1;32mYour health code is %d\e[0m", normalUser[index].health_code);
        break;
    case 2:
        printf("\e[1;33mYour health code is %d\e[0m", normalUser[index].health_code);
        break;
    case 3:
        printf("\e[1;91mYour health code is %d\e[0m", normalUser[index].health_code);
        break;
    case 4:
        printf("\e[1;31mYour health code is %d\e[0m", normalUser[index].health_code);
        break;
    case 0:
        printf("You haven't taken the test yet");
        break;
    }
}

void health_test(int* score)
{
    char choice[10];
    puts("\nPlease ONLY answer with Y or N.\nQ1.Have you coughed badly and repeatedly in the last few days? (Y or N) ");
    scanf("%s", choice);
    choice_check(choice);
    if (!strcmp(choice, "Y") || !strcmp(choice, "y"))
        *score += 30;
    puts("Q2. Have you had fever(tab!(\\t)) in the last week? (Y or N) ");
    scanf("%s", choice);
    choice_check(choice);
    if (choice[0] == 'y' || choice[0] == 'Y')
        *score += 20;
    puts("Q3. Have you experienced shortness of breath(tangi nafas!) in the last week? (Y or N) ");
    scanf("%s", choice);
    choice_check(choice);
    if (choice[0] == 'y' || choice[0] == 'Y')
        *score += 20;
    puts("Q4. Have you felt pain or contusion(koftegi!) in the last week? (Y or N) ");
    scanf("%s", choice);
    choice_check(choice);
    if (choice[0] == 'y' || choice[0] == 'Y')
        *score += 15;
    puts("Q5. Have you had sore throat(galo dard!) in the last week? (Y or N) ");
    scanf("%s", choice);
    choice_check(choice);
    if (choice[0] == 'y' || choice[0] == 'Y')
        *score += 15;
}

void choice_check(char choice[])
{
    while (choice[0] != 'Y' && choice[0] != 'y' && choice[0] != 'n' && choice[0] != 'N')
    {
        printf("\nEnter valid Input(Y or N) : ");
        scanf("%s", choice);
    }
}

void edit_info(char userType, int index)
{
    int choice;
    printf("\e[1;1H\e[2J");
    switch (userType)
    {
    case 'a':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change ID code.");
        puts("4. Change security questions and/or their answers.");
        puts("5. Return to previous menu.");
        printf(">> ");
        scanf("%d", &choice);
        while (choice < 0 || choice > 5)
        {
            printf("\n Wrong choice, Enter again..\n");
            printf(">> ");
            scanf("%d", &choice);
        }
        switch (choice)
        {
        case 1:
            printf("Current Name: %s %s\n", admin.fname, admin.lname);
            printf("Enter new first and last name with a space between them : ");
            scanf("%s", admin.fname);
            scanf("%s", admin.lname);
            printf("Name changed successfuly, press enter to proceed...");
            getchar();
            edit_info('a', 0);
            break;
        case 2:
            printf("Enter password to proceed : ");
            getPasswd(pass1);
            if (!strcmp(admin.passwd, pass1))
            {
                printf("Current email address is %s\n", admin.email);
                printf("Enter new e-mail address : ");
                scanf("%s", admin.email);
                printf("Email changed successfuly, press enter to proceed...");
                getchar();
                edit_info('a', 0);
            }
            else
            {
                printf("Password was incorrect, retry ...");
                sleep(1);
                edit_info('a', 0);
            }
            break;
        case 3:
            printf("Current ID : %li\n", admin.codeMelli);
            printf("Enter new ID code : ");
            scanf("%li", &admin.codeMelli);
            while (!codemelli_check(admin.codeMelli))
            {
                printf("your Id code must have 10 digits!, enter again : ");
                scanf("%ld", &admin.codeMelli);
                puts("");
            }
            printf("ID Code changed successfully, press a key to proceed.");
            getchar();
            edit_info('a', 0);
            break;
        case 4:
            printf("Enter password to proceed : ");
            getPasswd(pass1);
            if (!strcmp(admin.passwd, pass1))
            {
                printf("Current security question and answer 1 are %s : %s\n", admin.TFAQ01, admin.TFAA01);
                printf("Enter new Security question(1) : ");
                scanf("%[^\n]s", admin.TFAQ01);
                printf("Enter new answer(1) : ");
                scanf("%[^\n]s", admin.TFAA01);
                printf("Current security question and answer 2 are %s : %s\n", admin.TFAQ02, admin.TFAA02);
                printf("Enter new Security question(2) : ");
                scanf("%[^\n]s", admin.TFAQ02);
                printf("Enter new answer(2) : ");
                scanf("%[^\n]s", admin.TFAA02);
                printf("Security questions changed successfully, press a key to proceed.");
                getchar();
                edit_info('a', 0);
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(1);
                edit_info('a', 0);
            }
            break;
        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            sleep(1);
            printf("\e[1;1H\e[02J");
            admin_page();
            break;
        default:
            puts("Wrong input ...");
            sleep(1);
            edit_info('a', 0);
            break;
        }
        break;
    case 'n':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change ID code.");
        puts("4. Change additional information.");
        puts("5. Return to previous menu.");
        printf(">> ");
        scanf("%d", &choice);
        while (choice < 0 || choice > 5)
        {
            printf("\n Wrong choice, Enter again..\n");
            printf(">> ");
            scanf("%d", &choice);
        }
        switch (choice)
        {
        case 1:
            printf("Current Name : %s %s\n", normalUser[index].fname, normalUser[index].lname);
            printf("Enter new first and last name with a space between them : ");
            scanf("%s", normalUser[index].fname);
            scanf("%s", normalUser[index].lname);
            printf("Name changed successfully, press a key to proceed.");
            getchar();
            edit_info('n', index);
            break;
        case 2:
            printf("Enter password to proceed : ");
            getPasswd(pass1);
            if (!strcmp(normalUser[index].passwd, pass1))
            {
                printf("Current email address is %s\n", normalUser[index].email);
                printf("Enter new e-mail address : ");
                scanf("%s", normalUser[index].email);
                sleep(1);
                edit_info('n', index);
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(1);
                edit_info('n', index);
            }
            printf("Email address changed successfully, press a key to proceed.");
            getchar();
            edit_info('n', index);
            break;
        case 3:
            printf("Current ID : %li\n", normalUser[index].codeMelli);
            printf("Enter new ID code* : ");
            scanf("%li", &normalUser[index].codeMelli);
            while (codemelli_check(normalUser[index].codeMelli))
            {
                printf("your Id code must have 10 digits!, enter again : ");
                scanf("%li", &normalUser[index].codeMelli);
                puts("");
            }
            printf("ID Code changed successfully, press a key to proceed.");
            getchar();
            edit_info('n', index);
            break;
        case 4:
            printf("Enter your new Blood group(null to skip) : ");
            scanf("%s", normalUser[index].bloodG);
            puts("");
            printf("Enter your new age :) (0 to skip) : ");
            scanf("%d", &normalUser[index].age);
            puts("");
            printf("Enter your new height :/ (0 to skip) : ");
            scanf("%d", &normalUser[index].height);
            puts("");
            printf("Enter your new weight :/ (0 to skip) : ");
            scanf("%d", &normalUser[index].weight);
            puts("");
            printf("Successfull!, press a key to proceed.");
            getchar();
            edit_info('n', index);
            break;
        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            sleep(1);
            printf("\e[1;1H\e[02J");
            normal_page(index);
            break;
        default:
            puts("Wrong input ...");
            sleep(1);
            edit_info('n', index);
            break;
        }
        break;
    case 's':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change ID code.");
        puts("4. Change store info.");
        puts("5. Return to previous menu.");
        printf(">> ");
        scanf("%d", &choice);
        while (choice < 0 || choice > 5)
        {
            printf("\n Wrong choice, Enter again..\n");
            printf(">> ");
            scanf("%d", &choice);
        }
        switch (choice)
        {
        case 1:
            printf("Current Name : %s %s\n", shopUser[index].fname, shopUser[index].lname);
            printf("Enter new first and last name with a space between them : ");
            scanf("%s", shopUser[index].fname);
            scanf("%s", shopUser[index].lname);
            printf("Name changed successfully, press a key to proceed.");
            getchar();
            edit_info('s', index);
            break;
        case 2:
            printf("Enter password to proceed : ");
            scanf("%s", pass1);
            if (!strcmp(shopUser[index].passwd, pass1))
            {
                printf("Current email address is %s\n", shopUser[index].email);
                printf("Enter new e-mail address : ");
                scanf("%s", shopUser[index].email);
                printf("Email address changed successfully, press a key to proceed.");
                getchar();
                edit_info('s', index);
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(1);
                edit_info('s', index);
            }
            break;
        case 3:
            printf("Current ID : %li\n", shopUser[index].codeMelli);
            printf("Enter new ID code* : ");
            scanf("%li", &shopUser[index].codeMelli);
            while (codemelli_check(shopUser[index].codeMelli))
            {
                printf("your Id code must have 10 digits!, enter again : ");
                scanf("%li", &shopUser[index].codeMelli);
                puts("");
            }
            printf("ID Code changed successfully, press a key to proceed.");
            getchar();
            edit_info('s', index);
            break;
        case 4:
            printf("Enter your new shop name: ");
            fgets(shopUser[index].store_name, strSize, stdin);
            getchar();
            puts("");
            printf("Enter your shops city followed by its district e.g. (Isfahan 12): ");
            scanf("%s", shopUser[index].cityName);
            scanf("%d", &shopUser[index].mantaghe);
            printf("Store information changed successfully, press a key to proceed.");
            getchar();
            edit_info('s', index);
            break;
        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            sleep(1);
            printf("\e[1;1H\e[02J");
            shop_page(index);
            break;
        default:
            puts("Wrong input ...");
            sleep(1);
            edit_info('s', index);
            break;
        }
        break;
    }
}
