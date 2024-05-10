#include <stdio.h>
#include <stdlib.h>

char board_char(int x)
{
    switch(x)
    {
        case -1: // player
            return 'X';
            break;
        case 0: 
            return ' ';
            break;
        case 1:
            return 'O';
            break;
        default:
            return ' ';
            break;
    }
}

void print_board(int board[9])
{
    printf(" %c | %c | %c \n", board_char(board[0]), board_char(board[1]), board_char(board[2])); 
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board_char(board[3]), board_char(board[4]), board_char(board[5])); 
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board_char(board[6]), board_char(board[7]), board_char(board[8])); 
}

int win(int *board)
{
    int wins[8][3] = 
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };
    for (int i = 0; i < 8; i++)
    {
        if (board[wins[i][0]] != 0 && 
            board[wins[i][0]] == board[wins[i][1]] &&
            board[wins[i][1]] == board[wins[i][2]])
        {
            return board[wins[i][2]];
        }
    }
    return 0;
}

int draw(int *board)
{
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == 0) 
		{
			return 0;
		}
	}
	return 1;
}

int minimax(int* board, int player)
{
	int winner = win(board);
	if (winner != 0)
	{
		return winner * player;
	}
	int best_move = -1;	
	int best_score = -2;

	for (int move = 0; move < 9; move++)
	{
		if (board[move] == 0)
		{
			board[move] = player;
			int this_state_score = -minimax(board, -player);
			if (this_state_score > best_score)
			{
				best_score = this_state_score;
				best_move = move;
			}
			board[move] = 0;
		}
	}
	if (best_move == -1)
	{
		return 0;
	}
	return best_score;
}

void computer_move(int *board)
{
	int best_move = -1, best_score = -2;
	for (int move = 0; move < 9; move++)
	{
		if (board[move] == 0) // legal move
		{
			board[move] = 1;
			int this_state_score = -minimax(board, -1);
			board[move] = 0;
			if (best_score < this_state_score)
			{
				best_score = this_state_score;
				best_move = move;
			}
		}
	}
	board[best_move] = 1;
}

void player_move(int *board)
{
    int move;
	do {
		printf("Input move ([0, 1, ..., 8]): ");
		scanf("%d", &move);
		if (move > 9 || move < 0)
		{
			printf("Out of range!\n");
		}
		if (board[move] != 0)
		{
			printf("Invalid move!\n");
		}
	}
	while (move > 9 || move < 0 || board[move] != 0);
	board[move] = -1;
}

int main(int argc, char **argv)
{
    int order;
    int board[9] = {0};

    printf("Computer: O, You: X\n");
    printf("Play (1)st or (2)nd? ");
    scanf("%d", &order);
	int i = 0;
    while (i < 9)
    {
		i++;
		if (order == 1)
		{
			player_move(board);
			if (win(board))
			{
				print_board(board);
				break;
			}
			computer_move(board);
			print_board(board);
		} else 
		{
			computer_move(board);
			if (win(board))
			{
				print_board(board);
				break;
			}
			print_board(board);
			player_move(board);
		}
	}
	
	if (win(board) == 1)
	{
		printf("You lost");
	} else if (win(board) == -1) 
	{
		printf("You won");
	} else 
	{
		printf("Draw");
	}
    return 0;
}
