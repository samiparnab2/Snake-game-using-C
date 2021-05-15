#include<stdio.h>
#include<stdlib.h>
#include"snake.c"
void main()
{
    int gd =DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int maxx=getmaxx(),maxy=getmaxy(),radius=5,length=3,incx,incy;
    char ch;
    struct snake_body_parts *head;
    head=create_default_snake(50,50,radius,length);
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