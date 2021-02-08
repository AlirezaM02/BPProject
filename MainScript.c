
//////*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//////**********************************Basics of programming, first semester project**********************************/
////********************************************ImmuneTastic Application**********************************************/
////*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
////********************************************Developed and designed by:******************************************/
//*************************************************~#Alireza Mirzaei#~*********************************************/
//*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <mysql/mysql.h>
#define strSize 45

//TO RUN THE SCRIPT : gcc MainScript.c `mysql_config --cflags --libs`

//Global variables
long int national_code;
int province, type = 0;
char username[strSize], pass1[strSize], pass2[strSize], email[60], statement[1000];
char TFAQ01[90], TFAA01[90], TFAQ02[90], TFAA02[90], uni[20], ushi[20], hos_name[50], city[50];
//statement variable is for using in mysql_query

//Initialize MySQL connections and etc.
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

//Structures (DEFINED GLOBALLY)
struct users
{
    //char user_type[strSize];
    int id;
    char user_name[strSize];
    char passwd[strSize];
    char fname[strSize];
    char lname[strSize];
    char email[strSize];
    long int national_code;
    //Normal only
    char bloodG[4];
    int age;
    int height;
    int weight;
    int test_score;
    int test_counter;
    int health_code;
    int test_score_history[100];
    time_t test_time_history[100];
    //Shop only
    int disinfection;
    int mantaghe;
    char store_name[strSize];
    char cityName[strSize];
};
struct users normalUser;
struct users shopUser;
struct users admin;

//Function prototypes
void welcome();

//Menus
void main_menu();
void help_mm();
void command_mm();
void signup_menu();
void forgot_passwd();

//login
void login();
void findUsernormal(int);
void findUsershop(int);

//Signup
void signupNorm();
void signupShop();
char getPasswd(char *, int, int);
int national_code_check(long int);

//pages
void admin_page();
void normal_page();
void shop_page();
void medical_advices();
void health_test(int *);
void healthCode();
void choice_check(char *);
void edit_info(char);

//MySQL functions
void finish_with_error(MYSQL *conn);
void create_statement(char *, char *);

// Main Driver Program
// Mostly users info

int main()
{
    //Program Start

    //Initialize database
    conn = mysql_init(NULL);
    //puts("\e[1;1H\e[02J");
    //puts("Please Enter database password to proceed: ");
    //getPasswd(&pass1, 1, 1);
    //Connect to database
    if (!mysql_real_connect(conn, "localhost", "root", "Guess1Pass@AM", "project_database", 0, NULL, 0))
        finish_with_error(conn);
    //mysql_query(conn, "CREATE DATABASE testdb1"); For testing connection

    strcpy(TFAQ01, "What is your ascii_sum?");
    strcpy(TFAA01, "ChertoPeRt!!!!! :-/");
    strcpy(TFAQ02, "What is your first class teacher + Your favorite color?");
    strcpy(TFAA02, "Ms.RedZade :)))))))");

    welcome();
    sleep(2);
    main_menu();
    mysql_close(conn); //End of program
}

//Functions body
//Welcome and main menu section
void welcome()
{
    printf("\e[1;1H\e[2J");
    sleep(1);
    printf("\n\n                                                     \e[1;40;37m     _____                                             \e[0m\n");
    puts("                                                     \e[1;40;37m     |_   _|                                           \e[0m");
    puts("                                                     \e[1;40;37m       | |  _ __ ___  _ __ ___  _   _ _ __   ___       \e[0m");
    puts("                                                     \e[1;40;37m       | | | '_ ` _ \\/ '_ ` _ \\| | | | '_ \\ / _ \\      \e[0m");
    puts("                                                     \e[1;40;37m      _| |_| | | | | | | | | | | |_| | | | |  __/      \e[0m");
    puts("                                                     \e[1;40;37m     |_____|_| |_| |_|_| |_| |_|\\__,_|_| |_|\\___|      \e[0m");
    puts("                                                     \e[1;40;37m     |__   __|      | | (_)                            \e[0m");
    puts("                                                     \e[1;40;37m        | | __ _ ___| |_ _  ___                        \e[0m");
    puts("                                                     \e[1;40;37m        | |/ _` / __| __| |/ __|                       \e[0m");
    puts("                                                     \e[1;40;37m        | | (_| \\__ \\ |_| | (__                        \e[0m");
    puts("                                                     \e[1;40;37m        |_|\\__,_|___/\\__|_|\\___|                       \e[0m");
    puts("                                                     \e[1;40;37m                                                       \e[0m");
    puts("");
    sleep(5);
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t\t            \e[36;1mWelcome to ImmuneTastic!\n\n\e[0m");
    sleep(2);
    printf("\t\t\t\t\t\t      >>>>>>>>    \e[1;32mDeveloped By : Alireza Mirzaei\e[0m     <<<<<<<<\n");
    sleep(2);
}

void main_menu()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    sleep(1);
    puts("\e[21;24;36mMain Menu\e[0m  \n\n\e[31;1mlogin(1)\e[0m || \e[32;1msign up(2)\e[0m || \e[33;1mforgot password(3)\e[0m || \e[34;1mhelp(4)\e[0m || \e[35;1mchange password layout(5)\e[0m || \e[1mexit(0)\e[0m");
    printf("\n>> ");
    command_mm();
}

//Helps
void help_mm()
{
    puts("\e[46;37mHelp for : Main menu\r"); //Help for main menu
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
        sleep(5);
        getchar();
        main_menu();
        break;
    case 'c':
    case 'C':
    case '5':
        puts("Do you want password fields to be linux-type(1) or star-type(0)?");
        int temp;
        scanf("%d", &temp);
        type = temp;
        sleep(1);
        getchar();
        main_menu();
        break;
    case 'e':
    case 'E':
    case '0':
        mysql_close(conn);
        exit(0);
    default:
        printf("Enter a valid input please \n>> ");
        command_mm();
    }
}

char getPasswd(char *password, int tekrar, int type)
{
    int cnt = 0;
    *password = '\0';
    while ((strlen(password) < 6 || strlen(password) > strSize) && strcmp(password, "-1") != 0)
    {
        if (cnt == 1)
        {
            if (tekrar == 1)
                printf("\e[34mPlease enter your Password: \e[0m");
            else
                printf("\e[34mPlease enter your Password again: \e[0m");
        }
        int i;
        char ch1;
        for (i = 0; i < strSize; i++)
        {
            ch1 = getch();
            if (ch1 != 10)
                if (ch1 != 127)
                {
                    if (type == 1)
                        printf("");
                    else
                        printf("*");
                    password[i] = ch1;
                }
                else if (i > 0)
                {
                    printf("\b \b");
                    i -= 2;
                }
                else
                    i = -1;
            else
                break;
        }
        password[i] = '\0';
        if (strlen(password) < 5 && strcmp(password, "-1") != 0)
            puts("\n\e[32;1mThe password should be more than 5 characters!\e[0m");
        cnt++;
    }
    return password;
}

