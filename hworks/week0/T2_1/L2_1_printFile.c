#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[])
{
    ssize_t flag = 1;
    char *buf = NULL;
    size_t len = 0;
    FILE *fp = fopen(argv[1], "r");

    if (NULL == fp)
    {
        printf("Error openning the file!\n\r");
        return 0;
    }

    while (flag != -1)
    {
        flag = getline(&buf, &len, fp);

        if (flag != -1)
            printf("%s", buf);
        else 
            break; 
    }
    
    free(buf);
    fclose(fp);
    return 0;
}
