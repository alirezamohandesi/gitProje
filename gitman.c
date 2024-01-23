#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void alias(char** dastoorat,int tedad_kalame);
char* dotGitYab();
void configor(char** dastoorat,int tedad_kalame){
    if ((strncmp("alias" , dastoorat[2],5)==0)||(strncmp("alias" , dastoorat[3],5)==0))
    {
        alias(dastoorat,tedad_kalame);
        return;
    }
    
if (strcmp("--global" , dastoorat[2])==0){
        FILE* hoviat; 
hoviat= fopen("/mnt/e/desktop/daneshgah/my daneshgah/proje/global/name.txt","r");
if(hoviat==NULL)
hoviat= fopen("/mnt/e/desktop/daneshgah/my daneshgah/proje/global/name.txt","w+");

    char name[30]="";
    char email[30]="";
    fscanf(hoviat,"name:%s\nemail:%s\n",name,email);
if (strcmp("user.name" , dastoorat[3])==0)
strcpy(name,dastoorat[4]);
if (strcmp("user.email" , dastoorat[3])==0)
strcpy(email,dastoorat[4]);
    fclose(hoviat);
    hoviat= fopen("/mnt/e/desktop/daneshgah/my daneshgah/proje/global/name.txt","w");
fprintf(hoviat,"name:%s\nemail:%s\n",name,email);
printf("%s\n%s",name,email);
fclose(hoviat);
}

if ((strcmp("user.name" , dastoorat[2])==0)||(strcmp("user.email" , dastoorat[2])==0)){
    char* addres=dotGitYab();
    if (strcmp(addres,"?")==0)
  return;
    
    strcat(addres,"/config.txt");
FILE* config =fopen(addres,"r");
if(config==NULL)
 config =fopen(addres,"w+");
if(config==NULL){
printf("fatal: not in a gitman directory\n");
return;
}
char name[30]="";
    char email[30]="";
    fscanf(config,"name:%s\nemail:%s\n",name,email);
if (strcmp("user.name" , dastoorat[2])==0)
strcpy(name,dastoorat[3]);
if (strcmp("user.email" , dastoorat[2])==0)
strcpy(email,dastoorat[3]);
    fclose(config);
    config= fopen(addres,"w");
fprintf(config,"name:%s\nemail:%s\n",name,email);
printf("%s\n%s",name,email);
fclose(config);
}
}

void alias(char** dastoorat,int tedad_kalame){
    if (strcmp(dastoorat[1],"config")!=0)
    {
printf("command not found");
return;
    }
    else if (strcmp(dastoorat[2],"--global")==0)
    {
       FILE* aliasgol= fopen("/mnt/e/desktop/daneshgah/my daneshgah/proje/global/alias.txt","a");
    //    aliaschap(dastoorat,tedad_kalame,1,aliasgol);
    }
    else  
    {
        char* addres=dotGitYab();
        strcat(addres,"/alias.txt");
       FILE* aliasngol=fopen(addres,"a");
    //    aliaschap(dastoorat,tedad_kalame,1,aliasngol);
    }


}
void init(char** dastoorat,int tedad_kalame){
system("mkdir .gitman");
FILE* avalesh = fopen(".gitman/config.txt","w");
fprintf(avalesh,"#");
}

char* dotGitYab(){
    char* addres =malloc(100);
    char dot2[100];
    strcpy(addres,".gitman");
    for (int i = 0; i < 10; i++)
    {
    strcpy(dot2,"../");
        if (access(addres,F_OK)==0)
            return addres;
        strcat(dot2,addres);
        strcpy(addres,dot2);
    }
    printf("fatal: not in a gitman directory\n");
    return "?";
}

int main(int tedad_kalame , char** dastoorat)
{
    if (strcmp("config" , dastoorat[1])==0)
    configor(dastoorat,tedad_kalame);
        if (strcmp("init" , dastoorat[1])==0)
    init(dastoorat,tedad_kalame);


	return 0;
}
