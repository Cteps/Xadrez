#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

int round();
void chess_piece();
void overlap_range(int x, int y, int type);
int get_coordenates_y(int y);
void overlap_range(int x, int y, int type);
int get_coordenates_y(int y);
int get_coordenates_x(int x);
int move_unit(int x, int y, int first_x, int first_y, int roundnum);
void ingame_interface_menu();

//dados que cada peça tem
typedef struct {
	char design;
	int x, y, type, first_move;
	int move_range[8][8];
}Piece;
//dados que cada player tem
typedef struct {
	Piece pieces[16];
	char name[50];
}Players;

int roundnum = 1;
char matriz[18][18];
int num1 = 49;
int num = 65;
int pp1 = 0;
int pp2 = 0;
Players players[2];
//Função para mudar o round
int round()
{
	if (roundnum == 1)
	{
		roundnum++;
	}
	else roundnum = 1;
}
//gerador das peças dos players
void start_game_randomizer()
{

	srand((unsigned)time(NULL));
	pp1 = rand() % 2;

	if (pp1 == 1)
	{
		pp2 = 0;
	}
	else pp2 = 1;
}
//Função para por as peças no campo com as informações da struct
void chess_piece()
{
	char s = 'e';
	int sx = 0;

	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			players[p].pieces[i].first_move = 1;

			if (i <= 7)
			{
				if (p == 0)          //PAWN
				{
					s = 'P';
					sx = 0;
				}
				else
				{
					s = 'p';
					sx = 5;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 65 + i;
				players[p].pieces[i].y = 2 + sx;
				players[p].pieces[i].type = 1;
			}
			else if (i == 8)
			{
				if (p == 0)           //ROOK
				{
					s = 'T';
					sx = 0;
				}
				if (p == 1)
				{
					s = 't';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 65;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 2;
			}
			else if (i == 9)
			{
				if (p == 0)           //ROOK
				{
					s = 'T';
					sx = 0;
				}
				if (p == 1)
				{
					s = 't';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 72;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 2;
			}
			else if (i == 10)
			{
				if (p == 0)           //KNIGHT
				{
					s = 'N';
					sx = 0;
				}
				if (p == 1)
				{
					s = 'n';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 66;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 3;
			}
			else if (i == 11)
			{
				if (p == 0)
				{
					s = 'N';           //KNIGHT
					sx = 0;
				}
				if (p == 1)
				{
					s = 'n';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 71;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 3;

			}
			else if (i == 12)
			{
				if (p == 0)
				{
					s = 'B';            //BISHOP
					sx = 0;
				}
				if (p == 1)
				{
					s = 'b';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 67;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 4;
			}
			else if (i == 13)
			{
				if (p == 0)             //BISHOP
				{
					s = 'B';
					sx = 0;
				}
				if (p == 1)
				{
					s = 'b';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 70;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 4;
			}
			else if (i == 14)
			{
				if (p == 0)            //KING
				{
					s = 'K';
					sx = 0;
				}
				if (p == 1)
				{
					s = 'k';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 68;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 5;
			}
			else if (i == 15)
			{
				if (p == 0)            //QUEEN
				{
					s = 'Q';
					sx = 0;
				}
				if (p == 1)
				{
					s = 'q';
					sx = 7;
				}
				players[p].pieces[i].design = s;
				players[p].pieces[i].x = 69;
				players[p].pieces[i].y = 1 + sx;
				players[p].pieces[i].type = 6;
			}
		}
	}
}
//função que atribui as coordenadas que cada peça pode dar
void overlap_range(int x, int y, int roundnum)
{
	int count[64];
	int num_piece = 0;
	int xte = 0, xtd = 0;
	int ytc = 0, ytb = 0;
	int j = 0;
	int type = 0;

	for (int i = 0; i < 64; i++)
	{
		count[i] = 0;
	}

	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (players[p].pieces[i].x == x && players[p].pieces[i].y == y)
			{
				num_piece = i;
				//peao
				if (players[p].pieces[i].type == 1)
				{
					if (players[p].pieces[i].first_move == 1)
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y + 1][x - 65] = 1;
							}
							if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y + 2][x - 65] = 1;
							}

							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 1] = 2;
							}
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 1] = 2;
							}
						}

						if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y - 1][x - 65] = 1;
							}
							if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y - 2][x - 65] = 1;
							}
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 2;
							}
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 1] = 2;
							}
						}

					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y + 1][x - 65] = 1;
							}
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 1] = 2;
							}
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 1] = 2;
							}
						}

						if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] == ' ')
							{
								players[p].pieces[i].move_range[y - 1][x - 65] = 1;
							}
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 2;
							}
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 1] = 2;
							}
						}
					}
				}
				//torre
				else if (players[p].pieces[i].type == 2)
				{
					ytb = 1;
					ytc = 1;
					xtd = 1;
					xte = 1;

					do {
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] == ' ')
						{
							players[p].pieces[i].move_range[y + (ytb)][x - 65] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] <= 122)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] <= 90)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65] = 2;
								}
							}
							ytb = 8;
						}
						ytb++;
					} while (ytb < 8);

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] == ' ')
						{
							players[p].pieces[i].move_range[y - (ytc)][x - 65] = 1;
						}
						else
						{

							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] <= 122)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] <= 90)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65] = 2;
								}
							}

							ytc = 8;
						}
						ytc++;

					} while (ytc < 8);

					do
					{
						if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y][x - 65 + xtd] = 1;
						}
						else
						{

							if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] <= 122)
							{
								players[p].pieces[i].move_range[y][x - 65 + xtd] = 2;
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y][x - 65 + xtd] = 2;
								}
							}

							xtd = 8;
						}
						xtd++;

					} while (xtd < 8);

					do
					{
						if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y][x - 64 - xte] = 1;
						}
						else
						{

							if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] <= 122)
							{
								players[p].pieces[i].move_range[y][x - 65 - xte] = 2;
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y][x - 65 - xte] = 2;
								}
							}

							xte = 8;
						}
						xte++;

					} while (xte < 8);
				}
				//knight
				else if (players[p].pieces[i].type == 3)
				{

					if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 2)] == ' ')
					{
						players[p].pieces[i].move_range[y + 1][x - 65 - 2] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 2)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 2)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 2] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 2)] >= 65 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 2)] <= 90)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 2] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 2)] == ' ')
					{
						players[p].pieces[i].move_range[y + 1][x - 65 + 2] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 2)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 2)] <= 122)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 2] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 2)] >= 65 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 2)] <= 90)
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 2] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 2)] == ' ')
					{
						players[p].pieces[i].move_range[y - 1][x - 65 - 2] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 2)] >= 97 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 2)] <= 122)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 2] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 2)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 2)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 2] = 2;
							}

						}
					}

					if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 2)] == ' ')
					{
						players[p].pieces[i].move_range[y - 1][x - 65 + 2] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 2)] >= 97 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 2)] <= 122)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 2] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 2)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 2)] <= 90)
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 2] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] == ' ')
					{
						players[p].pieces[i].move_range[y + 2][x - 65 - 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 2][x - 65 - 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] <= 90)
							{
								players[p].pieces[i].move_range[y + 2][x - 65 - 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x + 1)] == ' ')
					{
						players[p].pieces[i].move_range[y + 2][x - 65 + 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y + 2)][get_coordenates_x(x + 1)] <= 122)
							{
								players[p].pieces[i].move_range[y + 2][x - 65 + 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y + 2)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y + 2)][get_coordenates_x(x + 1)] <= 90)
							{
								players[p].pieces[i].move_range[y + 2][x - 65 + 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x - 1)] == ' ')
					{
						players[p].pieces[i].move_range[y - 2][x - 65 - 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y - 2)][get_coordenates_x(x - 1)] <= 122)
							{
								players[p].pieces[i].move_range[y - 2][x - 65 - 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y - 2)][get_coordenates_x(x - 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 2][x - 65 - 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x + 1)] == ' ')
					{
						players[p].pieces[i].move_range[y - 2][x - 65 + 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y - 2)][get_coordenates_x(x + 1)] <= 122)
							{
								players[p].pieces[i].move_range[y - 2][x - 65 + 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if (matriz[get_coordenates_y(y - 2)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y - 2)][get_coordenates_x(x + 1)] <= 90)
							{
								players[p].pieces[i].move_range[y - 2][x - 65 + 1] = 2;
							}
						}
					}
				}
				//bispo
				else if (players[p].pieces[i].type == 4)
				{
					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do {
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y + (ytb)][x - 65 + xtd] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] <= 122)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 + xtd] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 + xtd] = 2;
								}
							}
							ytb = 8;
							xtd = 8;
						}
						ytb++;
						xtd++;

					} while (ytb < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y - (ytc)][x - 65 + xtd] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] <= 122)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65 + xtd] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65 + xtd] = 2;
								}
							}
							ytc = 8;
							xtd = 8;
						}
						ytc++;
						xtd++;

					} while (ytc < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y - (ytc)][x - 65 - xte] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] <= 122)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65 - xte] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y - (ytc)][x - 65 - xte] = 2;
								}
							}
							xte = 8;
						}
						xte++;
						ytc++;
					} while (xte < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y + (ytb)][x - 65 - xte] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] <= 122)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 - xte] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 - xte] = 2;
								}
							}
							xte = 8;
							ytb = 8;
						}
						xte++;
						ytb++;

					} while (xte < 8);

				}
				//king
				else if (players[p].pieces[i].type == 5)
				{

					if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] == ' ')
					{
						players[p].pieces[i].move_range[y + 1][x - 65 + 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] <= 122))
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x + 1)] <= 90))
							{
								players[p].pieces[i].move_range[y + 1][x - 65 + 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] == ' ')
					{
						players[p].pieces[i].move_range[y + 1][x - 65 - 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] <= 122))
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x - 1)] <= 90))
							{
								players[p].pieces[i].move_range[y + 1][x - 65 - 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] == ' ')
					{
						players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] <= 122))
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x + 1)] <= 90))
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] == ' ')
					{
						players[p].pieces[i].move_range[y - 1][x - 65 - 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] <= 122))
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x - 1)] <= 90))
							{
								players[p].pieces[i].move_range[y - 1][x - 65 - 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] == ' ')
					{
						players[p].pieces[i].move_range[y + 1][x - 65] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] <= 122))
							{
								players[p].pieces[i].move_range[y + 1][x - 65] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y + 1)][get_coordenates_x(x)] <= 90))
							{
								players[p].pieces[i].move_range[y + 1][x - 65] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] == ' ')
					{
						players[p].pieces[i].move_range[y - 1][x - 65] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] <= 122))
							{
								players[p].pieces[i].move_range[y - 1][x - 65] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y - 1)][get_coordenates_x(x)] <= 90))
							{
								players[p].pieces[i].move_range[y - 1][x - 65] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y)][get_coordenates_x(x + 1)] == ' ')
					{
						players[p].pieces[i].move_range[y][x - 65 + 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y)][get_coordenates_x(x + 1)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x + 1)] <= 122))
							{
								players[p].pieces[i].move_range[y][x - 65 + 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y)][get_coordenates_x(x + 1)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x + 1)] <= 90))
							{
								players[p].pieces[i].move_range[y - 1][x - 65 + 1] = 2;
							}
						}
					}

					if (matriz[get_coordenates_y(y)][get_coordenates_x(x - 1)] == ' ')
					{
						players[p].pieces[i].move_range[y][x - 65 - 1] = 1;
					}
					else
					{
						if (roundnum == 1)
						{
							if ((matriz[get_coordenates_y(y)][get_coordenates_x(x - 1)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x - 1)] <= 122))
							{
								players[p].pieces[i].move_range[y][x - 65 - 1] = 2;
							}
						}
						else if (roundnum == 2)
						{
							if ((matriz[get_coordenates_y(y)][get_coordenates_x(x - 1)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x - 1)] <= 90))
							{
								players[p].pieces[i].move_range[y][x - 65 - 1] = 2;
							}
						}
					}
				}
				//queen
				else if (players[p].pieces[i].type == 6)
				{
					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do {
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y + ytb][x - 65 + xtd] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] <= 122)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 + xtd] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 + xtd] = 2;
								}
							}
							ytb = 8;
							xtd = 8;
						}
						ytb++;
						xtd++;

					} while (ytb < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y - ytc][x - 65 + xtd] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] <= 122)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65 + xtd] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65 + xtd] = 2;
								}
							}
							ytc = 8;
							xtd = 8;
						}
						ytc++;
						xtd++;

					} while (ytc < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y - ytc][x - 65 - xte] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] <= 122)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65 - xte] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65 - xte] = 2;
								}
							}
							xte = 8;
						}
						xte++;
						ytc++;
					} while (xte < 8);

					xte = 1;
					xtd = 1;
					ytc = 1;
					ytb = 1;

					do
					{
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y + ytb][x - 65 - xte] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] <= 122)
								{
									players[p].pieces[i].move_range[y + ytb][x - 65 - xte] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y + (ytb)][x - 65 - xte] = 2;
								}
							}
							xte = 8;
							ytb = 8;
						}
						xte++;
						ytb++;

					} while (xte < 8);
					ytb = 1;
					ytc = 1;
					xtd = 1;
					xte = 1;

					do {
						if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] == ' ')
						{
							players[p].pieces[i].move_range[y + (ytb)][x - 65] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] <= 122)
								{
									players[p].pieces[i].move_range[y + ytb][x - 65] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y + ytb)][get_coordenates_x(x)] <= 90)
								{
									players[p].pieces[i].move_range[y + ytb][x - 65] = 2;
								}
							}
							ytb = 8;
						}
						ytb++;
					} while (ytb < 8);

					do
					{
						if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] == ' ')
						{
							players[p].pieces[i].move_range[y - ytc][x - 65] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] >= 97 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] <= 122)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] >= 65 && matriz[get_coordenates_y(y - ytc)][get_coordenates_x(x)] <= 90)
								{
									players[p].pieces[i].move_range[y - ytc][x - 65] = 2;
								}
							}
							ytc = 8;
						}
						ytc++;

					} while (ytc < 8);

					do
					{
						if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] == ' ')
						{
							players[p].pieces[i].move_range[y][x - 65 + xtd] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] <= 122)
								{
									players[p].pieces[i].move_range[y][x - 65 + xtd] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x + xtd)] <= 90)
								{
									players[p].pieces[i].move_range[y][x - 65 + xtd] = 2;
								}
							}
							xtd = 8;
						}
						xtd++;

					} while (xtd < 8);

					do
					{
						if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] == ' ')
						{
							players[p].pieces[i].move_range[y][x - 65 - xte] = 1;
						}
						else
						{
							if (roundnum == 1)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] >= 97 && matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] <= 122)
								{
									players[p].pieces[i].move_range[y][x - 65 - xte] = 2;
								}
							}
							else if (roundnum == 2)
							{
								if (matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] >= 65 && matriz[get_coordenates_y(y)][get_coordenates_x(x - xte)] <= 90)
								{
									players[p].pieces[i].move_range[y][x - 65 - xte] = 2;
								}
							}
							xte = 8;
						}
						xte++;

					} while (xte < 8);
				}

			}
		}
	}
}

