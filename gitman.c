#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#define ADDRRES_GLOBAL /mnt/f/my daneshgah/proje/global
void alias(char **dastoorat, int tedad_kalame);
char *dotGitYab();
int wildkart(char* dastoor2,int tedWildcart,char direntrry[20][20],int j,int shdorosta[20]);
int configyab(char name[30],char email[30]);

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
        // printf("%s\n%s", name, email);
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
        // printf("%s\n%s", name, email);
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
        printf("command not found\n");
        return;
    }
    else if (strcmp(dastoorat[2], "--global") == 0)
    {
        if (strncmp(dastoorat[4],"gitman ",7)!=0)
        {
        printf("command not found\n");
        return;
        }
        
        FILE *aliasgol = fopen("/mnt/f/my daneshgah/proje/global/alias.txt", "a");
        aliaschap(dastoorat, tedad_kalame, 1, aliasgol);
        fclose(aliasgol);
    }
    else
    {
        if (strncmp(dastoorat[3],"gitman ",7)!=0)
        {
        printf("command not found\n");
        return;
        }

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
    return;
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
        printf("there is already a .gitman directory here or in upper directories \n");
        return;
    }
    
    system("mkdir .gitman");
    printf("Initialized empty Git repository ");
    system("mkdir -p .gitman/staged");
    system("mkdir -p .gitman/commitha");
    system("mkdir -p .gitman/resetshode");
    FILE *avalesh = fopen(".gitman/commit_info.txt", "w");
    fclose(avalesh);
     avalesh = fopen(".gitman/config.txt", "w");
    fprintf(avalesh, "#");
    fclose(avalesh);
    avalesh = fopen(".gitman/branch_hal.txt", "w");
    fprintf(avalesh, "master");
    fclose(avalesh);
    printf("\n");
}
//addha =============================================================
 void copyCon( char** dastoorat,int tedad_kalame,char* addres);
