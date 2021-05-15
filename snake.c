#include<stdio.h>
#include<graphics.h>

struct  snake_body_parts
{
    int x,y;
    struct snake_body_parts *next;
};

void move_snake_body(struct snake_body_parts *head)
{
    if((head->next)->next!=NULL)
        move_snake_body(head->next);
    
    (head->next)->x=head->x;
    (head->next)->y=head->y;

}
 
void move_snake_head(struct snake_body_parts *head,int x,int y)
{
    head->x=head->x+x;
    head->y=head->y+y;
}

void increase_len(struct snake_body_parts *head,int radius)
{
    while (head->next!=NULL)
        head=head->next;
    head->next=(struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
    head->next->x=head->x+(2*radius);
    head->next->y=head->y;
    head->next->next=NULL;
}

void draw_snake(struct snake_body_parts *head,int radius)
{
    while(head!=NULL)
    {
        circle(head->x,head->y,radius);
        head=head->next;
    }
}

struct snake_body_parts * create_default_snake(int x,int y,int radius,int len)
{
    struct snake_body_parts *head,*tmp;
    head=(struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
    tmp=head;
    head->x=x;
    head->y=y;
    while(--len)
    {
        tmp->next=(struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
        tmp->next->x=tmp->x+(2*radius);
        tmp->next->y=tmp->y;
        tmp->next->next=NULL;
        tmp=tmp->next;
    }
   
    return head;
}