#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define USAGE "Usage: ./2048 <size>"

bool death = 0;
int** battlefield = NULL;
int Score = 0;
int blank;
int flag = 0;

int** init(int size);
void run(int size);
int up(int size);
int left(int size);
int right(int size);
int down(int size);
void print(int size);
int addnew(int size);
void clean(int size);
void addhelper(int size);

int main(int argc, char const *argv[])
{
	system("clear");
	if (argc != 2)
	{
		puts(USAGE);
		exit(1);
	}
	battlefield = init(atoi(argv[1]));
	addhelper(atoi(argv[1]));
	//battlefield[0][0] = 2;
	blank--;
	print(atoi(argv[1]));
	run(atoi(argv[1]));
	clean(atoi(argv[1]));
	return 0;
}

int** init(int size)
{
	int** ret = (int**)calloc(size, sizeof(int*));
	for (int i = 0; i < size; i++)
	{
		ret[i] = (int*)calloc(size, sizeof(int));
	}
	blank = size * size;
	return ret;
}

void run(int size)
{
	char operation;
	char* buffer = NULL;
	size_t length = 0;
	while (getline(&buffer, &length, stdin) != -1)
	{
		operation = buffer[0];

		int death = 0;
		int success = 0;
		switch (operation)
		{
			case 'w':
				success = up(size);
				break;
			case 'a':
				success = left(size);
				break;
			case 'd':
				success = right(size);
				break;
			case 's':
				success = down(size);
				break;
			case 'q':
				system("clear");
				printf("Quit Game 2048\n");
				return;
			default:
				continue;
		}
		if (success)
		{
			printf("Congratulations! You got score: %d\n", Score);
			return;
		}

		if (flag)
		{
			death = addnew(size);
			flag = 0;
			if (death)
			{
				puts("GAME OVER");
				return;
			}
		}
		system("clear");
		print(size);
		printf("Score: %d, Blank Left: %d\n", Score, blank);
	}
}

int up(int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (battlefield[i][j] == 0)
			{
				continue;
			}
			else
			{
				flag = 1;
				while (i >= 1 && (battlefield[i - 1][j] == 0 || battlefield[i][j] == battlefield[i - 1][j]))
				{
					if (battlefield[i - 1][j] == 0)
					{
						battlefield[i - 1][j] = battlefield[i][j];
						battlefield[i][j] = 0;
					}
					else
					{
						Score += battlefield[i - 1][j];
						battlefield[i - 1][j] *= 2;
						battlefield[i][j] = 0;
						blank++;
						if (battlefield[i - 1][j] == 2048)
							return 1;
					}
					i--;
					system("clear");
					print(size);
					usleep(70000);
				}
			}
		}
	}
	return 0;
}

int left(int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (battlefield[j][i] == 0)
			{
				continue;
			}
			else
			{
				flag = 1;
				while (i >= 1 && (battlefield[j][i - 1] == 0 || battlefield[j][i] == battlefield[j][i - 1]))
				{
					if (battlefield[j][i - 1] == 0)
					{
						battlefield[j][i - 1] = battlefield[j][i];
						battlefield[j][i] = 0;
					}
					else
					{
						Score += battlefield[j][i - 1];
						battlefield[j][i - 1] *= 2;
						battlefield[j][i] = 0;
						blank++;
						if (battlefield[j][i - 1] == 2048)
							return 1;
					}
					i--;
					system("clear");
					print(size);
					usleep(70000);
				}
			}
		}
	}
	return 0;
}

int right(int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (battlefield[j][i] == 0)
			{
				continue;
			}
			else
			{
				flag = 1;
				while (i <= size - 2 && (battlefield[j][i + 1] == 0 || battlefield[j][i] == battlefield[j][i + 1]))
				{
					if (battlefield[j][i + 1] == 0)
					{
						battlefield[j][i + 1] = battlefield[j][i];
						battlefield[j][i] = 0;
					}
					else
					{
						Score += battlefield[j][i + 1];
						battlefield[j][i + 1] *= 2;
						battlefield[j][i] = 0;
						blank++;
						if (battlefield[j][i + 1] == 2048)
							return 1;
					}
					i++;
					system("clear");
					print(size);
					usleep(70000);
				}
			}
		}
	}
	return 0;
}

int down(int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (battlefield[i][j] == 0)
			{
				continue;
			}
			else
			{
				flag = 1;
				while (i <= size - 2 && (battlefield[i + 1][j] == 0 || battlefield[i][j] == battlefield[i + 1][j]))
				{
					if (battlefield[i + 1][j] == 0)
					{
						battlefield[i + 1][j] = battlefield[i][j];
						battlefield[i][j] = 0;
					}
					else
					{
						Score += battlefield[i + 1][j];
						battlefield[i + 1][j] *= 2;
						battlefield[i][j] = 0;
						blank++;
						if (battlefield[i + 1][j] == 2048)
							return 1;
					}
					i++;
					system("clear");
					print(size);
					usleep(70000);
				}
			}
		}
	}
	return 0;
}

void print(int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("+------");
		printf("+\n");
		for (int j = 0; j < size; j++)
		{
			printf("| %4d ", battlefield[i][j]);
		}
		printf("|\n");
	}
	//printf(" ");
	for (int i = 0; i < size; i++)
		printf("+------");
	printf("+\n");
}

void addhelper(int size)
{
	srand(time(0));
	int x = (rand() % size);
	int y = (rand() % size);
	while (battlefield[y][x] != 0)
	{
		x = (rand() % size);
		y = (rand() % size);
	}
	printf("x = %d, y = %d\n", x, y);
	battlefield[y][x] = ((rand() % 10 == 9) ? 4 : 2);
}

int addnew(int size)
{
	if (flag == 0)
		return 0;
	if (blank <= 0)
		return 1;
	else
	{
		addhelper(size);
		blank--;
		return 0;
	}	
}

void clean(int size)
{
	for (int i = 0; i < size; i++)
	{
		free(battlefield[i]);
	}
	free(battlefield);
}
