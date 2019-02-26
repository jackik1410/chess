
void colordemo(){
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			Color(j,i);
			printf("Test i=%d j=%d\n", i, j);
		}
	}
}

void BreakError() {
  printf("\n Broken!!!\n");
  getch();
}

void debugPrintBoard(){
	for(int x=0; x<rangeX; x++) {
		printf("------");
	}
  printf("\n");

	//skiphSpaces(1);
	for(int y=0; y<rangeY; y++){
		for(int n=0; n<3; n++){//1 squre needs 3 lines, 2 lines blank and 1 with the pieces
			if(n=0){
        BreakError();
				Color(0,15);//nocolor
				for(int x=0; x<rangeX; x++) {//printing divider
					printf("------");
				}
				printf("\n");
			};//var x reset here

      printf("|");
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
						}
						else if (owner(x, y) == 1) {
							fr = CPlayer1;
						} else fr = 15;
					}
				} else fr = 15;
					Color(bg, fr);
					printf("	");

					if (n==1) {
					printChar(board[x][y]);//print piece
				} else printf(" ");

					printf("	");
					Color(0,15);//nocolor
					printf("|");

			}
		}

/*
		if(y+1==rangeY) {//print divider if there is another row
			printf("\n|");
			for(int x=0; x<rangeX; x++){
				printf("		 |");
			}
			printf("\n");
			for(int x=0; x<rangeX; x++) {
				printf("------");
			}
			printf("\n");
		} //else skiphSpaces(3);
*/
	}
}
