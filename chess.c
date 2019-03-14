#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <stdint.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>   // what, we can't use them? I'll just use it indirectly then

int playernum = 2;//not gonna be changeable too soon...

//dimensions...
//#define int rangeZ=8; //will not dable with 3D chess for now
#define rangeX 8
#define rangeY 8
//typedef unsigned uint8_t b[rangeX][rangeY]; //bitmap??
int board[rangeX][rangeY];

#define CPlayer0  15
#define CPlayer1  0
#define WhiteTile 7
#define BlackTile 8
//for cases when colors match if defined equal
#define AltWhiteColor 15
#define AltBlackColor 8
	//	colors:

#ifdef __unix__ //if linux
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
	void getch(){
		const char* nothing;
		scanf("%s\n", nothing);
		//nothing comes from nothing and if you return to nothing, what have you lost? NOTHING!
	}

	void Color(int bg, int fr){//ignores bg color for now, i don't know how to set that sadly...

	}
#elif defined(_WIN32) || defined(WIN32) //if windows (primary focus, colors work a LOT better here!)
//the following small bit was copied from the internet, i had no other way to use colors apart from passing the windows console simple batch commands, which would change the color of the whole window, not just a few characters
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
#endif

//debug();

void ErrorMsg(int num, char* reason){
	Color(0,4);//KRED
	printf("\nAn ERROR HAS OCCURED, CODE: %d, %s\n", num, reason);
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
						ErrorMsg(__COUNTER__, "unknown error");//wrong board size?
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

//will be editable in settings to properly identify players
char *player0name = "White";//in here like this to make it editable during runtime
char * player1name = "Black";
const char * PlayerName(int player){//will become configurable via string input
	switch (player) {
		case 0:
			return player0name;
			break;
		case 1:
			return player1name;
			break;
		default:
			ErrorMsg(__COUNTER__, "unknown error");//wrong player argument
			return "undefined";
	}
}

int Status = 0;//will be updated every turn and compared to the one before the register check and checkmate
int checkBoard(int turn){
	//return 0;//just forr debugging or else...
	int LastStatus = Status;

	for (int player = 0; player < playernum; player++) {//checking for eachplayer just to be safe
		int Kingx; int Kingy; findKings(player, &Kingx, &Kingy);//check for check and compare to last status for checkmate and game over
		for (int a = 0; a < rangeY; a++) {//looking for pieces that can attack the king pieces
			for (int b = 0; b < rangeY; b++) {
				if ((player+1)%2==owner(a,b)) if(1==checkAllMoves( board, board[a][b], (player+1)%2, a, b, Kingx, Kingy)) {//schach!!!
					//compare to last
					Color(4,15);
					printf(" Check for player %d, %s ", player, PlayerName(player));
					Color(0,15);
					//checking if checkmate can be avoided
					int testboard[rangeX][rangeY];
					for (int x = 0; x < rangeX; x++) {
						for (int y = 0; y < rangeY; y++) {
							testboard[x][y]=board[x][y];//setting them the same, so that it can test testboard[][] instead of potentially chainging the actual board
						}
					}
					for (int x = 0; x < rangeX; x++) {
						for (int y = 0; y < rangeY; y++) {
							if (owner(x,y)==player) {//finding the checked player's pieces
							//trying all possible moves
								for (int moveX = 0; moveX < rangeX; moveX++) {
									for (int moveY = 0; moveY < rangeY; moveY++) {
										if (owner(moveX,moveY)!=player && 1==checkAllMoves( board, testboard[x][y], player, x, y, moveX, moveY)) {//evaluate move if valid
											//now checking if enemies pieces are still attacking the checked player's King

											//for---
											for (int x2 = 0; x2 < rangeX; x2++) {
												for (int y2 = 0; y2 < rangeY; y2++) {
													if (owner(x2,y2)!=player) {
														findKings(player, &Kingx, &Kingy);
														if (1==checkAllMoves( board, testboard[x2][y2], owner(x2,y2), x2, y2, Kingx, Kingy)) {
															printf("GAMEOVER\n   Winner: %d", (player+1)%2);
															//GAMEOVER();
															return 1;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}

					return 1;//further specified somewhere else
				}
			}
		}
	}

	return 0;
}

char * PieceName(int piece){//player color already applied!
	if(piece==0) {
		return " ";
	} else {
		switch (piece%6) {//printing piece char
			case 0://pawn 6 12
				return "P";
				break;
			case 1://Rook 1 7
				return "R";
				break;
			case 2://Knight 3 9 or Springer
				return "Spr";
				break;
			case 3://Bishop 2 8
				return "Bis";
				break;
			case 4://Queen 4 10
				return "Queen";
				break;
			case 5://King 5 11
				return "King";
				break;
			default:
				ErrorMsg(__COUNTER__, "unknown error");//wrong argument or wrong value in array
				return "unknown";
				break;
		}
	}
}

int squareW = 5;//height and width, just affects visuals
int squareH = 3;
int divider=0; //dividers on or off, will be configurable
int coords=1; //whether to show the coordinates
void printBoard(int xpiece, int ypiece, int player){ //coords for showing possible moves
	printf("\n");//safety
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
		for(int n=0; n<squareH; n++){//1 squre needs 3 lines, 2 lines blank and 1 with the pieces
			if (coords==1 && n==(int)(squareH-1)/2) {
				printf(" %d", y);
			} else {
				printf("  ");
			}
			if(n==0 && divider==1){//horizontal divider before square
				Color(0,15);//nocolor
				for(int x=0; x<rangeX; x++) {//printing divider
					printf("------");//maybe custom characters later, so that (2+width)*rangeX are printed
				}
				printf("\n");
				if (divider==1) {
					printf("  ");
				}
			}//var x reset here

			if(divider==1) printf("|");

			for(int x=0; x<rangeX; x++){//going through x coords
				//Colorcoding
				int bg;//actual color
				if(xpiece!=-1 && ypiece!=-1 && 1==checkAllMoves( board, board[xpiece][ypiece], player, xpiece, ypiece, x, y)) {
					bg = 2;//green for valid position
				} else {
					switch ((x+y)%2) {//white or black square
						case 0:
							bg = WhiteTile;//both defined at top, because of potential text/bg color issues, for quick change
							break;
						case 1:
							bg = BlackTile;//defined at top
							break;
					}
				}


				int fr;//player color
				if(n==(int)(squareH-1)/2){//line with actual pieces
					if (board[x][y]!=0) {//text color
						if (owner(x, y)==0) {
							fr = CPlayer0;
							if(fr==bg) fr = AltWhiteColor;//just in case there aren't enough colors for players and board
						}
						else if (owner(x, y) == 1) {
							fr = CPlayer1;
							if(fr==bg) fr = AltBlackColor;
						} else fr = 15;
					}
				} else fr = 15;
					Color(bg, fr);

					if (n==(int)(squareH-1)/2) {
						char* name=PieceName(board[x][y]);
						if (strlen(name)>squareW) ErrorMsg(__COUNTER__, "Piece name too long for colomn width");
						int leftSpacing = squareW-strlen(name);//howmuch space is not occupied with name
						for (int m = 0; m < leftSpacing/2; m++) {
							printf(" ");
						}
						leftSpacing=leftSpacing-leftSpacing/2;
						printf("%s", name);//print piece
						for (int m = 0; m < leftSpacing; m++) {
							printf(" ");
						}
					} else {
						for (int m = 0; m < squareW; m++) {
							printf(" ");
						}
					}
					Color(0,15);//nocolor
					if(divider==1) printf("|");

			}
			printf("\n");
		}
	}
	if (divider!=0) {
		printf("  ");
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
		printf("Linux");
	#elif defined(_WIN32) || defined(WIN32)
		printf("Windows");
	#else
		printf("something this wasn't intended to work on!");
	#endif
	printf("\n\n Written and stuff done and so on by Jack ");
	Color(0,15);
	char null;
	scanf(" %c", &null);
}

int ShowAiThoughts = 1;//displays info about ai during move
int AiMove(int aiplayer){
	int af, bf, cf, df =-1; //final positions
	int lastPlayerScore = 0;
	for (int a = 0; a < rangeY; a++) {
		for (int b = 0; b < rangeX; b++) {
			if (owner(a,b)!=aiplayer) continue;//can only move own pieces
			if (ShowAiThoughts==1) printf("\n found own piece at %d,%d  ", a, b);
			for (int c = 0; c < rangeY; c++) {
				for (int d = 0; d < rangeX; d++) {
					if(owner(c,d)!=aiplayer && 1==checkAllMoves( board, board[a][b], aiplayer, a, b, c, d)){//save move if valid and most points, rather more points than previous
//rand()%2-1 is there to also allow non slaying moves and provide unpredictability without sacrificing "intelligence"
//may add points for future opportunities and deduct points for possible piece losses later
						if (ShowAiThoughts==1) printf("can slay piece with value %d at %d %d", PieceScore(board[c][d]), c, d);
						int PieceValue = 0;
						for (int e = 0; e < rangeY; e++) {
							for (int f = 0; f < rangeX; f++) {//looking for enemie pieces that attack the position to move to
								if (owner(e,f)!=aiplayer && board[e][f]!=0 && checkAllMoves( board, board[e][f], owner(e,f), e, f, c, d)) {
									PieceValue = PieceScore(board[a][b]); // because piece may be lost (consider cover chains later, with both allies and enemies, possible chain lenghts and values)
								} else PieceValue = 0;//would not be lost
							}
						}
						if (lastPlayerScore < (PieceScore(board[c][d]) + rand()%3-1 - PieceValue)) {
							lastPlayerScore = PieceScore(board[c][d]);
							//saving move
							af = a;
							bf = b;
							cf = c;
							df = d;
						}
					}
				}
			}
		}
	}
	if (af==-1 || bf==-1 || cf==-1 || df==-1) {
		ErrorMsg(__COUNTER__, "Ai failed to find good move");
	}
	if(ShowAiThoughts==1) printf("\n Moving piece %s from %d,%d to %d,%d\n", PieceName(board[af][bf]), af, bf, cf, df);
	MovePiece(board, af, bf, cf, df, 1); // doesn't yet work correctly
	return 1;
}

int playerMove(int player){
	printf("choose piece: ");
	int inputx=-1; int inputy=-1;
	while(2 != scanf(" %d,%d", &inputx, &inputy) || inputx>=rangeX || 0>inputx  ||  inputy>=rangeY || 0>inputy || owner(inputx, inputy)!=player){ //check for input validity as long as
		//not valid coordinates, out of bounds or not own
		Color(0,4);//KRED
		printf("\nnot a valid piece that you own");
		Color(0,15);//nocolor
		printf("\nplease check your input: ");
	}
	//better save than sorry, checking the second time
	if(inputx<=rangeX && 0<=inputx  &&  inputy<=rangeY && 0<=inputy){//in bounds
		if(owner(inputx, inputy)==player){//checking ownership
			printBoard(inputx, inputy, player);
			int possMoves = 0;
			for (int y = 0; y < rangeY; y++) {
				for (int x = 0; x < rangeX; x++) {
					possMoves = possMoves + checkAllMoves( board, board[inputx][inputy], player, inputx, inputy, x, y);
				}
			}
			printf("possible moves = %d, choose destination (x,y): ", possMoves);
			int xpos=inputx; int ypos=inputy;
			inputx=-1; inputy=-1;//resetting for new input to not trigger returning to selection
			while (0==checkAllMoves( board, board[xpos][ypos], player, xpos, ypos, inputx, inputy)) {
				while (2 != scanf(" %d,%d", &inputx, &inputy) || player == owner(inputx, inputy) || inputx>=rangeX || 0>inputx  ||  inputy>=rangeY || 0>inputy) {//second check includes check for no movment
					if(inputx==xpos && inputy==ypos){//opens dialog to go back
						//might add actual commands in the future to access menu and other things in the future
						printf("\nSwitch piece? (y/n) ");
						char input;
						scanf(" %c", &input);
						if(input == 'y' || input == 'Y'){
							printf("\nreturning to piece selection\n");
							printBoard( -1, -1, player);
							return playerMove(player);
						}
						printf("\n canceled\n");
					}
					printf("\ninvalid, check again: ");
				}
			}
			//if succeded, execute movement
			MovePiece(board, xpos, ypos, inputx, inputy, 0);
			return 1;
		}
	}
	ErrorMsg(__COUNTER__, "unknown error");
	return 0;
}

int GameOver(int Status){
	ClearScreen();
	printf("GAME OVER\n\nWinner: Player %d", Status);
	return Status;//makes no sense right now... but i could make some operations with it here before sending it back...
}

void AivsAI() {//mostly for debugging and fun, not an actual mode really...
	int player=0;
	int Status=0;
	while (1) {
		AiMove(player);
		Color(0,15);
		printf("player %d, %s           ", player, PlayerName(player));
		Status = checkBoard(player);
		printBoard( -1, -1, -1);//prints just the board, no other information like moves
		getch();
		player= (player +1)%playernum;
	}
}

int play(int player, int numTurns, int aiplayer){
	Color(0,15);
	printf("player %d, %s           ", player, PlayerName(player));
	checkBoard(player);//checks for status, such as checkmate
	Color(0,15);//nocolor
	printBoard(-1, -1, player);
	printf("Your Move! (x,y)\n");
	//AiMove(player);
	//getch();

	if (player==aiplayer) {
		AiMove(player);
	} else {
		playerMove(player);
	}

	checkBoard(player);//checks for status, such as checkmate
	ClearScreen();
	if(Status!=0) 	return GameOver(Status);

	if(numTurns==-1) return 0;//debuging and inital moves
	return play((player + 1) % playernum, numTurns + 1, aiplayer); //may not use numTurns, but would be a nice feature for stats
}

int Rochade0 = 0;//set 1 if done, was in check or moves through check
int Rochade1 = 0;
void beginPlay(int ai){// will become settings for the ai and player
	Rochade0 = 0; Rochade1 = 0;
	for (int n = 0; n < playernum; n++) {
		PlayerScores[n] = 0;//reset scores for all players
	}
	SetBoard();
	play(0, 0, ai);
}

void settings(){
	ClearScreen();
	Color(1, 15);
	int input;
	while(0!=input){
		printf("settings:\n\n 0. RETURN\n ");
		printf(" 6. Show Ai thoughts: %d\n 7. Divider: %d\n 8. Show coordinates: %d\n 9. \n\n", ShowAiThoughts, divider, coords);
		scanf(" %d", &input);
		switch (input) {
			case 0://breaks the while loop by itself
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
				///////////////////////
			case 6:
				ShowAiThoughts = (ShowAiThoughts + 1)%2;
				break;
			case 7:
				divider = (divider + 1)%2;
				break;
			case 8:
				coords = (coords + 1)%2;
				break;
			case 9:
				break;
			default:
				printf("\n didn't understand that, try again\n");
		}
		ClearScreen();
	}
}

void Rainbow(char * string, int bg) {
	int k = rand()%16;
	for (int i = 0; i < strlen(string); i++) {
		if ((i + k)%16==bg) k++;
		Color(bg, (i + k)%16);
		printf("%c", string[i]);
	}
	Color(0,15);
}

#include "extrafilefeatures.c" //for importing and exporting settings and stuff like that

int main(){
	Init();
	debug();// solely for testing purposes
	ClearScreen();
	int input = 10;
	while (0!=input) {
		Color(0,15);
		Rainbow("\n CHESS SIM FOR C-COURSE!\n\n", 0);
		Color(15, 11);
		printf("Do not write any non-number characters apart from the comma ',' symbol\n Also this Game works best with a num-pad\n");
		Color(0, 15);
		printf("\n 1. play 2player mode\n 2. play as white agains ai\n 3. play as black agains ai\n");
		if (0) printf(" 4. view last board/Continue\n"); // to be edited
		printf(" 8. settings \n 9. credits \n press 0 to quit\n");
		int output = 0;
		while(output==0){
			 output = scanf(" %d", &input);
		};

		switch (input){
			case 0:
				goto eof;
				break;
	 		case 1:
				ClearScreen();
	 			beginPlay(-1);
	 			break;
	 		case 2:
				ClearScreen();
	 			beginPlay(1);
	 			break;
			case 3:
				ClearScreen();
				beginPlay(0);
				break;
			case 4://hidden and mostly for debuging i guess
				ClearScreen();
				SetBoard();
				AivsAI();
				break;
	 		case 8:
				settings();
	 			break;
	 		case 9:
	 			credits();
	 			break;
	 		default:
				Color(0,4);//KRED
	 			printf("\nnot an option ^^\n");
				Color(0,15);//nocolor
		}
		ClearScreen();
	}

eof:
	printf("BYE\n");
	getch();
}
