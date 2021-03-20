
               /*   Ido Lev
                I.D:206282527   */

//////////////General Discription //////////////////

/*The program creates new head and delete the tail every round
  I used a pointer fot the last node that keeps updating without a loop
  and pointer for the first node that keeps updating without the loop
  I did it by heaving a pointer to the previous and to the next node inside the struct of my linked list
  for the game over codition when the snake meet itself I used a 2 dimentional array
  to map snake at all time by 1 and 0 so I would know which slot at the array I should check every round*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define ROW 25
#define COL 75

typedef struct INDEX
{
	int row;
	int col;
}index;

typedef struct listNode
{
	index index;
	struct listNode* next;
	struct listNode* previous;
}ListNode;

// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen, 
// but rather a command to the terminal (or most likely terminal emulatoion).

// Turn escape codes ON.
void init(void);

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y);

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs);

//////////My Declerations////////////

void printBoard();

ListNode* createNewNode(index data, ListNode* next);

char snakeLegalDirection(char arrow);

index snakeMovement(char arrow, index spot);

ListNode* nodeToHead(index spot, ListNode* firstNode);

ListNode* deleteLastNode(ListNode* lastNode);

void gameOverMain();

bool gameOver(ListNode* firstNode);


        /*   Ido Lev
         I.D:206282527   */


int main() 
{
	///////////////////
	init();
	printBoard();
	///////////////////
	index spot;
	float time;
	int count;
	char arrow;
	int board[ROW][COL];
	arrow = 'd';
	time = 1;
	count = 0;
	spot.col = COL / 2;
	spot.row = ROW / 2;
	ListNode* firstNode = createNewNode(spot, NULL);
	ListNode* lastNode = firstNode;
	ListNode* tempLastNode = firstNode;

		while ( gameOver(firstNode))
		{
			//Aesthetic action , Puts the sign at the bottom of the screen
			gotoxy(ROW + 2, 0);
			//if there was a keyboard use, it updates the arrow to the relevant one
			if (_kbhit()) {arrow = snakeLegalDirection(arrow);} 
			//Updates the spot accordingly to the arrow char at this round
			spot = snakeMovement(arrow, spot);
			//Condition to check if the snake got into himself as a apperance of 1 or 0 in a 2 dimentional array that represent the snake
			if (board[spot.row][spot.col] == 1) { gameOverMain(); break; }
			else { board[spot.row][spot.col] = 1; }
			//Creates new node at the adress of the previous node of the cureent first node
			firstNode->previous= nodeToHead(spot, firstNode);
			//Updates the first node as the one we just created
			firstNode = firstNode->previous;
			//Every 5 steps the program won't erase the last node so the snake will be longer
			if (count % 5!= 0)
			{
				board[lastNode->index.row][lastNode->index.col] = 0;
				lastNode=deleteLastNode(lastNode);
			}
			else { if (time > 0.1)time = time - 0.03; }//speed up in 0.03 sec every 5 turns
			gotoxy(ROW + 1, 0);
			sleep(time);
			gotoxy(firstNode->index.row, firstNode->index.col);
			printf("@\n");
			count++;
		}
		gameOverMain();
	}


// Turn escape codes ON.
void init(void) 
{
	system("cls");
}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y) {
	printf("\x1b[%d;%df", x, y);
}

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs) {
	clock_t clocks_start = clock();

	while (clock() - clocks_start < secs*CLOCKS_PER_SEC)
		;
}

//////////My Functions////////////

//Prints the board of 25X75
void printBoard()
{
	int i, j;
	for (i = 0; i <= ROW; i++)
	{
		for (j = 0; j <= COL; j++)
		{
			if (i == 0 || i == 25)
			{
				gotoxy(i, j);
				printf("#\n");
			}
			if (j == 0 || j == 75)
			{
				gotoxy(i, j);
				printf("#\n");
			}
		}
	}
	gotoxy(ROW + 5, 0);
}

//Creates new node and returns him
//Paremters:
//data:Index type data of rows and cols
//next:Pointer of the next node
ListNode* createNewNode(index data, ListNode* next)
{
	
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->index.row = data.row;
	node->index.col = data.col;
	node->next = next;
	node->previous = NULL;

	return node;
}

//Checks if the arrow is valid 
//Return the same one if it isn't ,and the new one if it is 
//Parameter : the letter that program got from the player
char snakeLegalDirection(char arrow)
{
	char tempArrow;
	tempArrow = arrow;
	arrow = _getch();
	if (arrow == 's' || arrow == 'w' || arrow == 'd' || arrow == 'a')return arrow;
	else return tempArrow;
}

//Checks the arrow direction
//Changes the direction accordingly with the spot value
//And return
//Paremeter:
//arrow:'a''s''d''w' as direction
//spot:index of row and col
index snakeMovement(char arrow,index spot)
{
	switch (arrow)
	{
	case 's': spot.row++; return spot; break;
	case 'w': spot.row--; return spot; break;
	case 'd': spot.col++; return spot; break;
	case 'a': spot.col--; return spot; break;
	}
}

//Create new node at the head of the linked list and returns the new one
//Paremeter:
//spot:index of row and col
//first node:adress of current first node
ListNode* nodeToHead(index spot,ListNode* firstNode)
{
	ListNode* newFirstNode = createNewNode(spot, firstNode);
	return newFirstNode;
}

//Delete the last node of the snake 
//prints space aboce the @ of the last node
//free the node from the memory
//Paremeter: lastNode : cureent lastNode
ListNode* deleteLastNode(ListNode* lastNode)
{
	gotoxy(lastNode->index.row, lastNode->index.col);
	printf(" ");
	lastNode = lastNode->previous;
	free(lastNode->next);
	lastNode->next = NULL;
	return lastNode;
}

 //Resets the board and prints GAME OVER
void gameOverMain()
{
	init();
	printBoard();
	gotoxy(ROW / 2, (COL / 2) - 4);
	printf("GAME OVER\n");
	gotoxy(ROW + 2, 0);
}

//Condition for the game borders
//Main condition of the Loop
//Paremeter: adress of the first node to get the index values
bool gameOver(ListNode* firstNode) 
{
	if (firstNode->index.row < 24 && firstNode->index.row >1 && firstNode->index.col < 74 && firstNode->index.col> 1) return true;
	else return false;
}