int get_coordenates_y(int y)
{
	y = y * 2;

	return y;
}

int get_coordenates_x(int x)
{
	x = x - 65 + 1;
	x = x * 2;
	return x;
}

char piece_on_board(int l, int c)
{
	char s = ' ';

	for (int p = 0; p <= 1; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (l == get_coordenates_y(players[0].pieces[i].y) && c == get_coordenates_x(players[0].pieces[i].x))
			{
				s = players[0].pieces[i].design;
			}
			else if (l == get_coordenates_y(players[1].pieces[i].y) && c == get_coordenates_x(players[1].pieces[i].x))
			{
				s = players[1].pieces[i].design;
			}
		}
	}
	return s;
}

char game_board(int l, int c)
{
	char cara = ' ';


	if (l == 0)
	{
		if (c % 2 == 0 && c != 0)
		{
			cara = ('%c', num++);
		}
		else if (c % 3 == 0)
		{
			cara = ' ';
		}
	}
	else if (l % 2 == 0)
	{
		if (c == 0)
		{
			cara = ('%c', num1++);
		}
		else if (c % 2 == 0)
		{
			cara = piece_on_board(l, c);
		}
		else
		{
			cara = '|';
		}
	}
	else
	{
		if (c == 0)
		{
			cara = ' ';
		}
		else if (c % 2 == 0)
		{
			cara = '-';
		}
		else
		{
			cara = '+';
		}
	}

	return cara;
}
//Testa se tem peça na coordenada
int overlap_test(char x, int y)
{
	int test = 0;

	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if ((x == players[p].pieces[i].x) && (y == players[p].pieces[i].y))
			{
				if (roundnum - 1 == p)
				{
					test = 1;
				}
				else
				{
					test = 0;
				}
			}
		}
	}
	return test;
}
//remover peças
int remove_unit(int x, int y)
{
	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (players[p].pieces[i].x == x && players[p].pieces[i].y == y)
			{
				players[p].pieces[i].x = -1;
				players[p].pieces[i].y = -1;
			}
		}
	}
}

