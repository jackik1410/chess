//backup plan:
void CollisionAlert(){ //I know it's not worth it to be it's own function ^^
	Color(0,4);//KRED
	printf("\ncollision with your own piece!\n");
	Color(0,15);//nocolor
}


int owner(int x, int y) {
	if (board[x][y] == 0) return 3;//shouldn't happen

	if (board[x][y] <=6 && board[x][y] >=1){
		return 0;
	}
	else if (board[x][y] >=7 && board[x][y] <=12){
		return 1;
	}

	ErrorMsg(__COUNTER__, "error checking piece ownership at ");	printf("%d %d \n", x, y);
	return 3;
}

int checkAllMoves(int content, int player, int posX, int posY, int moveX, int moveY) {
		// target position on board is already checked! No invalid (off board) coordinates passed.
	if(posX==moveX && posY==moveY) return 0;//check for no move
	if(owner(posX, posY)!=player) {//shouldn't happen
		Color(0,4);//KRED
		printf("\nnot your piece!\n");
		Color(0,15);//nocolor
		ErrorMsg(__COUNTER__, "unknown error");//probably artificial input, such as an error in checkBoard()
		return 0;
	}
	if(owner(moveX, moveY)==player) return 0;//check if slaying own piece
	if (content == 0) {//shouldn't happen
		Color(0,4);//KRED
		printf("\nempty square\n");
		Color(0,15);//nocolor
		return 0;
	}

	//check if move leads to check for current play, then deny move

	int deltaX = moveX-posX;//for checking moves
	int deltaY = moveY-posY;

	switch (content%6) { //checking moves for all pieces, ignoring player
					//remember checking for path for other pieces and collisions!!!
		case 0://pawn 6 12
			if (deltaX == 0) {
				if( ((player == 0)&&(deltaY==-1)) || ((player == 1)&&(deltaY==1))){
					if (board[moveX][moveY]==0) {//checking for collision on normal move
						return 1;//normal move forward
					}
					return 0;//collision
				} else {
					if((player == 0 && posY==6 && deltaY==-2) || (player==1 && posY==1 && deltaY==2)){//double move if not moved
						if (board[moveX][moveY]==0) {//checking for collision on normal move
							return 1;//double move forward
						}
						return 0;//collision
					}
				return 0;
				}
			}
			if (Betrag(deltaX) == 1 && ((player==0 && deltaY==1) || (player==1 && deltaY==-1)) ) {//check for enemy piece taking
				if (board[moveX][moveY] != 0 && owner(moveX, moveY) != player) return 1; //slay piece if move valid, piece there and not your piece
			}
			return 0;
			break;
		case 5://king 5 11
			if((-1<=deltaX && deltaX<=1) && (-1<=deltaY && deltaY<=1)){
				return 1;
			}
			if (deltaY==0) {
				/* code */
			}
			return 0;
			break;
		case 4://queen 4 10, check rook and bishop for movment
				if (1==checkAllMoves(1+6*player, player, posX, posY, moveX, moveY) || 1==checkAllMoves(3+6*player, player, posX, posY, moveX, moveY)) return 1;//check details for rook and bishop movement
				return 0;
			break;
		case 1://rook 1 7
			if((deltaX==0 && deltaY!=0) || (deltaY==0 && deltaX!=0)) {//check if movement is only along 1 axis
				int delta=Betrag(deltaX+deltaY);//equals movement, as one of them is 0
				//printf("\nBetrag = %d", delta);
				for (int n = 1; n < delta; n++) {//check for path but not final position
					if(board[deltaX/delta * n + posX][deltaY/delta * n + posY]!=0) return 0;
					//printf("  n = %d, x= %d, y= %d\n", n, deltaX/delta * n + posX, deltaY/delta * n + posY);
				}
				if(owner(moveX, moveY)==player) return 0; //can't move if own piece, only if empty or enemy
				return 1;
			}
			return 0;
			break;
		case 2://knight = Springer  2 8
			if( (Betrag(deltaX)==1 && Betrag(deltaY)==2) || (Betrag(deltaX)==2 && Betrag(deltaY)==1) ){
				if(board[moveX][moveY]==0) { //check collision
					return 1;
				}else{
					return 0;
				}
			} else return 0;
			break;
		case 3://bishop 3 9
			if(Betrag(deltaX)==Betrag(deltaY) && deltaX!=0){//check basic validity
				int dx = deltaX / Betrag(deltaX); //needed for iterative square check
				int dy = deltaY / Betrag(deltaY);
				int distance = Betrag(deltaX);
				for (int n = 1; n < distance; n++) {
					if (board[dx*n + posX][dy*n + posY] != 0) return 0; //cancel on finding obstacle (not include final position)
				}
				if (owner(moveX, moveY) != player) return 1;//only slay pieces if final location not own piece!
			}
			return 0;//invalid move
			break;
		default:
			Color(0,4);//KRED
			printf("\n error checking move! (piece not found)\n");
			printf("piece num = %d\n", content);
			ErrorMsg(__COUNTER__, "unknown error");
			Color(0,15);//nocolor
			return 0;
	}
	ErrorMsg(__COUNTER__,"error checking move!");
	return 0;

}

