#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <ncurses.h>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <iostream>
#include <algorithm>
#include <random>


bool end_player = false;
std::vector<std::string> files;

void init_audio() {
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096);
	Mix_Init(MIX_INIT_MP3);
}

void init_screen() {
	initscr();
	cbreak();
	noecho();
	move(0,0);
	addstr("SIMPLE BORING MP3 PLAYER\n\nKEYBINDINGS: \nSPACE: Pause/Resume\nN: NEXT SONG\nQ: QUIT\nR: Randomize songs\nSONG LIST:\n\n");

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
	bool playing = true;

	Mix_Music *music;
	music = Mix_LoadMUS(file_name.c_str());

	Mix_PlayMusic(music,1);

	while(playing) {
		int ch = getch();
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

			case 'n':
				playing = false;
				break;
			case 'r':
				randomize_files();
				break;
		}
	}
}

int main(int argc, char* argv[])
{
	if(argc == 1) {
		std::cout << "SBMP \n sbmp [music_directory] \n";
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
