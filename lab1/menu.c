
/**************************************************************************************************/
/* Copyright (C) mc2lab.com, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  Jiangwenzhong                                                        */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/12                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Jiangwenzhong, 2014/09/12
 *
 */


#include <stdio.h>
#include <stdlib.h>

int help();
int ex();

#define CMD_MAX_LEN 128
#define DESC_LEN    1024

/* data struct and its operations */

typedef struct DataNode
{
    char * cmd;
    char * desc;
    int (* handler)();
    struct DataNode * next;
}tDataNode;

/* find a cmd in the linklist */
tDataNode * FindCmd(tDataNode * head, char * cmd)
{
    tDataNode * p = head;
    while(p != NULL)
    {
        if(!strcmp(p->cmd, cmd))
        {
            break;
        }
        p = p->next;
    }
    return p;
}

/* show all cmds in the linklist */
int ShowAllCmd(tDataNode * head)
{
    tDataNode * p = head;
    printf("Menu List:\n");
    while(p != NULL)
    {
        printf("%s - %s\n", p->cmd, p->desc);
        p = p->next;
    }
    return 0;
}

/* menu program */

static tDataNode head[] =
{
    {"help", "this is help cmd!", help, &head[1]},
    {"version", "menu program version 1.0", NULL, &head[2]},
    {"exit", "this is exit cmd!", ex, NULL}
};

main()
{
    int i = 0;
    printf("\n** this is a menu program **\n");
    while(!i)
    {
        char cmd[CMD_MAX_LEN];
        printf("\ninput a cmd > ");
        scanf("%s", cmd);
        tDataNode * p = FindCmd(head, cmd);
        if(p == NULL)
        {
            printf("\nThis is a wrong cmd!\n");
            continue;
        }
        printf("\n%s - %s\n\n", p->cmd, p->desc);
        if(p->handler != NULL)
        {
            i = p->handler();
        }
    }
}

int help()
{
    ShowAllCmd(head);
    return 0;
}

int ex()
{
    printf("exit successfully!\n");
    return 1;
}