int PlayerScores[2];//number will be variable later using playernum
//is set 0 before a match
int PieceScore(int piece){//maybe later used for AI
	if (piece>0&&piece<=12) {//check if not empty square
		int score = 0;
		switch (piece%6) {
			case 0://pawn
				score = 1;
				break;
			case 1://rook
				score = 5;
				break;
			case 2://knight Springer
				score = 3;
				break;
			case 3://bishop
				score = 3;
				break;
			case 4://queen
				score = 9;
				break;
			case 5://king
				score = 10000;//infty really, but meh
				break;
			default:
				ErrorMsg(__COUNTER__, "faulty piece or no score for piece");
		}
		return score;
	} else return 0;
}


//Kingposition[player][coordinate(x or y)]
void findKings(int player, int *a, int *b){// run this if not up to date anymore
	for (int x = 0; x < rangeX; x++) {
		for (int y = 0; y < rangeY; y++) {
			if(board[x][y]%6 == 5 && owner(x, y)==player){
				*a = x;
				*b = y;
				break;
			}
		}
	}
}

int TryMove(int player, int depth){//for a more advanced ai

	return TryMove( player, depth+1);
}

int MovePiece(int x, int y, int a, int b, int ifaiplayer){
	if(board[a][b]!=0){//no score if empty
		if(owner(x,y)==owner(a,b)) ErrorMsg(__COUNTER__, "slaying own piece!");//safety
	}
	int slainpiece = board[a][b];
	int slayingpiece = board[x][y];
	int player = owner(x, y);

		//moving pieces for now, can return them if not valid
	board[a][b]=board[x][y];//moving
	board[x][y]=0;//deleting

	int Kingx; int Kingy; findKings(player, &Kingx, &Kingy);

	for (int xtest = 0; xtest < rangeX; xtest++) {
		for (int ytest = 0; ytest < rangeY; ytest++) {
			if(owner(xtest, ytest)!=player) {
				//printf("not checked\n");
			} else {
				//printf("could check? testing now\n");
				if(1==checkAllMoves( board[xtest][ytest], owner(xtest, ytest), xtest, ytest, Kingx, Kingy)) {
					//printf("is checking!!!\n");
					//returning pieces
					board[a][b] = slainpiece;
					board[x][y] = slayingpiece;
					if (ifaiplayer!=1) {
						Color(0, 4);
						printf("Can not move, moving into check position\n");
						Color(0, 15);
					}
					return 0;
				}
			}
		}
	}


	//moving and changing score only after found not moving into check position
	PlayerScores[owner(x,y)] += PieceScore(board[a][b]);//attributing score
}
