#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

#define EVENT_SIZE      (sizeof(struct inotify_event))
#define EVENT_BUF_LEN   (1024 * (EVENT_SIZE + 16))


int main(int argc, char *argv[])
{
    FILE *fp;
    int InID;
    int watchDesc;
    int len;
    char buf[EVENT_BUF_LEN];
    struct inotify_event *ev = (struct inotify_event *)buf;

    // Receive inotify ID for this instance
    InID = inotify_init();

    watchDesc = inotify_add_watch(InID, (const char*)argv[1], IN_CREATE);
    if (watchDesc < 0)
    {
        printf("Error adding watch!\n\r");
        close(InID);        // close watch
        return 0;
    }

    printf("Start Monitoring...\n\r");
    len = read(InID, buf, EVENT_BUF_LEN);

    if (len < 0)
    {
        // In case of error ensure correct returning from the program
        printf("Error in reading. Exit!\n\r");
        inotify_rm_watch(InID, watchDesc);
        close(InID);
        return 0;
    }

    if (ev->mask & IN_CREATE)
    {
        printf("File is created in %s\n\r", argv[1]);
    }
    else
    {
        printf("Wrong detection prcedure. Exit\n\r");
    }

    
    inotify_rm_watch(InID, watchDesc);
    close(InID);
    return 0;
}
