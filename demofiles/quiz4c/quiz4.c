//quiz4.c

//this program uses the linux cp command to copy a file

#include <stdio.h>
#include <stdlib.h>


int main() 
{
    //create file "copy_me!.txt"
    FILE *file = fopen("copy_me!.txt", "w"); 

    //use the system command to copy the file
    int result = system("cp copy_me!.txt copy_me_copy.txt");

    //print the result of the system command
    if (result == 0) {
        printf("File copied successfully.\n");
    } else {
        printf("Error copying file.\n");
    }

    return 0;
}