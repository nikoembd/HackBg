#include <stdio.h>


char buf[20];


int main(int argc, char *argv[])
{
    FILE *fp;

    fp = fopen(argv[1], "w");
    if (NULL == fp)
    {
        printf("Error!\n\r");
        return 0;
    }

    printf("Enter word: \n\r");
    scanf("%s", buf);

    fprintf(fp, "%s", buf);
    close(fp);

    return 0;    
}
