#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_USERS 1000
#define CODE_LENGTH 6
#define FILE_NAME "user_data.txt"
#define MAX_PASSWORD_LENGTH 20
#define MAX_ATTEMPTS 3

void faculty();
void staff();

struct teacher
{
    char tname[100];
    char sectionHandled[100];
};

struct student {
    float gwa;
    long int lrn;
    char firstname[100];
    char middlename[100];
    char lastname[100];
    char gender;
    int month, day, year;
    int age;
    char citizenship[50];
    char civstat[50];
    char address[50];
    char email[30];
    int contnumber;
    char school[100];
    int yeargrad;
    char id[20];
    char name[100];
    char statuss[20];
    int id_num;
    char mother[100];
    char father[100];
};

typedef struct {
    char name[50];
    char lastName[50];
    char code[CODE_LENGTH + 1]; // +1 for null terminator
} User;

User users[MAX_USERS];
int totalUsers = 0;

int isCodeUnique(const char *code) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].code, code) == 0) {
            return 0; // Code is not unique
        }
    }
    return 1; // Code is unique
}

void generateCode(char *code, int length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    do {
        for (int i = 0; i < length; i++) {
            int index = rand() % (sizeof(charset) - 1);
            code[i] = charset[index];
        }
        code[length] = '\0'; // Null-terminate the code
    } while (!isCodeUnique(code));
}

void saveUserDataToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < totalUsers; i++) {
        fprintf(file, "%s %s %s\n", users[i].name, users[i].lastName, users[i].code);
    }

    fclose(file);
}

void loadUserDataFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(file, "%49s %49s %6s", users[totalUsers].name, users[totalUsers].lastName, users[totalUsers].code) == 3) {
        totalUsers++;
        if (totalUsers >= MAX_USERS) {
            break;
        }
    }

    fclose(file);
}

void signUp() {
    if (totalUsers >= MAX_USERS) {
        printf("Maximum users limit reached.\n");
        return;
    }

    User newUser;

    printf("\t\tEnter your name: ");
    scanf("%s", newUser.name);

    printf("\t\tEnter your last name: ");
    scanf("%s", newUser.lastName);

    generateCode(newUser.code, CODE_LENGTH);

    users[totalUsers++] = newUser;
    printf("\t\tUser signed up successfully! Your login code is: %s\n", newUser.code);

    // Save user data to file after signup
    saveUserDataToFile();
}

void signIn() {
    char inputCode[CODE_LENGTH + 1];
    int validUser = 0;

    printf("\n\n\t\t\t\tSIGN IN\n\n\n");
    printf("\t\t\tEnter your login code: ");
    scanf("%6s", inputCode);

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].code, inputCode) == 0) {
            printf("\n\t\t*------------------------------------------*\n");
            printf("\t\t|                                          |\n");
            printf("\t\t|      User signed in successfully!        |\n");
            printf("\t\t|                                          |\n");
            printf("\t\t*------------------------------------------*\n");
            printf("\n\t\t\tPress any key to continue...");
            getchar(); // Consume the newline character left in the input buffer
            getchar(); // Wait for user to press a key
            validUser = 1;
            stud();
            break;
        }
    }

    if (!validUser) {
        printf("\n\t\t*---------------------------------------*\n");
        printf("\t\t|                                       |\n");
        printf("\t\t|         Invalid login code.            |\n");
        printf("\t\t|                                       |\n");
        printf("\t\t*---------------------------------------*\n");
    }

    return validUser;
}

void login()
{
    char inputCode[CODE_LENGTH + 1];
    int validUser = 0;

    printf("\n\n\t\t\t\tSIGN IN\n\n\n");
    printf("\t\t\tEnter your login code: ");
    scanf("%6s", inputCode);

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].code, inputCode) == 0) {
            printf("\n\t\t*------------------------------------------*\n");
            printf("\t\t|                                          |\n");
            printf("\t\t|      User signed in successfully!        |\n");
            printf("\t\t|                                          |\n");
            printf("\t\t*------------------------------------------*\n");
            printf("\n\t\t\tPress any key to continue...");
            getchar(); // Consume the newline character left in the input buffer
            getchar(); // Wait for user to press a key
            validUser = 1;
            break;
        }
    }

    if (!validUser) {
        printf("\n\t\t*---------------------------------------*\n");
        printf("\t\t|                                       |\n");
        printf("\t\t|         Invalid login code.            |\n");
        printf("\t\t|                                       |\n");
        printf("\t\t*---------------------------------------*\n");
    }

    return validUser;
}