int move_unit(int x, int y, int first_x, int first_y, int roundnum)
{
	int test = 0;
	int tipo = 0;
	if (matriz[get_coordenates_y(y)][get_coordenates_x(x)] == 'x' || matriz[get_coordenates_y(y)][get_coordenates_x(x)] == 'O')
	{
		remove_unit(x, y);

		for (int p = 0; p < 2; p++)
		{
			for (int i = 0; i <= 15; i++)
			{
				if (players[p].pieces[i].x == first_x && players[p].pieces[i].y == first_y)
				{


					players[p].pieces[i].x = x;
					players[p].pieces[i].y = y;
					players[p].pieces[i].first_move = 0;
					test = 1;

					if (p == 0)
					{
						if (y == 8)
						{
							printf("Introduza que tipo de peça deseja trocar pelo peão");
							printf("1 - Torre");
							printf("2 - Bispo");
							printf("3 - Rainha");
							printf("4 - Cavalo");
							scanf("%d", &tipo);

							players[p].pieces[i].type = tipo;
						}
					}
					else if (p == 1)
					{
						if (y == 0)
						{
							printf("Introduza que tipo de peça deseja trocar pelo peão");
							printf("1 - Torre");
							printf("2 - Bispo");
							printf("3 - Rainha");
							printf("4 - Cavalo");
							scanf("%d", &tipo);

							players[p].pieces[i].type = tipo;
						}
					}
				}
			}
		}
	}
	return test;
}

