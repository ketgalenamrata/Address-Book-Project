#include <stdio.h>
#include "file.h"


void saveContactsToFile(AddressBook *addressBook) 

    {
    FILE *fptr = fopen("contacts.txt", "w");
    if (fptr == NULL)
        return;

    fprintf(fptr, "#%d\n", addressBook->contactcount);

    for (int i = 0; i < addressBook->contactcount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name_str,
                addressBook->contacts[i].phone_str,
                addressBook->contacts[i].email_str);
    }

    fclose(fptr);
    
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    
     
    
}