//Login_section
void login()
{
    sleep(1);
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    printf("Username(type return/-1 to go back): ");
    scanf("%s", username);
    findUsernormal(1);
    findUsershop(1);
    create_statement("fetch_data", "admin");

    if (!strcmp(username, "return") || !strcmp(username, "Return") || !strcmp(username, "-1"))
    {
        puts("\nReturning to main menu ...");
        sleep(1);
        getchar();
        main_menu();
    }

    else if ((strcmp(uni, "NULL") == 0) && (strcmp(ushi, "NULL") == 0) && (strcmp(username, "admin") != 0))
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
        getPasswd(&pass1, 1, type);
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
    else if (strcmp(uni, "NULL") != 0)
    {
        create_statement("fetch_data", "normal_users");
        if (normalUser.health_code == 5)
        {
            puts("Sorry but you were reported \e[1;31mDEAD\e[0m, therefore you cannot login! Enter a key...");
            getchar();
            getchar();
            login();
        }
        getPasswd(&pass1, 1, type);
        if (!strcmp(normalUser.passwd, pass1))
        {
            puts("\n\e[32;1;24mLogin successful, Welcome to your account!\e[0m");
            sleep(1);
            normal_page();
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

    // Shop Login
    else if (strcmp(ushi, "NULL") != 0)
    {
        create_statement("fetch_data", "shop_users");
        getPasswd(&pass1, 1, type);
        if (!strcmp(pass1, shopUser.passwd))
        {
            puts("\n\e[32;1;24mLogin successful, Welcome to your account!\e[0m");
            sleep(1);
            shop_page();
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

// These 2 functions return id if they find the username
// in the database, else "NULL"
void findUsernormal(int stat)
{
    if (stat == 1)
    {
        //Username duplicates
        snprintf(statement, sizeof(statement), "SELECT id FROM normal_users WHERE username = '%s';", username);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(uni, row[0]);
        else
            strcpy(uni, "NULL");
        mysql_free_result(res);
    }

    else if (stat == 2) //check email duplicates
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM normal_users WHERE email = '%s';", email);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(uni, row[0]);
        else
            strcpy(uni, "NULL");
        mysql_free_result(res);
    }

    else if (stat == 3) //national_code duplicate
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM normal_users WHERE national_code = %ld;", national_code);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(uni, row[0]);
        else
            strcpy(uni, "NULL");
        mysql_free_result(res);
    }
}

void findUsershop(int stat)
{
    if (stat == 1)
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM shop_users WHERE username = '%s';", username);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(ushi, row[0]);
        else
            strcpy(ushi, "NULL");
        mysql_free_result(res);
    }

    else if (stat == 2)
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM shop_users WHERE email = '%s';", email);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(ushi, row[0]);
        else
            strcpy(ushi, "NULL");
        mysql_free_result(res);
    }

    else if (stat == 3)
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM shop_users WHERE national_code = %ld;", national_code);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(ushi, row[0]);
        else
            strcpy(ushi, "NULL");
        mysql_free_result(res);
    }

    else if (stat == 4)
    {
        snprintf(statement, sizeof(statement), "SELECT id FROM shop_users WHERE store_name = '%s';", hos_name);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL)
            strcpy(ushi, row[0]);
        else
            strcpy(ushi, "NULL");
        mysql_free_result(res);
    }
}