void matrix_maker()
{
	for (int l = 0; l <= 17; l++)
	{
		for (int c = 0; c <= 17; c++)
		{
			matriz[l][c] = game_board(l, c);
		}
	}
	num1 = 49;
	num = 65;
}

void show_matrix()
{
	system("COLOR 7");
	for (int l = 0; l <= 17; l++)
	{
		for (int c = 0; c <= 17; c++)
		{
			if (c == 0)
			{
				printf("\n");
			}
			printf("%c", matriz[l][c]);
		}
	}
}

void players_name()
{
	printf("Player 1: \n"); scanf("%s", players[pp1].name);

	printf("Player 2: \n"); scanf("%s", players[pp2].name);
}

void players_round()
{
	if (roundnum == 1)
	{
		printf("Player : %s", players[0].name);
	}
	else
	{
		printf("Player : %s", players[1].name);
	}
}

void give_up()
{
	if (roundnum == 1)
	{
		printf("O player: %s  ganhou!!", players[1].name);
		scanf("%s", players[1].name);
	}
	else if (roundnum == 2)
	{
		printf("O player: %s  ganhou!!", players[0].name);
		scanf("%s", players[0].name);
	}
}

void players_peças()
{
	if (pp1 == 0)
	{
		printf("%s joga com as peças grandes!\n", players[pp1].name);
		printf("%s joga com as peças pequenas! \n", players[pp2].name);
	}
	else
	{
		printf("%s joga com as peças grandes! \n", players[pp2].name);
		printf("%s joga com as peças pequenas! \n", players[pp1].name);
	}
}

