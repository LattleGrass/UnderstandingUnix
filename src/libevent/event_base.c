/*
 * =====================================================================================
 *
 *       Filename:  event_base.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-05-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */


// gcc event_base.c -l event -o eb
#include <event2/event-config.h>
#include <event2/event.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main() {
        //  print supported methods
        int i;
        const char **methods = event_get_supported_methods();
        printf("Staring Libevent %s. Available methods are: \n",
               event_get_version());
        for (i = 0; methods[i] != NULL; i++)
                printf("    %s \n", methods[i]);

        struct event_base *base;
        enum event_method_feature f;

        base = event_base_new();

        if (!base) {
                puts("Couldn't get an event_base!");
        } else {
                printf("Using Libevent with backend method %s \n",
                       event_base_get_method(base));
                f = event_base_get_features(base);
                if ((f & EV_FEATURE_ET))
                        printf("  Edge-triggered events are supported.\n");
                if ((f & EV_FEATURE_O1))
                        printf("  O(1) event notification is supported.\n");
                if ((f & EV_FEATURE_FDS))
                        printf("  All FD types are supported.");
                puts("");
        }

        return 0;
}
