#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialise_hash_table(HashTable *ht)
{
    // no return value required
if (ht == NULL)
{
    return;
}
for (int i = 0; i < HASH_TABLE_SIZE; i++)
{
ht ->buckets[i] = NULL;
}
}




// This function should return a valid hash table
// index (which will be a value >= 0), or a value 
// of -1 if an error or issue is detected.
// Don't use the ERROR return type, use -1 instead
int get_bucket_for_user(int user_id)
{
int index = user_id % HASH_TABLE_SIZE;
if (index >= 0  )
{
    return index;
}
else
{
    return -1;
}
}







// This function should return a pointer to a user found
// or a value of NULL otherwise. Don't use the ERROR return type
User *find_user(const HashTable *ht, int user_id)
{
  if (ht == NULL || user_id < 0)
{
    return NULL;
}
 int table = get_bucket_for_user(user_id);
 User *pointer =  ht ->buckets[table];
 while (pointer != NULL)
 {
 if (pointer -> user_id == user_id)
 {
 return pointer;
 }
 pointer = pointer -> next;

 }
    return NULL;
}







// This function should return SUCCESS upon successful addition
// of user to table (or successful updating of existing user).
// It should return ERROR for any other outcome.
int register_user(HashTable *ht, int user_id, char password[])
{
if ( ht == NULL || user_id <0 || password == NULL )
{
    return ERROR;
    
}
if (strlen(password) > MAX_PASSWORD_LEN)
{
    return ERROR;
}
User *currentuser = find_user(ht , user_id);
if (currentuser != NULL)
{
    strcpy(currentuser ->password, password);
    return SUCCESS;
}
int table = get_bucket_for_user(user_id);
if (table < 0)
{
    return ERROR;
}
User *newuser  = (User*)malloc(sizeof (User));
if (newuser == NULL)
{
 return ERROR;
}
newuser ->user_id = user_id;           // fill in the new user details 
strcpy(newuser ->password, password);

newuser -> next = ht ->buckets[table];
ht ->buckets[table] = newuser;

    return SUCCESS;
}







// This function should return SUCCESS if it ascertains that 
// the password provided is a correct match for the relevant
// user in the table (as identified by 'user_id').
// It should return ERROR for any other outcome.
int is_valid_password(const HashTable *ht, int user_id, char password[])
{
if ( ht == NULL || user_id < 0 || password == NULL)
{
    return ERROR;
}
User *relevantuser = find_user( ht, user_id);
if ( relevantuser == NULL)
{
    return ERROR;
}
if (strcmp( relevantuser -> password, password) == 0)
{
    return SUCCESS;
}
    return ERROR;
}







void free_buckets(HashTable *ht)
{
    // nothing to return
if ( ht == NULL)
{
    return;
}
for ( int i = 0; i < HASH_TABLE_SIZE; i++)
{
User *pointer = ht ->buckets[i];
while ( pointer != NULL)
{
    User *nextuser = pointer ->next;
    free(pointer);
    pointer = nextuser;
}
ht ->buckets[i] = NULL;
}
}







// This function should return SUCCESS upon successful loading
// of data from the file. 
// It should return ERROR for any other outcome.
int load_users_from_file(HashTable *ht, char filename[])
{
if ( ht == NULL || filename == NULL)
{
    return ERROR;
}
FILE *filepointer;
filepointer = fopen(filename ,"r");
if (filepointer == NULL)
{
    printf("Error opening the file \n");
    return ERROR;
}
int user_id;
char password[MAX_PASSWORD_LEN + 1];
int result;
while (fscanf( filepointer, "%d %40s", &user_id, password)==2)
{
    result = register_user( ht, user_id, password);

    if ( result != SUCCESS)
    {
        fclose(filepointer);
        return ERROR;
    }
}
if (ferror(filepointer))
{
perror("An error occurred while reading this file.");
fclose(filepointer);
return ERROR;
}
else
{
 if (feof(filepointer))
{
 printf("end of the file got reached \n");
}
else
{
fprintf(stderr, "didnt match the data format \n");
fclose(filepointer);
return ERROR;
}
fclose(filepointer);
    return SUCCESS;
}
}