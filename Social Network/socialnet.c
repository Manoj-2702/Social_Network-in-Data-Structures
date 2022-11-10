#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAX 100

typedef struct node
{
    int id;             // ID of user
    int numfren;        // number of friends of user
    char name[MAX];     // name of user
    int *friends;       // friends of user as an array
    struct node *right; // user to the right
    struct node *left;  // user to the left
} node;

struct node *retUser(char str[MAX])
{
    char name[MAX];
    char ID[MAX];
    char strfriends[MAX];

    // copied ID
    char *token = strtok(str, ",");
    strcpy(ID, token);

    // copied Name
    token = strtok(NULL, ",");
    strcpy(name, token);

    // copied friends' ID
    token = strtok(NULL, ",");
    strcpy(strfriends, token);
    // printf("%s\n",(strfriends));

    // creating user nodes
    int id = atoi(ID);
    struct node *user = malloc(sizeof(struct node));
    user->id = id;
    user->friends = (int *)malloc(MAX * sizeof(int));
    strcpy(user->name, name);

    // adding user's friend's IDs
    token = strtok(strfriends, "|");
    int i = 0;
    while (token != NULL)
    {

        int temp = atoi(token);
        user->friends[i] = temp;
        i++;
        token = strtok(NULL, "|");
    }
    user->numfren = i;
    if (i == 0)
    {
        user->friends[i] = -1;
    }
    return user;
}

// search for user with id=key
struct node *search(int key, struct node *users)
{
    // CODE HERE
    struct node *curr_manoj=users;
    while((curr_manoj)->id!=key && curr_manoj!=NULL)
    {
        if((curr_manoj->id) > key)
        {
            curr_manoj=curr_manoj->right;
        }
        else
        {
            curr_manoj=curr_manoj->left;
        }
    }
    return curr_manoj;
}

// see document for explanattion
struct node *refineUser(struct node *user, struct node *users)
{
    // CODE HERE
    user->right=NULL;
    user->left=NULL;
    while(search(user->id,users))
    {
        (user->id)++;
    }
    node *temp_manoj=NULL;
    for(int j=0;j < (user->numfren); j++)
    {
        if(temp_manoj=search(user->friends[j],users))
        {
            temp_manoj->friends[(temp_manoj->numfren)++] = user->id;
        }
        else
        {
            for(int i=j;i<(user->numfren)-1;i++)
            {
                user->friends[i]=user->friends[i+1];
            }
            j--;
            user->numfren--;
            if(user->numfren==0)
            {
                user->friends[user->numfren]=-1;
            }
        }
    }
    return user;
}

// insert user with id
struct node *insertUser(struct node *root, int id, struct node *user)
{
    // CODE HERE
    if (root == NULL)
    {
        return user;
    }
    else
    {
        struct node *curr_manoj = root;
        struct node *prev_manoj = NULL;
        while(curr_manoj != NULL)
        {
            prev_manoj=curr_manoj;
            if(id > curr_manoj->id)
            {
                curr_manoj=curr_manoj->right;
            }
            else
            {
                curr_manoj=curr_manoj->left;
            }
        }
        if((prev_manoj->id) > id)
        {
            curr_manoj->left=user;
        }
        else
        {
            curr_manoj->right=user;
        }
    }
    return root;
}

// prints friends list
void friends(int id, struct node *users)
{
    // CODE HERE
    struct node *curr_manoj = search(id,users);
    if(curr_manoj==NULL)
    {
        return;
    }
    if(curr_manoj->numfren == 0)
    {
        printf("-1\n");
    }
    else
    {
        for(int j=0;j<(curr_manoj->numfren);j++)
        {
            printf("%d\n",(curr_manoj->friends)[j]);
        }
    }
}