//Pages_section
//Admin_page
void admin_page()
{
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t\t\e[1;32mHi %s %s, Welcome to your account\n\e[0m", admin.fname, admin.lname);
    puts("\e[1mEnter desired command to proceed.\e[0m");
    puts("\e[34m1. Add a Hospital");
    puts("2. See statistics");
    puts("3. Edit users health info");
    puts("4. See all users");
    puts("5. Show the list of deaths");
    puts("6. List of registered shops");
    puts("7. List of all registered hospitals");
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
        printf("\e[1;1H\e[2J");
        sleep(1);
        getchar();
        printf("Enter Hospital Name: ");
        scanf("%[^\n]s", hos_name);
        getchar();
        printf("\nEnter city name : ");
        scanf("%[^\n]s", city);
        getchar();
        printf("\nEnter hospitals province as a whole number : ");
        scanf("%d", &province);
        getchar();
        create_statement("add_hospital", "admin");
        printf("Hospital %s created successfully\n", hos_name);
        sleep(2);
        admin_page();
        break;

    case 2:
    case 3:
        puts("\nList of sick people sorted by name\n");
        create_statement("see_sicks", "admin");

        if (choice == 2)
        {
            getchar();
            puts("Press a key to proceed...");
            getchar();
            sleep(1);
            admin_page();
            break;
        }

        else
        {
            if (strcmp(city, "NULL"))
            {
                puts("Choose a user to heal or to kill!\nEnter his/her national code first: ");
                scanf("%ld", &national_code);
                int a;
                findUsernormal(3);
                while ((a = national_code_check(national_code)) == 0 || strcmp("NULL", uni) == 0)
                {
                    while (strcmp("NULL", uni))
                    {
                        puts("User not found!, try again...");
                        scanf("%ld", &national_code);
                        findUsernormal(3);
                    }
                    while (a)
                    {
                        printf("your national code must have 10 digits!, enter again : ");
                        scanf("%ld", &national_code);
                        a = national_code_check(national_code);
                        puts("");
                    }
                }
                puts("Now, do you wanna kill the guy or heal him/her??input (heal or kill)");
                scanf("%s", email);
                if (strcmp("heal", email) == 0 || strcmp("Heal", email) == 0)
                    create_statement("heal", "admin");
                else if (strcmp("kill", email) == 0 || strcmp("Kill", email) == 0)
                    create_statement("kill", "admin");
                puts("Successful!");
            }
        }

        printf("Press a key to proceed");
        getchar();
        getchar();
        sleep(2);
        admin_page();
        break;

    case 4:
        puts("List of normal users sorted by their names");
        create_statement("see_all_normals", "admin");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        sleep(1);
        admin_page();
        break;

    case 5:
        puts("Here's the list of all deaths :");
        create_statement("see_deaths", "admin");
        printf("\n\e[1;32mPress a key to proceed...\e[0m");
        getchar();
        getchar();
        admin_page();
        break;

    case 6:
        puts("\nList of shops sorted by store name\n");
        create_statement("see_all_shops", "admin");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        admin_page();
        break;

    case 7:
        puts("List of hospitals ordered by their cities and then names : ");
        create_statement("show_hospital", "admin");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        sleep(1);
        admin_page();
        break;

    case 8:
        edit_info('a');
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
void normal_page()
{
    if (normalUser.health_code < 4 && normalUser.health_code > 1)
    {
        time_t t = time(NULL);
        if (abs(normalUser.test_time_history[normalUser.test_counter - 1] - t) > 604800)
        {
            normalUser.health_code -= 1;
            snprintf(statement, sizeof(statement), "UPDATE normal_users SET cov_code = cov_code - 1 WHERE username = '%s';", normalUser.user_name);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }
    }

    int sth = normalUser.test_counter;

    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t\t\t\e[1;32mHi %s %s, Welcome to your account\n\e[0m", normalUser.fname, normalUser.lname);
    printf("\nHealth Status: ");
    healthCode();
    puts("\n");
    puts("\e[1m\nEnter desired command(number only) to proceed.\e[0m");
    puts("\e[34m1. Edit info");
    puts("2. Give health test");
    puts("3. See a history of your tests");
    puts("4. Register a visit to other users");
    puts("5. History of visits");
    puts("6. Register a place you've recently been to");
    puts("7. See history of visited locations");
    puts("8. See covid-19 statistics");
    puts("9. Find nearby hospitals");
    puts("10. Corona Virus medical tips and suggestions");
    puts("11. Logout");
    puts("0. Exit the program\e[0m");
    printf(">> ");

    char choice[5];
    scanf("%s", choice);
    while (atoi(choice) < 0 || atoi(choice) > 11)
    {
        printf("\n Wrong choice, Enter again..\n");
        printf(">> ");
        scanf("%d", &choice);
    }

    if (!strcmp("1", choice))
        edit_info('n');

    else if (!strcmp("2", choice))
    {
        if (normalUser.health_code == 4)
        {
            puts("You \e[1mcannot\e[0m take the test because your code is \e[1;31m4\e[0m (so don't think of cheating :))");
            puts("press a key to proceed...");
            getchar();
            getchar();
            sleep(1);
        }
        else
        {
            time_t t = time(NULL);
            health_test(&normalUser.test_score);
            normalUser.test_score_history[normalUser.test_counter] = normalUser.test_score;
            normalUser.test_time_history[normalUser.test_counter] = t;
            if (normalUser.test_score <= 15)
                normalUser.health_code = 1;
            else if (normalUser.test_score > 15 && normalUser.test_score <= 50)
                normalUser.health_code = 2;
            else if (normalUser.test_score > 50 && normalUser.test_score <= 75)
                normalUser.health_code = 3;
            else if (normalUser.test_score > 75 && normalUser.test_score <= 100)
            {
                normalUser.health_code = 4;
                snprintf(statement, sizeof(statement), "UPDATE normal_users SET sickness_time = %ld WHERE id = %d;", t, normalUser.id);
                if (mysql_query(conn, statement))
                    finish_with_error(conn);
                res = mysql_use_result(conn);
                mysql_free_result(res);
            }
            sleep(1);
            printf("\e[1;1H\e[2J");
            snprintf(statement, sizeof(statement), "INSERT INTO health_tests VALUES (%d, %d, %ld);", normalUser.id, normalUser.test_score, t);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
            normalUser.test_counter++;
            snprintf(statement, sizeof(statement), "UPDATE normal_users SET test_counter = test_counter + 1, cov_code = %d WHERE id = %d;", normalUser.health_code, normalUser.id);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }

        normal_page();
    }

    else if (!strcmp("3", choice))
    {
        if (sth)
        {
            for (int i = 0; i < sth; i++)
                if (i < 10)
                    printf("Test number %d\nTaken at %sresult: %d/100\n~~~~~~~~~~~~~~~~~~~~~\n", i + 1, asctime(localtime(&normalUser.test_time_history[i])), normalUser.test_score_history[i]);
                else
                    break;
            puts("Please enter a key to proceed ...");
            getchar();
            getchar();
            normal_page();
        }

        else
        {
            printf("You have not taken the test yet!\n");
            sleep(2);
            normal_page();
        }
    }

    else if (!strcmp("4", choice))
    {
        getchar();
        printf("Enter his/her national code(10 digits)* : ");
        scanf("%ld", &national_code);
        int a;
        findUsershop(3);
        while ((a = national_code_check(national_code)) == 0 && strcmp("NULL", ushi) != 0)
        {
            while (strcmp("NULL", uni))
            {
                puts("User not found!, try again...");
                scanf("%ld", &national_code);
                puts("");
                findUsershop(3);
            }
            while (!a)
            {
                printf("your national code must have 10 digits!, enter again : ");
                scanf("%ld", &national_code);
                puts("");
            }
        }
        puts("");
        create_statement("visit_person", "normal_users");
        puts("\e[1;32mSuccessful\e[0mPress a key to proceed");
        getchar();
        getchar();
        sleep(2);
        normal_page();
    }

    else if (!strcmp("5", choice))
    {
        getchar();
        time_t t = 1612282173;
        puts("Here's a list of your visited users : \n");
        printf(" Name | visited's code | date of visiting \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("hossein hosseini | \e[31m4\e[0m | %s \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", asctime(localtime(&t)));
        //create_statement("see_visited_users", "normal_users");
        printf("\npress a key to proceed...");
        getchar();
        getchar();
        normal_page();
    }

    else if (!strcmp("6", choice))
    {
        getchar();
        printf("Please enter store name : ");
        scanf("%[^\n]s", hos_name);
        findUsershop(4);
        puts("");
        while (!strcmp(ushi, "NULL"))
        {
            puts("Sorry, this store name doesn't exist");
            printf("Enter store name again : ");
            fgets(hos_name, 50, stdin);
            findUsershop(4);
            puts("");
        }
        //Store name is correct here
        create_statement("visit_place", "normal_users");
        puts("\e[1;32mSuccessful!\e[0m\nPress a key to proceed...");
        getchar();
        getchar();
        normal_page();
    }

    else if (!strcmp("7", choice))
    {
        getchar();
        puts("Here's a list of places you've visited : \n");
        create_statement("see_visited_places", "normal_users");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        normal_page();
    }

    else if (!strcmp("8", choice))
    {
        getchar();
        puts("Here's a list of people infected in the last week : \n");
        create_statement("see_sicks", "normal_users");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        normal_page();
    }

    else if (!strcmp("9", choice))
    {
        getchar();
        puts("List of hospitals around you : ");
        create_statement("show_hospitals", "normal_users");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        sleep(2);
        normal_page();
    }

    else if (!strcmp("10", choice))
    {
        getchar();
        medical_advices();
        sleep(1);
        normal_page();
    }

    else if (!strcmp("11", choice))
    {
        printf("\n\e[1mReturning to main menu...\e[0m");
        sleep(1);
        printf("\e[1;1H\e[02J");
        getchar();
        main_menu();
    }

    else if (!strcmp(choice, "0"))
        exit(0);

    else
    {
        printf("\nCommand not valid, enter again.");
        sleep(1);
        getchar();
        normal_page();
    }
}

//shop_page
void shop_page()
{
    printf("\e[1;1H\e[2J");
    printf("\t\t\t\t\t\t \e[1;32mHi %s %s, Welcome to your account\n\e[0m", shopUser.fname, shopUser.lname);
    if (shopUser.disinfection == 0)
        puts("\e[1mYour store status is\e[0m \e[31mRED\e[0m");
    else
        puts("\e[1mYour store status is\e[0m \e[32mWHITE\e[0m");
    puts("\e[1mEnter desired command(number only) to proceed.(NA = not yet available)\e[0m");
    puts("\e[34m1. Your stores status");
    puts("2. Report disinfection");
    puts("3. See the status of the users who've come to your store");
    puts("4. See covid-19 advices");
    puts("5. Logout");
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
        if (shopUser.disinfection == 1)
            puts("\nYour store status is \e[1;32mWHITE\e[0m");
        else
            puts("\nYour store status is \e[1;31mRED\e[0m");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        sleep(1);
        shop_page();
        break;
    case 2:
        shopUser.disinfection = 1;
        shop_page();
        break;
    case 3:
        puts("List of all your visitors : ");
        create_statement("see_all_normals", "shop_users");
        puts("Press a key to proceed...");
        getchar();
        getchar();
        sleep(1);
        shop_page();
        break;
    case 4:
        getchar();
        medical_advices();
        getchar();
        sleep(1);
        shop_page();
        break;
    case 5:
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
        shop_page();
        break;
    }
}

void medical_advices()
{
    printf("\e[1;1H\e[2J");
    puts("\e[1mA. General Advices\e[0m");
    puts("\n1. Wearing a mask is vital to protecting yourself and those around you from spreading the virus.");
    puts("\n2. A mask should also help with another precaution: don’t touch your face. \nWhile it’s not the primary way the virus is spread, it’s still possible to pick up the virus off a surface and infect yourself by touching your mouth, nose or eyes. ");
    puts("\n3. Also be sure to wash your hands regularly and thoroughly with soap, \nespecially after returning to your home from being out in public. \nIt’s important, too, to lather your hands with soap for at least 20 seconds to get them fully clean.");
    puts("Finally, be sure to socially distance yourself from others, staying at least 6 feet away.\n Because of the distance that exhaled droplets can travel, you want to make sure you’re not too close to someone, \neven if they don’t show any symptoms. And, yes, that includes even when you’re wearing a mask. ");
    puts("\n\e[1mB. Grocery shopping\e[0m");
    puts("\n1. Limit the number of people from your household who make the trip. \nIt’s also helpful in keeping high-risk people home and away from that danger.");
    puts("\n2. Choose a low-traffic time for trips to grocery store.");
    puts("\n3. Get delivery or curbside pickup instead of going in person.");
    puts("\nSource : \e[4;34mhttps://health.clevelandclinic.org/coronavirus-tips-prevention-and-safety-for-everyday-life/\e[0m");
    puts("\n\e[1;31mThanks for reading, press a key to proceed");
    getchar();
    getchar();
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
    puts("Fields marked with * are required");

    printf("Enter your first name* : ");
    scanf("%s", normalUser.fname);
    puts("");

    printf("Enter your last name* : ");
    scanf("%s", normalUser.lname);
    puts("");

    printf("Enter your username* : ");
    scanf("%s", username);
    findUsernormal(1);
    puts("");
    while (strcmp(uni, "NULL"))
    {
        puts("Sorry, the username already exists");
        printf("Enter your username again* : ");
        scanf("%s", username);
        findUsernormal(1);
        puts("");
    }
    strcpy(normalUser.user_name, username);
    puts("");

    getPasswd(&pass1, 1, type);
    puts("");
    getPasswd(&pass2, 2, type);
    while (strcmp(pass1, pass2))
    {
        puts("\nPasswords don't match. Try again");
        getPasswd(&pass1, 1, type);
        puts("");
        getPasswd(&pass2, 2, type);
    }
    strcpy(normalUser.passwd, pass1);
    puts("");

    printf("Enter your email* : ");
    scanf("%s", email);
    findUsernormal(2);
    puts("");
    while (strcmp(uni, "NULL"))
    {
        puts("Sorry, the email already exists");
        printf("Enter your email again* : ");
        scanf("%s", email);
        findUsernormal(2);
        puts("");
    }
    strcpy(normalUser.email, email);
    puts("");

    printf("Enter your national code(10 digits)* : ");
    scanf("%ld", &national_code);
    int a;
    findUsernormal(3);
    while ((a = national_code_check(national_code)) == 0 && strcmp("NULL", uni) != 0)
    {
        while (strcmp("NULL", uni))
        {
            puts("User not found!, try again...");
            scanf("%ld", national_code);
            puts("");
            findUsernormal(3);
        }
        while (!a)
        {
            printf("your national code must have 10 digits!, enter again : ");
            scanf("%ld", &national_code);
            puts("");
        }
    }
    normalUser.national_code = national_code;
    puts("");

    printf("Enter your city followed by your district(esfahan 4) : ");
    scanf("%s %d", normalUser.cityName, &normalUser.mantaghe);
    puts("");

    printf("Enter your Blood group(NULL to skip) : ");
    scanf("%s", normalUser.bloodG);
    puts("");

    printf("Enter your age(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser.age);
    puts("");

    printf("Enter your height(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser.height);
    puts("");

    printf("Enter your weight(enter 0 if you don't want to enter) : ");
    scanf("%d", &normalUser.weight);
    puts("");

    printf("\e[1;1H\e[02J");
    getchar();
    create_statement("signup", "normal_users");
    main_menu();
}

void signupShop()
{
    printf("\e[1;1H\e[2J");
    fflush(stdout);
    sleep(1);
    puts("");
    puts("All fields are required");

    printf("Enter your first name* : ");
    scanf("%s", shopUser.fname);
    puts("");

    printf("Enter your last name* : ");
    scanf("%s", shopUser.lname);
    puts("");

    printf("Enter your username* : ");
    scanf("%s", username);
    findUsershop(1);
    puts("");
    while (strcmp(ushi, "NULL"))
    {
        puts("Sorry, the username already exists");
        printf("Enter your username again* : ");
        scanf("%s", username);
        findUsershop(1);
        puts("");
    }
    strcpy(shopUser.user_name, username);
    puts("");

    getPasswd(&pass1, 1, type);
    puts("");
    getPasswd(&pass2, 2, type);
    while (strcmp(pass1, pass2))
    {
        puts("\nPasswords don't match. Try again");
        getPasswd(&pass1, 1, type);
        puts("");
        getPasswd(&pass2, 2, type);
    }
    strcpy(shopUser.passwd, pass1);
    puts("");

    printf("Enter your email* : ");
    scanf("%s", email);
    findUsershop(2);
    puts("");
    while (strcmp(ushi, "NULL"))
    {
        puts("Sorry, the email already exists");
        printf("Enter your email again* : ");
        scanf("%s", email);
        findUsershop(2);
        puts("");
    }
    strcpy(shopUser.email, email);
    puts("");

    printf("Enter your national code(10 digits)* : ");
    scanf("%ld", &national_code);
    int a;
    findUsershop(3);
    while ((a = national_code_check(national_code)) == 0 && strcmp("NULL", ushi) != 0)
    {
        while (strcmp("NULL", uni))
        {
            puts("User not found!, try again...");
            scanf("%ld", &national_code);
            puts("");
            findUsershop(3);
        }
        while (!a)
        {
            printf("your national code must have 10 digits!, enter again : ");
            scanf("%ld", &national_code);
            puts("");
        }
    }
    shopUser.national_code = national_code;
    puts("");

    getchar();
    printf("Enter your store name* : ");
    fgets(hos_name, 50, stdin);
    findUsershop(4);
    puts("");
    while (strcmp(ushi, "NULL"))
    {
        puts("Sorry, this store name already exists");
        printf("Enter your store name again : ");
        fgets(hos_name, 50, stdin);
        findUsershop(4);
        puts("");
    }
    strcpy(shopUser.store_name, hos_name);

    printf("Enter the city your store is located in* : ");
    fgets(shopUser.cityName, strSize, stdin);
    puts("");

    printf("Enter your city district zone* : ");
    scanf("%d", &shopUser.mantaghe);

    printf("\e[1;1H\e[02J");
    create_statement("signup", "shop_users");
    getchar();
    main_menu();
}

int national_code_check(long int code)
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
    findUsernormal(1);
    findUsershop(1);
    if (!strcmp("return", username) || !strcmp("-1", username))
    {
        printf("Returning to main menu...");
        getchar();
        main_menu();
    }
    printf("Enter your 'code melli'!(return to go back to main menu) : ");
    scanf("%li", &codem);
    puts("");
    printf("Enter your email(return to go back to main menu) : ");
    scanf("%s", email);
    puts("");
    if (strcmp(admin.user_name, username) && (strcmp(uni, "NULL")) && (strcmp(ushi, "NULL")))
    {
        printf("\nUsername not found! returning to main menu...");
        sleep(1);
        getchar();
        main_menu();
    }
    //Admin
    else if ((codem == admin.national_code) && (!strcmp(admin.user_name, username)) && (!strcmp(admin.email, email)))
    {
        //3 step verification (2 left)
        //Steps 2 & 3
        printf("%s\n", TFAQ01);
        scanf("%s", ans1);
        printf("%s\n", TFAQ02);
        scanf("%s", ans2);
        if (!strcmp(ans1, TFAA01) && !strcmp(ans2, TFAA02))
        {
            getPasswd(&pass1, 1, type);
            puts("");
            getPasswd(&pass2, 2, type);
            while (strcmp(pass1, pass2))
            {
                puts("\nPasswords don't match. Try again");
                getPasswd(&pass1, 1, type);
                puts("");
                getPasswd(&pass2, 2, type);
            }
            strcpy(admin.passwd, pass1);
            create_statement("forget", "admin");
            login();
        }
        else
        {
            printf("\n\e[31mYou failed the 2FA test, try again if it's really you.\n");
            sleep(2);
            printf("\e[1;1H\e[2J");
            getchar();
            main_menu();
        }
    }
    //Normal
    else if (strcmp(uni, "NULL") != 0)
    {
        getPasswd(&pass1, 1, type);
        puts("");
        getPasswd(&pass2, 2, type);
        while (strcmp(pass1, pass2))
        {
            puts("\nPasswords don't match. Try again");
            getPasswd(&pass1, 1, type);
            puts("");
            getPasswd(&pass2, 2, type);
        }
        strcpy(normalUser.passwd, pass1);
        create_statement("forget", "normal_users");
        login();
    }
    //Shop
    else if (strcmp(ushi, "NULL") != 0)
    {
        getPasswd(&pass1, 1, type);
        puts("");
        getPasswd(&pass2, 2, type);
        while (strcmp(pass1, pass2))
        {
            puts("\nPasswords don't match. Try again");
            getPasswd(&pass1, 1, type);
            puts("");
            getPasswd(&pass2, 2, type);
        }
        strcpy(shopUser.passwd, pass1);
        create_statement("forget", "shop_users");
        login();
    }
    else
    {
        puts("\e[3-1mThe information you entered didn't match with any user, returning to main menu...\e[0m");
        sleep(2);
        getchar();
        main_menu();
    }
}

void healthCode()
{
    switch (normalUser.health_code)
    {
    case 1:
        printf("\e[1;32mYour health code is %d\e[0m", normalUser.health_code);
        break;
    case 2:
        printf("\e[1;33mYour health code is %d\e[0m", normalUser.health_code);
        break;
    case 3:
        printf("\e[1;91mYour health code is %d\e[0m", normalUser.health_code);
        break;
    case 4:
        printf("\e[1;31mYour health code is %d\e[0m", normalUser.health_code);
        break;
    case 0:
        printf("You haven't taken the test yet");
        break;
    }
}

void health_test(int *score)
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

void edit_info(char userType)
{
    int choice;
    printf("\e[1;1H\e[2J");
    switch (userType)
    {

    //Admin
    case 'a':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change national code.");
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
            printf("Name changed successfuly, proceeding ...");
            sleep(1);
            edit_info('a');
            break;
        case 2:
            getPasswd(&pass1, 1, type);
            if (!strcmp(admin.passwd, pass1))
            {
                printf("\nCurrent email address is %s\n", admin.email);
                printf("Enter new e-mail address : ");
                scanf("%s", email);
                if (!strcmp(email, admin.email))
                {
                    puts("Email remained unchanged...");
                    edit_info('a');
                }
                else
                    strcpy(admin.email, email);
                printf("Email changed successfuly, proceeding...");
                sleep(1);
                edit_info('a');
            }
            else
            {
                printf("Password was incorrect, retry ...");
                sleep(2);
                edit_info('a');
            }
            break;

        case 3:
            printf("Current ID : %li\n", admin.national_code);
            printf("Enter new national code : ");
            scanf("%li", national_code);
            if (national_code == admin.national_code)
            {
                printf("National code is unchanged!, returning...");
                sleep(1);
                edit_info('a');
            }
            while (!national_code_check(national_code))
            {
                printf("your national code must have 10 digits!, enter again : ");
                scanf("%ld", &national_code);
                puts("");
            }
            admin.national_code = national_code;
            puts("");
            printf("national code changed successfully, proceeding...");
            sleep(1);
            edit_info('a');
            break;

        case 4:
            getPasswd(&pass1, 1, type);
            if (!strcmp(admin.passwd, pass1))
            {
                printf("\nCurrent security question and answer 1 are %s : %s\n", TFAQ01, TFAA01);
                printf("Enter new Security question(1) : ");
                scanf("%[^\n]s", TFAQ01);
                getchar();
                printf("Enter new answer(1) : ");
                scanf("%[^\n]s", TFAA01);
                getchar();
                printf("Current security question and answer 2 are %s : %s\n", TFAQ02, TFAA02);
                printf("Enter new Security question(2) : ");
                scanf("%[^\n]s", TFAQ02);
                getchar();
                printf("Enter new answer(2) : ");
                scanf("%[^\n]s", TFAA02);
                getchar();
                printf("Security questions changed successfully, proceeding...");
                sleep(2);
                edit_info('a');
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(1);
                edit_info('a');
            }
            break;

        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            create_statement("edit", "admin");
            sleep(1);
            printf("\e[1;1H\e[02J");
            admin_page();
            break;

        default:
            puts("Wrong input ...");
            sleep(1);
            edit_info('a');
            break;
        }
        break;

    //Normal Users
    case 'n':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change national code.");
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
            printf("Current Name : %s %s\n", normalUser.fname, normalUser.lname);
            printf("Enter new first and last name with a space between them : ");
            scanf("%s", normalUser.fname);
            scanf("%s", normalUser.lname);
            printf("Name changed successfully, proceeding...");
            sleep(1);
            edit_info('n');
            break;

        case 2:
            getPasswd(&pass1, 1, type);
            if (!strcmp(normalUser.passwd, pass1))
            {
                printf("Current email address is %s\n", normalUser.email);
                printf("Enter your new email address : ");
                scanf("%s", email);
                if (!strcmp(email, normalUser.email))
                {
                    puts("Email remained unchanged...");
                    sleep(1);
                    edit_info('n');
                }
                findUsernormal(2);
                puts("");
                while (strcmp(uni, "NULL"))
                {
                    puts("Sorry, this email already exists");
                    printf("Enter your email again : ");
                    scanf("%s", email);
                    findUsernormal(2);
                    puts("");
                }
                strcpy(normalUser.email, email);
                puts("");
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(2);
                edit_info('n');
            }
            printf("Email address changed successfully, proceeding...");
            sleep(1);
            edit_info('n');
            break;

        case 3:
            printf("Current ID : %li\n", normalUser.national_code);
            printf("Enter your new national code(10 digits) : ");
            scanf("%ld", &national_code);
            puts("");
            if (national_code == normalUser.national_code)
            {
                puts("National code remained unchanged...");
                sleep(1);
                edit_info('n');
            }
            while (!national_code_check(national_code))
            {
                printf("your national code must have 10 digits!, enter again : ");
                scanf("%ld", &national_code);
                puts("");
            }
            findUsernormal(3);
            while (strcmp(uni, "NULL"))
            {
                puts("Sorry, this national code is already registered");
                printf("Enter your national code again : ");
                scanf("%ld", &national_code);
                findUsernormal(3);
                puts("");
            }
            normalUser.national_code = national_code;
            puts("");
            printf("national code changed successfully, proceeding...");
            sleep(1);
            edit_info('n');
            break;

        case 4:
            printf("Enter your new Blood group(NULL to skip) : ");
            scanf("%s", normalUser.bloodG);
            puts("");
            printf("Enter your new age :) (0 to skip) : ");
            scanf("%d", &normalUser.age);
            puts("");
            printf("Enter your new height :/ (0 to skip) : ");
            scanf("%d", &normalUser.height);
            puts("");
            printf("Enter your new weight :/ (0 to skip) : ");
            scanf("%d", &normalUser.weight);
            puts("");
            printf("Successfull!, proceeding...");
            sleep(1);
            edit_info('n');
            break;

        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            create_statement("edit", "normal_users");
            sleep(1);
            printf("\e[1;1H\e[02J");
            normal_page();
            break;

        default:
            puts("Wrong input ...");
            sleep(1);
            edit_info('n');
            break;
        }
        break;

    case 's':
        puts("Enter a command to proceed.");
        puts("1. Edit your (first / last)name.");
        puts("2. Edit your email address.");
        puts("3. Change national code.");
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
            printf("Current Name : %s %s\n", shopUser.fname, shopUser.lname);
            printf("Enter new first and last name with a space between them : ");
            scanf("%s", shopUser.fname);
            scanf("%s", shopUser.lname);
            printf("Name changed successfully, proceeding...");
            sleep(1);
            edit_info('s');
            break;

        case 2:
            getPasswd(&pass1, 1, type);
            if (!strcmp(shopUser.passwd, pass1))
            {
                printf("Current email address is %s\n", shopUser.email);
                printf("Enter your new email address : ");
                scanf("%s", email);
                if (!strcmp(email, shopUser.email))
                {
                    puts("Email remained unchanged...");
                    sleep(1);
                    edit_info('s');
                }
                findUsershop(2);
                puts("");
                while (strcmp(ushi, "NULL"))
                {
                    puts("Sorry, this email already exists");
                    printf("Enter your email again : ");
                    scanf("%s", email);
                    findUsershop(2);
                    puts("");
                }
                strcpy(shopUser.email, email);
                puts("");
            }
            else
            {
                printf("Password was incorrect ...");
                sleep(1);
                edit_info('s');
            }
            printf("Email address changed successfully, proceeding...");
            sleep(1);
            edit_info('s');
            break;
        case 3:
            printf("Current ID : %li\n", shopUser.national_code);
            printf("Enter your new national code(10 digits) : ");
            scanf("%ld", &national_code);
            puts("");
            if (national_code == shopUser.national_code)
            {
                puts("National code remained unchanged...");
                sleep(1);
                edit_info('s');
            }
            while (!national_code_check(national_code))
            {
                printf("your national code must have 10 digits!, enter again : ");
                scanf("%ld", &national_code);
                puts("");
            }
            findUsershop(3);
            while (strcmp(ushi, "NULL"))
            {
                puts("Sorry, this national code is already registered");
                printf("Enter your national code again : ");
                scanf("%ld", &national_code);
                findUsershop(3);
                puts("");
            }
            shopUser.national_code = national_code;
            puts("");
            printf("national code changed successfully, proceeding...");
            sleep(1);
            edit_info('s');
            break;

        case 4:
            printf("Enter your new shop name: ");
            fgets(shopUser.store_name, strSize, stdin);
            getchar();
            puts("");
            printf("Enter your shops city followed by its district e.g. (Isfahan 12): ");
            scanf("%s %d", shopUser.cityName, &shopUser.mantaghe);
            printf("Store information changed successfully...");
            sleep(1);
            edit_info('s');
            break;

        case 5:
            printf("\n\e[1mReturning to previous menu...\e[0m");
            create_statement("edit", "shop_users");
            sleep(1);
            printf("\e[1;1H\e[02J");
            shop_page(index);
            break;

        default:
            puts("Wrong input, try again ...");
            sleep(1);
            edit_info('s');
            break;
        }
        break;
    }
}

void create_statement(char *use, char *ut)
{
    int i = 0;
    char values[300];
    if (!strcmp(use, "fetch_data"))
    {
        if (strcmp("admin", ut) != 0)
        {
            snprintf(statement, sizeof(statement), "SELECT * FROM %s WHERE username = '%s';", ut, username);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);
            if (!strcmp("normal_users", ut))
            {
                normalUser.id = atoi(row[0]);
                strcpy(normalUser.user_name, row[1]);
                strcpy(normalUser.passwd, row[2]);
                strcpy(normalUser.fname, row[3]);
                strcpy(normalUser.lname, row[4]);
                strcpy(normalUser.email, row[5]);
                normalUser.national_code = atoi(row[6]);
                normalUser.test_counter = atoi(row[11]);
                normalUser.health_code = atoi(row[12]);
                strcpy(normalUser.cityName, row[14]);
                normalUser.mantaghe = atoi(row[15]);
                mysql_free_result(res);
                snprintf(statement, sizeof(statement), "SELECT * FROM health_tests WHERE id = %d;", normalUser.id);
                if (mysql_query(conn, statement))
                    finish_with_error(conn);
                res = mysql_use_result(conn);
                row = mysql_fetch_row(res);
                if (row != NULL)
                {
                    normalUser.test_score_history[i] = atoi(row[1]);
                    normalUser.test_time_history[i] = atoi(row[2]);
                    i++;
                    while ((row = mysql_fetch_row(res)) != NULL)
                    {
                        normalUser.test_score_history[i] = atoi(row[1]);
                        normalUser.test_time_history[i] = atoi(row[2]);
                        i++;
                    }
                }
                mysql_free_result(res);
            }

            else if (!strcmp("shop_users", ut))
            {
                shopUser.id = atoi(row[0]);
                strcpy(shopUser.user_name, row[1]);
                strcpy(shopUser.passwd, row[2]);
                strcpy(shopUser.fname, row[3]);
                strcpy(shopUser.lname, row[4]);
                strcpy(shopUser.email, row[5]);
                shopUser.national_code = atoi(row[6]);
                strcpy(shopUser.cityName, row[7]);
                shopUser.mantaghe = atoi(row[8]);
                shopUser.disinfection = atoi(row[9]);
                strcpy(shopUser.store_name, row[10]);
                mysql_free_result(res);
            }
        }

        //admin
        else
        {
            if (mysql_query(conn, "SELECT * FROM admin;"))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);
            strcpy(admin.user_name, row[0]);
            strcpy(admin.passwd, row[1]);
            strcpy(admin.fname, row[2]);
            strcpy(admin.lname, row[3]);
            strcpy(admin.email, row[4]);
            admin.national_code = atoi(row[5]);
            mysql_free_result(res);
        }
    }

    else if (!strcmp("signup", use))
    {
        if (!strcmp("normal_users", ut))
        {
            snprintf(statement, sizeof(statement),
                     "INSERT INTO normal_users VALUES(DEFAULT, '%s', '%s', '%s', '%s', '%s', %ld, '%s', %d, %d, %d, DEFAULT, DEFAULT, DEFAULT,'%s', %d);",
                     normalUser.user_name, normalUser.passwd, normalUser.fname, normalUser.lname, normalUser.email,
                     normalUser.national_code, normalUser.bloodG, normalUser.age, normalUser.height, normalUser.weight, normalUser.cityName, normalUser.mantaghe);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }

        if (!strcmp("shop_users", ut))
        {
            snprintf(statement, sizeof(statement),
                     "INSERT INTO shop_users VALUES(DEFAULT, '%s', '%s', '%s', '%s', '%s', %ld, '%s', %d, %d, '%s');",
                     shopUser.user_name, shopUser.passwd, shopUser.fname, shopUser.lname, shopUser.email,
                     shopUser.national_code, shopUser.cityName, shopUser.mantaghe, shopUser.disinfection, shopUser.store_name);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }
    }

    else if (!strcmp("forget", use))
    {
        char newpass[50];

        //Admin
        if (!strcmp("admin", ut))
            strcpy(newpass, admin.passwd);

        //normal
        else if (!strcmp("normal_users", ut))
            strcpy(newpass, normalUser.passwd);

        //shop
        else if (!strcmp("shop_users", ut))
            strcpy(newpass, shopUser.passwd);

        snprintf(statement, sizeof(statement), "UPDATE %s SET password = '%s' WHERE username = '%s';", ut, newpass, username);

        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        mysql_free_result(res);
    }

    else if (!strcmp("edit", use))
    {
        //Admin
        if (!strcmp("admin", ut))
        {
            snprintf(statement, sizeof(statement),
                     "UPDATE admin SET username = '%s', password = '%s', first_name = '%s', last_name = '%s', email = '%s', national_code = %ld, Sec_Q1 = '%s', Sec_A1 = '%s', Sec_Q2 = '%s', Sec_A2 = '%s';",
                     admin.user_name, admin.passwd, admin.fname, admin.lname, admin.email, admin.national_code,
                     TFAQ01, TFAA01, TFAQ02, TFAA02);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }

        //Normal
        else if (!strcmp("normal_users", ut))
        {
            snprintf(statement, sizeof(statement),
                     "UPDATE normal_users SET first_name = '%s', last_name = '%s', email = '%s', national_code = %ld, blood_group = '%s', age = %d, height = %d, weight = %d WHERE username = '%s';",
                     normalUser.fname, normalUser.lname, normalUser.email, normalUser.national_code, normalUser.bloodG,
                     normalUser.age, normalUser.height, normalUser.weight, normalUser.user_name);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }

        //Shop
        else if (!strcmp("shop_users", ut))
        {
            snprintf(statement, sizeof(statement),
                     "UPDATE shop_users SET first_name = '%s', last_name = '%s', email = '%s', national_code = %ld, city = '%s', province = %d, store_name = '%s' WHERE username = '%s';",
                     shopUser.fname, shopUser.lname, shopUser.email, shopUser.national_code, shopUser.cityName,
                     shopUser.mantaghe, shopUser.store_name, shopUser.user_name);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            mysql_free_result(res);
        }
    }

    else if (!strcmp("add_hospital", use)) //admin
    {
        snprintf(statement, sizeof(statement), "INSERT INTO hospitals values (DEFAULT, '%s', '%s', %d);", hos_name, city, province);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        mysql_free_result(res);
    }

    else if (!strcmp("show_hospital", use))
    {
        //Admin
        if (!strcmp("admin", ut))
        {
            if (mysql_query(conn, "SELECT * FROM hospitals ORDER BY city, name;"))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            if ((row = mysql_fetch_row(res)) == NULL)
                puts("No hospital was found, Sorry :(");
            else
            {
                puts("\nName | City | District~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n%s | %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[1], row[2], row[3]);
                while ((row = mysql_fetch_row(res)) != NULL)
                    printf("\n%s | %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[1], row[2], row[3]);
            }
            mysql_free_result(res);
        }

        //Normal
        else if (!strcmp("normal_users", ut))
        {
            snprintf(statement, sizeof(statement), "SELECT * FROM hospitals WHERE city = '%s', district = %d ORDER BY name;", normalUser.cityName, normalUser.mantaghe);
            if (mysql_query(conn, "SELECT * FROM hospitals ORDER BY city, name;"))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            if ((row = mysql_fetch_row(res)) == NULL)
                puts("No hospital was found, Sorry :(");
            else
            {
                puts("\nName | City | District~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n%s | %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[1], row[2], row[3]);
                while ((row = mysql_fetch_row(res)) != NULL)
                    printf("\n%s | %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[1], row[2], row[3]);
            }
            mysql_free_result(res);
        }
    }

    else if (!strcmp("see_all_normals", use)) //admin
    {
        if (!strcmp("admin", ut))
        {
            if (mysql_query(conn, "SELECT first_name, last_name, national_code, cov_code FROM normal_users ORDER BY last_name, first_name;"))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            puts("      Name     | national_code | Corona code\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            while ((row = mysql_fetch_row(res)) != NULL)
                printf("%s %s | %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], row[1], row[2], row[3]);
            mysql_free_result(res);
        }

        else
        {
            snprintf(statement, sizeof(statement), "SELECT pm.person_id, n.first_name, n.last_name, n.cov_code FROM place_meetings pm JOIN normal_users n ON pm.person_id = n.id AND pm.place_id = %d;", shopUser.id);
            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            puts(" ID |        Name        | Corona code\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            while ((row = mysql_fetch_row(res)) != NULL)
                printf("%s | %s %s | %s\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], row[1], row[2], row[3]);
            mysql_free_result(res);
        }
    }

    else if (!strcmp("see_all_shops", use))
    {
        if (mysql_query(conn, "SELECT store_name, national_code, disinfection_status FROM shop_users ORDER BY store_name, national_code;"))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        puts(" Store Name   | national_code | Store status\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            if (!strcmp(row[2], "1"))
                printf("%s | %s | \e[1;42;37mWHITE\e[0m\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], row[1]);
            else
                printf("%s | %s | \e[1;37;41mRED\e[0m\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], row[1]);
        }
        mysql_free_result(res);
    }

    else if (!strcmp("see_sicks", use))
    {
        if (!strcmp("admin", ut))
        {
            if (mysql_query(conn, "SELECT first_name, last_name, national_code, sickness_time FROM normal_users WHERE cov_code = 4 ORDER BY last_name, first_name;"))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);
            if (row == NULL)
            {
                puts("\e[1;32mNo one is sick!! :)\e[0m");
                strcpy(city, "NULL");
            }
            else
            {
                printf("\n       Name      | national code | date of sickness\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                long int t = atoi(row[3]);
                printf("\n\n%s %s | %s | %s\n", row[0], row[1], row[2], asctime(localtime(&t)));
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                while ((row = mysql_fetch_row(res)) != NULL)
                {
                    long int t = atoi(row[3]);
                    printf("\n\n%s %s | %s | %s\n", row[0], row[1], row[2], asctime(localtime(&t)));
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                }
                puts("");
            }
        }

        else if (!strcmp("normal_users", ut))
        {
            long int t = time(NULL);
            snprintf(statement, sizeof(statement), "SELECT last_name, sickness_time FROM normal_users WHERE cov_code = 4 AND ABS (sickness_time - %ld) < 604800 ORDER BY sickness_time DESC;", t);

            if (mysql_query(conn, statement))
                finish_with_error(conn);
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);

            if (row == NULL)
                puts("\e[1;32mNo one got sick in the previous week :)\e[0m");

            else
            {
                printf("\n     Name    | date of sickness\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                long int t = atoi(row[1]);
                printf("\n\n%s | %s \n", row[0], asctime(localtime(&t)));
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                while ((row = mysql_fetch_row(res)) != NULL)
                {
                    long int t = atoi(row[1]);
                    printf("\n\n%s | %s \n", row[0], asctime(localtime(&t)));
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                }
                puts("");
            }
        }
        mysql_free_result(res);
    }

    else if (!strcmp("heal", use))
    {
        snprintf(statement, sizeof(statement), "UPDATE normal_users SET cov_code = 2 WHERE national_code = %ld;", national_code);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        // res = mysql_use_result(conn);
        //mysql_free_result(res);
    }

    else if (!strcmp("kill", use))
    {
        time_t time_kill = time(NULL);
        snprintf(statement, sizeof(statement), "UPDATE normal_users SET cov_code = 5, sickness_time = %ld WHERE national_code = %ld;", time_kill, national_code);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        // res = mysql_use_result(conn);
        //mysql_free_result(res);
    }

    else if (!strcmp("see_deaths", use))
    {
        if (mysql_query(conn, "SELECT first_name, last_name, national_code, sickness_time FROM normal_users WHERE cov_code = 5 ORDER BY last_name, first_name;"))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row == NULL)
            puts("\e[1;32mNo one is dead!! :)\e[0m");
        else
        {
            printf("\n       Name      | national code | date of death report\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            long int t = atoi(row[3]);
            printf("\n\n%s %s | %s | %s\n", row[0], row[1], row[2], asctime(localtime(&t)));
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                long int t = atoi(row[3]);
                printf("\n\n%s %s | %s | %s\n", row[0], row[1], row[2], asctime(localtime(&t)));
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            }
            puts("");
        }
        mysql_free_result(res);
    }

    else if (!strcmp("visit_place", use))
    {
        time_t t = time(NULL);
        snprintf(statement, sizeof(statement), "INSERT INTO place_meetings VALUES (%d, %d, %ld);", normalUser.id, atoi(ushi), t);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        mysql_free_result(res);
    }

    else if (!strcmp("visit_person", use))
    {
        time_t t = time(NULL);
        snprintf(statement, sizeof(statement), "INSERT INTO person_meetings VALUES (%ld, %ld, %ld);", normalUser.national_code, national_code, t);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        mysql_free_result(res);
    }

    else if (!strcmp("see_visited_places", use))
    {
        snprintf(statement, sizeof(statement), "SELECT sh.store_name, sh.disinfection_status, pm.time FROM place_meetings pm JOIN shop_users sh ON pm.place_id = sh.id AND pm.person_id = %d;", normalUser.id);
        if (mysql_query(conn, statement))
            finish_with_error(conn);

        res = mysql_use_result(conn);
        puts("    Name    |    Status    | Time of visit\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            long int t = atoi(row[2]);
            if (!strcmp(row[1], "1"))
                printf("%s | \e[1;42;37mWHITE\e[0m | %s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], asctime(localtime(&t)));

            else
                printf("%s | \e[1;37;41mRED\e[0m | %s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], asctime(localtime(&t)));
        }
        mysql_free_result(res);
    }

    /*else if (!strcmp("see_visited_users", use))
    {
        snprintf(statement, sizeof(statement), "SELECT sh.store_name, sh.disinfection_status, pm.time FROM place_meetings pm JOIN shop_users sh ON pm.place_id = sh.id AND pm.person_id = %d;", normalUser.id);
        if (mysql_query(conn, statement))
            finish_with_error(conn);
        res = mysql_use_result(conn);
        puts("    Name    |    Status    | Time of visit\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            long int t = atoi(row[2]);
            if (!strcmp(row[1], "1"))
                printf("%s | \e[1;42;37mWHITE\e[0m | %s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], asctime(localtime(&t)));

            else
                printf("%s | \e[1;37;41mRED\e[0m | %s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", row[0], asctime(localtime(&t)));
        }
        mysql_free_result(res);
    }*/
}

void finish_with_error(MYSQL *conn)
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}
