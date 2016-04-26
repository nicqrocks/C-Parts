/*
Nicola Quoziente
cis-170-01
Part Tracker final
*/

//This will use a linked list to keep track of and hold
//data for parts.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define some generic things.
#define errNotFound "The part you are looking for could not be found. :("
#define errUnknown "Sorry, I did not catch that, try again."
#define errNumRange "Number not in valid range, try again."


//Make a struct to hold part info.
struct Part {
    //Part id number
    int num;
    int qty;
    float price;
    struct Part *next;
};


//Make some prototypes
char dispMenu   ();
void newPart    (struct Part *);
void delPart    (struct Part *);
struct Part * findPart   (int);
void getParent  (struct Part *, struct Part *);
void dispInfo   (struct Part *);
void saveInfo   ();
void loadInfo   ();
void getPartInfo(struct Part *);


//Make a global for the base pointer
static struct Part *ptrBase;


//Main
int main() {
    //Make some vars
    int cont = 1;

    //Setup the base pointer for use.
    ptrBase =  malloc( sizeof(struct Part) );
    ptrBase->num = 0;
    ptrBase->qty = 0;
    ptrBase->price = 0.0;
    ptrBase->next = 0;

    //Loop until the user wants to exit.
    while (cont) {
        //Use a switch statement to check the user's response
        switch (dispMenu()) {
            case 'A':
            case 'a':
            {
                //Make some vars
                char ans;

                //Make a new set of parts for the user.
                //Ask if the user wants to save.
                if (ptrBase) {
                    while (cont) {
                        printf("Would you like to save? (Enter 'y' or 'n')\n");
                        scanf("\n%c", &ans);

                        switch (ans) {
                            case 'y':
                            case 'Y':
                                //Save the data currently in the list.
                                cont = 0;
                                saveInfo();
                                break;
                            case 'n':
                            case 'N':
                                //Do not save
                                cont = 0;
                                break;
                            default:
                                printf("%s\n", errUnknown);
                        }
                    }
                }
                cont = 1; //So that the main loop continues to function.

                //Remove all parts currently in the list.
                while (ptrBase != NULL) {
                    delPart(ptrBase);
                }

                //Add info to the new base.
                ptrBase =  malloc( sizeof(struct Part) );
                getPartInfo(ptrBase);

                //Add a new part and stay in the loop
                while (cont) {
                    printf("Would you like to add another part? ('y' or 'n')\n");
                    scanf("\n%c", &ans);

                    switch (ans) {
                        case 'y':
                        case 'Y':
                            {
                                //Add a new part and stay in the loop
                                struct Part tmp;
                                getPartInfo(&tmp);
                                newPart(&tmp);
                            }
                            break;
                        case 'n':
                        case 'N':
                            //Exit the loop
                            cont = 0;
                            break;
                        default:
                            printf("%s\n", errUnknown);
                    }
                }
                cont = 1; //So that the main loop continues to function.
            }
                break;

            case 'b':
            case 'B':
                //Load a part list from a file and add to the existing list.
                loadInfo();
                break;

            case 'c':
            case 'C':
                {
                    //Display the entire list to the user.
                    struct Part *i = ptrBase;
                    printf("---Parts list---\n");
                    while (i != 0) {
                        dispInfo(i);
                        //Go to next part.
                        i = i->next;
                    }
                }
                break;

            case 'd':
            case 'D':
                {
                    //Display the info of a particular part to the user.
                    int ans;
                    struct Part *find;

                    while (cont) {
                        printf("Part number to find: ");
                        scanf("%d", &ans);

                        if (ans >= 0) {
                            cont = 0;
                        }
                        else {
                            printf("%s\n", errNumRange);
                        }
                    }
                    cont = 1; //So that the main loop continues to function.

                    //Find the part number
                    find = findPart(ans);

                    //If the part has been not been found, tell the user. Otherwise,
                    //display the part info.
                    if (find) {
                        dispInfo(find);
                    }
                    else {
                        printf("%s\n", errNotFound);
                    }
                }
                break;

            case 'e':
            case 'E':
                {
                    //Add a new part to the list.
                    char ans;
                    while (cont) {
                        struct Part tmp;
                        getPartInfo(&tmp);
                        newPart(&tmp);

                        printf("Would you like to add another part? ('y' or 'n')\n");
                        scanf("\n%c", &ans);

                        switch (ans) {
                            case 'y':
                            case 'Y':
                                //Add a new part and stay in the loop
                                break;
                            case 'n':
                            case 'N':
                                //Exit the loop
                                cont = 0;
                                break;
                            default:
                                printf("%s\n", errUnknown);
                        }
                    }
                    cont = 1; //So that the main loop continues to function.
                }
                break;

            case 'f':
            case 'F':
                {
                    //Edit a part in the list.
                    int ans;
                    struct Part *find;
                    struct Part new;
                    while (cont) {
                        printf("Part number to find: ");
                        scanf("%d", &ans);

                        if (ans >= 0) {
                            cont = 0;
                        }
                        else {
                            printf("%s\n", errNumRange);
                        }
                    }
                    cont = 1; //So that the main loop continues to function.

                    //Find the part number
                    find = findPart(ans);

                    if (find) {
                        dispInfo(find);
                        getPartInfo(&new);
                        newPart(&new);
                        delPart(find);
                    }
                    else {
                        printf("%s\n", errNotFound);
                    }
                }
                break;

            case 'g':
            case 'G':
                {
                    //Delete a part from the list.
                    int ans;
                    struct Part *find;
                    while (cont) {
                        printf("Part number to find: ");
                        scanf("%d", &ans);

                        if (ans >= 0) {
                            cont = 0;
                        }
                        else {
                            printf("%s\n", errNumRange);
                        }
                    }
                    cont = 1; //So that the main loop continues to function.

                    //Find the part number
                    find = findPart(ans);

                    if (find) {
                        delPart(find);
                    }
                    else {
                        printf("%s\n", errNotFound);
                    }
                }
                break;

            case 'h':
            case 'H':
                //Save the list to a file.
                saveInfo();
                break;

            case 'Q':
            case 'q':
                //Exit the main loop
                cont = 0;
                break;

            default:
                printf("%s\n", errUnknown);
        }
    }

    return 0;
}


