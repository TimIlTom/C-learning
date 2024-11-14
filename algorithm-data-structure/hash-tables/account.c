#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100000
#define MAX_PASSWORD 10
#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)
#define NUM_BITS 20

unsigned long oaat(char *key, unsigned long len, unsigned long bits);
password_node *in_hash_table(password_node *hash_table[], char *find);
void add_to_hash_table(password_node *hash_table[], char *find);

typedef struct password_node
{

    char password[MAX_PASSWORD + 1];
    int total;
    struct password_node *next;
} password_node;

int main()
{

    static char users[MAX_USERS][MAX_PASSWORD + 1];
    int num_ops, op, op_type, total;
    char password[MAX_PASSWORD + 1];
    int num_users = 0;

    scanf("%d", &num_ops);

    for (op = 0; op < num_ops; op++)
    {

        scanf("%d %s", &op_type, password);

        if (op_type == 1)
        {

            strcpy(users[num_users], password);
            num_users++;
        }
        else
        {
            total = 0;
            for (int j = 0; j < num_users; j++)
            {

                if (strstr(users[j], password))
                {

                    total++;
                }
            }
            printf("%d\n", total);
        }
    }

    return 0;
}

unsigned long oaat(char *key, unsigned long len, unsigned long bits)
{
    unsigned long hash, i;
    for (hash = 0, i = 0; i < len; i++)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}

password_node *in_hash_table(password_node *hash_table[], char *find){

    unsigned password_code;
    password_node *password_ptr;
    password_code = oaat(find, strlen(find), NUM_BITS);

    password_ptr = hash_table[password_code];

    while(password_ptr){

        if(strcmp(password_ptr->password, find) == 0) return password_ptr;

        password_ptr = password_ptr->next;
    }

    return NULL;
}

void add_to_hash_table(password_node *hash_table[], char *find){

    unsigned password_code;
    password_node *password_ptr;

    password_ptr = in_hash_table(hash_table, find);

    if(password_ptr == NULL){

        password_code = oaat(find, strlen(find), NUM_BITS);
        password_ptr = malloc(sizeof(password_node));
        if(password_ptr == NULL){

            fprintf(stderr, "malloc error\n");
            exit(1);
        }

        strcpy(password_ptr->password, find);
        password_ptr->total = 0;
        password_ptr->next = hash_table[password_code];
        hash_table[password_code] = password_ptr;
    }
    
    password_ptr->total++;
}