void preadmin2() {
    int choice;

    do {
        printf("\n\t\t***************************************\n");
        printf("\t\t**             ACCOUNT MENU          **\n");
        printf("\t\t***************************************\n");
        printf("\n\t\t1. Sign Up\n");
        printf("\n\t\t2. Sign In\n");
        printf("\n\t\t3. Exit\n");
        printf("\n\t\t======================================");
        printf("\n\n\t\tChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                signIn();
                break;
            case 3:
                printf("\n\t\t\tExiting program...");
                exit(0);
                break;
            default:
                printf("\n\t\tInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);
}

void preadmin1() {
    int choice;

    do {
        printf("\n\t\t***************************************\n");
        printf("\t\t**             ACCOUNT MENU          **\n");
        printf("\t\t***************************************\n");
        printf("\n\t\t1. Sign Up\n");
        printf("\n\t\t2. Sign In\n");
        printf("\n\t\t3. Exit\n");
        printf("\n\t\t======================================");
        printf("\n\n\t\tChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("\n\t\t\tExiting program...");
                exit(0);
                break;
            default:
                printf("\n\t\tInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);
}

void mainmenu() {
    int choice;

    do {
        system("cls");

        printf("\n\t\t***************************************\n");
        printf("\t\t**             MAIN MENU             **\n");
        printf("\t\t***************************************\n");
        printf("\n\t\t1. STUDENT\n");
        printf("\n\t\t2. ADMIN\n");
        printf("\n\t\t3. EXIT\n");
        printf("\n\t\t======================================");
        printf("\n\n\t\tAre you a student or an admin? \n");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                student();
                break;

            case 2:
                preadmin();
                break;

            case 3:
                printf("\n\t\t\tExiting Program...");
                exit(0);
                break;

            default:
                printf("\n\t\tInvalid, please enter another. \n");
        }
    } while (choice != 3);
}

void student()
{
    preadmin2();
}

int main() {
    loadUserDataFromFile();
    mainmenu();
    return 0;
}

void stud()
{
    int choice;

    do{
        system("cls");
        printf("\n\t\t***************************************\n");
        printf("\t\t**           STUDENT MENU            **\n");
        printf("\t\t***************************************\n");
        printf("\n\n\t\t1. Fill out Application Form");
        printf("\n\n\t\t2. Check Status");
        printf("\n\n\t\t3. Exit");
        printf("\n\n\t\t======================================");
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            fillout();
            break;

        case 2:
            check();
            break;
        case 3:
            exit(1);
            break;

        default:
            printf("\nInvalid choice, please enter another");
            break;
        }
    }while(choice!=3);
}

void makeUpperCase(char str[])
{
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}


void fillout()
{
    system("cls");
    int i;
    char status[50];

    struct student s;
	int size;
	FILE *fp;
	size=sizeof(s);
	fp=fopen("jaxper.dat","ab");



    printf("\n\t\t*================================*\n");
    printf("\t\t||\t\t\t\t||\n");
    printf("\t\t||\tGWA: ");
    scanf("%f", &s.gwa);
    printf("\t\t||\t--------------------\t||\n");
    printf("\t\t||\t\t\t\t||\n");
    printf("\t\t*================================*\n");
    printf("\n\nApplication Information\n");
    Sleep(2000);

    system("cls");


    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tLRN:\t");
    scanf("%ld", &s.lrn);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tFirst Name:\t");
    scanf(" %[^\n]s", &s.firstname);
    makeUpperCase(s.firstname);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tMiddle Name:\t");
    scanf(" %[^\n]s", &s.middlename);
    makeUpperCase(s.middlename);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tLast Name:\t");
    scanf(" %[^\n]s", &s.lastname);
    makeUpperCase(s.lastname);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tGender (M/F):\t");
    scanf(" %s", &s.gender);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tDate of Birth (mm dd yyyy): ");
    scanf("%d %d %d", &s.month, &s.day, &s.year);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tAge: ");
    scanf("%d", &s.age);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tCitizenship: ");
    scanf(" %s", &s.citizenship);
    makeUpperCase(s.citizenship);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tCivil Status: ");
    scanf(" %s", &s.civstat);
    makeUpperCase(s.civstat);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tAddress: ");
    scanf(" %[^\n]s", &s.address);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tEmail: ");
    scanf(" %s", &s.email);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tContact Number: ");
    scanf("%d", &s.contnumber);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tName of Last School Attended: ");
    scanf(" %[^\n]s", &s.school);
    makeUpperCase(s.school);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tYear Graduated: ");
    scanf("%d", &s.yeargrad);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tName Of Mother: ");
    scanf(" %[^\n]s", &s.mother);
    makeUpperCase(s.mother);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t\t\t\t\t\t\t\t\t\t\t||\n");
    printf("\t\t||\tName of Father: ");
    scanf(" %[^\n]s", &s.father);
    makeUpperCase(s.father);
    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");

    printf("\t\t||\t\t----------------------------------------\t\t\t\t\t||\n");
    printf("\n\t\t*===============================================================================================*\n\n\n");

    strcpy(status, "Pending");
    strcpy(s.statuss, status);

    s.id_num = -1;

		fwrite(&s,size,1,fp);
		fclose(fp);

    printf("\nRecord Saved...");
    Sleep(1000);

    printf("\nGoing back to Student Function in ");
    for(int i=3; i>0; i--)
    {
        printf(" %d", i);
        Sleep(1000);
    }

    system("cls");


}


void admin()
{
    int choice;

    do {
        system("cls");

        printf("\n\t\t***************************************\n");
        printf("\t\t**               ADMIN               **\n");
        printf("\t\t***************************************\n");
        printf("\n\t\t1. FACULTY\n");
        printf("\n\t\t2. STAFF\n");
        printf("\n\t\t3. GO BACK\n");
        printf("\n\t\t======================================");
        printf("\n\n\t\tAre you a student or an admin? \n");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                faculty();
                break;

            case 2:
                staff();
                break;

            case 3:
                return;

            default:
                printf("\n\t\tInvalid, please enter another. \n");
        }
    } while (choice != 3);
}

void faculty()
{
    preadmin1();
}

void staff()
{
    int choice;

    do
    {
        printf("\n\t\t***************************************\n");
        printf("\t\t**               STAFF               **\n");
        printf("\t\t***************************************\n");
        printf("\t\t1. Add Teacher and his/her section handled\n");
        printf("\t\t2. View List\n");
        printf("\t\t3. Delete Techear\n");
        printf("\t\t4. Edit Teacher\n");
        printf("\t\t5. Go back\n");
        printf("\t\t\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addTeacher();
            break;
        case 2:
            viewlistTeach();
            break;
        case 3:
            deleTeacher();
            break;
        case 4:
            modify();
            break;
        case 5:
            admin();

            break;
        default:
            printf("Invalid, please enter only 1-4");
            break;
        }
    }while(1);
}

addTeacher()
{
FILE *fp;
    struct teacher t;

    fp = fopen("teacher.dat", "ab");

    if (fp == NULL) {
        printf("Error opening the file.");
        return;
    }

    printf("Name of Teacher: ");
    scanf(" %[^\n]s", t.tname); // Removed & before t.tname
    printf("Section he/she handles: ");
    scanf(" %[^\n]s", t.sectionHandled); // Removed & before t.sectionHandled

    fwrite(&t, sizeof(struct teacher), 1, fp); // Changed s to t and included sizeof(struct teacher)
    fclose(fp);


}

void viewlistTeach() {
    system("cls");
    FILE *fp;
    struct teacher t;
    fp = fopen("teacher.dat", "rb");

    printf("\n\t\t*===============================================================================================*\n");
    printf("\t\t\t\t    TEACHERS AND ASSIGNED SECTIONS\n\n\t\t\t");
    printf("\n\t\t*===============================================================================================*\n");

    printf("\n\t\t______________________________________________________\n");
    printf("\t\t| %-4s | %-20s | %-20s |\n", "No.", "Teacher", "Section");
    printf("\t\t|______|______________________|______________________|\n");

    int no = 1;

    while (1) {
        fread(&t, sizeof(t), 1, fp);

        if (feof(fp)) {
            break;
        }
        printf("\t\t| %-4d | %-20s | %-20s |\n", no++, t.tname, t.sectionHandled);
        printf("\t\t|______|______________________|______________________|\n");
    }

    printf("\n===============================================================================================================\n\n");

    fclose(fp);

    printf("Press any key to continue...");
    getch();
    system("cls");
    return;
}

void deleTeacher()
{
    FILE *fp, *fp1;
    struct teacher t;
    int found = 0;

    char tnametoDel[50];

    fp = fopen("teacher.dat", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError opening file for reading.\n");
        return;
    }

    fp1 = fopen("temporary.dat", "wb");
    if (fp1 == NULL)
    {
        printf("\n\t\tError opening file for writing.\n");
        fclose(fp);
        return;
    }

    printf("\n\t\tEnter the name of the teacher you want to delete: ");
    scanf(" %[^\n]s", tnametoDel);

    while (fread(&t, sizeof(t), 1, fp) == 1)
    {
        if (strcmp(t.tname, tnametoDel) == 0)
        {
            found = 1;
            printf("%s Deleted\n", t.tname);
            printf("Press any Key to continue\n");
            getch();
        }
        else
        {
            fwrite(&t, sizeof(t), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found == 0)
    {
        printf("\n\t\tSorry, No Record Found.\n\n");
    }
    else
    {
        fp = fopen("teacher.dat", "wb");
        if (fp == NULL)
        {
            printf("\n\t\tError opening file for writing.\n");
            return;
        }

        fp1 = fopen("temporary.dat", "rb");

        if (fp1 == NULL)
        {
            printf("\n\t\tError opening file for reading.\n");
            fclose(fp);
            return;
        }

        while (fread(&t, sizeof(t), 1, fp1) == 1)
        {
            fwrite(&t, sizeof(t), 1, fp);
        }
    }

    fclose(fp);
    fclose(fp1);
}

void modify()
{
    FILE *fp, *fp1;
    struct teacher t;
    char tnametoEdit[50];
    int found = 0;

    fp = fopen("teacher.dat", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError opening file for reading.\n");
        return;
    }

    fp1 = fopen("temporary.dat", "wb");
    if (fp1 == NULL)
    {
        printf("\n\t\tError opening file for writing.\n");
        fclose(fp);
        return;
    }

    printf("\n\t\tEnter the name of Teacher you want to modify: ");
    scanf(" %[^\n]s", tnametoEdit);

    while (fread(&t, sizeof(t), 1, fp) == 1)
    {
        if (strcmp(t.tname, tnametoEdit) == 0)
        {
            found = 1;

            printf("\n\t\tEnter the new data for Teacher\n");
            printf("Edit the Name: ");
            scanf(" %[^\n]s", t.tname);
            printf("Edit the Section: ");
            scanf(" %[^\n]s", t.sectionHandled);

            printf("\nInformation Successfully Updated\n");
            printf("Press Any Key to Continue...");
            getch();
            fwrite(&t, sizeof(t), 1, fp1);
        }
        else
        {
            fwrite(&t, sizeof(t), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found == 0)
    {
        printf("\t\tSorry, No Record Found.\n\n");
    }
    else
    {
        fp = fopen("teacher.dat", "wb");
        if (fp == NULL)
        {
            printf("\n\t\tError opening file for writing.\n");
            return;
        }

        fp1 = fopen("temporary.dat", "rb");
        if (fp1 == NULL)
        {
            printf("\n\t\tError opening file for reading.\n");
            fclose(fp);
            return;
        }

        while (fread(&t, sizeof(t), 1, fp1) == 1)
        {
            fwrite(&t, sizeof(t), 1, fp);
        }
    }

    fclose(fp);
    fclose(fp1);
}

void check() {
    system("cls");
    char searchCode[CODE_LENGTH + 1];
    int found = 0;

    printf("\n\t\t***************************************\n");
    printf("\t\t**        CHECK STATUS MENU         **\n");
    printf("\t\t***************************************\n");
    printf("\n\t\tEnter your login code: ");
    scanf("%6s", searchCode);

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].code, searchCode) == 0) {
            printf("\n\t\t*----------------------------------------*\n");
            printf("\t\t|    User Information                   |\n");
            printf("\t\t*----------------------------------------*\n");
            printf("\t\t| Name: %s %s\n", users[i].name, users[i].lastName);
            printf("\t\t*----------------------------------------*\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\t*---------------------------------------*\n");
        printf("\t\t|                                       |\n");
        printf("\t\t|   User not found or invalid code.     |\n");
        printf("\t\t|                                       |\n");
        printf("\t\t*---------------------------------------*\n");
    }

    printf("\n\t\tPress any key to continue...");
    getchar(); // Consume the newline character left in the input buffer
    getchar(); // Wait for user to press a key
}

void getPasswordInput(char *buffer) {
    // Function to capture password securely
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13 || ch == 10) { // Enter key
            buffer[i] = '\0'; // Null terminate the string
            break;
        } else if (ch == 8 && i > 0) { // Backspace
            printf("\b \b");
            i--;
        } else if (i < MAX_PASSWORD_LENGTH - 1) {
            buffer[i++] = ch;
            printf("*");
        }
    }
}

void preadmin()
{
    int choice;

    printf("1.LOG IN\n");
    printf("2.CHANGE PASSWORD\n");
    printf("3.Main Menu\n");
    printf("ENTER CHOICE: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            systemPassword();
            break;
        case 2:
            changeSystemPassword();
            break;
        case 3:
            mainmenu();
            break;
    }
}

void systemPassword() {
    char enteredPassword[MAX_PASSWORD_LENGTH + 1];
    int attempts = 0;

    printf("\n\t\t***************************************\n");
    printf("\t\t**            SYSTEM LOGIN           **\n");
    printf("\t\t***************************************\n");

    while (attempts < MAX_ATTEMPTS) {
        printf("\n\n\t\tEnter System Password: ");
        getPasswordInput(enteredPassword);

        if (strcmp(enteredPassword, "1") == 0) { // Replace "YOUR_SYSTEM_PASSWORD" with the actual system password
            printf("\n\n\t\tPassword Correct!\n");
            printf("\n\n\n\t\tPress any key to continue...");
            getch();
            admin();
            return 1;
        } else {
            attempts++;
            printf("\n\t\tLogin Failed. Incorrect system password.\n");
            printf("\n\t\tAttempts left: %d\n", MAX_ATTEMPTS - attempts);
            printf("\n\t\t***************************************\n");
        }
    }

    printf("\n\t\tMaximum login attempts reached. Exiting program...\n");
}

void changeSystemPassword() {


    char currentPassword[MAX_PASSWORD_LENGTH + 1];
    char newPassword[MAX_PASSWORD_LENGTH + 1];

    printf("\n\t\t***************************************\n");
    printf("\t\t**         CHANGE PASSWORD          **\n");
    printf("\t\t***************************************\n");

    printf("\n\n\t\tEnter Current Password: ");
    getPasswordInput(currentPassword);

    // Validate the current password (replace "1" with the actual current password)
    if (strcmp(currentPassword, "1") != 0) {
        printf("\n\t\tInvalid current password. Change password failed.\n");
        return;
    }

    printf("\n\n\t\tEnter New Password: ");
    getPasswordInput(newPassword);

    // Save or update the new password (replace "1" with the actual storage/update logic)
    printf("\n\t\tPassword changed successfully!\n");
    printf("\n\t\t***************************************\n");
}

