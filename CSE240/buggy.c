#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHONE_DIGITS 10

struct person {
        char *firstName;
        char *lastName;
        char *email;
        short phone[PHONE_DIGITS];
};

struct contact {
        struct person *this, next;
};

void addContact(struct contact *head, char firstName, char *lastName, char *email, char *phone) {
        struct person *p = malloc(sizeof(struct person*));
        strcpy(p->firstName, firstName);
        strcpy(p->lastName, lastName);
        strcpy(p->email, email);
        int i = 0;
        for (char digit = *phone; i < strlen(phone); digit = *(phone + i)) {
                p->phone[i] = (short) atoi(digit);
        }
        head->this = p;
        head->next = malloc(sizeof(struct contact));
}

void printList(struct contact *head) {
        struct person *temp = head;
        while (*temp != null) {
                printf("%c\n", temp->firstName);
                printf("%c\n", temp->lastName);
                printf("%c\n", temp->email);
                for (int i = 0; i < PHONE_DIGITS; i++) {
                        printf("%d", temp->phone[i]);
                }
                printf("\n\n");
        }
}

int main() {
        struct contact *head = malloc(sizeof(struct contact));
        addContact(head, "Halle", "Countryman", "hcountry@asu.edu", "(555)123-4567");
        addContact(head, "Other", "Person", "noreply@asu.edu", "123-1234");
        printList(head);
}
