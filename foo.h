typedef struct {
    char *name;
    char phone[10];
} person;

person* create_person(char *name, char *phone);

void call(person *p);
