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

#define CPlayer0  15
#define CPlayer1  0
#define WhiteTile 7
#define BlackTile 8
//for cases when colors match if defined equal
#define AltWhiteColor 15
#define AltBlackColor 8
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
		if(kernel32==0) return NULL;
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

//debug();

void ErrorMsg(int reason){
	Color(0,4);//KRED
	printf("\nAn ERROR HAS OCCURED, CODE: %d  GAME WILL CONTINUE\n", reason);
	//
	getch();
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
		if(y==1){//placing pawns here
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

		int player = 3;
		if(y<(rangeY / 2)) {
			player = 1;
				//all pieces are owned by player 1(black)
		} else {
			player = 0;
				//all pieces are owned by player 0(white)
		}

		if (y==0||y==7) {//valuable pieces
			for(int x=0; x<rangeX; x++){
				int b = Betrag(x -(rangeX / 2));
				if (x==3||x==4){// pieces non central are mirrorablen King and Queen are not
					//will replace hardcoded positions with ones relavtive to board size for variability later
					board[3][y]= 4 + 6*player;//queen
					board[4][y]= 5 + 6*player;//king
				} else {
					if (x<(rangeX/2)) {
						board[x][y]=1+x+6*player; //piece values are fitted to match
					} else if (x>(rangeX/2)) {
						board[x][y]=8-x+6*player;
					} else {
						ErrorMsg(__COUNTER__);//wrong board size?
					}
				}
				//board[x][y] = ...
			}
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
	if(piece==0) {
		printf(" ");
	} else{
		switch (piece%6) {//printing piece char
			case 0://pawn 6 12
				printf("P");
				break;
			case 1://Rook 1 7
				printf("R");
				break;
			case 2://Knight 3 9 or Springer
				printf("S");
				break;
			case 3://Bishop 2 8
				printf("B");
				break;
			case 4://Queen 4 10
				printf("Q");
				break;
			case 5://King 5 11
				printf("K");
				break;
			default:
				ErrorMsg(__COUNTER__);//wrong argument or wrong value in array
				break;
		}
	}
}


int divider=1; //dividers on or off, will be configurable
int coords=1; //whether to show the coordinates
void printBoard(){
	if (coords==1) {
		printf("  ");
		for (int x = 0; x < rangeY; x++) {
			if (divider==1) {
				printf(" ");
			}
			printf("  %d  ", x);
		}
		printf("\n");
	}
	for(int y=0; y<rangeY; y++){
		for(int n=0; n<3; n++){//1 squre needs 3 lines, 2 lines blank and 1 with the pieces
			if (coords==1) {
				if (n==1) {
					printf(" %d", y);
				} else {
					printf("  ");
				}
			}
			if(n==0 && divider==1){//horizontal divider before square
				Color(0,15);//nocolor
				for(int x=0; x<rangeX; x++) {//printing divider
					printf("------");//maybe custom characters later, so that (2+width)*rangeX are printed
				}
				printf("\n");
			}//var x reset here

			if(divider==1) printf("|");
			for(int x=0; x<rangeX; x++){//going through x coords
				//Colorcoding
				int bg;//actual color
				switch ((x+y)%2) {//white or black square
					case 0:
						bg = WhiteTile;//both defined at top, because of potential text/bg color issues, for quick change
						break;
					case 1:
						bg = BlackTile;//defined at top
						break;
				}

				int fr;//player color
				if(n==1){//line with actual pieces
					if (board[x][y]!=0) {//text color
						if (owner(x, y)==0) {
							fr = CPlayer0;
							if(fr==bg) fr = AltWhiteColor;
						}
						else if (owner(x, y) == 1) {
							fr = CPlayer1;
							if(fr==bg) fr = AltBlackColor;
						} else fr = 15;
					}
				} else fr = 15;
					Color(bg, fr);
					printf("  ");

					if (n==1) {
					printChar(board[x][y]);//print piece
				} else printf(" ");

					printf("  ");
					Color(0,15);//nocolor
					if(divider==1) printf("|");

			}
			printf("\n");
		}
	}
	if (divider!=0) {
		for(int x=0; x<rangeX; x++) {//printing last divider line
			printf("------");
		}
	}
	printf("\n");
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

int playerMove(int player){
	printf("choose piece: ");
	int inputx=-1; int inputy=-1;
	while(2 != scanf("%d,%d", &inputx, &inputy) || inputx>=rangeX || 0>inputx  ||  inputy>=rangeY || 0>inputy || owner(inputx, inputy)!=player){ //check for input validity as long as
		//not valid coordinates, out of bounds or not own
		Color(0,4);//KRED
		printf("\nnot a valid piece that you own");
		Color(0,15);//nocolor
		printf("\nplease check your input: ");
	}
	//better save than sorry, checking the second time
	if(inputx<=rangeX && 0<=inputx  &&  inputy<=rangeY && 0<=inputy){//in bounds
		if(owner(inputx, inputy)==player){//checking ownership
			printf("\nchoose destination (x,y): ");
			int xpos=inputx; int ypos=inputy;
			inputx=-1; inputy=-1;//resetting for new input to not trigger returning to selection
			while (0==checkAllMoves(board[xpos][ypos], player, xpos, ypos, inputx, inputy)) {
				while (2 != scanf("%d,%d", &inputx, &inputy) || player == owner(inputx, inputy) || inputx>=rangeX || 0>inputx  ||  inputy>=rangeY || 0>inputy) {//second check includes check for no movment
					if(inputx==xpos && inputy==ypos){//opens dialog to go back
						//might add actual commands in the future to access menu and other things in the future
						printf("\nSwitch piece? (y/n) ");
						char input;
						scanf(" %c", &input);
						if(input == 'y' || input == 'Y'){
							printf("\nreturning to piece selection\n");
							printBoard();
							return playerMove(player);
						}
					}
					printf("\ninvalid, check again :");
				}
			}



			//if succeded, execute movement
			board[inputx][inputy]=board[xpos][ypos];
			board[xpos][ypos]=0;
			return 1;
		}
	}
	ErrorMsg(__COUNTER__);
	return 0;
}

int GameOver(int Status){
	ClearScreen();
	printf("GAME OVER\n\nWinner: Player %d", Status);
	return Status;//makes no sense right now... but i could make some operations with it here before sending it back...
}

//will be editable in settings to properly identify players
char player0name[20] = "White";//in here like this to make it editable during runtime
char player1name[20] = "Black";
const char * PlayerName(int player){//will become configurable via string input
	switch (player) {
		case 0:
			return player0name;
			break;
		case 1:
			return player1name;
			break;
		default:
			ErrorMsg(__COUNTER__);//wrong player argument
			return "undefined";
	}
}

int play(int player, int numTurns){
	ClearScreen();
	Color(0,15);
	printf("player %d, %s\n", player, PlayerName(player));
	Color(0,15);//nocolor
	printBoard();
	printf("\n Your Move! (x,y)\n");
	playerMove(player);
	int Status=checkBoard(player);//checks for status, such as checkmate
	if(Status!=0) 	return GameOver(Status);

	return play((player + 1) % playernum, numTurns + 1); //may not use numTurns, but would be a nice feature for stats
}

void beginPlay(int a, int b){// will become settings for the ai and player
	for (int n = 0; n < playernum; n++) {
		PlayerScores[n] = 0;
	}
	SetBoard();
	play(0,0);
}

void settings(){
	int input;
	Color(0, 15);
	printf("settings:\n");
	while(1!=scanf("%d\n", &input) || 0!=input){
		switch (input) {
			case 1:
				break;
			default:
				printf("\n didn't understand that, try again\n");
		}
	}
	ClearScreen();
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

int main(){
	Init();
	debug();// solely for testing purposes
	ClearScreen();
start:;
	int input;
	input = menu();
	switch (input){
		case 0:
			goto eof;
			break;
 		case 1:
 			beginPlay(0, 0);
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
