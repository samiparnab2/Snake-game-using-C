#include <stdio.h>
// #include<conio.h>
#include <stdlib.h>
#include <graphics.h>

//////////////////////////////////////////////////////////////////////////////////////
struct snake_body_parts
{
	int x, y;
	struct snake_body_parts *next;
};

struct board
{
	int startx, starty, lenx, leny, endx, endy;
};

struct normal_food
{
	int x, y, radius;
};

struct bonus_food
{
	int x, y, time, radius[2];
};

void move_snake_body(struct snake_body_parts *head)
{
	if ((head->next)->next != NULL)
		move_snake_body(head->next);

	(head->next)->x = head->x;
	(head->next)->y = head->y;
}

void move_snake_head(struct snake_body_parts *head, int x, int y)
{
	head->x = head->x + x;
	head->y = head->y + y;
}

struct snake_body_parts *increase_len(struct snake_body_parts *head, int radius, int inx, int iny)
{
	struct snake_body_parts *tmp;
	tmp = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
	tmp->x = head->x;
	tmp->y = head->y;
	tmp->next = head;
	head = tmp;
	move_snake_head(head, inx, iny);
	return head;
}

void draw_snake(struct snake_body_parts *head, int radius)
{
	while (head != NULL)
	{
		circle(head->x, head->y, radius);
		head = head->next;
	}
}

struct snake_body_parts *create_default_snake(int x, int y, int radius, int len)
{
	struct snake_body_parts *head, *tmp;
	head = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
	tmp = head;
	head->x = x;
	head->y = y;
	while (--len)
	{
		tmp->next = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
		tmp->next->x = tmp->x + (2 * radius);
		tmp->next->y = tmp->y;
		tmp->next->next = NULL;
		tmp = tmp->next;
	}

	return head;
}
//////////////////////////////////////////////////////////////////////////////////////

int play_game(struct snake_body_parts *head, struct normal_food *nf, struct bonus_food *bf, int score, int level, int face_dir)
{
	int radius = 5, length = 3, incx, incy, delta, maxx, maxy;
	char ch;
	struct board b;
	maxx = getmaxx();
	maxy = getmaxy();
	delta = radius * 2;
	b.startx = (maxx / 2) - 200;
	b.starty = 70;
	b.lenx = 400;
	b.leny = 400;
	b.endx = b.startx + b.lenx;
	b.endy = b.starty + b.leny;
	srand(time(0));
	if (head == NULL)
	{
		head = create_default_snake(b.startx + 25, b.starty + 5, radius, length);
		nf = (struct normal_food *)malloc(sizeof(struct normal_food));
		nf->radius = 2;
		nf->x = ((rand() % 40) * 10) + b.startx + 5;
		nf->y = ((rand() % 40) * 10) + b.starty + 5;
		bf = (struct bonus_food *)malloc(sizeof(struct bonus_food));
		bf->radius[0] = 5;
		bf->radius[1] = 3;
		bf->x = ((rand() % 40) * 10) + b.startx + 5;
		bf->y = ((rand() % 40) * 10) + b.starty + 5;
		bf->time = -10;
		face_dir = 3;
	}

	if (face_dir == 0)
	{
		incx = 0;
		incy = -10;
	}
	else if (face_dir == 1)
	{
		incx = -10;
		incy = 0;
	}
	else if (face_dir == 2)
	{
		incx = 0;
		incy = 10;
	}
	else if (face_dir == 3)
	{
		incx = 10;
		incy = 0;
	}

	while (1)
	{
		cleardevice();

		if (kbhit())
		{
			ch = getche();
			if (ch == 'w' && incy != 10)
			{
				incy = -10;
				incx = 0;
			}
			else if (ch == 'a' && incx != 10)
			{
				incx = -10;
				incy = 0;
			}
			else if (ch == 's' && incy != -10)
			{
				incy = 10;
				incx = 0;
			}
			else if (ch == 'd' && incx != -10)
			{
				incx = 10;
				incy = 0;
			}
			else if (ch == 27)
				break;
		}
		move_snake_body(head);
		move_snake_head(head, incx, incy);
		if (head->x >= b.endx)
		{
			head->x = b.startx + 5;
		}
		else if (head->x <= b.startx)
		{
			head->x = b.endx - 5;
		}
		else if (head->y >= b.endy)
		{
			head->y = b.starty + 5;
		}
		else if (head->y <= b.starty)
		{
			head->y = b.endy - 5;
		}
		if (head->x == nf->x && head->y == nf->y)
		{
			nf->x = ((rand() % 40) * 10) + b.startx + 5;
			nf->y = ((rand() % 40) * 10) + b.starty + 5;
			head = increase_len(head, radius, incx, incy);
			bf->time++;
			if (bf->time == 0)
				bf->time = 15;
		}
		if (bf->time > 0 && head->x == bf->x && head->y == bf->y)
		{
			head = increase_len(head, radius, incx, incy);
			bf->x = ((rand() % 40) * 10) + b.startx + 5;
			bf->y = ((rand() % 40) * 10) + b.starty + 5;
			bf->time = -10;
		}
		draw_snake(head, radius);
		circle(nf->x, nf->y, nf->radius);
		if (bf->time > 0)
		{
			circle(bf->x, bf->y, bf->radius[bf->time % 2]);
			bf->time--;
			if (bf->time == 0)
			{
				bf->x = ((rand() % 40) * 10) + b.startx + 5;
				bf->y = ((rand() % 40) * 10) + b.starty + 5;
				bf->time = -10;
			}
		}
		rectangle(b.startx, b.starty, b.endx, b.endy);
		outtextxy(10, 40, "score:-");
		delay(300);
	}
	return 1;
}
void main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	play_game(NULL, NULL, NULL, 0, 1, -1);
	closegraph();
}
