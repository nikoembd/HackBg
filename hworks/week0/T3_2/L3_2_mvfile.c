#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
    FILE *fsr = fopen(argv[1], "r");
    FILE *fde;
    char *name, *c;
    int cntr=0, sz, del=0;
    size_t len=0;
    ssize_t resp=1;

    if (NULL == fsr)
    {
        printf("Error openning files!\n\r");
        // Just in case - close files
        fclose(fsr);
        return 0;
    }

    // Get the initial filename and assign it for the new file
    // in the new folder
    while ( *(argv[1]+cntr) != '\0')
    {
        cntr++;     // find the last sign
    }
    sz = cntr;

    while ( *(argv[1]+cntr) != '/')
    {
        cntr--;
    }
    sz -= cntr-1;
    c = ++cntr + argv[1];       // get the adress of the first letter of the file's name

    // Allocate memory for string to save the new path
    name = malloc(strlen(argv[2]) + sz);
    sprintf(name, "%s%s", argv[2], c);
    
    // Try create the new file
    fde = fopen(name, "w");
    if (NULL == fde)
    {
        printf("Error computing dest file name!\n\r");
        free(name);
        fclose(fsr);
        return 0;
    }
    printf("Writing to destination file...\n\r");

    do
    {
        resp =  getline(&c, &len, fsr);

        if (resp != -1)
        {
            fprintf(fde, "%s", c);
        }
        else
            break;

    }
    while (resp != -1);

    printf("Finishing...\n\r");
    free(name);
    free(c);
    fclose(fsr);
    fclose(fde);
    
    del = unlink(argv[1]);    // delete the file
    if (del == 0)
    {
        printf("Successful!\n\rEnd\n\r");
    }
    else
    {
        printf("ERROR-Src file not deleted.\n\r");
    }


    return 0;
}
