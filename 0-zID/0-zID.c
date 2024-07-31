/******************************
 * Project: CLEAR (C LEARning)
 * Author: R
 * Date: 2024/07/28
 * Time took: DOC - 4h 11min |  07-30 [19:00 - 22:18] | 07-31 [ 20:01 - 21:02]
 ******************************/
/* <DESC>
* Paprastumui, AK = zmogausID
* Programa skirta neabuse'inimui, o treniravimuisi.
* Programa naudotis tik edukaciniais tikslais! 
* Visos generacijos pagal algoritma.
* Pagrindine uzduotis paziureti - koks Jusu *zmogausID galejo buti :)
* </DESC>
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char* getZmogausID(){
    char zmogausID[12];

    printf("Iveskite savo zmogausID: ");
    scanf("%11s",zmogausID);

    char* ptr = (char*)malloc(strlen(zmogausID) + 1);

    if ( ptr == NULL ){
        printf("malloc fail.");
        exit(1);
    }

    strcpy(ptr,zmogausID);

    return ptr;
}

int calculateControlNumber(char* dob){
    int control, preControl;
    int zID0, zID1, zID2, zID3, zID4, zID5, zID6, zID7, zID8, zID9;
    
    //Priskiriam variables individualiam skaiciui, kad galetume atlikt skaiciavimus
    
    zID0 = dob[0] - '0';
    zID1 = dob[1] - '0';
    zID2 = dob[2] - '0';
    zID3 = dob[3] - '0';
    zID4 = dob[4] - '0';
    zID5 = dob[5] - '0';
    zID6 = dob[6] - '0';
    zID7 = dob[7] - '0';
    zID8 = dob[8] - '0';
    zID9 = dob[9] - '0';

    //Atliekam skaiciavima kontroliniam skaiciui

    preControl = (((zID0) + (zID1 * 2) + (zID2 * 3) + (zID3 * 4) + (zID4 * 5) +
     (zID5 * 6) + (zID6 * 7) + (zID7 * 8) + (zID8 * 9) + (zID9)) % 11);
    
    if ( preControl == 10){
        preControl = (((zID0 * 3) + (zID1 * 4) + (zID2 * 5) + (zID3 * 6) + (zID4 * 7) +
         (zID5 * 8) + (zID6 * 9) + (zID7 * 1) + (zID8 * 2) + (zID9 * 3)) % 11);
        if ( preControl == 10 ){ preControl = 0; }
    }

    control = preControl;

    return control;
}



// Metodas nustatyti pirma zID skaiciu
char yearSexCorrelation(char* year, char sex){
    int year1, year2;
    int firstSymbolZID = 0;

    year1 = year[0] - '0';
    year2 = year[1] - '0';

    switch (year1){
        //Jeigu metai < 2000
        case 1:
            switch( year2 ){
                // 1800...1899
                case 8:
                    if ( sex == 'V' ) { firstSymbolZID = '1'; }
                    else { firstSymbolZID = '2'; }
                    break;
                // 1900...1999
                case 9:
                    if ( sex == 'V' ) { firstSymbolZID = '3'; }
                    else { firstSymbolZID = '4'; }
                    break;
            }
            break;
        // Jeigu metai >= 2000
        case 2:
            //Jeigu vyras gimes nuo 21 a.
            if ( sex == 'V' ) { firstSymbolZID = '5'; }
            //Jeigu moteris gimus nuo 21a.
            else { firstSymbolZID = '6'; }
            break;
    }

    return firstSymbolZID;
}

// Sugeneruoja pirmus 7 zID skaicius
char* getDOB(){
    char sex;
    char year[5], month[3], day[3];

    printf("Iveskite metus: ");
    scanf("%4s",year);

    printf("Iveskite menesi (01...12): ");
    scanf("%2s",month);

    printf("Iveskite diena (01...31): ");
    scanf("%2s",day);

    printf("Iveskite lyti (V/M): ");
    scanf(" %c",&sex);
    sex = toupper(sex);

    char zIDFirstChar = yearSexCorrelation(year,sex);

    char zIDPrefix[8] = {0};
    snprintf(zIDPrefix, sizeof(zIDPrefix), "%c%c%c%s%s", zIDFirstChar, year[2], year[3],month,day);
    //printf("%s",zIDPrefix);
    
    char* ptr = (char*)(malloc(strlen(zIDPrefix + 1)));
    strcpy(ptr,zIDPrefix);
    return ptr;
}

//Sugeneruos tris skaitmenis ir panaudos kontrolinio skaiciaus metoda
// 990 - visi
// 140 - top 5
char** prefixLoop(char *zIDPrefix, int length){
    char** allPossibleZIDs = (char**)malloc(length * sizeof(char*));
    int elementCount = 0;
    int controlNumber;
    char zIDPlaceholder[11] = { 0 };
    char zID[12];
    for( int i = 10; i<length+10; i++){
        //Sujungia turima prefix'a su turimais skaiciais
        snprintf(zIDPlaceholder,sizeof(zIDPlaceholder),"%s%03d",zIDPrefix,i);

        //Apskaiciuoja kontrolini skaiciu galutiniam zID
        controlNumber = calculateControlNumber(zIDPlaceholder);
        snprintf(zID,sizeof(zID),"%s%d",zIDPlaceholder,controlNumber);

        //Priskiriam atminti zID'ui ir idedam i masyva
        allPossibleZIDs[elementCount] = (char*)malloc(strlen(zID)+1);
        strcpy(allPossibleZIDs[elementCount],zID);
        elementCount++;
    }

    return allPossibleZIDs;
}

void informacinisBlokas(){
    printf("\nProject: CLEAR\n");
    printf("Repo: github.com/raksnys\n");
    printf("Uztrukta laiko: 7h 2min\n");
    printf("Build skaicius: 41\n");
    printf("Tikslas - susipazinti su C:\n");
    printf("    1. Pointeriais\n");
    printf("    2. int, char manipuliacija\n");
    printf("    3. Sintakse\n");
    printf("    4. Galvos skausmu\n");
}

void naudojimosiInstrukcija(){
    printf("\nNaudojimosi instrukcija:\n");
    printf("    1 - zID patikra (true || false)\n");
    printf("    2 - zID generacija (visi miestai)\n");
    printf("    3 - zID generacija (top 5 miestai)\n");
    printf("    4 - Informacinis blokas\n");
    printf("    5 - Iseiti\n\n");
}

bool compareTwoZIDs(char* zID1,char* zID2){
    if ( strcmp(zID1,zID2) == 0 ){
        return true;
    }
    return false;
}

void loop(char** zIDList, int length){
    for ( int i = 0; i<length; i++){
        if( i == 0 ){
            printf("==== %s ====\n","Vilnius.");
        }
        if( i == 40 ){
            printf("==== %s ====\n","KAUNAS.");
        }
        if ( i == 80 ){
            printf("==== %s ====\n","Klaipeda.");
        }
        if ( i == 100 ){
            printf("==== %s ====\n","SIAULIAI.");
        }
        if( i == 120 ){
            printf("==== %s ====\n","Panevezys.");
        }
        printf("%03d. %12s\n",i,zIDList[i]);
        free(zIDList[i]);
    }
    free(zIDList);
}

void methodCall(int method){
    switch (method){
        case 1:{
            char* zID1 = getZmogausID();
            char zID2[12];
            strcpy(zID2,zID1);

            zID2[strlen(zID1)-1] = '\0'; 
            int zID2_controlNum = calculateControlNumber(zID2);
            snprintf(zID2,12,"%s%d",zID2,zID2_controlNum);
            
            if(compareTwoZIDs(zID1,zID2)){
                printf("%s yra validus zID\n\n",zID1);
            }
            else{
                printf("%s nera validus zID...\n",zID1);
                printf("%s butu validus zID\n\n",zID2);
            }
        
            free(zID1);
            break;
        }
        case 2:{
            char* zIDPrefix = getDOB();
            char** zIDList = prefixLoop(zIDPrefix, 990);
            loop(zIDList, 990);
            free(zIDPrefix);
            break;
        }
        case 3: {
            char* zIDPrefix = getDOB();
            char** zIDList = prefixLoop((void*)zIDPrefix, 140);
            loop(zIDList, 140);
            free(zIDPrefix);
            break;
        }
        case 4:{
            informacinisBlokas();
            break;
        }
        case 5:{
            exit(1);
        }
        default:{
            printf("bandyk dar karta...");
        }
    }
}

int main(){
    

    int method;
    for(;;){
        naudojimosiInstrukcija();
        printf("Iveskite norima funkcija: ");
        scanf("%d", &method);
        methodCall(method);
    }

    return 0;
}