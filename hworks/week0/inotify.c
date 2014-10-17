#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

#define EVENT_SIZE      (sizeof(struct inotify_event))
#define EVENT_BUF_LEN   (1024 * (EVENT_SIZE + 16))



int main()
{
    int iid;
    int resp;
    int dummy;
    char buf[EVENT_BUF_LEN];
    struct inotify_event *ev = (struct inotify_event *)buf;
    
    
    iid = inotify_init();
    if (iid < 0)
    {
        printf("\n\rError init");
        return 0;
    } 

    resp = inotify_add_watch(iid, "./src", IN_CREATE);
    if (resp < 0)
    {
        printf("\n\rError adding watch");
        return 0;
    }

    printf("\n\rStart Monitoring...");
    fflush(stdout);
    dummy = read(iid, buf, sizeof(buf));
    printf("\n\rProcessing:");

    if (dummy < 0)
    {
        printf("\n\rError reading!");
    }

    if (ev->mask & IN_CREATE)
    {
        printf("\n\rCaptured!");
    }
    else
    {
        printf("\n\rNot Captured!");
    }


    printf("\n\r");
    inotify_rm_watch(iid, resp);
    close(iid);
    return 0;
}


