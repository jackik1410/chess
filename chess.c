/*
changing pieces to values from 0(empty) to 12 (2 * 6 pieces)
player = 0(if below 7) || 1 (if >6)

optionally research bitmaps~
*/

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <stdint.h>
//#include<windows.h>   // what?

//	colors:
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
//#define K
#define nocolor   "\x1b[0m"

#define CPlayer1  "\x1b[37m" //color light grey
#define CPlayer2  "\x1B[30m" //color black


// typedef struct move {
//	int x;
//	int y;
//};
int playernum = 2;

void debug(){ // not recommended, may not work
	//put your code here and it will run before anything else

	//printBoard();
}


#define rangeX 8
#define rangeY 8
//dimensions...
//#define int rangeZ=8; //will not dable with 3D chess for now

//typedef unsigned uint8_t b[rangeX][rangeY];


int board[rangeX][rangeY];

int Betrag(int zahl){
	if(zahl < 0){
		zahl *= -1;
	}
	return zahl;
}

const char* playerColor(int player){
	if(player==0){
		return "";
	}else{
		return "";
	}
}

#include "pieces.c" //all declarations and definitions for pieces and movement


int SetBoard(){

	for(int y=0; y<rangeY; y++){
		if(y>2&&y<6) continue;
		if(y==2){//placing pawns here
			for(int x=0; x<rangeX; x++){
				board[x][y]= 12; //see definitions in pieces.c
			}
			continue;
		}if(y==6){//placing pawns here
			for(int x=0; x<rangeX; x++){
				board[x][y]= 6;
			}
			continue;
		}
		//no need to check more, placing other pieces for each player

		if(y<rangeY) {
			int player = 1;
				//all pieces are owned by player 1(black)
		} else {
			int player = 0;
				//all pieces are owned by player 0(white)
		}
		for(int x=0; x<rangeX; x++){
			int b = Betrag(x -(rangeX / 2)); // pieces non central are mirrorable
			if (b==1){

			} else {

			}
			//board[x][y] = ...
		}

	}

	return 1;
}

void ClearScreen(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

}

int checkBoard(int turn){
	if(turn == 0){
	//check white
	} else {
	//check black
	}
	return 0;
}
void skiphSpaces(int rep){
	if(rep==0) return ;
	if(rep == 2) {

		for(int x=0; x<rangeX; x++) {
		printf("------");
	}//printing line breaker
	//printf("\n");

	} else {
		printf("\n|");
		for(int x=0; x<rangeX; x++){
			printf("     |");
		}
		printf("\n");
	}
	skiphSpaces(rep-1);
}

void printBoard(){
	for(int x=0; x<rangeX; x++) {
		printf("------");
	}//printing first line


	skiphSpaces(1);
	for(int y=0; y<rangeY; y++){
		printf("|");
		for(int x=0; x<rangeX; x++){
			if (board[x][y]!=0) {
				if (owner(x, y)==0) {
					printf(CPlayer1);
				}
				else if (owner(x, y) == 1) {
						printf(CPlayer2);
				}
			}
			char p = 'c';
			//char piece= (&pos)->name;
			//printf(playerColor((&pos)->player));//unsure how to implement player color coding here

			printf("  %c  " nocolor "|", p);// piece
		}
		if(y+1==rangeY) {//print divider if there is another row
			printf("\n|");
			for(int x=0; x<rangeX; x++){
				printf("     |");
			}
			printf("\n");
			for(int x=0; x<rangeX; x++) {
				printf("------");
			}
			printf("\n");
		} else skiphSpaces(3);
	}
}

void credits(){
	ClearScreen();
	printf("compiled on:" __DATE__ " at " __TIME__ " using C99 version: %li", __STDC_VERSION__  );
	printf("\n Written and done stuff and so on by Jack ");
	char null;
	scanf("%c", &null);
}

int menu(){
	printf("\n\n modular Chess:\n\n");
	printf(" 1. play 2player mode\n 8. settings \n 9. credits \n press 0 to quit");
	int input;
	int output = 0;
	while(output==0){
		 output = scanf("%d", &input);
	};
	return input;
}

int playerMove(int player){
	printf("\n Your Move! (x,y)\n");
	printf("choose piece:");
	int inputx; int inputy;
	while(2 != scanf("%d,%d", &inputx, &inputy)){ //check for inpput validity
		printf(KRED"\nnot a piece that you own\n"nocolor"please check your input:");
	}
	if(inputx<=rangeX && 0<=inputx  &&  inputy<=rangeY && 0<=inputy){
	if(1){} //check piece ownership

		//copied behavior for checking movement validity
	/*
	while(2 != scanf("%d,%d", &inputx, &inputy)){ //check for inpput validity
		printf(KRED"\nnot a piece that you own\n"nocolor"please check your input:");
	}
	*/
	}else return 0;
	return 0;
}

int play(int player, int numTurns){
	ClearScreen();
	printf("player %d\n" nocolor, player);
	printBoard();
	playerMove(player);
	int Status=checkBoard(player);
	if(Status!=0) 	return Status;

	return play((player + 1) % playernum, numTurns + 1); //may not use numTurnss
}

int main(){
	ClearScreen();
	debug();// solely for testing purposes
start:;
	int input;
	input = menu();
	switch (input){
		case 0:
			goto eof;
			break;
 		case 1:
 			play(0, 0);
 			break;
 		/*
 		case 2: // not sensical! white always starts! only implement when using an C-player
 			//play(1, 0);
 			break;
 		*/
 		case 8:
			ClearScreen();
			printf("Not yet coded and stuff, but there are some little things planned...\n");
			printf("such as custom player colors or so\n");
			goto start;
 			break;
 		case 9:
 			credits();
 			goto start;
 			break;

 		default:
 			printf(KRED "\nERROR, review input!\n" nocolor);
 			goto start;
	}

eof:
	printf("BYE\n");
}