//Function to display the main menu to the user.
char dispMenu() {
    char ans;

    printf("\n\nPart Info Database\n");
    printf("Enter the letter of the option you want.\n");
    printf("%-3s%-40s\n", "A.", "Make a new part list");
    printf("%-3s%-40s\n", "B.", "Load part list from a file");
    printf("%-3s%-40s\n", "C.", "Display the current part list");
    printf("%-3s%-40s\n", "D.", "Display a particular part from the list");
    printf("%-3s%-40s\n", "E.", "Add a new part to the set");
    printf("%-3s%-40s\n", "F.", "Edit a part in the list");
    printf("%-3s%-40s\n", "G.", "Delete a part from the current list");
    printf("%-3s%-40s\n", "H.", "Save the current list to a file");
    printf("%-3s%-40s\n", "Q.", "Quit the program");
    printf("\n");

    scanf("\n");
    scanf("%c", &ans);

    return ans;
}


//Function to add a new part into the list.
void newPart(struct Part *new) {
    //Make some vars
    struct Part *counter;
    struct Part *tmp;

    //Go along the list until the part is in the right spot
    counter = ptrBase;
    while (counter) {
        if (counter->num > new->num) {
            break;
        }
        else if (counter->num == new->num) {
            printf("Part #%d, already exists.\n", new->num);
            return;
        }
        tmp = counter;
        counter = counter->next;
    }

    if (counter == ptrBase) {
        tmp = ptrBase;
        ptrBase = malloc( sizeof(struct Part) );
        ptrBase->num = new->num;
        ptrBase->qty = new->qty;
        ptrBase->price = new->price;
        ptrBase->next = tmp;
    }
    else {
        tmp->next = malloc( sizeof(struct Part) );
        tmp = tmp->next;
        tmp->num = new->num;
        tmp->qty = new->qty;
        tmp->price = new->price;
        tmp->next = counter;
    }
}


//Function to delete a part
void delPart(struct Part *del) {
    //Make some vars
    struct Part *parent;

    //Check if the base variable is the part to delete.
    if (ptrBase == del) {
        ptrBase = del->next;
        free(del);
        return;
    }

    //Find the parent of the part to delete
    parent = ptrBase;
    while (parent->next != del && parent != NULL) {
        parent = parent->next;
    }

    //If parent is null, then give an error
    if (parent == NULL) {
        printf("%s\n", errNotFound);
        return;
    }

    //Remove the struct from the list
    parent->next = del->next;
    free(del);
}


