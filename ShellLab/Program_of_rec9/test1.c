#include"stdio.h"
#include"unistd.h"
int main(int argc, char** argv)
{
    char* args[3];
    args[0]="/bin/echo";
    args[1]="Hi 18213!";
    args[2]=NULL;
    execv(args[0],args);
    printf("Hi 15213!\n");
    exit(0);
}