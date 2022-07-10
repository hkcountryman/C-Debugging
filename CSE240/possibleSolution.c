#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHONE_DIGITS 10

struct person {
        char *firstName;
        char *lastName;
        char *email;
        char phone[PHONE_DIGITS];
};

struct contact {
        struct person *this;
        struct contact *next;
};

void addContact(struct contact **head, char *firstName, char *lastName, char *email, char *phone) {
        struct person *p = malloc(sizeof(struct person));
        p->firstName = malloc(sizeof(char) * strlen(firstName));
        p->lastName = malloc(sizeof(char) * strlen(lastName));
        p->email = malloc(sizeof(char) * strlen(email));
        strcpy(p->firstName, firstName);
        strcpy(p->lastName, lastName);
        strcpy(p->email, email);
        int i = 0;
        for (char digit = *phone; i < strlen(phone); digit = *(phone + i++)) {
                p->phone[i] = digit;
        }
        struct contact *temp = *head;
        while (temp->next != NULL) {
                temp = temp->next; // Find end of list
        }
        temp->this = p;
        temp->next = malloc(sizeof(struct contact));
}

void printList(struct contact *head) {
        struct contact *temp = head;
        while (temp->next != NULL) {
                printf("%s\n", temp->this->firstName);
                printf("%s\n", temp->this->lastName);
                printf("%s\n", temp->this->email);
                for (int i = 0; i < PHONE_DIGITS; i++) {
                        printf("%c", temp->this->phone[i]);
                }
                printf("\n\n");
                temp = temp->next;
        }
}

int main() {
        struct contact *head = malloc(sizeof(struct contact));
        addContact(&head, "Halle", "Countryman", "hcountry@asu.edu", "5551234567");
        addContact(&head, "Other", "Person", "noreply@asu.edu", "5551231234");
        printList(head);
}
