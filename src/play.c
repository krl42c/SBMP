#include "play.h"

void init_audio() {
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096); 
	Mix_Init(MIX_INIT_MP3); 
}

void init_screen() {
	initscr();
	cbreak();
	noecho();
	move(0,0);
	addstr("SIMPLE BORING MP3 PLAYER\n\n");
	addstr("Keybindings: \nSPACE: Pause/Resume\n"); 
}

void play_loop(const char* file_name) {
	int playing = 0;
	int paused = 0;
	
	Mix_Music *music = Mix_LoadMUS(file_name);

	Mix_PlayMusic(music,1); 
	while(playing == 0) {
		int ch = getch();
		switch(ch) {
			case 'q':
				playing = 1;
				break;
			case ' ':
				if(paused == 0) {
					Mix_PauseMusic();
					paused = 1;
				} else {
					Mix_ResumeMusic(); 
					paused = 0;
				}
				break;	

			case KEY_UP:
				break;

			case KEY_DOWN:
				break;
		}
	}
}


void end() {
	SDL_Quit();
	endwin();

}
