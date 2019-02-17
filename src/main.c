#include "play.h" 


int main(int argc, char *argv[]) {
	if(argc == 1)
		return -1;
	
	init_audio();
	init_screen();
	play_loop(argv[1]);
	end();	

	return 0;

}
