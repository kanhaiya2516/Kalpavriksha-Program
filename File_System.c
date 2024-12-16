#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME "users.txt"

typedef struct {
    char ID[10];
    char name[50];
    int age;
} User;

int load_users(User users[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s,%49[^,],%d\n", users[count].ID, users[count].name, &users[count].age) == 3) {
        count++;
    }
    fclose(file);
    return count;
}

void save_users(User users[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%d\n", users[i].ID, users[i].name, users[i].age);
    }
    fclose(file);
}

void create_user(User users[], int *count) {
    User new_user;
    printf("Enter unique ID: ");
    scanf("%s", new_user.ID);

    for (int i = 0; i < *count; i++) {
        if (strcmp(users[i].ID, new_user.ID) == 0) {
            printf("User ID already exists. Please use a unique ID.\n");
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", new_user.name);
    printf("Enter Age: ");
    scanf("%d", &new_user.age);

    users[*count] = new_user;
    (*count)++;
    save_users(users, *count);
    printf("User added successfully.\n");
}

void display_users(User users[], int count) {
    if (count == 0) {
        printf("No users found.\n");
        return;
    }

    printf("\nUser ID | Name | Age\n");
    printf("------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s | %s | %d\n", users[i].ID, users[i].name, users[i].age);
    }
    printf("------------------------\n");
}

void update_user(User users[], int count) {
    char id[10];
    printf("Enter the ID of the user to update: ");
    scanf("%s", id);

    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].ID, id) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Updating details for user ID: %s\n", users[found].ID);
        printf("Enter new Name (leave blank to keep current): ");
        char new_name[50];
        getchar();
        fgets(new_name, sizeof(new_name), stdin);
        new_name[strcspn(new_name, "\n")] = '\0';

        if (strlen(new_name) > 0) {
            strcpy(users[found].name, new_name);
        }

        printf("Enter new Age (leave blank to keep current): ");
        int new_age;
        if (scanf("%d", &new_age) == 1) {
            users[found].age = new_age;
        }

        save_users(users, count);
        printf("User details updated successfully.\n");
    } else {
        printf("User ID not found.\n");
    }
}

void delete_user(User users[], int *count) {
    char id[10];
    printf("Enter the ID of the user to delete: ");
    scanf("%s", id);
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(users[i].ID, id) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (int i = found; i < *count - 1; i++) {
            users[i] = users[i + 1];
        }
        (*count)--;
        save_users(users, *count);
        printf("User deleted successfully.\n");
    } else {
        printf("User ID not found.\n");
    }
}

int main() {
    User users[100];
    int user_count = load_users(users);

    int choice;
    do {
        printf("\nUser Management System\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_user(users, &user_count);
                break;
            case 2:
                display_users(users, user_count);
                break;
            case 3:
                update_user(users, user_count);
                break;
            case 4:
                delete_user(users, &user_count);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice\n");
        }
        
    } while (choice != 5);

    return 0;
}
