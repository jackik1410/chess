/*
//using the integer method now!

typedef struct pieces{
	char name;
	int player;
	int points; //for optinoal points counter
	struct move{
		// function instead?
	};
} piece;

//points counter for pieces?
//aditional data type for pieces required
//deconstructer to add points to players

struct pieces empty = {
	.name=' '
};

struct pieces pawn0 = {
	.name='p',
	.player=0,
	.points=1
};
struct pieces pawn1 = {
	.name='p',
	.player=1,
	.points=1
};

struct pieces king0 = {
	.name='k',
	.player=0
};
struct pieces king1 = {
	.name='k',
	.player=1
};
struct pieces rook0 = {
	.name='r',
	.player=0
};
struct pieces rook1 = {
	.name='r',
	.player=1
};
*/

// function pointer to movement functions that check movement validity?

/*			//deprecated...
int pawn(int Xpos, int Ypos, int Xmove, int Ymove, void* Board){
	//check if simple move forward and if space empty
		//return 1
	//else check if diagonal and if enemy piece there
		//if so, delete piece and move to square
			//return 1
	//return 0 otherwise, invalid move
}
*/

//where Board is an array pointing to Null or a piece


//not used !
void place(char piece, int player, int x, int y){

	//board[x][y] =
}





//backup plan:
void CollisionAlert(){ //I know it's not worth it to be it's own function ^^
	Color(0,4);//KRED
	printf("\ncollision with your own piece!\n");
	Color(0,15);//nocolor
}


int owner(int x, int y) {
	if (board[x][y] == 0) return 3;

	if (board[x][y] <=6){
		return 0;
	}
	else {
		return 1;
	}

}

int checkAllMoves(int content, int player, int posX, int posY, int moveX, int moveY) {
		// target position on board is already checked! No invalid (off board) coordinates passed.

	if (content == 0) {
		Color(0,4);//KRED
		printf("\nempty square\n");
		Color(0,15);//nocolor
		return 0;
	}
	if(content<=6){int owner = 0;} else {int owner = 1;}
	if(((int)owner)!=((int)player)) {
		Color(0,4);//KRED
		printf("\nnot your piece!\n");
		Color(0,15);//nocolor
		return 0;
	}

	int piece = content%6;//ingores player
	int deltaX = moveX-posX;//for checking moves
	int deltaY = moveY-posY;


	switch (piece) { //checking moves for all pieces
					//remember checking for path for other pieces!!!
		case '0'://pawn 6 12
			if (deltaX == 0) {
				if( ((player == 0)&&(deltaY==1)) || ((player == 1)&&(deltaY==-1))){
					return 1;//normal move forward
				} else {
					if((player == 0 && posY==2) || (player==1 && posY==7)){//double move if not moved

				}

				return 0;
				}

			}
			else if (deltaX == 1 || deltaY == -1) {//check for enemy piece taking
				if (board[moveX][moveY] != 0 && owner(moveX, moveY) != player) return 1; //slay piece if move valid, piece there and not your piece
			}
			return 0;
			break;
		case '5'://king 5 11
			if((-1<=deltaX && deltaX<=1) && (-1<=deltaY && deltaY<=1)) return 1;
			break;
		case '4'://queen 4 10
				//other option much easier!  rook+bishop as if-else
				//maybe define them as separate functions to do so?
				//or is there a better way to loop it?
			break;
		case '1'://rook 1 7
			if((deltaX==0 && deltaY!=0) || (deltaY==0 && deltaX!=0)) {
				return 1;
			} else return 0;
			break;
		case '2'://bishop 2 8
			if(Betrag(deltaX)==Betrag(deltaY)){//check collision
				int dx = deltaX / Betrag(deltaX); //needed for iterative square check
				int dy = deltaY / Betrag(deltaY);
				int distance = Betrag(deltaX);
				for (int n = 1; n <= distance; n++) {
					if (board[dx*n][dy*n] == 0) continue;
					if (n == distance && owner(dx*n, dy*n) != player) return 1;//only slay pieces if on final location and not your piece!
					return 0;
				}

				return 1;//passed checks
			} else return 0;//invalid move
			break;
		case '3'://knight = Läufer  3 9
			if( (Betrag(deltaX)==1 && Betrag(deltaY)==2) || (Betrag(deltaX)==2 && Betrag(deltaY)==1) ){
				if(board[moveX][moveY]==0) { //check collision
					return 1;
				}else{
					return 0;
				}
			} else return 0;
			break;
		default:
		Color(0,4);//KRED
			printf("\n error checking move! (piece not found)\n");
			Color(0,15);//nocolor
			return 0;
	}
	Color(0,4);//KRED
	printf("\n error checking move!\n");
	Color(0,15);//nocolor
	return 0;

}
