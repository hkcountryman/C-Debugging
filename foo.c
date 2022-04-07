#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "foo.h"

person* create_person(char *name, char *phone) {
    person* person = malloc(sizeof(person));
    person->name = name;
    strcpy(person->phone, phone);
    return person;
}

void call(person *person) {
    printf("Dialing (");
    for (int i = 0; i < 10; i++) {
        printf("%d", person->phone[i]);
        if (i == 2) {
            printf(")");
        }
        if (i == 5) {
            printf("-");
        }
    }
    printf("...\n");
    printf("Hello, %s here! Is this the person to whom I am speaking?", person->name);
}

int main (int argc, char **argv) {
    person *p = create_person("Halle", "15551234567");
    call(p);
    return 0;
}