void reset_paint_move_possibilty(int x, int y)
{
	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (players[p].pieces[i].x == x && players[p].pieces[i].y == y)
			{
				for (int row = 0; row < 8; row++)
				{
					for (int colunm = 0; colunm < 8; colunm++)
					{
						players[p].pieces[i].move_range[row][colunm] = 0;
					}
				}
			}
		}
	}
}

void paint_move_possibilty(int x, int y)
{
	for (int p = 0; p < 2; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (players[p].pieces[i].x == x && players[p].pieces[i].y == y)
			{
				for (int row = 0; row < 8; row++)
				{
					for (int colunm = 0; colunm < 8; colunm++)
					{
						if (players[p].pieces[i].move_range[row][colunm] == 1)
						{
							matriz[get_coordenates_y(row)][get_coordenates_x(colunm + 65)] = 'x';
						}
						else if (players[p].pieces[i].move_range[row][colunm] == 2)
						{
							matriz[get_coordenates_y(row)][get_coordenates_x(colunm + 65)] = 'O';
						}

					}
				}
			}
		}
	}
}

void save_game()
{
	FILE *saves;
	saves = fopen("save.txt", "w");
	setlocale(LC_ALL, "portuguese");

	if (saves == NULL)
	{
		printf("Não foi possível abrir o ficheiro...");
	}
	else
	{
		fprintf(saves, "NamePlayer/design/x/y/tipo/firsttime/round\n");

		for (int p = 0; p <= 1; p++)
		{
			fprintf(saves, players[p].name);


			for (int i = 0; i <= 15; i++)
			{
				fprintf(saves, "%s\t%c/%d/%d\t%d\t%d\t%d\n", players[p].name, players[p].pieces[i].design, players[p].pieces[i].x, players[p].pieces[i].y,players[p].pieces[i].first_move, players[p].pieces[i].type,roundnum);
			}
		}
		fclose(saves);
	}
}

