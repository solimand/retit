#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//check if a student (string -matricola-) is inside a text file (containing all students)
int checkStud (char * id, char* filename);

void generateHTMLpageSuccess(char matricola[5][100]);
void generateHTMLNotInListFailure(char* matricola);
void generateHTMLpageFileWriteFailure();
void generateHTMLpageDoubleSubmissionFailure(char* matricola);

//if success Res =0 
int updateLogFile(char matricola[5][100]);


void main(int argc, char**argv) {
        char student[100];
        char line[2048];
        char matricola[5][100];
        char finesezione[256];
        int studentNumber=0;

        for(int i=0; i<5; i++){
                gets(line); /* ---------------------------xxxx */
                gets(line); /* Content-Disposition: form-data; name="cognome" */
                gets(line); /* new line */
                gets(matricola[i]); matricola[i][strlen(matricola[i])-1]='\0';
        }

        if(strcmp(matricola[4],"")==0){
                studentNumber=4;
        } else {
                studentNumber=5;
        }


        for(int i=0; i<studentNumber; i++){
                if (checkStud(matricola[i], "../Courses/RetiT/iscrizioni/ListaFinale.txt")<0){ //matricola non trovata nella lista iscritti
                        generateHTMLNotInListFailure(matricola[i]);
                        return;
                }
                else if (checkStud(matricola[i], "../Courses/RetiT/iscrizioni/groups.txt")>0){ //matricola già in un altro gruppo
                        generateHTMLpageDoubleSubmissionFailure(matricola[i]);
                        return;
                }
        }

        if (updateLogFile(matricola)<0){
                generateHTMLpageFileWriteFailure();
        }
        else {
                generateHTMLpageSuccess(matricola);        
        }

}

//Res >0 if success
int checkStud (char * id, char* filename){
        FILE *file;
        char string[50];
        int res=0;
        string[0]='\0';

        file = fopen(filename, "r");
        
        while (fscanf(file,"%s", string) == 1){
                if(strcmp(string, id)==0){
                        return 1;
                }
        }
        fclose(file);
        return -1;
}

void generateHTMLpageSuccess(char matricola[5][100]){
        
        printf("Content-type: text/html\n\n");
        printf("<H1>Riassunto dati ricevuti</H1>\n");

        for(int i=0; i<5; i++){
                printf("<p>Matricola-%d: %s</p>\n", i+1, matricola[i]); 
        }        
        fflush(stdout);
}

void generateHTMLNotInListFailure(char* matricola){
        printf("Content-type: text/html\n\n");
        printf("<H1>Failure</H1>\n");
        printf("<p> La matricola %s non &egrave; nella lista degli iscritti.</p>", matricola);
        fflush(stdout);
}

void generateHTMLpageFileWriteFailure(){
        printf("Content-type: text/html\n\n");
        printf("<H1>Errore Scrittura file</H1>\n");
        fflush(stdout);
}

void generateHTMLpageDoubleSubmissionFailure(char* matricola){
        printf("Content-type: text/html\n\n");
        printf("<H1>Failure</H1>\n");
        printf("<p> La matricola %s &egrave; gi&agrave; in un altro gruppo.</p>", matricola);
        fflush(stdout);
}

int updateLogFile(char matricola[5][100]){

        FILE *groupsFile;

        char groups[255] = "../Courses/RetiT/iscrizioni/groups.txt";

        groupsFile = fopen(groups, "a");

        if (groupsFile==NULL){                
                return -1;
        }

        /* scrittura file anagrafiche */
        /* formato comma-separated */
        for(int i=0; i<5; i++){
                fprintf(groupsFile,"%s ", matricola[i]);            
        }
        fprintf(groupsFile,"\n");

        fclose(groupsFile);
        return 0;
}