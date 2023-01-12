#include <stdio.h> 
#include <stdlib.h>     // includes malloc
#include <string.h>

void print_modules(char data[]);

//-------------------------------------------
// Step 1: Datenstruktur und Datentyp anlegen
//-------------------------------------------

// Structures
typedef struct                  // using typedef to make struct "cleaner" -> typedef is a 'new datatype'
{
    // members
    char module[100];            // Modulbezeichnung
    char abbreviation[10];      // Abkürzung
    int valuation;              // Gewichtung
    int grade;                  // Note
} course;                       //giving the name "course" to this struct


int main (void)
{
    system("clear");

    course ree;                 // groups together the variables in the struct under the name "ree"
                                // when using typedef, you do not have to write struct anymore (cleaner)
    // strcpy(ree.module, "math"); // first argument of strcpy is the destination, second is the source
    // strcpy(ree.abbreviation, "MA_1");
    // ree.valuation = 8;
    // ree.grade = 10;

    // printf("module: %s\n", ree.module);
    // printf("abbreviation: %s\n", ree.abbreviation);
    // printf("valuation: %d\n", ree.valuation);
    // printf("grade: %d\n", ree.grade);

    // Defining Pointer to the struct 

    course *coursePtr_1;
    coursePtr_1 = &ree; 

    // printf("\n");
    // coursePtr_1->valuation = 1;               //arrow notation gives us access to the member variables 

    // printf("valuation: %d\n", ree.valuation);           //option 1 to output 
    // printf("valuation: %d\n", coursePtr_1->valuation);  //option 2 to output

    //dynamically allocating space for the struct

    course *coursePtr_2;
    coursePtr_2 = malloc(sizeof(course));   // go get enough space for something as large as the struct course
                                            // sizeof(course) returns how many bytes are needed to store a course
                                            // malloc returns memory adress for a block of memory that is large enough to store a struct like "course"
    // // coursePtr_2->valuation = 2;
    // printf("valuation: %d\n", coursePtr_2->valuation);   

    //---------------------------------
    // Schritt 2: Daten einlesen
    //---------------------------------

    // Defining Pointer to File
    FILE *csv;
    char buffer[100];                        // buffer array to store the read values

    csv = fopen("module.csv", "r");         // fopen returns a file pointer which is stored into "csv"

    if (csv == NULL)
    {
        printf("file open unsuccessfull\n");

    }else
    {
        while (fgets(buffer, 80, csv) != NULL)        // csv -> telling the fgets where to get the string from //
        {                                               // fgets returns a NULL when it gets to the end (we continue as long as we are not at the end of the line)
            // saving module
            coursePtr_2 = strtok(buffer, ";");   // Funktion sucht in der Zeichenkette 'buffer' nach einem Semikolon und setzt überall dort, wo es ein Semikolon findet die Null-Terminierung rein

            //printf(" %s \n", buffer);
            //strcpy(ree.module, coursePtr_2);     // the first token is already a string so we can just copy it into our struct variable ree.module
            strcpy(ree.module, coursePtr_2);
            printf("%s\n", ree.module);
       
            //saving abbreviation
            coursePtr_2 = strtok(NULL, ";");   // "NULL" says continue where you stopped last time
            strcpy(ree.abbreviation, coursePtr_2);
            printf("%s\n", ree.abbreviation);

            //saving valuation
            coursePtr_2 = strtok(NULL, ";");
            ree.valuation = atoi(coursePtr_2);
            printf("%d\n", ree.valuation);

            //saving grade
            coursePtr_2 = strtok(NULL, ";");
            ree.grade = atoi(coursePtr_2);
            printf("%d\n", ree.grade);

            // printf("%s  %s  %d  %d\n", ree.module, ree.abbreviation, ree.valuation, ree.grade);

        //     free(coursePtr_2);
        // }
    }
    
    fclose(csv);

    return 0;
}
}

//------------------------
// Funktionsdeklarationen
// void print_modules(char data[])
// {
//     printf("%s\n", data);
// }

