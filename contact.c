/*
Name: Namrata Subhash Ketgale
Start Date: 12/12/2025
AdmissioN id : 25031_168
Description: This file contains all the main functions to manage an address book:
             - Create new contacts with validation
             - Search contacts by name, phone, or email
             - Edit contact details
             - Delete contacts
             - List all contacts in a tabular format
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

#include <ctype.h>
#define RESET   "\033[0m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

void listContacts(AddressBook *addressBook) 
{
    //addressBook->contactcount = 0;
    // Sort contacts based on the chosen criteria
   // printf("#%d\n",addressBook->contactcount);
   if (addressBook->contactcount == 0)
    {
        printf("No contacts found\n");
        return;
    }
    

    printf("\n--------- Contact List ---------\n");
    printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactcount; i++)
{
    printf("%-4d %-15s %-15s %-25s\n",
           i + 1,
           addressBook->contacts[i].name_str,
           addressBook->contacts[i].phone_str,
           addressBook->contacts[i].email_str);
}
    printf("\n");
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactcount = 0;

FILE *fptr = fopen("contacts.txt", "r");

    if (fptr == NULL)
    {
        addressBook->contactcount = 0;
        return;
    }

    fscanf(fptr, "#%d\n", &addressBook->contactcount);

    for (int i = 0; i < addressBook->contactcount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name_str,
               addressBook->contacts[i].phone_str,
               addressBook->contacts[i].email_str);
    }
    fclose(fptr);
}


void saveAndExit(AddressBook *addressBook) 
{
   //saveContactsToFile(addressBook);
// Save contacts to file
    FILE *fptr = fopen("contacts.txt","w");

    if(fptr == NULL)
    {
        printf("Error opening file for saving\n");
        return;
    }
    fprintf(fptr,"#%d\n",addressBook->contactcount);

    for(int i=0;i<addressBook->contactcount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
        addressBook->contacts[i].name_str,
        addressBook->contacts[i].phone_str,
        addressBook->contacts[i].email_str);
    }
    fclose(fptr);
    printf("\n✅ Contact saved successfully!");
    exit(EXIT_SUCCESS);
}

 int validate_name(const char *name_str,AddressBook *addressBook)
 {
        for(int i=0;name_str[i]!='\0';i++)
        {
          if (!((name_str[i] >= 'A' && name_str[i] <= 'Z') ||
              (name_str[i] >= 'a' && name_str[i] <= 'z') ||
              (name_str[i] == '.') ||
              (name_str[i] == ' ')))
            {
                printf(RED"Invalid name! Only alphabets,dot and space is allowed\n"RESET);
                return 0;
                printf("\n");
            }
        }
        return 1;//valid

 }

 int validate_phone(const char *phone_str,AddressBook *addressBook)
 {
        if(strlen(phone_str)!=10)
        {
            printf("Invalid number!Phone number must contain 10 digit\n");
            return 0;
        }
       for (int i = 0; phone_str[i] != '\0'; i++)
    {
        if (phone_str[i] < '0' || phone_str[i] > '9')
        {
            printf("Invalid number! Only digits are allowed\n");
            return 0;
        }
    }
     //check if number is already present in database
        for(int i=0;i<addressBook->contactcount;i++)
        {
          if(strcmp(addressBook->contacts[i].phone_str,phone_str)==0)
          {
            printf("This phone number is already exist\n");
            return 0;
           }
        }
        return 1;//valid
 }

 int validate_email(const char *email_str,AddressBook *addressBook)
{
    int i = 0;
    int at_count = 0;

    // must start with lowercase letter
    if (email_str[0] < 'a' || email_str[0] > 'z')
    {
        printf("Email must start with lowercase alphabet\n");
        return 0;
    }

    while (email_str[i] != '\0')
    {
        char ch = email_str[i];

        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9') ||
            ch == '@' || ch == '.' || ch == '_')
        {
            if (ch == '@')
                at_count++;

            i++;
        }
        else
        {
            printf("Invalid email! Only lowercase letters, digits, '@', '.', '_' allowed\n");
            return 0;
        }
    }

    // must contain exactly one '@'
    if (at_count != 1)
    {
        printf("Email must contain exactly one '@'\n");
        return 0;
    }

    int len = strlen(email_str);

    // check length
    if (len < 5)
    {
        printf("Invalid email length\n");
        return 0;
    }

    // must end with .com
    if (!(email_str[len-4] == '.' &&
      email_str[len-3] == 'c' &&
      email_str[len-2] == 'o' &&
      email_str[len-1] == 'm'))
    {
        printf("Email must end with .com\n");
        return 0;
    }

    return 1;   // VALID
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    // contact c;
    char name_str[30];
    char phone_str[30];
    char email_str[30];
  do{
    printf("Enter the name: ");
    scanf(" %[^\n]", name_str);
    }while(validate_name(name_str, addressBook) == 0);

    do{
        printf("Enter phone number:");
        scanf("%s",phone_str);
    }while(validate_phone(phone_str, addressBook) == 0);

    do{
        printf("Enter the email id:");
        scanf("%s",email_str);
    }while(validate_email(email_str, addressBook) == 0);

    strcpy(addressBook->contacts[addressBook->contactcount].name_str,name_str);
    strcpy(addressBook->contacts[addressBook->contactcount].phone_str,phone_str);
    strcpy(addressBook->contacts[addressBook->contactcount].email_str,email_str);
    addressBook->contactcount++;
    printf("\n");
    printf("✅ Contact created successfully!\n\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char name_str[30];
    char phone_str[30];
    char email_str[30];
    int choice;
    int contactcount=0;
     printf("\n🔍 Search contact by:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email id\n");
    
    int found=0;
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice!\n");
        while (getchar() != '\n'); // clear buffer
        return;
    }

    switch(choice)
    {
      case 1:
      {     
                printf("Enter name to search: ");
                scanf(" %[^\n]", name_str);  
                int arr[100];
                int matchcount = 0;
                int serial;

                for (int i = 0; i < addressBook->contactcount; i++)
                {
                 if (strstr(addressBook->contacts[i].name_str, name_str) != NULL)
                 {
                    arr[matchcount++] = i;
                 }
                }


                if (matchcount == 0)
                {
                   printf("Contact not found\n");
                     break;
                }
                else if (matchcount == 1)
                {
                int idx = arr[0];

                printf("\n---- Contact Found ----\n");
                printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------\n");

                printf("%-4d %-15s %-15s %-25s\n",
                1,
                addressBook->contacts[idx].name_str,
                addressBook->contacts[idx].phone_str,
                addressBook->contacts[idx].email_str);
                }
                else
               {
                int serial;
                
                printf("\n---- Multiple contact found ----\n");
                printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------\n");

                for (int i = 0; i < matchcount; i++)
                {
                  int idx = arr[i];

                   printf("%-4d %-15s %-15s %-25s\n",
                   i + 1,
                   addressBook->contacts[idx].name_str,
                   addressBook->contacts[idx].phone_str,
                   addressBook->contacts[idx].email_str);
                }
    
                printf("Enter serial number: ");
                scanf("%d", &serial);

                if (serial < 1 || serial > matchcount)
                {
                   printf("Invalid serial number.\n");
                   break;
                }

                int idx = arr[serial - 1];
                printf("\n---- Contact Detail ----\n");
                printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
                printf("--------------------------------------------------------------\n");
                printf("%-4d %-15s %-15s %-25s\n",
                serial,
                addressBook->contacts[idx].name_str,
                addressBook->contacts[idx].phone_str,
                addressBook->contacts[idx].email_str);
               }

                break; 
                
             }
            
    case 2: 
            {
                  printf("Enter phone number to search");
                  scanf("%s",phone_str);

                  for(int i=0; i<addressBook->contactcount; i++)
                  {
                   if (strcmp(addressBook->contacts[i].phone_str, phone_str) == 0)
                   {
                    printf("\n---- Contact Found ----\n");
                    printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
                    printf("--------------------------------------------------------------\n");

                    printf("%-4d %-15s %-15s %-25s\n",
                    1,
                    addressBook->contacts[i].name_str,
                    addressBook->contacts[i].phone_str,
                    addressBook->contacts[i].email_str);

                    found = 1;
                    break;

                  }
                  break;
                }
    case 3: 
            {               
                 printf("Enter email id to search:");
                  scanf("%s",email_str);

                  for(int i = 0; i < addressBook->contactcount; i++)
                  {
                    if(strcmp(addressBook->contacts[i].email_str,email_str)==0)
                    {
                        printf(RED"\n---- Contact Found ----\n"RESET);
                        printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
                        printf("--------------------------------------------------------------\n");

                        printf("%-4d %-15s %-15s %-25s\n",
                        1,
                        addressBook->contacts[i].name_str,
                        addressBook->contacts[i].phone_str,
                        addressBook->contacts[i].email_str);

                        found = 1;
                        break;

                    }
                  }
                  break;
                
                }
                    
    default:  
                 printf("Invalid choice\n");
                 return;
                 break;
            }

                   
        
         if(!found)
         {
             printf("Contact not found\n");
         }
        }
        printf("\n");
    }
        
          

void editContact(AddressBook *addressBook)
/* Define the logic for Editcontact */
{
    if (addressBook->contactcount == 0)
    {
        printf("No contacts to edit\n");
        return;
    }

    char name[50];
    printf("Enter name to edit: ");
    scanf(" %[^\n]", name);

    int indexArr[100];
    int matchCount = 0;

    // Find matching contacts
    for (int i = 0; i < addressBook->contactcount; i++)
    {
        if (strstr(addressBook->contacts[i].name_str, name) != NULL)
        {
            indexArr[matchCount++] = i;
        }
    }

    if (matchCount == 0)
    {
        printf("Contact not found\n");
        return;
    }

    int idx;

    // If multiple contacts found, ask user to choose
    if (matchCount > 1)
    {
        printf("\nMultiple contacts found:\n");
        printf("\nNo.  %-15s %-15s %-25s\n", "Name", "Phone", "Email");
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < matchCount; i++)
        {
        int pos = indexArr[i];

        printf("%-4d %-15s %-15s %-25s\n",
               i + 1,
               addressBook->contacts[pos].name_str,
               addressBook->contacts[pos].phone_str,
               addressBook->contacts[pos].email_str);  //
        }


        int choice;
        printf("Enter serial number to edit: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > matchCount)
        {
            printf("Invalid choice\n");
            return;
        }

        idx = indexArr[choice - 1];
    }
    else
    {
        idx = indexArr[0];
    }

    printf("\nEditing contact:\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email ID\n");
    printf("Enter your choice: ");

    int opt;
    scanf("%d", &opt);

    char temp[50];

    switch (opt)
    {
        case 1:
            do
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", temp);
            } while (!validate_name(temp, addressBook));

            strcpy(addressBook->contacts[idx].name_str, temp);
            break;

        case 2:
            do
            {
                printf("Enter new phone number: ");
                scanf("%s", temp);
            } while (!validate_phone(temp, addressBook));

            strcpy(addressBook->contacts[idx].phone_str, temp);
            break;

        case 3:
            do
            {
                printf("Enter new email ID: ");
                scanf("%s", temp);
            } while (!validate_email(temp, addressBook));

            strcpy(addressBook->contacts[idx].email_str, temp);
            break;

        default:
            printf("Invalid option\n");
            return;
    }
    printf("\n");
    printf("✅ Contact updated successfully!\n");
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char name_str[30];
    int deleteindex = -1;
    char searchcontact[60];
    printf("Enter name to delete:");
    scanf(" %[^\n]", name_str);
    for(int i=0;i<addressBook->contactcount;i++)
    {
       if(strcmp(addressBook->contacts[i].name_str,name_str)==0)
      {
        deleteindex = i;
        break;

      }
    }
   

   if(deleteindex == -1)
   {
    printf("Contact not found\n");
    return;
   }

   for(int i = deleteindex;i<addressBook->contactcount-1;i++)
   {
    addressBook->contacts[i] = addressBook->contacts[i+1];

   }
   addressBook->contactcount--;
   printf("Contact deleted successfully\n");
}
