#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[100];
    char author[50];
    int year;
    struct Book* next;  // pointer to the next book in the list
} Book;
// Create a new book in memory and return a pointer to it
Book* createBook(int id, char* title, char* author, int year) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->next = NULL;
    return newBook;
}
// Add a book at the beginning of the list
void addBook(Book** head, int id, char* title, char* author, int year) {
    Book* newBook = createBook(id, title, author, year);
    newBook->next = *head;
    *head = newBook;
}
// Display all books in the list
void displayBooks(Book* head) {
    if (head == NULL) {
        printf("Library is empty.\n");
        return;
    }
    Book* current = head;
    while (current != NULL) {
        printf("[%d] %s by %s (%d)\n", current->id, current->title, current->author, current->year);
        current = current->next;
    }
}
void deleteBook(Book** head, int id) {
    if (*head == NULL) {
        printf("Library is empty.\n");
        return;
    }

    Book* current = *head;
    Book* prev = NULL;

    // search for the book with the given id
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // book not found
    if (current == NULL) {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    // book is the first node
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Book deleted successfully!\n");
}
int main() {
    Book* head = NULL;
    int choice;

    do {
        printf("\n--- Library Menu ---\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Delete a book\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // clear the newline left by scanf

        if (choice == 1) {
            int id, year;
            char title[100], author[50];

            printf("ID: ");
            scanf("%d", &id);
            getchar();

            printf("Title: ");
            fgets(title, 100, stdin);
            title[strcspn(title, "\n")] = 0; // remove the \n at the end

            printf("Author: ");
            fgets(author, 50, stdin);
            author[strcspn(author, "\n")] = 0;

            printf("Year: ");
            scanf("%d", &year);

            addBook(&head, id, title, author, year);
            printf("Book added successfully!\n");

        } else if (choice == 2) {
            displayBooks(head);
        } else if (choice == 3) {
            int id;
            printf("Enter book ID to delete: ");
            scanf("%d", &id);
            deleteBook(&head, id);
}

    } while (choice != 0);

    printf("Goodbye!\n");
    return 0;
}