//Function to find a part
struct Part * findPart (int searchNum) {
    //Check if each part's number matches the one to find.
    struct Part *base;
    base = ptrBase;

    while (base) {
        if (base->num == searchNum) {
            break;
        }
        base = base->next;
    }

    //If the part is found set the pointer to it, otherwise set it to null.
    if (base) {
        return base;
    }
    else {
        return 0;
    }
}


//Function to display the information about a part
void dispInfo(struct Part *part) {
    printf("\n");
    printf("Part number: %-5d\n", part->num);
    printf("Quantity: %d\n", part->qty);
    printf("Price per item: %0.3f\n", part->price);
    printf("\n");
}


//Function to save the list to a file.
void saveInfo () {
    //Make some vars
    FILE *fp;
    char filename[256];
    char ans;

    //Ask the user for the name of the file to save to.
    printf("Enter the name of the CSV file to save to: ");
    scanf("\n");
    scanf("%s", filename);

    //Open the file, and check if the file exists already.
    strcat(filename, ".csv");
    fp = fopen(filename, "r");
    if (fp != NULL) {
        //Ask the user if they want to overwite the file.
        printf("A file with this name already exists.\n");
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            printf("Do you want to overwrite it? [y/n]\n");
            scanf("\n");
            scanf("%c", &ans);
        }
        if (ans == 'n' || ans == 'N') {
            return;
        }
        fclose(fp);
    }

    //The file does not exist, so close it and reopen it for editing.
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open the files for editing!\n");
        getchar();
        return;
    }

    //Go through the list structure and save the data to the file in
    //CSV format.
    struct Part *base = ptrBase;
    while (base != NULL) {
        fprintf(fp, "%d,%d,%f\n", base->num, base->qty, base->price);
        base = base->next;
    }

    //Close the file
    fclose(fp);
}


//Function to load data from a file.
void loadInfo() {
    //Make some vars
    FILE *fp;
    char filename[256];
    char line[100];
    char *in;

    //Ask the user for the name of the file to load from.
    printf("Enter the name of the CSV file to load from: ");
    scanf("\n");
    scanf("%s", filename);

    //Try to open the file.
    strcat(filename, ".csv");
    fp = fopen(filename, "r");
    while (fp == NULL) {
        //The file does not exist. Ask the user to try again.
        printf("'%s' not found, try again or 'quit' to exit.\n", filename);
        scanf("\n");
        scanf("%s", filename);

        if (! strcmp(filename, "quit")) {
            return;
        }

        strcat(filename, ".csv");
        fp = fopen(filename, "r");
    }

    //The file exists and is open.
    while (fgets(line, 100, fp) != NULL) {
        //Make a new part for each line, and add it to the list.
        struct Part new;
        in = strtok(line, ",");
        //Check for an error reading the line.
        if (in == NULL) {
            printf("Error reading line '%s'\n", line);
            continue;
        }
        sscanf(in, "%d", &new.num);

        in = strtok(NULL, ",");
        //Check for an error reading the line.
        if (in == NULL) {
            printf("Error reading line '%s'\n", line);
            continue;
        }
        sscanf(in, "%d", &new.qty);

        in = strtok(NULL, ",");
        //Check for an error reading the line.
        if (in == NULL) {
            printf("Error reading line '%s'\n", line);
            continue;
        }
        sscanf(in, "%f", &new.price);

        newPart(&new);
    }

    //Close the file
    fclose(fp);
}


//Function to ask the user for input to make a new part
void getPartInfo(struct Part *outPtr) {
    //Alocate memory for the part. And set the next var to null.
    //outPtr =  malloc( sizeof(struct Part) );
    outPtr->next = 0;

    //Ask the user for the part number and make sure it's valid
    printf("Enter the part number: ");
    scanf("%d", &outPtr->num);

    while (outPtr->num < 0) {
        printf("%s\n", errNumRange);
        scanf("%d", &outPtr->num);
    }

    //Ask for the quantity and make sure it's valid
    printf("Enter the quantity for part %4d: ", outPtr->num);
    scanf("%d", &outPtr->qty);

    while (outPtr->qty < 0) {
        printf("%s\n", errNumRange);
        scanf("%d", &outPtr->num);
    }

    //Ask for the price of the part and make sure it's valid
    printf("Enter the price of the part: ");
    scanf("%f", &outPtr->price);

    while (outPtr->price < 0.0) {
        printf("%s\n", errNumRange);
        scanf("%f", &outPtr->price);
    }
}
