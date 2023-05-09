#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>
#include <stdlib.h>

void handler()
{
  //char num[]={"child process was terminated\n" };
   FILE *fptr;

   fptr = fopen("logfile.txt","a");
   fprintf(fptr, "child process was terminated\n");
   fclose(fptr);
}

void readc(char arr[],char cmd[],char *par[])
{ while(1){
    char *found;
    char *sep[100];
    int i=0 ;
    printf(">>");

        gets(arr);

    //found = malloc(100*sizeof(char));
    found = strtok(arr," ");

    while(found)
    {
        //sep[i]=malloc(100*sizeof(char));
        sep[i++]=strdup(found);
        found = strtok(NULL," ");
    }
    strcpy(cmd,sep[0]);

    for(int j=0 ; j<i; j++)
    {
        par[j]=sep[j];
        par[i]= NULL;
    }
if(strcmp("&",par[i-1])==0){

par[i-1]=NULL;
par[i]="&";
}
signal(SIGCHLD, handler);
pid_t pid = fork();
        if(pid!=0)
        {

         if(par[i]==NULL){
            waitpid(pid,NULL,0);
            }
        }
        else
        {
             if (execvp(cmd, par) < 0&&strcmp(cmd,"exit")!=0) {
            printf("\nCould not execute command..");
        }
        exit(0);
        }
        if(strcmp(cmd,"exit")==0)
        {
            break;
            break;

        }

}
}



int main()
{
    char arr[1000],cmd[1000],*par[100];

    printf("####################### welcome in my simpleshell ###################\n");
    readc(arr,cmd,par);
    return 0;
}