int importBoard(){
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
		fscanf(file, "Player 0 as %s\nPlayer 1 as %s\n", &player0name, player1name);
	printf("Found and opened!\n");//well, i'll have to decide on a format then won't i?
	return 1;//only if found and imported!!
}

int exportBoard(){
	ClearScreen();
	printf("Enter File name to save as (overwrites without warning!):\n");
	char * filename = "";
	FILE * file = NULL;
	while (file==NULL) {
		while (strcmp(filename, "")) {
			scanf("%s\n", filename);
		}
    file = fopen(filename, "w");
	}
	//writing to file
	fprintf(file, "Game compiled on: %s\n", __DATE__);
	fprintf(file, "Player 0 as %s\nPlayer 1 as %s\n", PlayerName(0), PlayerName(1));
	for (int x = 0; x < rangeX; x++) {
		for (int y = 0; y < rangeY; y++) {
			fprintf(file, "%s\n", "nothing to see here! ...(yet)" );
		}
	}
	return 1;//should be for successful translation...
}