void dirpakCon(char** dastoorat,int tedad_kalame,char* addres);
void add_n(int omgh,char* add_folder);
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
    // printf("%d\n%s",tedWildcart,dastoorat[2]);
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
int omgh =(int)(dastoorat[3][0]-48);
add_n(omgh,".");
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
        if (strncmp(entry->d_name, ".",1) == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
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
else if (strcmp("-redo", dastoorat[2]) == 0)
{
    char command[300];
    sprintf(command,"mv %s/resetshode/* %s/staged",dotGitYab(),dotGitYab());
    system(command);
    char resetshode[100];
    sprintf(resetshode,"%s/resetshode.txt",dotGitYab());
    FILE* resetshodef =fopen(resetshode,"r");
    char addha[100];
    sprintf(addha,"%s/addha.txt",dotGitYab());
    FILE* addhaf =fopen(addha,"a");
    char c=' ';
    while (c!=EOF)
    {
        c=fgetc(resetshodef);
        if(c!=EOF)
        fprintf(addhaf,"%c",c);

    }
    // fprintf(addhaf,"@\n");
    fclose(addhaf);
    fclose(resetshodef);
    addhaf =fopen(resetshode,"w");
    fclose(addhaf);
}

 
else
  copyCon( dastoorat, tedad_kalame,addres);
fclose(addhaFile1);

}
void add_n(int omgh,char* add_folder){
char direntrry[20][20];
    DIR *dir;
    // char cwd[PATH_MAX];
    // getcwd(cwd, sizeof(cwd));
    struct dirent *entry;
    dir = opendir(add_folder);
    int j=0;
    while ((entry = readdir(dir)) != NULL) {
        if(strncmp(entry->d_name,".",1)==0)
        continue;
        strcpy(direntrry[j],entry->d_name);
        char add_zirfol[600];
        sprintf(add_zirfol,"%s/%s",add_folder,entry->d_name);
        if ((opendir(add_zirfol)!=NULL)&&(omgh>1))
        {
            add_n(omgh-1,add_zirfol);
        }
        
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

void copyCon(char** dastoorat,int tedad_kalame,char* addres){
char address2[100];
strcpy(address2,dotGitYab());
strcat(address2,"/addha.txt"); 
 FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\ncp -r %s %s ",dastoorat[2],addres);
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
 if(access(dastoorat[2],F_OK)!=0){
    return;
 }
 FILE* addha=fopen(address2,"a");
    fprintf(addha,"%s\n",dastoorat[2]);
    fclose(addha);
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
         if (strncmp(direntrry[i], ".",1) == 0 || strcmp(direntrry[i], "..") == 0) {
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
        if (strncmp(entry1->d_name, ".",1) == 0 || strcmp(entry1->d_name, "..") == 0) 
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
//resetha=========================================================
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
    // printf("%d\n%s",tedWildcart,dastoorat[2]);
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
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }

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
char add_staged[500];
sprintf(add_staged,"%s/%s",addres,resetiha);
       if(access(add_staged,F_OK)==0){
 FILE* bash = fopen("bash.sh","w");
 fprintf(bash,"#!/bin/bash\nmv %s/%s %s/resetshode ",addres,resetiha,dotGitYab());
 fclose(bash);
 system("./bash.sh");
 system("rm bash.sh");
        // resetcon(resetiha,addres,resetiha);
        
       }
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
char add_resetshode[300];
    sprintf(add_resetshode,"%s/resetshode.txt",dotGitYab());
    FILE* resetshodeha =fopen(add_resetshode,"a");
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
    fprintf(addhaFile1,"\n");
   c= fgetc(addhaFile);
    while (c!='@')
    {
       c= fgetc(addhaFile);
       if(c!='@')
       fprintf(resetshodeha,"%c",c);
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
 fprintf(bash,"#!/bin/bash\nmv %s/%s %s/resetshode",addres,dastoor2j,dotGitYab());
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
    char add_resetshode[300];
    sprintf(add_resetshode,"%s/resetshode.txt",dotGitYab());
    FILE* resetshodeha =fopen(add_resetshode,"a");
    fprintf(resetshodeha,"%s\n",name);
    fclose(resetshodeha);
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
    for (int j = 0; j < i-1; j++)
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
//tahresetha=========================================================
//commitha==============================================================
void commit_ghabli_biar(int sh_commit);
int file_yab(char* file_name);
void commit(char** dastooorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
    char add_head[100];
    strcpy(add_head,dotGitYab());
    strcat(add_head,"/head.txt");
    FILE* x=fopen(add_head,"r");
    if (x!=NULL)
    {
printf("you can't commit out of HEAD\n");
return;
    }
    
char address_staged[100];
char address_commit[100];
char address_addha[100];
char address_sh_akhcom[100];
strcpy(address_staged,dotGitYab());
strcat(address_staged,"/staged");
strcpy(address_commit,dotGitYab());
strcat(address_commit,"/commitha");
strcpy(address_addha,dotGitYab());
strcat(address_addha,"/addha.txt");
strcpy(address_sh_akhcom,dotGitYab());
strcat(address_sh_akhcom,"/sh_akhcom.txt");
struct dirent* staged;
  DIR *dirstag= opendir(address_staged);
  int n=0;
  char staged_entry[100][100];
  char name[30];
  char email[30];
  int parcham =configyab(name,email);  

  while ((staged=readdir(dirstag))!=NULL)
  {
    if (strcmp(staged->d_name, ".") == 0 || strcmp(staged->d_name, "..") == 0) 
            continue;
    strcpy(staged_entry[n],staged->d_name);
    n++;
  }
   if (parcham==0)
{
    printf("please config\n");
    return;
}

  else if (n<=0){
    printf("sataged is empty\n");
    return;
  }
 else if (strcmp(dastooorat[2],"-s")==0){
    char address_short[100];
    strcpy(address_short,dotGitYab());
    strcat(address_short,"/shortcut.txt");
    FILE* short_file =fopen(address_short,"r");
    if (short_file==NULL){
        printf("shortcut doesn't exist\n");
        return;
    }

 char shortname[100];    
        char c;
    int k =0;
    int m=0;
    fscanf(short_file,"%s",shortname);
    while (shortname[0]!=EOF)
    {    m++;
        if(strcmp(dastooorat[3],shortname)==0){
        k=1;
        break;
        }
    while (c !='\n'){
    c =fgetc(short_file);
    if(c==EOF)
    break;
    if(m==1000)
    break;
    }
    if(m==1000)
    break;
    fscanf(short_file,"%s",shortname);
    }
  char* aldastoorat =malloc(100);
    if (k==1)
{
    
    fscanf(short_file," : \"%[^\"]",aldastoorat);
    fclose(short_file);
    dastooorat[3]=aldastoorat;
    strcpy(dastooorat[2],"-m");
  }
  else 
          printf("shortcut doesn't exist\n");
          return;
 }
 else if (strcmp(dastooorat[2],"-m")!=0){
    printf("command not found\n");
    return;
  }
   else if (dastooorat[3]==NULL){
    printf(" write a message for commit\n");
    return;
  }
    else if (tedad_kalame!=4){
    printf("command not found\n");
    return;
  }
  else if (strlen(dastooorat[3])>72){
    printf("the message contain more than 72 character\n");
    return;
  }

char address_commit_info[100];
strcpy(address_commit_info,dotGitYab());
strcat(address_commit_info,"/commit_info.txt");
FILE* com_info = fopen(address_commit_info,"a");
  struct dirent* commitha;
  DIR *dircommit= opendir(address_commit);
  int m=0;
    //=====
    time_t rawtime;
   struct tm *info;
   char buffer[80];
   time(&rawtime);

   info = localtime( &rawtime );

   strftime(buffer,80,"%Y/%m/%d %X", info);
    //==========

  while ((commitha=readdir(dircommit))!=NULL)
  {
    if (strcmp(commitha->d_name, ".") == 0 || strcmp(commitha->d_name, "..") == 0) 
            continue;
    m++;
  }
  FILE* avalesh = fopen(".gitman/branch_hal.txt", "r");
  char branch_name[100];
    fscanf(avalesh, "%s",branch_name);
    fclose(avalesh);

fprintf(com_info,"payam: \"%s\"\ntime: \"%s\"\nname: %s\nemail: %s\nnumber of files: %d\nID: %d\nbranch: %s\n@\n",dastooorat[3],buffer,name,email,n,m+1,branch_name);
fclose(com_info);
// brancham bezar
  closedir(dircommit);
  closedir(dirstag);
  char command[500];
  sprintf(command,"mkdir %s/commit%d",address_commit,m+1);
//   printf("%s", command);
    system(command);
  commit_ghabli_biar(m+1);
    sprintf(command,"mv %s/* %s/commit%d",address_staged,address_commit,m+1);
    system(command);
     FILE* a= fopen(address_addha,"w");
    fclose(a);
     a= fopen(address_sh_akhcom,"w");
     fprintf(a,"%d",m+1);
    fclose(a);
}

void commit_ghabli_biar(int sh_commit){
if(sh_commit==1)
return;
char add_jadcom[100];
char add_akhcom[100];
strcpy(add_akhcom,dotGitYab());
strcpy(add_jadcom,dotGitYab());
char tahjad[25];
sprintf(tahjad,"/commitha/commit%d",sh_commit);
char tahakh[25];
sprintf(tahakh,"/commitha/commit%d",sh_commit-1);
strcat(add_jadcom,tahjad);
strcat(add_akhcom,tahakh);
DIR* akhcom;
akhcom= opendir(add_akhcom);
if(akhcom==NULL){
printf("???");
return ;
}
struct dirent* fileha_akhcom;
while ((fileha_akhcom = readdir(akhcom)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
        if (strcmp(fileha_akhcom->d_name, ".") == 0 || strcmp(fileha_akhcom->d_name, "..") == 0) 
            continue;
       int vogood = file_yab(fileha_akhcom->d_name);
       if(vogood==1){
        char command[500];
        sprintf(command,"cp %s/%s %s",add_akhcom,fileha_akhcom->d_name,add_jadcom);
        system(command);
       }
    }
}

int file_yab(char *file_name){
 char command[400];
 sprintf(command,"find . -name %s >1.txt",file_name);
 system(command);
 FILE* javab = fopen("1.txt","r");
 char c=' ';
 char khat[200];
 while (c!=EOF)
 {
   c= fgetc(javab);
   if(c==EOF)
   break;
    fgets(khat,199,javab);
if (strncmp(khat,"/.git",5)!=0)
return 1;

 }
 return 0;
}

void set(char** dastooorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
  if (strcmp(dastooorat[2],"-m")!=0){
    printf("command not found\n");
    return;
  }
   else if (strcmp(dastooorat[4],"-s")!=0){
    printf("command not found\n");
    return;
  }
  char address_short[100];
  strcpy(address_short,dotGitYab());
  strcat(address_short,"/shortcut.txt");
  FILE* short_file=fopen(address_short,"a");
  fprintf(short_file,"%s : \"%s\"\n",dastooorat[5],dastooorat[3]);
  fclose(short_file);
}

void replace(char** dastooorat,int tedad_kalame,int rem_or_rep){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
   char old_address_short[100];
    strcpy(old_address_short,dotGitYab());
  strcat(old_address_short,"/shortcut.txt");
FILE* old_short = fopen(old_address_short,"r");
if (old_short==NULL)
{
printf("shortcut doesn't exist\n");
        return;
        }
char new_address_short[150];
    strcpy(new_address_short,dotGitYab());
  strcat(new_address_short,"/shortcut1.txt");
FILE* new_short = fopen(new_address_short,"w");
char c;
int n_newlin=0;
while (c!=EOF)
{
    c=fgetc(old_short);
    if(c=='\n')
    n_newlin++;
}
rewind(old_short);
char shortcut[100];
int parcham=0;
for (int i = 0; i < n_newlin; i++)
{
    fgets(shortcut,99,old_short);
    if((strncmp(dastooorat[5],shortcut,strlen(dastooorat[5]))==0)){
        parcham=1;
        char shortcut_name[40];
        char shortcut_mes[100];
    sscanf(shortcut,"%s : %s",shortcut_name,shortcut_mes);
    if (strlen(dastooorat[3])>72)
    {
     printf("the message contain more than 72 character\n");
    return;
    }
    fprintf(new_short,"%s : \"%s\"\n",shortcut_name,dastooorat[3]);
    continue;
    }
    if(strncmp(dastooorat[3],shortcut,strlen(dastooorat[3]))==0){
    parcham=1;
    continue;
    }
    fprintf(new_short,"%s",shortcut);
}
if(parcham==0){
printf("shortcut doesn't exist\n");
return;
}
char command[500];
sprintf(command,"rm %s",old_address_short);
system(command);
sprintf(command,"mv %s %s",new_address_short,old_address_short);
system(command);


}
//tahcommitha==============================================================
//log ha ===============================================================
  int austhor_yab(char* author,int n,int sh_commit_ok[n],FILE* cominfo_file);
  int zoodtaryab(char* zaman_aval,char*zaman_dovom);
  int time_com(char* time_hadaf,int n,FILE* cominfo_file);
 void logcom(char** dastooorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
char address_cominfo[100];
strcpy(address_cominfo,dotGitYab());
strcat(address_cominfo,"/commit_info.txt");
FILE* cominfo_file =fopen(address_cominfo,"r");
char c;
int n=0;
while (c!=EOF)
{
c=fgetc(cominfo_file);
if(c=='@')
n++;
}
int sh_commit_ok[n];
long ted_com=n;
if ((tedad_kalame==4)&&(strcmp(dastooorat[2],"-n")==0))
{
     ted_com=strtol(dastooorat[3],NULL,10);
}
else if ((tedad_kalame==4)&&(strcmp(dastooorat[2],"-author")==0))
{
 ted_com = austhor_yab(dastooorat[3],n,sh_commit_ok,cominfo_file);
 if (ted_com==0)
    printf("the author doesn't exist\n");
    return;
}
else if ((tedad_kalame==4)&&(strcmp(dastooorat[2],"-branch")==0))
{
 ted_com = austhor_yab(dastooorat[3],n+1000,sh_commit_ok,cominfo_file);
 if (ted_com==0)
    printf("the branch doesn't exist\n");
    return;
}
else if ((tedad_kalame>=4)&&(strcmp(dastooorat[2],"-search")==0))
{
    ted_com=0;
    for (int i = 0; i <tedad_kalame-3 ; i++)
    {
 ted_com+= austhor_yab(dastooorat[i+3],n+500,sh_commit_ok,cominfo_file);
    }
    
 if (ted_com==0)
    printf("the word doesn't exist\n");
    return;
}
else if ((tedad_kalame==4)&&((strcmp(dastooorat[2],"-since")==0)||(strcmp(dastooorat[2],"-before")==0)))
{
    if((strcmp(dastooorat[2],"-since")==0))
    n+=500;
 ted_com = time_com(dastooorat[3],n,cominfo_file);
 if (ted_com==0)
    printf("no commit %s this time\n",dastooorat[2]);
    return;
}
rewind(cominfo_file);
int k=0;
for (int i = 0; i < ted_com; i++)
{
    while (k!=(n-i-1))
    {
    
    c= fgetc(cominfo_file);
    if(c=='@')
     k++;
    }
    if (k==(n-i-1))
    {
        fgetc(cominfo_file);
        char c2=' ';
        while (c2!='@')
        {
            c2 =fgetc(cominfo_file);
            printf("%c",c2);
        }
        printf("\n");
        k=0;
        rewind(cominfo_file);
        continue;
    }  
}
fclose(cominfo_file);
}

int time_com(char* time_hadaf,int n,FILE* cominfo_file){
    int mahala=0;
    int parcham=0;
    if(n>=500){
        n-=500;
        parcham=1;
        //since
    }
    int mahalp=n;
rewind(cominfo_file);
char zamanha[100];
for (int i = 0; i < n; i++)
{
    char alak[200];
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"time: \"%[^\"]\"\n",zamanha);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
int parcham2 =zoodtaryab(zamanha,time_hadaf);
if ((parcham2==1)&&(parcham==1))
{
mahala=i;
//az hamin shroo she
break;
}
else if((parcham2==2)&&(parcham==0)){
    mahalp=i+1;
// if(i==0)
// return 1;
}
else if ((i==n-1)&&(parcham==1))
{
return 0;
}
else if ((i==n-1)&&(parcham==0)&&(mahalp==n))
{
return 0;
}
    }


    rewind(cominfo_file);
int k=0;
char c;
for (int i = n-mahalp; i < n-mahala; i++)
{
    while (k!=(n-i-1))
    {
    
    c= fgetc(cominfo_file);
    if(c=='@')
     k++;
    }
    if (k==(n-i-1))
    {
        fgetc(cominfo_file);
        char c2=' ';
        while (c2!='@')
        {
            c2 =fgetc(cominfo_file);
            printf("%c",c2);
        }
        printf("\n");
        k=0;
        rewind(cominfo_file);
        continue;
    }  
}
fclose(cominfo_file);
return 1;
}

  int zoodtaryab(char* zaman_aval,char*zaman_dovom){
int sal_av;
    int mah_av;
    int rooz_av;
    int saat_av;
    int daghighe_av;
    int sanie_av;
    int sal_do;
    int mah_do;
    int rooz_do;
    int saat_do;
    int daghighe_do;
    int sanie_do;
    sscanf(zaman_aval,"%d/%d/%d %d:%d:%d",&sal_av,&mah_av,&rooz_av,&saat_av,&daghighe_av,&sanie_av);
    sscanf(zaman_dovom,"%d/%d/%d %d:%d:%d",&sal_do,&mah_do,&rooz_do,&saat_do,&daghighe_do,&sanie_do);
    if(sal_av>sal_do)
    return 1;
    if(sal_av<sal_do)
    return 2;
    else if(mah_av>mah_do)
    return 1;
    else if(mah_av<mah_do)
    return 2;
    else if(rooz_av>rooz_do)
    return 1;
    else if(rooz_av<rooz_do)
    return 2;
    else if(saat_av>saat_do)
    return 1;
    else if(saat_av<saat_do)
    return 2;
    else if(daghighe_av>daghighe_do)
    return 1;
    else if(daghighe_av<daghighe_do)
    return 2;
    else if(sanie_av>sanie_do)
    return 1;
    else if(sanie_av<sanie_do)
    return 2;
    else return 3;
  }

  int austhor_yab(char* author,int n,int sh_commit_ok[n],FILE* cominfo_file){
    int ted=0;
    int parcham=0;
    if(n>=1000){
parcham=1;
    n-=1000;
    }
        if(n>=500){
parcham=2;
    n-=500;
    }
rewind(cominfo_file);
char authorha[100];
for (int i = 0; i < n; i++)
{
    char alak[200];
    if(parcham==0){
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"name: %s\n",authorha);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
    }
    else if(parcham==1){
        fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"branch: %s\n",authorha);
fgets(alak,199,cominfo_file);
    }
        else if(parcham==2){
fscanf(cominfo_file,"payam: \"%[^\"]\"\n",authorha);
        fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
    }
    if(parcham!=2){
    if (strcmp(author,authorha)==0)
    {
        ted++;
        sh_commit_ok[ted]=i+1;
    } 
    }
    else{
        if (strstr(authorha,author)!=NULL)
    {
        ted++;
        sh_commit_ok[ted]=i+1;
    } 
    }
}
char c;
int k=0;
int j=0;
rewind(cominfo_file);
for (int i = 0; i < n; i++)
{
    while (k!=(n-i-1))
    {
    c= fgetc(cominfo_file);
    if(c=='@')
     k++;
    }
    if (k==(n-i-1))
    {
        fgetc(cominfo_file);
        char c2=' ';
        if((n-i)==sh_commit_ok[ted-j]){
        while (c2!='@')
        {
            c2 =fgetc(cominfo_file);
            printf("%c",c2);
        }
        printf("\n");
        j++;
        if(j==ted)
        return ted;
        }
        k=0;
        rewind(cominfo_file);
        continue;
    }  
}
return ted;
  }
//tah log ha ===============================================================
//branch===================================================================
void branch_chap(char add_branch_name[100]);
void branch(char** dastooorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
char add_branch_name[100];
strcpy(add_branch_name,dotGitYab());
strcat(add_branch_name,"/branches.txt");
    if(tedad_kalame==2){
    branch_chap(add_branch_name);
    return;
    }
    FILE* branch_name_file = fopen(add_branch_name,"r");
    int parcham =1;
    if (branch_name_file==NULL)
parcham=0;
char b_name[100];
char c;
while ((b_name[0]!=EOF)&&parcham)
{
fscanf(branch_name_file,"%s",b_name);
if (strcmp(b_name,dastooorat[2])==0)
{
    printf("the branch neme already exist\n");
    return;
}
c=fgetc(branch_name_file);
if(c==EOF)
break;
}
fclose(branch_name_file);

    branch_name_file = fopen(add_branch_name,"a");
    fprintf(branch_name_file,"%s\n",dastooorat[2]);
    fclose(branch_name_file);
    char add_branch_fir[100];
    if(strlen(dotGitYab())==1){
        printf("fatal: not in a gitman directory\n");
            return;
    }
    char address_sh_akhcom[100];
    strcpy(address_sh_akhcom,dotGitYab());
strcat(address_sh_akhcom,"/sh_akhcom.txt");
    char command[200];
    int sh_akhcom;
sprintf(command,"mkdir .git_branch_%s",dastooorat[2]);
system(command);
FILE* file_akhcom =fopen(address_sh_akhcom,"r");
if (file_akhcom!=NULL)
{
fscanf(file_akhcom,"%d",&sh_akhcom);
sprintf(command,"cp .gitman/commitha/commit%d/* .git_branch_%s",sh_akhcom,dastooorat[2]);
system (command);
}
fclose(file_akhcom);
}

void branch_chap(char add_branch_name[100]){
FILE* branches =fopen(add_branch_name,"r");
if (branches==NULL)
{
printf("There are no branches\n");
return;
}
char b_name[100];
char c;
while (b_name[0]!=EOF)
{
fscanf(branches,"%s",b_name);
c=fgetc(branches);
if(c==EOF)
break;
printf("%s\n",b_name);

}



}
//tahbranch===================================================================
//checkout====================================================================
int check_taqir();
void checkout(char** dastooorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
    char hal_bra[100];
FILE* branch_hal_file =fopen(".gitman/branch_hal.txt","r");
fscanf(branch_hal_file,"%s",hal_bra);
fclose(branch_hal_file);
    int check =check_taqir();
    int head_par =0;
     if(strcmp(dastooorat[2],"HEAD")==0){
strcpy(dastooorat[2],hal_bra);
system("rm .gitman/head.txt");
head_par =1;
}

else if (check==0)
{
printf("please commit your changes\n");
return;
}

if(isdigit( dastooorat[2][0])){
    //پیدا کردن هد
        char hal_bra[100];
    int sh_akhcom;
FILE* branch_hal_file =fopen(".gitman/branch_hal.txt","r");
fscanf(branch_hal_file,"%s",hal_bra);
fclose(branch_hal_file);
FILE* file_akhcom= fopen(".gitman/sh_akhcom.txt","r");
fscanf(file_akhcom,"%d", &sh_akhcom);
fclose(file_akhcom);
FILE* cominfo_file = fopen(".gitman/commit_info.txt","r");
char alak[200];
int sh_akhcom_bra=0;
for (int i = 0; i < sh_akhcom; i++)
{
    fgets(alak,199,cominfo_file);
    fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"branch: %s\n",alak);
// printf("%s",alak);
if (strcmp(alak,hal_bra)==0){
    sh_akhcom_bra=i+1;
}
fgets(alak,199,cominfo_file);
}
FILE* file = fopen(".gitman/head.txt","w");
fprintf(file,"%d\n",sh_akhcom_bra);
fclose(file);
//پاک کردن هد و ریختن فایلای فعلی توش و پاک کردن محل کار
char command[150];
    char dir_commit_hal[100];
    sprintf(dir_commit_hal,".gitman/commitha/commit%d",sh_akhcom_bra);
    sprintf(command,"rm -r %s",dir_commit_hal);
        system(command);
    
    sprintf(command,"mkdir %s",dir_commit_hal);
        system(command);
        sprintf(command,"mv [!.]* %s",dir_commit_hal);
        system(command);
        //ریختن فایل های کامیته در اینجا
        char dir_commit_jad[100];
            sprintf(dir_commit_jad,".gitman/commitha/commit%s",dastooorat[2]);
        sprintf(command,"cp -r %s/[!.]* .",dir_commit_jad);
        system(command);

}

else{
    char command[150];
    char dir_branch_hal[100];
    strcpy(dir_branch_hal,".git_branch_");
    strcat(dir_branch_hal,hal_bra);
    if(head_par==0){
    if (access(dir_branch_hal, F_OK) == 0){
    sprintf(command,"rm -r %s",dir_branch_hal);
        system(command);
    }
    sprintf(command,"mkdir %s",dir_branch_hal);
        system(command);
        sprintf(command,"mv [!.]* %s",dir_branch_hal);
        system(command);
    }
    else{
        sprintf(command,"rm [!.]* ");
        system(command);
    }
        char add_zaman_check[100];
        // strcpy(add_zaman_check,dir_branch_hal);
        // strcat(add_zaman_check,"/.zaman_check.txt");
// FILE* f= fopen(add_zaman_check,"w");
time_t rawtime;
   struct tm *info;
   char buffer[80];
   time(&rawtime);

   info = localtime( &rawtime );

   strftime(buffer,80,"%Y/%m/%d %X", info);
// fprintf(f,"%s",buffer);
// fclose(f);
        //rikhtan file haye bra jadid
        char dir_branch_jad[100];
    strcpy(dir_branch_jad,".git_branch_");
    strcat(dir_branch_jad,dastooorat[2]);
        sprintf(command,"cp -r %s/[!.]* .",dir_branch_jad);
        system(command);

        // strcpy(add_zaman_check,dir_branch_jad);
        // strcat(add_zaman_check,"/.zaman_check.txt");
// FILE* f1= fopen(add_zaman_check,"w");
// fprintf(f1,"%s",buffer);
// fclose(f1);
FILE* f1 =fopen(".gitman/.zaman_check.txt","w");
fprintf(f1,"%s",buffer);
fclose(f1);
FILE* branch_hal_file =fopen(".gitman/branch_hal.txt","w");
fprintf(branch_hal_file,"%s",dastooorat[2]);
fclose(branch_hal_file);
}
}

int check_taqir(){
    char hal_bra[100];
    int sh_akhcom;
FILE* branch_hal_file =fopen(".gitman/branch_hal.txt","r");
fscanf(branch_hal_file,"%s",hal_bra);
fclose(branch_hal_file);
FILE* file_akhcom= fopen(".gitman/sh_akhcom.txt","r");
fscanf(file_akhcom,"%d", &sh_akhcom);
fclose(file_akhcom);
FILE* cominfo_file = fopen(".gitman/commit_info.txt","r");
char alak[200];
char zaman_akhcom_bra[200];
char zamanha[200];
int sh_akhcom_bra=0;
for (int i = 0; i < sh_akhcom; i++)
{
    fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"time: \"%[^\"]\"\n",zamanha);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"branch: %s\n",alak);
// printf("%s",alak);
if (strcmp(alak,hal_bra)==0){
    sh_akhcom_bra=i+1;
strcpy(zaman_akhcom_bra,zamanha);
}
fgets(alak,199,cominfo_file);
}
if(sh_akhcom==0||sh_akhcom_bra==0)
strcpy(zaman_akhcom_bra,"2023/02/01 00:58:16");
// printf("%s\n",zaman_akhcom_bra);
// printf("%s\n",hal_bra);

