#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//check if a student (string -matricola-) is inside a text file (containing all students)
int checkStud (char * id, char* filename);

//Test-MAIN
int main(int argc, char**argv) {
        char student[100];

        printf("matricola?\n");
        scanf("%s", student);

        if (checkStud(student, "./allStud.txt")<0)
                printf("Student %s not found\n", student);
        else
                printf("student %s found!\n", student);
}

int checkStud (char * id, char* filename){
        FILE *file;
        char string[50];
        int res;

        file = fopen(filename, "r");
        if(filename!=NULL) 
                printf("file %s opened\n", filename);
        
        while (fscanf(file,"%s", string) == 1){
                if(strstr(string, id)!=NULL)
                        return 1;
        }
        fclose(file);
        return -1;
}