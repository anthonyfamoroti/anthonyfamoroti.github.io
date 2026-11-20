#include <stdio.h>
#include "hash_table.h"

int main(void)
{
    HashTable ht;
    initialise_hash_table(&ht);

 // Load existing users from the file
    if (load_users_from_file(&ht, "users.txt") != SUCCESS)
    {
        printf("Failed to load users from file.\n");
        free_buckets(&ht);
        return 1;
    }
 printf("Users loaded successfully!\n");

    int user_id;
    char password[MAX_PASSWORD_LEN + 1];
    char entered_password[MAX_PASSWORD_LEN + 1];

    // Get the user ID
    printf("Enter user ID: ");
    if (scanf("%d", &user_id) != 1)
    {
        printf("Invalid user ID.\n");
        free_buckets(&ht);
        return 1;
    }

    // Get the password
    printf("Enter password: ");
    if (scanf("%40s", password) != 1)
    {
        printf("Failed to read password.\n");
        free_buckets(&ht);
        return 1;
    }

    // Register the user
    int result = register_user(&ht, user_id, password);
    if (result == SUCCESS)
    {
        printf("User registered successfully!\n");
    }
    else
    {
        printf("User registration failed.\n");
        free_buckets(&ht);
        return 1;
    }

    // Check the password
    printf("Enter password to check: ");
    if (scanf("%40s", entered_password) != 1)
    {
        printf("Failed to read password.\n");
        free_buckets(&ht);
        return 1;
    }

    result = is_valid_password(&ht, user_id, entered_password);
    if (result == SUCCESS)
    {
        printf("Password is correct!\n");
    }
    else
    {
        printf("Password is incorrect.\n");
    }

    // Free allocated memory
    free_buckets(&ht);

    return 0;
}
