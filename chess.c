/*
changing pieces to values from 0(empty) to 12 (2 * 6 pieces)
player = 0(if below 7 but !=0) || 1 (if >6)

optionally research bitmaps~
*/

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <stdint.h>
//#include <graphic.h>//Doesn't work at all - doesn't seem to exist???
#include <conio.h>
#include <windows.h>   // what, we can't use them?

// typedef struct move {
//	int x;
//	int y;
//};
int playernum = 2;//not gonna be changeable too soon...

//dimensions...
//#define int rangeZ=8; //will not dable with 3D chess for now
#define rangeX 8
#define rangeY 8
//typedef unsigned uint8_t b[rangeX][rangeY]; //bitmap??
int board[rangeX][rangeY];

//TARGET SYSTEM, because some functions differ between OSes
//#define TargetSystem 'Lin'
#define TargetSystem 'Win'
//#define TargetSystem "And" //i'm thinking about it, not sure if i should...

#define CPlayer0  7
#define CPlayer1  8
#define WhiteTile 15
#define BlackTile 0
	//	colors:
#if (TargetSystem=='Win')
	void *getConsoleFunction(char *name);
	BOOL (WINAPI *doSetConsoleTextAttribute)(HANDLE hConsoleOutput, WORD attr);
	HANDLE hCon;

	void Init(){
		hCon=GetStdHandle(STD_OUTPUT_HANDLE);
		doSetConsoleTextAttribute=getConsoleFunction("SetConsoleTextAttribute");
	}

	void *getConsoleFunction(char *name) {
		static HMODULE kernel32=(HMODULE)0xffffffff;
		if(kernel32==0)
			return NULL;
			if((kernel32==(HMODULE)0xffffffff)){
			kernel32=LoadLibrary("kernel32.dll");
			if(kernel32==0)
				return 0;
			}
		return GetProcAddress(kernel32,name);
	}

	void Color(int bg, int fr){
		(*doSetConsoleTextAttribute)(hCon,(bg*16)+fr);
	}
#elif (TargetSystem=='Lin')
	/*
	#define KNRM  "\x1B[30m"
	#define KRED  "\x1B[31m"
	#define KGRN  "\x1B[32m"
	#define KYEL  "\x1B[33m"
	#define KBLU  "\x1B[34m"
	#define KMAG  "\x1B[35m"
	#define KCYN  "\x1B[36m"
	#define KWHT  "\x1B[37m"
	#define nocolor   "\e[0m"

	#define CPlayer0  "\x1B[37m" //color light grey
	#define CPlayer1  "\x1B[30m" //color black
	*/

	void Color(int bg, int fr){//ignores bg color for now, i don't know how to set that sadly...

	}
#endif

void debug(){ // not recommended, may not work
	//put your code here and it will run before anything else
	//system("COLOR 9C");


	Color(0,15);
	printf("TEST\n");
	debugPrintBoard();
	getch();
	ClearScreen();


	//colordemo();
}

void ErrorMsg(int reason){
	Color(0,4);//KRED
	printf("\n An ERROR HAS OCCURED, CODE: %d\nGAME WILL CONTINUE", reason);
	Color(0,15);//nocolor
}

int Betrag(int zahl){
	if(zahl < 0){
		zahl *= -1;
	}
	return zahl;
}

#include "debug.c" //just some test functions so that i don't have to enter the konami code every single time...
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
	//should i check also for own pieces for faulty moves?
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

void printChar(int piece){//player color already applied!
	printf("c");//for testing only!
	/*
	if(piece==0) printf(" ");

		switch (piece%6) {//printing piece char
			case 0://pawn 6 12
				printf("P");
				break;
			case 1://Knight 1 7
				printf("K");
				break;
			case 2://Bishop 2 8
				printf("B");
				break;
			case 3://Rook 3 9
				printf("R");
				break;
			case 4://Queen 4 10
				printf("Q");
				break;
			case 5://King 5 11
				printf("K");
				break;
			default:
				ErrorMsg(__COUNTER__);
				break;
		}
	}
	*/
}



void printBoard(){
	for(int x=0; x<rangeX; x++) {
		printf("------");
	}//printing first line

	skiphSpaces(1);
	for(int y=0; y<rangeY; y++){
		printf("|");
		for(int n=0; n<3; n++){//1 squre needs 3 lines, 2 lines blank and 1 with the pieces

			for(int x=0; x<rangeX; x++){


				//Colorcoding
				int square=(x+y)%2;//white or black square
				int bg;//actual color
				switch (square) {
					case 0:
						bg = WhiteTile;//both defined at top, because of potential text/bg color issues, for quick change
						break;
					case 1:
						bg = BlackTile;
						break;
				}

				int fr;//player color

				if (board[x][y]!=0) {//text color
					if (owner(x, y)==0) {
						fr = CPlayer0;
					}
					else if (owner(x, y) == 1) {
						fr = CPlayer1;
					} else fr = 15;
				}

				Color(bg, fr);
				printf("  ");
				printChar(board[x][y]);//print piece
				printf("  ");
				Color(0,15);//nocolor
				printf("|");
				}
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
	Color(0,12);
	printf("compiled on:" __DATE__ " at " __TIME__ " using C99 version: %li \n", __STDC_VERSION__);
		printf("Compiled on ");
	#ifdef __unix__
		printf("Linux");git
	#elif defined(_WIN32) || defined(WIN32)
		printf("Windows");
	#endif
	printf("\n\n Written and done stuff and so on by Jack ");
	Color(0,15);
	char null;
	scanf("%c", &null);
}

int menu(){
	Color(0,15);
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
		Color(0,4);//KRED
		printf("\nnot a piece that you own\n");
		Color(0,15);//nocolor
		printf("please check your input:");
	}
	if(inputx<=rangeX && 0<=inputx  &&  inputy<=rangeY && 0<=inputy){
	if(1){} //check piece ownership

		//copied behavior for checking movement validity to be DELETED
	/*
	while(2 != scanf("%d,%d", &inputx, &inputy)){ //check for inpput validity
		printf(KRED"\nnot a piece that you own\n" nocolor "please check your input:");
	}
	*/
	}else return 0;
	return 0;
}

int GameOver(int Status){
	ClearScreen();
	printf("GAME OVER\n\nWinner: Player %d", Status);
	return Status;//makes no sense right now... but i could make some operations with it here before sending it back...
}

int play(int player, int numTurns){
	ClearScreen();
	Color(0,15);
	printf("player %d\n", player);
	Color(0,15);//nocolor
	printBoard();
	playerMove(player);
	int Status=checkBoard(player);
	if(Status!=0) 	return GameOver(Status);

	return play((player + 1) % playernum, numTurns + 1); //may not use numTurns, but would be a nice feature for stats
}

int main(){
	ClearScreen();
	Init();
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
			Color(0,4);//KRED
 			printf("\nERROR, review input!\n");
			Color(0,15);//nocolor
 			goto start;
	}

eof:
	printf("BYE\n");
}
