#include <stdio.h> 
#include <stdlib.h>     // includes malloc
#include <string.h>

//-------------------------------------------
// Step 1: Datenstruktur und Datentyp anlegen
//-------------------------------------------

// structures
typedef struct                  // using typedef to make struct "cleaner" -> typedef is a 'new datatype'
{
    // members
    char module[100];            // Modulbezeichnung
    char abbreviation[10];       // Abkürzung
    int valuation;               // Gewichtung
    int grade;                   // Note
} course;                        // giving the name "course" to this struct

// function declarations
void print_courses(course x);                       // function to print the courses
void get_grades(course x);                          // function to get the grades of the user
short get_short(char text[], short MIN, short MAX); // function to get safe user input

int main (void)
{
    system("clear");

    course ree;                 // groups together the variables in the struct under the name "ree"
                                // when using typedef, you do not have to write struct anymore (cleaner)
                
    // defining pointer to the struct 
    // dynamically allocating space for the struct

    course *coursePtr_2;
    coursePtr_2 = malloc(sizeof(course));   // go get enough space for something as large as the struct course
                                            // sizeof(course) returns how many bytes are needed to store a course
                                            // malloc returns memory adress for a block of memory that is large enough to store a struct like "course"   

    //---------------------------------
    // Step 2: Daten einlesen
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
            strcpy(ree.module, coursePtr_2);     // the first token is already a string so we can just copy it into our struct variable ree.module
                                                 // first argument of strcpy is the destination, second is the source
       
            // saving abbreviation
            coursePtr_2 = strtok(NULL, ";");   // "NULL" says continue where you stopped last time
            strcpy(ree.abbreviation, coursePtr_2);
           
            // saving valuation
            coursePtr_2 = strtok(NULL, ";");
            ree.valuation = atoi(coursePtr_2);  // converting string to integer value

            print_courses(ree);                 // function to print the freshly filled struct

           
        }
        fclose(csv); // closing file after we read in the content
    }

    // free(coursePtr_2); // fragen: warum kann ich diesen pointer nicht befreien?

    return 0;

}

// function definitions

//----------------------------------------------------------------------------
// Step 3: Funktion die alle Module mit Abkürzung, Gewichtung und Note ausgibt
//----------------------------------------------------------------------------
void print_courses(course x)
{
    printf("Modulbezeichnung: %s\n", x.module);
    printf("Abkürzung: %s\n", x.abbreviation);
    printf("Gewichtung: %d\n", x.valuation);

    // getting grade from user and print it
    get_grades(x);  
}

void get_grades(course x)                          // function to get the grades of the user and print it
{
    x.grade = get_short("Geben Sie bitte hier Ihre Note ein", 0, 15);
    printf("Note: %d\n", x.grade);
    printf("-----------------------------------------------------------------------------------\n");
}

short get_short(char text[], short MIN, short MAX)
{
    //declare working variables 
    short value;
    int finished = 0; //0 für FALSE
    char ch;
    int retVal;

    do
    {
        printf("%s: ", text); //Abkürzung "s" für "string" / Zeichenkette

        ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0

        retVal = scanf("%hd%c", &value, &ch); // -> "hd" steht für short -> Adresse ist "Value"; scanf gibt auch einen Wert zurück, diesen speichern wir in retVal 

        // check for valid user input
        if (retVal != 2) printf("Das war keine korrekte Zahl!\n");
        else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
        else if (value < MIN) printf("Zahl ist zu klein (MIN: %hd)\n",MIN);
        else if (value > MAX) printf("Zahl ist zu gro%c (MAX: %hd)\n",225,MAX);
        else finished = 1; // falls die Variable tatsächlich 2 ist; und der character ein newline, ist alles richtig und die loop wird beendet

        //Variable finished wird auf 1 gesetzt -> weil 1 für TRUE

        //clear input stream buffer
        while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

    } while (!finished); //repeat if not finished 

    //return user input
    return value; //wer auch immer die Funktion get_short aufruft bekomm "value" zurück
}