// find child node with minimum value (inorder successor) - helper to delete node
struct node *minValueNode(struct node *node)
{
    // CODE HERE
    struct node *inorder_manoj = node;
    if((inorder_manoj->left==NULL) || (inorder_manoj->right==NULL))
    {
        if(inorder_manoj->left==NULL)
        {
            inorder_manoj=inorder_manoj->right;
        }
        else
        {
            inorder_manoj=inorder_manoj->left;
        }
    }
    else
    {
        inorder_manoj=inorder_manoj->right;
        while(inorder_manoj->left==NULL && inorder_manoj!=NULL)
        {
            inorder_manoj=inorder_manoj->left;
        }
    }
    return inorder_manoj;
}

// deletes itself from its friend's nodes
struct node *deleteFriends(int key, struct node *users)
{
    // CODE HERE
    struct node *user_manoj=search(key,users);
    if(user_manoj==NULL)
    {
        return NULL;
    }
    struct node *temp_manoj = NULL;
    for(int j=0;j<(user_manoj->numfren);j++)
    {
        temp_manoj=search((user_manoj->friends)[j],users);
        for(int z=0;z<(temp_manoj->numfren);z++)
        {
            if(temp_manoj->friends[z]==key)
            {
                for(int y=z ; y < ((temp_manoj->numfren)-1); y++)
                {
                    temp_manoj->friends[y]=temp_manoj->friends[y+1];
                }
                temp_manoj->numfren--;
                if(temp_manoj->numfren==0)
                {
                    (temp_manoj->friends)[temp_manoj->numfren]=-1;
                }
                break;
            }
        }
    }
    return users;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key)
{
    // CODE HERE
    node *current=root;
    node *previous=NULL;
    node *q=NULL;
    while(current!=NULL && current->id!=key)
    {
        previous=current;
        if(current->id > key)
            current=current->left;
        else
            current=current->right;
    }
    if(current==NULL)
    {
        // printf("The element is not found\n");
        return (root);
    }
    else if(current->left==NULL || current->right==NULL)
    {
        if(current->left==NULL)
        {
            q=current->right;
        }
        else
        {
            q=current->left;
        }
        if(previous==NULL)
        {
            free(current);
            return q;
        }
        if(current==previous->left)
        {
            previous->left=q;
        }
        else
        {
            previous->right=q;
        }
        free(current);
        return (root);
    }
    else
    {
        node *p=NULL;
        node *temp=current->right;
        while(temp->left!=NULL)
        {
            p=temp;
            temp=temp->left;
        }
        current->id=temp->id;
        if(p!=NULL)
        {
            p->left=temp->right;
        }
        else
        {
            current->right=temp->right;
        }
        free(temp);
        return (root);
    }
}

// Print USER's IDs in ascending order
void printInOrder(node *myusers)
{
    struct node *curr=myusers;
    if(curr==NULL)
    {
        return;
    }
    else
    {
        printInOrder(curr->left);
        printf("%d %s",curr->id,curr->name);
        printInOrder(curr->right);
    }
}

int main(int argc, char **argv)
{
    node *users = NULL;
    while (1)
    {

        int opt, id;
        fflush(stdin);
        scanf("%d", &opt);
        char str[MAX];
        switch (opt)
        {
        case 1:

            scanf("%s", str);
            struct node *tbins = retUser(str);
            tbins = refineUser(tbins, users);
            users = insertUser(users, tbins->id, tbins);
            break;

        case 2:

            scanf("%d", &id);
            deleteFriends(id, users);
            users = deleteNode(users, id);
            break;

        case 3:

            scanf("%d", &id);
            node *result = search(id, users);
            if (result == NULL)
                printf("USER NOT IN TREE.\n");
            else
            {
                printf("%d\n", result->id);
            }
            break;

        case 4:
            scanf("%d", &id);
            friends(id, users);
            break;

        case 5:
            printInOrder(users);
            break;

        case 6:
            exit(0);
            break;

        default:
            printf("Wrong input! \n");
            break;
        }
    }
    return 0;
}