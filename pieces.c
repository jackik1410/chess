//not used !
void place(int piece, int player, int x, int y){
	board[x][y] = piece + 6*player;//can be done directly anyway...
}

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

	ErrorMsg(__COUNTER__);
	return 3;
}

int checkAllMoves(int content, int player, int posX, int posY, int moveX, int moveY) {
		// target position on board is already checked! No invalid (off board) coordinates passed.
	if(posX==moveX && posY==moveY) return 0;//check for no move
	if(owner(posX, posY)!=player) {//shouldn't happen
		Color(0,4);//KRED
		printf("\nnot your piece!\n");
		Color(0,15);//nocolor
		ErrorMsg(__COUNTER__);//probably artificial input, such as an error in checkBoard()
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

	int piece = content%6;//ingores player
	int deltaX = moveX-posX;//for checking moves
	int deltaY = moveY-posY;

	switch (piece) { //checking moves for all pieces
					//remember checking for path for other pieces and collisions!!!
		case 0://pawn 6 12
			if (deltaX == 0) {
				if( ((player == 0)&&(deltaY==-1)) || ((player == 1)&&(deltaY==1))){
					return 1;//normal move forward
				} else {
					if((player == 0 && posY==6 && deltaY==-2) || (player==1 && posY==1 && deltaY==2)){//double move if not moved
						return 1;
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
		case 4://queen 4 10
				//other option much easier!  rook+bishop as if-else
				//maybe define them as separate functions to do so?
				//or is there a better way to loop it?
				if (1==checkAllMoves(1+6*player, player, posX, posY, moveX, moveY) || 1==checkAllMoves(3+6*player, player, posX, posY, moveX, moveY)){//check details for rook and bishop movement
					return 1;
				}
				return 0;
			break;
		case 1://rook 1 7
			if((deltaX==0 && deltaY!=0) || (deltaY==0 && deltaX!=0)) {//check if movement is only along 1 axis
				int delta=deltaX+deltaY;
				for (int n = 1; n < delta; n++) {//check for path
					if(board[deltaX/delta * n][deltaY/delta * n]==0){
						continue;
					} else return 0;
				}
				if(owner(moveX, moveY)==player) return 0;
				return 1;
			} else return 0;
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
		default:
			Color(0,4);//KRED
			printf("\n error checking move! (piece not found)\n");
			printf("piece num = %d\n", piece%6);
			ErrorMsg(__COUNTER__);
			Color(0,15);//nocolor
			return 0;
	}
	Color(0,4);//KRED
	printf("\n error checking move!\n");
	Color(0,15);//nocolor
	return 0;

}

int PlayerScores[2];//number will be variable later using playernum
//is set 0 before a match
void PieceScore(int piece, int player){//maybe later used for AI
	if (piece!=0&&piece<=12) {//check if valid piece
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
				ErrorMsg(__COUNTER__);
		}
		PlayerScores[player] += score;
	} else ErrorMsg(__COUNTER__);
}
