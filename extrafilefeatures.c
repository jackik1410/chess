int importBoard(){
  /*
	char * filepath = "";
	printf("\n Choose file to open");
	scanf("%s\n", filepath);
	FILE *file = fopen(filepath, "r");
	while (NULL==file) {
		printf("\n No file found, enter 'exit' to cancel");
		if(0== strcmp(filepath, "exit")) return 0;
		scanf("%s\n", filepath);
		file = fopen(filepath, "r");
	}
	char* filedate = "aeons ago";
		fscanf(file, "Game compiled on: %s\n", filedate);
		if (0!=strcmp(filedate, __DATE__)) {
			printf("possibly incompatible file, file is intended for versions compiled on %s, while this was compiled on %s\n returning to menu\n", filedate, __DATE__ );
			return 0;
		}
		fscanf(file, "Player 0 as %s\nPlayer 1 as %s\n", player0name, player1name);
	printf("Found and opened!\n");//well, i'll have to decide on a format then won't i?
  */

  if(logging==1) debuglog("attempting to import board");
  ClearScreen();
  printf("Enter File name to import (will lose current board):\n");
  char filename [200];
  FILE * file = NULL;
  while (file==NULL) {
    scanf(" %s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
  }
  printf("opened file, now copying board...\n");
  //extracting from file
  char* Date="";
  fscanf(file, "Game compiled on: %s\n", Date);
  if(0!=strcmp(__DATE__, Date)) {
    printf("File was exported for another game version,\n do you want to still attempt reading it (y/n)?");
    char* input = "";
    scanf("%s\n", input);
    if (0!=strcmp(input, "y")) {
      return 0;//if not y, then default to no
    }
  }
  fscanf(file, "Player 0 as %s\nPlayer 1 as %s\n", player0name, player1name);
  int player=-1;//not sure how to pass that to play()
  fscanf(file, "Current players turn: %d\n", &player);
  for (int y = 0; y < rangeX; y++) {
    for (int x = 0; x < rangeY; x++) {
      fscanf(file, "%d ", &board[x][y]);
    }
    fscanf(file, "\n");//should look like~ board in the file
  }
  fclose(file);
  printf("exported board, returning now\n");

  if(logging==1) debuglog("successfully exported board, starting play");
  int turns=0; int aiplayer=-1;//both not yet read or written
  play(player, turns, aiplayer);
	return 1;//only if found and imported!!
}

int exportBoard(int player, int board[rangeX][rangeY]){
  if(logging==1) debuglog("attempting to export board");
	ClearScreen();
	printf("Enter File name to save as (overwrites without warning!):\n");
	char filename [200];
	FILE * file = NULL;
	while (file==NULL) {
    scanf(" %s", filename);
    strcat(filename, ".txt");
    file = fopen(filename, "w");
	}
  printf("opened file, now copying board...\n");
	//writing to file
  printf("Game compiled on: %s\n", __DATE__);
	fprintf(file, "Game compiled on: %s\n", __DATE__);
	fprintf(file, "Player 0 as %s\nPlayer 1 as %s\n", PlayerName(0), PlayerName(1));
  fprintf(file, "Current players turn: %d\n", player);
	for (int y = 0; y < rangeX; y++) {
		for (int x = 0; x < rangeY; x++) {
			fprintf(file, "%d ", board[x][y]);
		}
    fprintf(file, "\n");//should look like~ board in the file
	}
  fclose(file);
  printf("exported board, returning now\n");

  if(logging==1) debuglog("successfully exported board");
	return 1;//should be for successful translation...
}