void load_game()
{
	FILE *saves;
	saves = fopen("save.txt", "r");
	char name[50];
	int n = 0;

	if (saves == NULL)
	{
		printf("Não foi possível abrir o ficheiro...");
	}
	else
	{
		while (fgetc(saves) != '\n');
		for (int p = 0; p <= 1; p++)
		{
			for (int i = 0; i <= 15; i++)
			{

				fscanf(saves, "%s\t%c/%d/%d\t%d\t%d\t%d\n", &players[p].name, &players[p].pieces[i].design, &players[p].pieces[i].x, &players[p].pieces[i].y,&players[p].pieces[i].first_move, &players[p].pieces[i].type,&roundnum) != EOF;
			}
		}
		fclose(saves);
	}
	system("CLS");
	matrix_maker();
	show_matrix();
	printf("\n");
	ingame_interface_menu();
}

int end_game()
{
	int end_game = 0;
	int player = 46;

	for (int p = 0; p <= 1; p++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (players[p].pieces[i].type == 5)
			{
				if (players[p].pieces[i].x == -1 && players[p].pieces[i].y == -1)
				{
					end_game = 1;
					player = p;
				}
			}
		}
	}

	if (end_game == 1)
	{
		if (player == 0)
		{
			printf("\nO player: %s  ganhou!!", players[1].name);
			scanf("%s", players[1].name);
		}
		else if (player == 1)
		{
			printf("O player: %s  ganhou!!", players[0].name);
			scanf("%s", players[0].name);
		}
	}

	return end_game;
}

