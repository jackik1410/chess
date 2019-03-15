
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

void debug(){ // not recommended, may not work
	//put your code here and it will run before anything else
	//system("COLOR 9C");

	//for (int i = 0; i < 20; i++) printf("%d\n", rand()%2-1);

	//debuglog("Testing Log");
	//getch();

	// char cominput [100]= " 4,3";
	// scanf("%20s", cominput);
	// printf(cominput);
	//int inputx, inputy;
	//sscanf(cominput, " %d,%d", &inputx, &inputy);
	

	//ErrorMsg(1, "i wanted it to!");
	//debugboard();
	//AivsAI();

	//play(0,0,-1);

	//checkAllMoves(6, 0);

	//getch();
	//ClearScreen();

	//colordemo();
}
