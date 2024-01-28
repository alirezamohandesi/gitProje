#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define ADDRRES_GLOBAL /mnt/f/my daneshgah/proje/global
void alias(char **dastoorat, int tedad_kalame);
char *dotGitYab();
int wildkart(char* dastoor2,int tedWildcart,char direntrry[20][20],int j,int shdorosta[20]);

//==========================================================================================
void configor(char **dastoorat, int tedad_kalame)
{
    if ((strncmp("alias", dastoorat[2], 5) == 0) || (strncmp("alias", dastoorat[3], 5) == 0))
    {
        alias(dastoorat, tedad_kalame);
        return;
    }

    if (strcmp("--global", dastoorat[2]) == 0)
    {
        FILE *hoviat;
        hoviat = fopen("/mnt/f/my daneshgah/proje/global/name.txt", "r");
        if (hoviat == NULL)
            hoviat = fopen("/mnt/f/my daneshgah/proje/global/name.txt", "w+");

        char name[30] = "";
        char email[30] = "";
        fscanf(hoviat, "name:%s\nemail:%s\n", name, email);
        if (strcmp("user.name", dastoorat[3]) == 0)
            strcpy(name, dastoorat[4]);
        if (strcmp("user.email", dastoorat[3]) == 0)
            strcpy(email, dastoorat[4]);
        fclose(hoviat);
        hoviat = fopen("/mnt/f/my daneshgah/proje/global/name.txt", "w");
        fprintf(hoviat, "name:%s\nemail:%s\n", name, email);
        printf("%s\n%s", name, email);
        fclose(hoviat);
    }

    if ((strcmp("user.name", dastoorat[2]) == 0) || (strcmp("user.email", dastoorat[2]) == 0))
    {
        char *addres = dotGitYab();
            if (strcmp(addres, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }

        strcat(addres, "/config.txt");
        FILE *config = fopen(addres, "r");
        if (config == NULL)
            config = fopen(addres, "w+");
        if (config == NULL)
        {
            printf("fatal: not in a gitman directory\n");
            return;
        }
        char name[30] = "";
        char email[30] = "";
        fscanf(config, "name:%s\nemail:%s\n", name, email);
        if (strcmp("user.name", dastoorat[2]) == 0)
            strcpy(name, dastoorat[3]);
        if (strcmp("user.email", dastoorat[2]) == 0)
            strcpy(email, dastoorat[3]);
        fclose(config);
        config = fopen(addres, "w");
        fprintf(config, "name:%s\nemail:%s\n", name, email);
        printf("%s\n%s", name, email);
        fclose(config);
    }
}
//aliasha   ==================================================================
int aliasbiar(char ** dastoorat,FILE* aliasFile,char***addastoorat);
//gol baraye tafavot global va qeiresh
void aliaschap(char **dastoorat, int tedad_kalame, int gole, FILE *aliasfile);

void alias(char **dastoorat, int tedad_kalame)
{
    if (strcmp(dastoorat[1], "config") != 0)
    {
        printf("command not found");
        return;
    }
    else if (strcmp(dastoorat[2], "--global") == 0)
    {
        FILE *aliasgol = fopen("/mnt/f/my daneshgah/proje/global/alias.txt", "a");
        aliaschap(dastoorat, tedad_kalame, 1, aliasgol);
        fclose(aliasgol);
    }
    else
    {
        char *addres = dotGitYab();
          if (strcmp(addres, "?") == 0){
         printf("fatal: not in a gitman directory\n");
            return;
        }
        strcat(addres, "/alias.txt");
        FILE *aliasngol = fopen(addres, "a");
        aliaschap(dastoorat, tedad_kalame, 0, aliasngol);
        fclose(aliasngol);
    }
}

void aliaschap(char **dastoorat, int tedad_kalame, int gole, FILE *aliasfile){
    char aliasName[100];
    sscanf(dastoorat[2+gole],"alias.%s",aliasName);
    fprintf(aliasfile,"%s : \"%s \"\n",aliasName,dastoorat[gole+3]);
}

void aliasGir(int tedad_kalame,char **dastoorat,char***addastoorat){
if(tedad_kalame!=2)
return;
char* addres = dotGitYab();
if(strcmp(addres,"?")==0)
return;
strcat(addres,"/alias.txt");
FILE* aliasFile=fopen(addres,"r");
int k=0;
if (aliasFile!=NULL)
 k = aliasbiar(dastoorat,aliasFile,addastoorat);    

// fclose(aliasFile);
if (k==1)
return;
  FILE* aliasFile1=fopen("/mnt/f/my daneshgah/proje/global/alias.txt","r");
if (aliasFile1==NULL)
{
    
    return;
}
k = aliasbiar(dastoorat,aliasFile1,addastoorat);

// fclose(aliasFile1);


}

int aliasbiar(char ** dastoorat,FILE* aliasFile,char***addastoorat){
    char aliasName[100];    
        char c;
    int k =0;
    int m=0;
    fscanf(aliasFile,"%s",aliasName);
    while (aliasName[0]!=EOF)
    {    m++;
        if(strcmp(dastoorat[1],aliasName)==0){
        k=1;
        break;
        }
    while (c !='\n'){
    c =fgetc(aliasFile);
    if(c==EOF)
    break;
    if(m==1000)
    break;
    }
    if(m==1000)
    break;
    fscanf(aliasFile,"%s",aliasName);
    }
  char** aldastoorat;
    aldastoorat=malloc(100*sizeof(int*));
    for (int i = 0; i < 100; i++)
    aldastoorat[i]=malloc(100);
    if (k==1)
{
    
    fscanf(aliasFile," : \"%s",aldastoorat[0]);
    for (int i = 0; ; i++)
    {
        if(strcmp(aldastoorat[i],"\"")==0)
        break;
        fscanf(aliasFile,"%s",aldastoorat[i+1]);
    }
    fclose(aliasFile);
    *addastoorat=aldastoorat;

    return k;
}
}
//tah alias ==========================================================================
void init(char **dastoorat, int tedad_kalame)
{
    char chek[100];
    strcpy(chek,dotGitYab());
    if (strcmp(chek,"?")!=0)
    {
        printf("there is already a .git directory here or in upper directories \n");
        return;
    }
    
    system("mkdir .gitman");
    printf("Initialized empty Git repository ");
    system("mkdir -p .gitman/staged");
    FILE *avalesh = fopen(".gitman/config.txt", "w");
    fprintf(avalesh, "#");
    printf("\n");
}
//addha =============================================================
 void copyCon( char** dastoorat,int tedad_kalame,char* addres);
void dirpakCon(char** dastoorat,int tedad_kalame,char* addres);
void add(char** dastoorat,int tedad_kalame){
    char addresaddha1[100];
strcpy(addresaddha1,dotGitYab());
    strcat(addresaddha1,"/addha.txt");
FILE* addhaFile1=fopen(addresaddha1,"a");
fprintf(addhaFile1,"@\n");


    char addres[100];
    int tedWildcart=0 ;
    for (int i = 0; i < strlen(dastoorat[2]); i++)
    {
        if(dastoorat[2][i]=='*')
        tedWildcart++;
    }
    printf("%d\n%s",tedWildcart,dastoorat[2]);
    if (strcmp(dotGitYab(),"?")==0)
    {
        printf("fatal: not in a gitman directory\n");
            return;
    }
    strcpy(addres,dotGitYab());
    strcat(addres,"/staged");
if (strcmp("-f", dastoorat[2]) == 0)
{
    for (int i = 0; i < tedad_kalame-3; i++)
    {
        strcpy(dastoorat[2],dastoorat[3+i]);
        copyCon( dastoorat, tedad_kalame,addres);
    }
    
}
else if (strcmp("-n", dastoorat[2]) == 0)
{
   char direntrry[20][20];
    DIR *dir;
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    struct dirent *entry;
    dir = opendir(cwd);
    int j=0;
    while ((entry = readdir(dir)) != NULL) {
        strcpy(direntrry[j],entry->d_name);
        j++;
    }
        closedir(dir);

    int shDorosta[20];  
    char nextLine;
  int l=0;
  char c;
char addresaddha[100];
strcpy(addresaddha,dotGitYab());
    strcat(addresaddha,"/addha.txt");
    char addha[100];
FILE* addhaFile=fopen(addresaddha,"r");
for ( int i = 0; i < j; i++){
    int parcham=0;
    do
    {
        fscanf(addhaFile,"%s",addha);
        c=fgetc(addhaFile);
        if (strcmp(addha,direntrry[i])==0)
        {
            parcham=1;
            break;
        }
        
        
    } while (c=='\n');
    rewind(addhaFile);
    if (parcham==1)
        {

shDorosta[l]=i;
l++;
        }
    
}
fclose(addhaFile);
int m=0;


    for (int i = 0; i < j; i++)
    {
if (strcmp(direntrry[i], ".") == 0 || strcmp(direntrry[i], "..") == 0) 
            continue;
    printf("%s",direntrry[i]);
    if ((i==shDorosta[m])&&(m!=l))
    {
       printf(" :st\n") ;
       m++;
    }
    else
    printf(" :un\n");
    
    
}

    return ;
}
else if (tedWildcart)
{
    //esm entry dakhel folder==============================
    char direntrry[20][20];
    DIR *dir;
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    struct dirent *entry;
    dir = opendir(cwd);
    int j=0;
    while ((entry = readdir(dir)) != NULL) {
        strcpy(direntrry[j],entry->d_name);
        j++;
    }
        closedir(dir);
int shDorosta[20];
   int o = wildkart( dastoorat[2], tedWildcart, direntrry, j,shDorosta);
    for (int i = 0; i < o; i++)
    {
        strcpy(dastoorat[2],direntrry[shDorosta[i]]);
        copyCon( dastoorat, tedad_kalame,addres);
    }
    
}

 
else
  copyCon( dastoorat, tedad_kalame,addres);
fclose(addhaFile1);

}

void copyCon(char** dastoorat,int tedad_kalame,char* addres){
char address2[100];
strcpy(address2,dotGitYab());
strcat(address2,"/addha.txt");
    FILE* addha=fopen(address2,"a");
    fprintf(addha,"%s\n",dastoorat[2]);
    fclose(addha);
 FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\ncp -r %s %s ",dastoorat[2],addres);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
 dirpakCon( dastoorat, tedad_kalame, addres);
}

void dirpakCon(char** dastoorat,int tedad_kalame,char* addres){
char direntrry[20][20];
    DIR *dir;
        int basgashtaya=0;
    struct dirent *entry;
    dir = opendir(addres);
    struct stat st;
    
    if (dir == NULL) {
        perror("opendir error");
        return ;
    }
    int j=0;
    while ((entry = readdir(dir)) != NULL) {
        strcpy(direntrry[j],entry->d_name);
        j++;
    }

    for (int i = 0; i < j; i++)
    {
         if (strcmp(direntrry[i], ".") == 0 || strcmp(direntrry[i], "..") == 0) {
            continue;
        }
        char address2[100];
strcpy(address2,dotGitYab());
strcat(address2,"/addha.txt");
        char addres2[100];
        strcpy(addres2,addres);
        strcat(addres2,"/");
        strcat(addres2,direntrry[i]);
        stat(addres2,&st);
       if( S_ISDIR(st.st_mode)){
        //==
    DIR *dir1;
    struct dirent *entry1;
    dir1 = opendir(addres2);
    
    while ((entry1 = readdir(dir1)) != NULL) {
        FILE* addha=fopen(address2,"a");
        if (strcmp(entry1->d_name, ".") == 0 || strcmp(entry1->d_name, "..") == 0) 
            continue;
    fprintf(addha,"%s\n",entry1->d_name);
    fclose(addha);
    }
        //==
        basgashtaya=1;
strcat(addres2,"/*");
        FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\ncp -r %s %s \nrm -r %s/%s",addres2,addres,addres,direntrry[i]);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
 
       }
    }
    closedir(dir);
    if(basgashtaya)
    dirpakCon(dastoorat, tedad_kalame, addres);
    return;
}
//tah addha===================================================
void resetcon(char* dastoor2,char addres[100],char dastoor2j[100]);
void undoreset(char addres[100]);
void file_addha_reset(char addres[100],char name[100]);
void file_addha_reset_undo(char addres[100],int tedkaj);
void reset(char** dastoorat,int tedad_kalame){
    char addres[100];
    int tedWildcart=0 ;
    for (int i = 0; i < strlen(dastoorat[2]); i++)
    {
        if(dastoorat[2][i]=='*')
        tedWildcart++;
    }
    printf("%d\n%s",tedWildcart,dastoorat[2]);
    if (strcmp(dotGitYab(),"?")==0)
    {
        printf("fatal: not in a gitman directory\n");
            return;
    }
    strcpy(addres,dotGitYab());
    strcat(addres,"/staged");
if (strcmp("-f", dastoorat[2]) == 0)
{
    for (int i = 0; i < tedad_kalame-3; i++)
    {
        strcpy(dastoorat[2],dastoorat[3+i]);
        resetcon( dastoorat[2],addres,dastoorat[2]);
    }
    
}
else if (tedWildcart)
{
    //esm entry dakhel folder==============================
    char direntrry[20][20];
    DIR *dir;
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    struct dirent *entry;
    dir = opendir(cwd);
    int j=0;
    while ((entry = readdir(dir)) != NULL) {
        strcpy(direntrry[j],entry->d_name);
        j++;
    }
        closedir(dir);
int shDorosta[20];
   int o = wildkart( dastoorat[2], tedWildcart, direntrry, j,shDorosta);
    for (int i = 0; i < o; i++)
    {
        strcpy(dastoorat[2],direntrry[shDorosta[i]]);
        resetcon( dastoorat[2],addres,dastoorat[2]);
    }
    
}
else if (strcmp("-undo", dastoorat[2]) == 0)
undoreset(addres);

 
else
  resetcon( dastoorat[2],addres,dastoorat[2]);
}

void undoreset(char addres[100]){
    char addres2[100];
    strcpy(addres2,dotGitYab());
    strcat(addres2,"/addha.txt");
    FILE* addhaFile =fopen(addres2,"r");
    int tedkaj=0;
    char c;
    do
    {
        c =fgetc(addhaFile);
        if(c=='@')
        tedkaj++;
    } while (c!=EOF);
    rewind(addhaFile);    
    for (int i = 0; i < tedkaj-1;)
    {
        c =fgetc(addhaFile);
        if(c=='@')
        i++;
    }
    if(tedkaj!=1)
    fgetc(addhaFile);
    char resetiha[100];
    do
    {
        fscanf(addhaFile,"%s",resetiha);
        fgetc(addhaFile);
        if(strcmp(resetiha,"@")!=0){
    struct stat st;

stat(resetiha,&st);
// goh sag dorost nashod :eror bara dir ha
    //    if(!( S_ISDIR(st.st_mode))){
 FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\nrm %s/%s ",addres,resetiha);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
        // resetcon(resetiha,addres,resetiha);
        
    //    }
        }
    } while (strcmp(resetiha,"@")!=0);
    strcpy(addres,dotGitYab());
strcat(addres,"/addha.txt");
    file_addha_reset_undo(addres,tedkaj);
    fclose(addhaFile);
}

void file_addha_reset_undo(char addres[100],int tedkaj){
char c;
FILE* addhaFile =fopen(addres,"r");
char addres2[100];
strcpy(addres2,addres);
strcat(addres2,"1");
FILE* addhaFile1 =fopen(addres2,"w");
    do
    {
        
        c =fgetc(addhaFile);
    } while (c!=EOF);

     rewind(addhaFile);    
    for (int i = 0; i < tedkaj-1;)
    {
        c =fgetc(addhaFile);
        fprintf(addhaFile1,"%c",c);
        if(c=='@')
        i++;
    }
                    FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\nrm -r %s\nmv %s %s",addres,addres2,addres);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
 fclose(addhaFile1);
 fclose(addhaFile);
}

void resetcon(char* dastoor2,char addres[100],char dastoor2j[100]){
    char address2[100];
    struct stat st;
strcpy(address2,dotGitYab());
strcat(address2,"/addha.txt");
stat(dastoor2,&st);
       file_addha_reset(address2,dastoor2j);
       if(!( S_ISDIR(st.st_mode))){
 FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\nrm %s/%s ",addres,dastoor2j);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
       }
       else{
        char direntrry[20][20];
    DIR *dir;
    struct dirent *entry;
    dir = opendir(dastoor2);
    while ((entry = readdir(dir)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
            continue;
        char address3[100];
        strcpy(address3,dastoor2);
         strcat(address3,"/");
        strcat(address3,entry->d_name);
        resetcon(address3,addres,entry->d_name);
    }
        closedir(dir);
       }
}
void file_addha_reset(char addres[100],char name[100]){
    FILE* addha=fopen(addres,"r");
    char c;
    char addshode[100];
    char addhajadid[100][100];
    int i=0;
    do
    {
        
        fscanf(addha,"%s",addshode);
        c=fgetc(addha);
        // printf("%s ",dic);
        if (strcmp(name,addshode)!=0)
        {
        strcpy(addhajadid[i],addshode);
        i++;
        }
        
        
    } while (c=='\n');
    fclose(addha);
    char addres3[100];
    strcpy(addres3,addres);
    strcat(addres3,"1");
   FILE* addha1=fopen(addres3,"a");
    for (int j = 0; j < i; j++)
{
        fprintf(addha1,"%s\n",addhajadid[j]);
        // printf("%s",addhajadid[j]);
}
        fclose(addha1);
                FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\nrm -r %s\nmv %s %s",addres,addres3,addres);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
}

//omoomy portekrar===================================================================
char *dotGitYab()
{
    char *addres = malloc(100);
    char dot2[100];
    strcpy(addres, ".gitman");
    for (int i = 0; i < 10; i++)
    {
        strcpy(dot2, "../");
        if (access(addres, F_OK) == 0)
            return addres;
        strcat(dot2, addres);
        strcpy(addres, dot2);
    }
    return "?";
}

int wildkart(char* dastoor2,int tedWildcart,char direntrry[20][20],int j,int shdorosta[20]){
    
    char tekeha[tedWildcart+1][10];
    int k =0;
    int o=0;
    char zapas[20];
    strcpy(zapas,dastoor2);
    const char s[2] = "*";
   char *token;
   token = strtok(zapas, s);
   
   while( token != NULL ) {
strcpy(tekeha[k],token) ; 
k++;  
      token = strtok(NULL, s);
   }
//=======================================
    for (int i = 0; i < j; i++)
    {
        int r=0;
        char* c;
        int parcham =0;
        if(dastoor2[0]!='*'){
    if(strncmp(tekeha[0],direntrry[i],strlen(tekeha[0]))!=0){
    continue;
    }
}
if(dastoor2[strlen(dastoor2)-1]!='*'){
    if (strcmp(tekeha[k-1],direntrry[i]+strlen(direntrry[i])-strlen(tekeha[k-1]))!=0)
    continue;
    
}

        for (int m = 0; m < k; m++)
        {
            parcham =0;
            if ((c=strstr(direntrry[i]+r,tekeha[m]))!=NULL)
            {
                 
                r=(int)(c-direntrry[i]);
                r+=strlen(tekeha[m]);
            }
            else {
            parcham =1;
            break;
            }
            
        }
        if(parcham==0){
shdorosta[o]=i;
o++;
        printf("%s",direntrry[i]);
        }
        
    }
    return o;
 }
 //==========================================================================
int main(int tedad_kalame, char **dastoorat)
{
 aliasGir(tedad_kalame, dastoorat,&dastoorat);
//  printf("%s",dastoorat[1]);
    if (strcmp("config", dastoorat[1]) == 0)
        configor(dastoorat, tedad_kalame);
    if (strcmp("init", dastoorat[1]) == 0)
        init(dastoorat, tedad_kalame);
    if (strcmp("add", dastoorat[1]) == 0)
    add(dastoorat, tedad_kalame);
    if (strcmp("reset", dastoorat[1]) == 0)
    reset(dastoorat, tedad_kalame);
    return 0;
}