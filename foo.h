typedef struct {
    char *name;
    int phone[10];
} person;

person* create_person(char *name, char *phone);

void call(person *p);
