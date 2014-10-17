#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[])
{
    FILE *fsr = fopen(argv[1], "r");
    FILE *fde = fopen(argv[2], "w");
    char *c;
    size_t len=0;
    ssize_t resp=1;

    if ( (NULL == fsr) || (NULL == fde) )
    {
        printf("Error openning files!\n\r");
        // Just in case - close files
        fclose(fsr);
        fclose(fde);
        return 0;
    }

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


    free(c);
    fclose(fsr);
    fclose(fde);
    return 0;
}