void ingame_interface_menu()
{
	int i_menu = 10;
	char xc = 0; int xy = 0, xtest = 0, ytest = 0;
	int test = 0;
	int i_menu2 = 35;
	int move_menu = 46;

	players_peças();

	do
	{
		printf("\n----------------------MENU----------------------\n");
		players_round();
		printf("\n \nFazer a jogada - 1                                                     Legenda:\n");
		printf("Salvar - 2\n");
		printf("Desistir - 3                                                                x - Casas para onde a peça se pode mover\n");
		printf("------------------------------------------------                            O - Peça que pode comer                 \n");

		scanf(" %d", &i_menu);

		if (i_menu == 1)
		{

			printf("Introduza as coordenadas da peça que pretende mover: \n");

			scanf(" %c", &xc);
			xc = toupper(xc);
			getchar();
			scanf("%d", &xy);

			if (overlap_test(xc, xy) == 1)
			{
				overlap_range(xc, xy, roundnum);
				paint_move_possibilty(xc, xy);
				system("CLS");
				show_matrix();

				printf("\nMover a peça - 1");
				printf("\nDescelecionar a peça - 2\n");
				scanf(" %d", &i_menu2);
				do {
					if (i_menu2 == 1)
					{
						printf("\nIntroduza as coordenadas para onde pretende mover a sua peça: \n");
						scanf(" %c", &xtest);
						xtest = toupper(xtest);
						getchar();
						scanf("%d", &ytest);

						test = move_unit(xtest, ytest, xc, xy, roundnum);
						move_menu = 25;
					}
					else if (i_menu2 == 2)
					{
						reset_paint_move_possibilty(xtest, ytest);
						matrix_maker();
						system("CLS");
						show_matrix();
						ingame_interface_menu();
						move_menu = 25;
					}
				} while (move_menu != 25);

				reset_paint_move_possibilty(xtest, ytest);

				system("CLS");
				if (test == 0)
				{
					printf("Coordenadas Erradas\nRepita a jogada");

				}
				else
				{
					round();
				}

				matrix_maker();
				show_matrix();

			}
			else
			{
				system("CLS");
				printf("Não foi encontrada nenhuma peça para mover! \n");
				show_matrix();
			}
		}
		else if (i_menu == 2)
		{
			save_game();

			system("CLS");
			matrix_maker();
			show_matrix();


		}
		else if (i_menu == 3)
		{
			int submenu = 10;

			printf("Prentende mesmo desistir? \n");
			printf("SIM - 1 \n");
			printf("NÃO - 2 \n");

			scanf("%d", &submenu);

			if (submenu == 1)
			{
				give_up(roundnum);
				main();
			}
			else if (submenu == 2)
			{

			}
		}
		else
		{
			printf("Opção Inexistente, tente novamente");
			ingame_interface_menu();
		}
	} while (end_game() != 1);
}

int main(void)
{
	start_game_randomizer();

	
	setlocale(LC_ALL, "portuguese");
	int menu_options = 100;
	char enter = ' ';
	do {
		system("COLOR 2");
		printf("\n----------------------MENU----------------------\n");
		printf("Jogar - 1\n");
		printf("Load Game - 2\n");
		printf("Sair - 3\n");
		printf("------------------------------------------------\n");

		scanf("%d", &menu_options);

		if (menu_options == 1)
		{
			chess_piece();
			matrix_maker();
			system("CLS");
			system("COLOR 2"); // COR DAS LETRAS
			printf("------------------NICKNAME MENU----------------------\n");
			printf("Introduza o seu nickname:\n");
			players_name();
			printf("------------------------------------------------");
			printf("\n");

			system("CLS"); //CONSOLE.CLEAR()
			show_matrix();
			printf("\n");
			ingame_interface_menu();
		}
		else if (menu_options == 2)
		{
			load_game();

		}

	} while (menu_options != 3);

	return 0;
}