DIR* branch_folder;
branch_folder= opendir(".");
if(branch_folder==NULL){
printf("???");
return 0 ;
}

struct dirent* fileha_branch;
while ((fileha_branch = readdir(branch_folder)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
        if (strncmp(fileha_branch->d_name, ".",1) == 0 || strcmp(fileha_branch->d_name, "..") == 0) 
            continue;
struct stat entryha;
stat(fileha_branch->d_name,&entryha);
// printf("%s  ",fileha_branch->d_name);
//=====
// time_t rawtime;
   struct tm *info;
   char buffer[80];
//    time(&entryha.st_mtime);

   info = localtime( &entryha.st_mtime );
      strftime(buffer,80,"%Y/%m/%d %X", info);
//=====
// printf("%s\n",buffer);
int a=zoodtaryab(buffer,zaman_akhcom_bra);
FILE* f1;
char zaman_checkout[100];
f1 =fopen(".gitman/.zaman_check.txt","r");
if(f1!=NULL){
fgets(zaman_checkout,99,f1);
fclose(f1);
if(zoodtaryab(buffer,zaman_checkout)==3)
a=2;
}
// printf("%s  %s   %s", buffer,zaman_checkout,zaman_akhcom_bra);
if (a==1)
return 0;
DIR* dirdakhel= opendir(fileha_branch->d_name);
if(dirdakhel==NULL)
continue;
struct dirent* fileha_branch_dakhel;
while ((fileha_branch_dakhel = readdir(dirdakhel)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
        if (strncmp(fileha_branch_dakhel->d_name, ".",1) == 0 || strcmp(fileha_branch_dakhel->d_name, "..") == 0) 
            continue;
struct stat entryha1;
char add[100];
strcpy(add,fileha_branch->d_name);
strcat(add,"/");
strcat(add,fileha_branch_dakhel->d_name);
stat(add,&entryha1);
// printf("%s  ",fileha_branch_dakhel->d_name);
//=================================
  struct tm *info;
   char buffer[80];
//    time(&entryha1.st_mtime);
   info = localtime( &entryha1.st_mtime );
      strftime(buffer,80,"%Y/%m/%d %X", info);
//=================================
// printf("%s\n",buffer);
int a=zoodtaryab(buffer,zaman_akhcom_bra);
FILE* f1;
char zaman_checkout[100];
f1 =fopen(".gitman/.zaman_check.txt","r");
if(f1!=NULL){
fgets(zaman_checkout,99,f1);
fclose(f1);
if(zoodtaryab(buffer,zaman_checkout)==3)
a=2;
}
if (a==1)
return 0;

}
    }
    return 1;
}
//tahcheckout====================================================================
//status==================================================================
void status(char** dastoorat,int tedad_kalame){
    char *addres5 = dotGitYab();
            if (strcmp(addres5, "?") == 0){
            printf("fatal: not in a gitman directory\n");
            return;
        }
    system("mv .gitman/addha.txt .gitman/addha1.txt");
    system("mv .gitman/staged .gitman/staged1");
    char** aldastoorat;
    aldastoorat=malloc(100*sizeof(int*));
    for (int i = 0; i < 100; i++)
    aldastoorat[i]=malloc(100);
    strcpy(aldastoorat[2],"*");
system("mkdir .gitman/staged");
    add(aldastoorat,3);
DIR* branch_folder;
branch_folder= opendir(".gitman/staged");
if(branch_folder==NULL){
printf("???");
return  ;
}

 char hal_bra[100];
    int sh_akhcom;
FILE* branch_hal_file =fopen(".gitman/branch_hal.txt","r");
fscanf(branch_hal_file,"%s",hal_bra);
fclose(branch_hal_file);
FILE* file_akhcom= fopen(".gitman/sh_akhcom.txt","r");
fscanf(file_akhcom,"%d", &sh_akhcom);
fclose(file_akhcom);
FILE* cominfo_file = fopen(".gitman/commit_info.txt","r");
char alak[200];
char zaman_akhcom_bra[200];
char zamanha[200];
int sh_akhcom_bra=0;
for (int i = 0; i < sh_akhcom; i++)
{
    fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"time: \"%[^\"]\"\n",zamanha);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fgets(alak,199,cominfo_file);
fscanf(cominfo_file,"branch: %s\n",alak);
// printf("%s",alak);
if (strcmp(alak,hal_bra)==0){
    sh_akhcom_bra=i+1;
strcpy(zaman_akhcom_bra,zamanha);
}
fgets(alak,199,cominfo_file);
}
if(sh_akhcom==0||sh_akhcom_bra==0)
strcpy(zaman_akhcom_bra,"2023/02/01 00:58:16");

struct dirent* fileha_branch;
while ((fileha_branch = readdir(branch_folder)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
        if (strncmp(fileha_branch->d_name, ".",1) == 0 || strcmp(fileha_branch->d_name, "..") == 0) 
            continue;
            if(access(fileha_branch->d_name,F_OK)!=0)
            continue;
struct stat entryha;
stat(fileha_branch->d_name,&entryha);
//=====
// time_t rawtime;
   struct tm *info;
   char buffer[80];
//    time(&entryha.st_mtime);
   info = localtime( &entryha.st_mtime );
      strftime(buffer,80,"%Y/%m/%d %X", info);
int a=zoodtaryab(buffer,zaman_akhcom_bra);
      if(a==2)   
      continue;
printf("%s  ",fileha_branch->d_name);
    char nextLine;
  int l=0;
  char c;
char addresaddha[100];
strcpy(addresaddha,".gitman/addha1.txt");
    char addha[100];
FILE* addhaFile=fopen(addresaddha,"r");
    int parcham=0;
    do
    {
        fscanf(addhaFile,"%s",addha);
        c=fgetc(addhaFile);
        if (strcmp(addha,fileha_branch->d_name)==0)
        {
            printf("+");
            parcham=1;
            break;
        }
        
        
    } while (c=='\n');
    if (parcham==0)
    printf("-");
    
    rewind(addhaFile);
    // time_t rawtime;
   struct tm *info1;
   char buffer1[80];
//    time(&entryha.st_mtime);

   info1 = localtime( &entryha.st_ctime );
      strftime(buffer1,80,"%Y/%m/%d %X", info1);
 a=zoodtaryab(buffer1,zaman_akhcom_bra);
 //  check add
 char add_file_incom[500];
 sprintf(add_file_incom,".gitman/commitha/commit%d/%s",sh_akhcom_bra,fileha_branch->d_name);
      if(access(add_file_incom,F_OK)!=0){
      printf("A\n");
      }
      else
      printf("M\n");
    // printf("%s   %s\n",buffer,buffer1);

}
//check delete
char add_commit_folder[100];
sprintf(add_commit_folder,".gitman/commitha/commit%d",sh_akhcom_bra);
DIR* commit_folder;
commit_folder= opendir(add_commit_folder);
struct dirent* fileha_commit;
while ((fileha_commit = readdir(commit_folder)) != NULL) {
        // strcpy(direntrry[j],entry->d_name);
         char add_file_incom[500];
 sprintf(add_file_incom,".gitman/staged/%s",fileha_commit->d_name);
      if(access(add_file_incom,F_OK)!=0){
        printf("%s  ",fileha_commit->d_name);
      }
      else
      continue;
        if (strncmp(fileha_commit->d_name, ".",1) == 0 || strcmp(fileha_commit->d_name, "..") == 0) 
            continue;
struct stat entryha_commit;
stat(fileha_commit->d_name,&entryha_commit);

    char nextLine;
  int l=0;
  char c;
char addresaddha[100];
strcpy(addresaddha,".gitman/addha1.txt");
    char addha[100];
FILE* addhaFile=fopen(addresaddha,"r");
    int parcham=0;
    do
    {
        fscanf(addhaFile,"%s",addha);
        c=fgetc(addhaFile);
        if (strcmp(addha,fileha_commit->d_name)==0)
        {
            printf("+");
            parcham=1;
            break;
        }
        
        
    } while (c=='\n');
    if (parcham==0)
    printf("-");
    
    rewind(addhaFile);

      printf("D\n");


}
//======================
system("rm -r .gitman/staged");
system("rm -r .gitman/addha.txt");
  system("mv .gitman/addha1.txt .gitman/addha.txt ");
    system("mv .gitman/staged1 .gitman/staged ");
}
//tahstatus==================================================================
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
 int configyab(char name[30],char email[30]){
char addres_conf[100];
strcpy(addres_conf,dotGitYab());
strcat(addres_conf,"/config.txt");
FILE* config_file = fopen(addres_conf,"r");
char c=fgetc(config_file);
if(c=='#'||config_file==NULL)
strcpy(addres_conf,"/mnt/f/my daneshgah/proje/global/name.txt");
fclose(config_file);
config_file =fopen(addres_conf,"r");
c= fgetc(config_file);
if(c=='#'||config_file==NULL)
return 0;
rewind(config_file);
fscanf(config_file, "name:%s\nemail:%s\n", name, email);
return 1;
}

int wildkart(char* dastoor2,int tedWildcart,char direntrry[20][20],int j,int shdorosta[20]){
    
    char tekeha[tedWildcart+1][10];
    int k =0;
    int o=0;
    char zapas[20];
    strcpy(zapas,dastoor2);
    if (strcmp(dastoor2,"*")==0)
    {
        for (int i = 0; i < j; i++)
            shdorosta[i]=i;
        
        return j;
    }
    
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
   else if (strcmp("add", dastoorat[1]) == 0)
    add(dastoorat, tedad_kalame);
   else if (strcmp("reset", dastoorat[1]) == 0)
    reset(dastoorat, tedad_kalame);
   else if (strcmp("reset", dastoorat[1]) == 0)
    reset(dastoorat, tedad_kalame);
    else if (strcmp("status", dastoorat[1]) == 0)
    status(dastoorat, tedad_kalame);
    else if (strcmp("commit", dastoorat[1]) == 0)
    commit(dastoorat, tedad_kalame);
    else if (strcmp("set", dastoorat[1]) == 0)
    set(dastoorat, tedad_kalame);
    else if (strcmp("replace", dastoorat[1]) == 0)
    replace(dastoorat, tedad_kalame,1);
    else if (strcmp("remove", dastoorat[1]) == 0)
    replace(dastoorat, tedad_kalame,0);
    else if (strcmp("log", dastoorat[1]) == 0)
    logcom(dastoorat, tedad_kalame);
    else if (strcmp("branch", dastoorat[1]) == 0)
    branch(dastoorat, tedad_kalame);
    else if (strcmp("checkout", dastoorat[1]) == 0)
    checkout(dastoorat, tedad_kalame);
    return 0;
}