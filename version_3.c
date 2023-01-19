// CSV Datei einlesen
// Praktikum 7 (Zusatzaufgabe)
// Tom Dora, Ole Pearse-Danker
// 12.01.2023  
// Version 1.0

#define _CRT_SECURE_NO_WARNINGS

#define COURSE_SIZE 36

#include <stdio.h> 
#include <stdlib.h>     // includes malloc
#include <string.h>

//-------------------------------------------
// Step 1: Datenstruktur und Datentyp anlegen
//-------------------------------------------

// structures
// using typedef to make struct "cleaner" -> typedef is a 'new datatype'
typedef struct course
{
    // members
    char module[100];            // Modulbezeichnung
    char abbreviation[10];       // Abk�rzung
    int valuation;               // Gewichtung
    int grade;                   // Note
} course;                        // giving the name "course" to this struct

// function declarations
void print_courses(course x);                       // function to print the courses
void get_grades(course x);                          // function to get the grades of the user
short get_short(char text[], short MIN, short MAX); // function to get safe user input
//void calculate_final(course x);

int main(void)
{
    system("cls");

    course ree;                 // groups together the variables in the struct course under the name "ree"
    course reeArray[COURSE_SIZE];
    // when using typedef, you do not have to write struct anymore (cleaner)

// defining pointer to the struct 
// dynamically allocating space for the struct

    course* coursePtr;
    coursePtr = malloc(sizeof(course));   // go get enough space for something as large as the struct course
                                            // sizeof(course) returns how many bytes are needed to store a course
                                            // malloc returns memory adress for a block of memory that is large enough to store a struct like "course"   

    //---------------------------------
    // Step 2: Daten einlesen
    //---------------------------------

    // Defining Pointer to File
    FILE* csv;
    char buffer[100];                        // buffer array to store the read values

    csv = fopen("module.csv", "r");         // fopen returns a file pointer which is stored into "csv"

    if (csv == NULL)
    {
        printf("file open unsuccessfull\n");
        return 1; // returning 1 is a signal to the shell that sth has gone wrong
    }


    printf("Abk.\t");           //printing headers
    printf("Gew.\t");
    printf("Note\n");

    course courses[COURSE_SIZE];              // Defining array of structs to store the input
    int i = 0;

    // Ueberschrift auslesen (kann ignoriert werden)
    // ...
  
    //course* ree = (course*)courses;           // pointer 

    while (fgets(buffer, 80, csv) != NULL)        // csv -> telling the fgets where to get the string from //
    {
        
                                             // fgets returns a NULL when it gets to the end (we continue as long as we are not at the end of the line)
        // saving module
        coursePtr = strtok(buffer, ";");   // Funktion sucht in der Zeichenkette 'buffer' nach einem Semikolon und setzt �berall dort, wo es ein Semikolon findet die Null-Terminierung rein
        strcpy(courses[i].module, coursePtr);     // the first token is already a string so we can just copy it into our struct variable ree.module
                                            // first argument of strcpy is the destination, second is the source

        // saving abbreviation
        coursePtr = strtok(NULL, ";");   // "NULL" says continue where you stopped last time
        strcpy(courses[i].abbreviation, coursePtr);

        // saving valuation
        coursePtr = strtok(NULL, ";");
        courses[i].valuation = atoi(coursePtr);  // converting string to integer value

        coursePtr = strtok(NULL, ";");
        courses[i].grade = atoi(coursePtr);

        // (*coursePtr).grade = 12;

        // printf("%d", (*coursePtr).grade);

        print_courses(courses[i]);
        // get_grades(ree);

        //ree++;           // pointer 
        i++;
    }


    // ----------------------------------------
    // Noten einlesen + Berechnung der Endnote
    // ----------------------------------------


    float product_sum = 0;

    for (int i = 0; i < COURSE_SIZE; i++)
    {
        courses[i].grade = get_short("Note", 0, 15);                            // hier fragen wie man bei get_short noch eine Modulabk�rzung hinzuf�gen kann ()
        printf("%d\n", courses[i].grade);

        product_sum = (courses[i].grade * courses[i].valuation) + product_sum;      // wie kann ich hier die valuation einf�gen? er findet sie nicht!
        printf("%.2lf", product_sum); // nur zur Kontrolle

    }

    float final_grade = product_sum / COURSE_SIZE;
    printf("Abschlussnote: %.3lf", final_grade);

    return 0;

}

// function definitions

void get_grades(course x)                          // function to get the grades of the user and print it
{
    get_short("Note", 0, 15);
    /* calculate_final(x);*/
}                                           // nein -> man wei� nicht wie gro� das array von modulen wird -> Zeiger anlegen -> Speicher vergr��ern (Speichererweiterung mit Realloc) -> Schleife

void print_courses(course x)
{

    printf("%-5s\t", x.abbreviation);
    printf("%d\t", x.valuation);
    printf("%d\t\n", x.grade);
}


/*void calculate_final(course x)
{
    int product = x.grade * x.valuation;
    int sum = sum + product;
    printf("%d\n", sum);
} */

short get_short(char text[], short MIN, short MAX)
{
    //declare working variables 
    short value;
    int finished = 0; //0 f�r FALSE
    char ch;
    int retVal;

    do
    {
        printf("%s: ", text); //Abk�rzung "s" f�r "string" / Zeichenkette

        ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0

        retVal = scanf("%hd%c", &value, &ch); // -> "hd" steht f�r short -> Adresse ist "Value"; scanf gibt auch einen Wert zur�ck, diesen speichern wir in retVal 

        // check for valid user input
        if (retVal != 2) printf("Das war keine korrekte Zahl!\n");
        else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
        else if (value < MIN) printf("Zahl ist zu klein (MIN: %hd)\n", MIN);
        else if (value > MAX) printf("Zahl ist zu gro%c (MAX: %hd)\n", 225, MAX);
        else finished = 1; // falls die Variable tats�chlich 2 ist; und der character ein newline, ist alles richtig und die loop wird beendet

        //Variable finished wird auf 1 gesetzt -> weil 1 f�r TRUE

        //clear input stream buffer
        while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

    } while (!finished); //repeat if not finished 

    //return user input
    return value; //wer auch immer die Funktion get_short aufruft bekomm "value" zur�ck
}
