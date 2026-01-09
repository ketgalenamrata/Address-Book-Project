#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name_str[50];
    char phone_str[20];
    char email_str[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactcount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

int validate_name(const char *name_str,AddressBook *addressBook);
int validate_phone(const char *phone_str,AddressBook *addressBook);
int validate_email(const char *email_str,AddressBook *addressBook);
#endif
