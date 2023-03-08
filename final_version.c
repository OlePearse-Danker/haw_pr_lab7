#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MODULE_COUNT 64


typedef struct MODULE
{
    char module_name[1024];
    char abbreviation[32];
    int weight;
    int grade;
}
MODULE;


void print_overview(MODULE *modules, size_t module_count);
short get_short(char text[], short MIN, short MAX);
void get_input(MODULE *modules, size_t module_count);
void grade_calculation(MODULE *modules, size_t module_count);


int main(int argc, char **argv)
{
    FILE *fp;
    FILE *fp_out;

    const size_t BUFFER_SIZE = 1024;

    char *buffer = malloc(sizeof(*buffer) * BUFFER_SIZE);
    if (!buffer)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    // Declare MODULE pointer
    // and initialize the pointer with allocating memory
    MODULE *modules = malloc(sizeof(*modules) * MAX_MODULE_COUNT);
    // Check for memory allocation error
    if (!modules)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    size_t module_count = 0;

    // Open file into filestream
    fp = fopen("module.csv", "r");
    if (!fp)
    {
        fprintf(stderr, "File could not be opened!\n");
        exit(EXIT_FAILURE);
    }

    // Read and discard first row (header)
    fgets(buffer, BUFFER_SIZE-1, fp);

    for (size_t i = 0; i < MAX_MODULE_COUNT; i++)
    {
        fgets(buffer, BUFFER_SIZE-1, fp);
        module_count++;

		strcpy(modules[i].module_name, strtok(buffer, ";"));
		strcpy(modules[i].abbreviation, strtok(NULL, ";"));
		modules[i].weight = atoi(strtok(NULL, ";"));
		modules[i].grade = atoi(strtok(NULL, ";"));

        // schaut wo end of file steht und hört dann auf -> feof steht am Ende einer Datei
        if (feof(fp)) break;                    

        // printf("Row: %s\n", modules[i].module_name);
    }

    // print_overview(modules, module_count);
    get_input(modules, module_count);
    grade_calculation(modules, module_count);

    // closing file 
    fclose(fp);

    // creating new csv files to store the grades of the user
    fp_out = fopen("user_modules.csv", "w");

    fprintf(fp_out,"Modul;Kuerzel;Gewichtung;Note\n");

    for (size_t i = 0; i < module_count; i++)
    {
        fprintf(fp_out, "%s;%s;%d;%d\n", modules[i].module_name, modules[i].abbreviation, modules[i].weight, modules[i].grade);
    }

    fclose(fp_out);
    
    // freeing pointers
    free(buffer);
    free(modules);

    return 0;
}

void print_overview(MODULE *modules, size_t module_count)
{
    for (size_t i = 0; i < module_count; i++)
    {
        printf("%s\n", modules[i].module_name);
        printf("%s\n", modules[i].abbreviation);
        printf("%d\n", modules[i].weight);
        printf("%d\n", modules[i].grade);

        printf("\n");
    }
    
    return;
}

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

void get_input(MODULE *modules, size_t module_count)
{
    

    // copying the whole struct so we can use it separately and overwrite it 
    // modules[module_count - 1]; 

    for (size_t i = 0; i < module_count; i++)
    {
        printf("Note für %s\n", modules[i].abbreviation);
        modules[i].grade = get_short("Meine Note" ,0 ,15);
        printf("\n");

    }

    return;

}

void grade_calculation(MODULE *modules, size_t module_count)
{
    int total_points = 0;

    int top = 0;
    int bottom = 0;
    float final_grade = 0;

    for (size_t i = 0; i < module_count; i++)
    {
        total_points += modules[i].grade;
        top += (modules[i].grade * modules[i].weight);
        bottom += modules[i].weight;
    }

    final_grade = (float) top / (float) bottom;

    printf("Total points: %d\n", total_points);
    printf("Your final grade: %.3f\n", final_grade);

    if (final_grade < 1)
    {
        printf("Ungenügend\n");
    }
    
    else if(final_grade >= 1 && final_grade <= 3)
    {
        printf("Mangelhaft\n");
    }

    else if(final_grade >= 4 && final_grade <= 6)
    {
        printf("Ausreichend\n");
    }

    else if(final_grade >= 7 && final_grade <= 9)
    {
        printf("Befriedigend\n");
    }

    else if(final_grade >= 10 && final_grade <= 12)
    {
        printf("Gut\n");
    }

    else if(final_grade >= 13 && final_grade <= 15)
    {
        printf("Sehr gut\n");
    }
    
    return;
}


// size_t für for-loops und für Mengen (überall da wo man hochzieht)
