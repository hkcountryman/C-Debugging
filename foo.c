/**
 * @author Halle Countryman
 * @brief Basic GDB demo: Dial up Halle at 1-555-123-4567!
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "foo.h"

person* create_person(char *name, char *phone) {
    person* p = malloc(sizeof(person));
    p->name = name;
    strcpy(p->phone, phone);
    return p;
}

void call(person *p) {
    printf("Dialing (");
    for (int i = 0; i < 10; i++) {
        printf("%c", p->phone[i]);
        if (i == 2) {
            printf(")");
        }
        if (i == 5) {
            printf("-");
        }
    }
    printf("...\n");
    printf("Hello, %s here! Is this the person to whom I am speaking?\n", p->name);
}

int main (int argc, char **argv) {
    person *p = create_person("Halle", "5551234567");
    call(p);
    return 0;
}
