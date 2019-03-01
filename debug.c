
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
