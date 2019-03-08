
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

	//for (int i = 0; i < 20; i++) printf("%d\n", rand()%2-1);

	//colordemo();
	//getch();
	//debugboard();
	//printBoard(3,4,owner(3, 4));
	//getch();
	//play(0,0,-1);
	//getch();

	//checkAllMoves(6, 0);

	//getch();
	//ClearScreen();


	//colordemo();
}

void debugboard(){
	board[3][0] = 11;
	board[3][3] = 12;
	board[3][4] = 4;
	board[3][7] = 5;
	/*
	board[][] = ;
	board[][] = ;
	board[][] = ;
	board[][] = ;
	board[][] = ;
	*/
}

int importBoard(){
	printf("\n Choose file to open");
	char * file = "";
	scanf("\n", &file);
	//fopen(file);
	return 1;//only if found and imported!!
}
