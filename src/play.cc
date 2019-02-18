#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <ncurses.h>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <iostream>
#include <algorithm>
#include <random>
#include <future>

Mix_Music *music;
std::vector<std::string> files;

bool playing = true;
bool end_player = false;

void init_audio() {
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096); 
	Mix_Init(MIX_INIT_MP3); 
}

void init_screen() {
	initscr();
	cbreak();
	noecho();
	move(0,0);
	addstr("SIMPLE BORING MP3 PLAYER\n\nKEYBINDINGS: \nSPACE: Pause/Resume\nN: NEXT SONG\nQ: QUIT\n\nSONG LIST:\n\n");

	for(auto &i : files) {
		addstr(i.c_str());
		addch('\n'); 
	}
}

void end() {
	SDL_Quit();
	endwin();
}

void file_list(std::string path) {
	namespace fs = std::experimental::filesystem;
	std::string file_aux;

	for(const auto &entry : fs::directory_iterator(path)) {
		file_aux = entry.path();
		if(file_aux.find(".mp3") != std::string::npos)
			files.push_back(entry.path());
	}
}

void randomize_files() {
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(files), std::end(files), rng);
}

void play_loop(std::string file_name) {
	bool paused = false;
	playing = true;
	
	music = Mix_LoadMUS(file_name.c_str());

	Mix_PlayMusic(music,1); 
	while(playing ) {
		int ch = getch();
		std::future<void> music_finished(std::async([&]() {while(Mix_PlayingMusic() == 1 && playing) { };  playing = false; } ));

		switch(ch) {
			case 'q':
				playing = false;
				end_player = true;
				break;
			case ' ':
				if(!paused) {
					Mix_PauseMusic();
					paused = true;
				} else {
					Mix_ResumeMusic(); 
					paused = false;
				}
				break;	

			case KEY_UP:
				playing = false;
				break;

			case KEY_DOWN:
				break;

			case 'n':
				playing = false;
				break; 
		}
	}
}

void print_help() {
	std::cout << "SBMP \nsbmp [music_directory] \n"; 
}

int main(int argc, char* argv[]) 
{
	if(argc == 1) {
		print_help(); 
		return -1; 
	}

	std::string path(argv[1]); 
	file_list(path);
	init_audio();
	init_screen();
	for(auto &i : files) {
		if(end_player)
			break;
		play_loop(i); 
	}
       	end();
	return 0;
}
