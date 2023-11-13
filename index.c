#include <stdio.h>
#include <string.h>

struct User
{
    char username[50];
    char password[50];
    union {
        int flag;
        _Bool isActive;
    };
};

void registerUser(struct User users[], int *userCount)
{
    struct User newUser;
    printf("Enter the username: ");
    scanf("%s", newUser.username);
    printf("Enter the password: ");
    scanf("%s", newUser.password);

    // Ask the user to set the flag
    printf("Enter flag (0 for False, 1 for True): ");
    scanf("%d", &newUser.flag);

    users[*userCount] = newUser;
    (*userCount)++;
    printf("Registration successful\n");
}

int loginUser(struct User users[], int userCount, char username[], char password[])
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return users[i].isActive;
        }
    }
    return 0;
}

int main()
{
    struct User users[100];
    int userCount = 0;
    int loggedIn = 0;
    char currentUser[50];

    int choice;
    do
    {
        printf("\n1. Register\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (userCount < 100)
            {
                registerUser(users, &userCount);
            }
            else
            {
                printf("Maximum number of users reached.\n");
            }
            break;
        case 2:
            if (loggedIn)
            {
                printf("You are already logged in as %s.\n", currentUser);
            }
            else
            {
                char username[50];
                char password[50];
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);

                int loginResult = loginUser(users, userCount, username, password);
                if (loginResult == 1)
                {
                    loggedIn = 1;
                    strcpy(currentUser, username);
                    printf("Login successful!\n");
                }
                else if (loginResult == 0)
                {
                    printf("Login failed. Invalid username or password.\n");
                }
                else
                {
                    printf("Login failed. Account is not active.\n");
                }
            }
            break;
        case 3:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 3);

    return 0;
}