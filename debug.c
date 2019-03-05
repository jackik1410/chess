
void colordemo(){
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			Color(j,i);
			printf("Test i=%d j=%d\n", i, j);
		}
	}
}

void BreakError() {//for quick testing
  printf("\n Broken!!!\n");
  getch();
}


void debug(){ // not recommended, may not work
	//put your code here and it will run before anything else
	//system("COLOR 9C");

	//colordemo();
	//getch();
	//debugboard();
	//printBoard();
	//playerMove(0);
	//getch();

	//checkAllMoves(6, 0);

	//getch();
	//ClearScreen();


	//colordemo();
}

void debugboard(){
	board[3][3] = 5;
	board[3][4] = 6;
	board[3][5] = 11;
	/*
	board[][] = ;
	board[][] = ;
	board[][] = ;
	board[][] = ;
	board[][] = ;
	*/
}
