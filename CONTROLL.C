#include <stdio.h>
// #include<conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <dos.h>
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

unsigned long get_highest_score();
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

struct snake_body_parts *increase_len(struct snake_body_parts *head, int inx, int iny)
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
	len--;
	while (len--)
	{
		tmp->next = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
		tmp->next->x = tmp->x - (2 * radius);
		tmp->next->y = tmp->y;
		tmp->next->next = NULL;
		tmp = tmp->next;
	}

	return head;
}

int if_touch_itself(struct snake_body_parts *head)
{
	struct snake_body_parts *tmp;
	tmp = head->next;
	while (tmp != NULL)
	{
		if (head->x == tmp->x && head->y == tmp->y)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////

void game_over_anim(struct snake_body_parts *head, int radius, unsigned long score)
{
	int x = 7, difficulty;
	FILE *f;
	char ch;
	sound(500);
	delay(200);
	sound(200);
	delay(100);
	nosound();
	settextstyle(3, 0, 5);
	while (x--)
	{
		if (x % 2 == 0)
			setcolor(WHITE);
		else
			setcolor(BLACK);
		draw_snake(head, radius);
		outtextxy(210, 20, "GAME OVER");
		delay(300);
	}
	if (get_highest_score() < score)
	{
		difficulty = get_difficulty();
		f = fopen("GAMEDATA", "w");
		fprintf(f, "%u\n", score);
		fprintf(f, "%d\n", difficulty);
		fclose(f);
		cleardevice();
		settextstyle(3, 0, 5);
		outtextxy(30, 200, "===NEW HIGHEST SCORE===");
		settextstyle(0, 0, 1);
		outtextxy(250, 450, "PRESS F TO GO BACK");
		do
		{
			ch = getch();
		} while (ch != 'f' && ch != 'F');
	}
	settextstyle(0, 0, 1);
}

void save_game_data(struct snake_body_parts *head, struct normal_food *nf, struct bonus_food *bf, unsigned long score, int level, int face_dir)
{
	FILE *f;
	f = fopen("CONTINUE", "w+");
	fprintf(f, "%u\n", score);
	fprintf(f, "%d\n", level);
	fprintf(f, "%d\n", face_dir);
	fprintf(f, "%d %d %d\n", nf->radius, nf->x, nf->y);
	fprintf(f, "%d %d %d %d %d\n", bf->radius[0], bf->radius[1], bf->time, bf->x, bf->y);
	while (head != NULL)
	{
		fprintf(f, "%d %d\n", head->x, head->y);
		head = head->next;
	}
	fclose(f);
}

int read_game_data(struct snake_body_parts *head, struct normal_food *nf, struct bonus_food *bf, unsigned long *score, int *level, int *face_dir)
{
	FILE *f;
	struct snake_body_parts *tmp;
	int x, y;
	f = fopen("CONTINUE", "r+");
	fscanf(f, "%u", score);
	fscanf(f, "%d", level);
	fscanf(f, "%d", face_dir);
	fscanf(f, "%d %d %d", &(nf->radius), &(nf->x), &(nf->y));
	fscanf(f, "%d %d %d %d %d", &(bf->radius[0]), &(bf->radius[1]), &(bf->time), &(bf->x), &(bf->y));
	fscanf(f, "%d %d", &(head->x), &(head->y));
	head->next = NULL;
	tmp = head;
	while (fscanf(f, "%d %d", &x, &y) != EOF)
	{
		tmp->next = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
		tmp = tmp->next;
		tmp->x = x;
		tmp->y = y;
		tmp->next = NULL;
	}
	fclose(f);
	system("del CONTINUE");
	return 1;
}

int if_continue()
{
	FILE *f;
	int x;
	f = fopen("CONTINUE", "r");
	if (f == NULL)
		return 0;
	fclose(f);
	return 1;
}
void show_highestscore()
{
	unsigned long h_score;
	char score_text[40], ch;
	h_score = get_highest_score();
	cleardevice();
	settextstyle(3, 0, 5);
	outtextxy(85, 100, "===HIGHEST SCORE===");
	sprintf(score_text, "%u", h_score);
	outtextxy(100, 160, score_text);
	settextstyle(0, 0, 1);
	outtextxy(250, 450, "PRESS F TO GO BACK");
	do
	{
		ch = getch();
	} while (ch != 'f' && ch != 'F');
}

void change_difficulty()
{
	int difficulty = 8, lower_d, upper_d;
	char diff_text[10], ch;
	unsigned long dummy;
	FILE *f;
	lower_d = 1;
	upper_d = 10;
	dummy = get_highest_score();
	difficulty = get_difficulty();
	cleardevice();

	outtextxy(250, 435, "HIGHER:W   LOWER:S");
	outtextxy(250, 450, "PRESS F TO GO BACK");
	settextstyle(3, 0, 5);
	outtextxy(130, 100, "===DIFFICULTY===");

	while (1)
	{
		sprintf(diff_text, "%d", difficulty);
		outtextxy(100, 160, diff_text);
		do
		{
			ch = getch();
		} while (ch != 'w' && ch != 's' && ch != 'f' && ch != 'W' && ch != 'S' && ch != 'F');
		if (ch == 'f' || ch == 'F')
			break;
		else if (ch == 'w' || ch == 'W')
		{
			setcolor(BLACK);
			outtextxy(100, 160, diff_text);
			difficulty++;
			if (difficulty > upper_d)
				difficulty = lower_d;
			setcolor(WHITE);
		}
		else if (ch == 's' || ch == 'S')
		{
			setcolor(BLACK);
			outtextxy(100, 160, diff_text);
			difficulty--;
			if (difficulty < lower_d)
				difficulty = upper_d;
			setcolor(WHITE);
		}
	}
	f = fopen("GAMEDATA", "w");
	fprintf(f, "%u\n", dummy);
	fprintf(f, "%d\n", difficulty);
	fclose(f);
	settextstyle(0, 0, 1);
}
int get_difficulty()
{
	FILE *f;
	unsigned long dummy;
	int difficulty;
	difficulty = 8;
	dummy = 1;
	f = fopen("GAMEDATA", "r");
	if (f != NULL)
	{
		fscanf(f, "%u", &dummy);
		fscanf(f, "%d", &difficulty);
	}
	else
	{
		f = fopen("GAMEDATA", "w");
		fprintf(f, "%u\n", dummy);
		fprintf(f, "%d\n", difficulty);
	}
	fclose(f);
	return difficulty;
}

unsigned long get_highest_score()
{
	FILE *f;
	unsigned long score = 1;
	f = fopen("GAMEDATA", "r");
	if (f != NULL)
	{
		fscanf(f, "%u", &score);
		fclose(f);
	}
	return score;
}
//////////////////////////////////////////////////////////////////////////////////////

int play_game(int new_game, int difficulty)
{
	FILE *f;
	int radius = 5, speed, length = 3, incx, incy, maxx, maxy, level, face_dir;
	unsigned long score;
	char ch, score_text[40];
	struct board b;
	struct snake_body_parts *head;
	struct normal_food *nf;
	struct bonus_food *bf;
	maxx = getmaxx();
	maxy = getmaxy();
	b.startx = (maxx / 2) - 200;
	b.starty = 70;
	b.lenx = 400;
	b.leny = 400;
	b.endx = b.startx + b.lenx;
	b.endy = b.starty + b.leny;
	speed = (11 - difficulty) * 100;
	srand(time(0));
	if (new_game == 1)
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
		score = 0;
		level = 1;
	}
	else if (new_game == 0)
	{
		nf = (struct normal_food *)malloc(sizeof(struct normal_food));
		bf = (struct bonus_food *)malloc(sizeof(struct bonus_food));
		head = (struct snake_body_parts *)malloc(sizeof(struct snake_body_parts));
		read_game_data(head, nf, bf, &score, &level, &face_dir);
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
		nosound();
		rectangle(b.startx, b.starty, b.endx, b.endy);
		if (kbhit())
		{
			ch = getche();
			if ((ch == 'w' || ch == 'W') && incy != 10)
			{
				incy = -10;
				incx = 0;
				face_dir = 0;
			}
			else if ((ch == 'a' || ch == 'A') && incx != 10)
			{
				incx = -10;
				incy = 0;
				face_dir = 1;
			}
			else if ((ch == 's' || ch == 'S') && incy != -10)
			{
				incy = 10;
				incx = 0;
				face_dir = 2;
			}
			else if ((ch == 'd' || ch == 'D') && incx != -10)
			{
				incx = 10;
				incy = 0;
				face_dir = 3;
			}
			else if (ch == 27)
			{
				save_game_data(head, nf, bf, score, level, face_dir);
				break;
			}
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

			sound(1000);
			nf->x = ((rand() % 40) * 10) + b.startx + 5;
			nf->y = ((rand() % 40) * 10) + b.starty + 5;
			head = increase_len(head, incx, incy);
			bf->time++;
			score += 5;
			if (bf->time == 0)
				bf->time = 15;
		}
		if (bf->time > 0 && head->x == bf->x && head->y == bf->y)
		{
			sound(1000);
			head = increase_len(head, incx, incy);
			bf->x = ((rand() % 40) * 10) + b.startx + 5;
			bf->y = ((rand() % 40) * 10) + b.starty + 5;
			score += (bf->time * 2) + 5;
			bf->time = -10;
		}
		if (if_touch_itself(head))
		{
			game_over_anim(head, radius, score);
			break;
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
		sprintf(score_text, "score:- %u", score);
		outtextxy(10, 40, score_text);
		delay(speed);
	}
	return 1;
}
int main_menu()
{
	int i, lower_i, upper_i;
	char ch;
	lower_i = 1;
	upper_i = 4;
	cleardevice();
	settextstyle(4, 0, 8);
	outtextxy(120, 50, "SNAKE-N");
	settextstyle(3, 0, 3);
	if (if_continue())
	{
		outtextxy(120, 240, "CONTINUE");
		lower_i = 0;
	}
	outtextxy(120, 280, "NEW GAME");
	outtextxy(120, 320, "HIGHEST SCORE");
	outtextxy(120, 360, "DIFICULTY");
	outtextxy(120, 400, "QUIT");
	settextstyle(0, 0, 1);
	outtextxy(250, 435, "GO UP:W   GO DOWN:S");
	outtextxy(250, 450, "PRESS  F  TO SELECT");
	i = lower_i;
	while (1)
	{
		rectangle(100, 253 + (40 * i), 105, 258 + (40 * i));
		do
		{
			ch = getch();
		} while (ch != 'w' && ch != 's' && ch != 'f' && ch != 'W' && ch != 'S' && ch != 'F');
		if (ch == 'f' || ch == 'F')
			return i;
		setcolor(BLACK);
		rectangle(100, 253 + (40 * i), 105, 258 + (40 * i));
		setcolor(WHITE);
		if (ch == 'w' || ch == 'W')
		{
			i--;
			if (i < lower_i)
				i = upper_i;
		}
		else if (ch == 's' || ch == 'S')
		{
			i++;
			if (i > upper_i)
				i = lower_i;
		}
	}
}
void main()
{
	int gd = DETECT, gm, choice;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	while (1)
	{
		choice = main_menu();
		if (choice == 4)
			break;
		else if (choice == 0)
			play_game(0, get_difficulty());
		else if (choice == 1)
			play_game(1, get_difficulty());
		else if (choice == 2)
			show_highestscore();
		else if (choice == 3)
			change_difficulty();
	}
	closegraph();
}
