#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//check if a student (string -matricola-) is inside a text file (containing all students)
int checkStud (char * id, char* filename);
// Returns 0 if s1 is substring of s2 
int isSubstring(char *s1, char *s2);

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
                res = isSubstring(id, string);
                if (res==0){
                        fclose(file);
                        return 1;
                }
        }
        fclose(file);
        return -1;
}

int isSubstring(char *s1, char *s2){ 
        int M = strlen(s1); //substring matricola =10
        int N = strlen(s2); //main-string

        char strTmp [M+1];
        strTmp[0]='\0';

        if(N>M){
                // slider-loop
                for (int i = 0; i <= N - M; i++) { 
                        //substring from i to i+M
                        strncpy(strTmp, s2+i, M);
                        strTmp[M]='\0';

                        //DBG
                        //printf("tmp string %s \n", strTmp);

                        if (strcmp(strTmp, s1)==0)
                                return 0;
                }
        } 

        return -1; 
} 