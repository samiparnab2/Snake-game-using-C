#include<stdio.h>
#include<stdlib.h>
#include"snake.c"
void main()
{
    int gd =DETECT, gm,maxx=getmaxx(),maxy=getmaxy(),radius,incx,incy;
    char ch;
    struct snake_body_parts *head;

    initgraph(&gd, &gm, NULL);
    head=create_default_snake(50,50,5,2);
    while(1)
    {
        if(kbhit())
        {
            ch=getch();
            if(ch=='w')
                incy=-10;
            else if(ch=='a')
                incx=-10;
            else if(ch=='s')
                incy=10;
            else if(ch=='d')
                incx=10;
            else if(ch==27)
                break;
        }
        move_snake_body(head);
        move_snake_head(head,incx,incy);
        
    }
    closegraph(); 
}