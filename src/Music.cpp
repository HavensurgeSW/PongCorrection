#include "Music.h"
Music gameMusic;

void loadMusic() {
	

	try{
		gameMusic = LoadMusicStream("../res/GameplayMusic.mp3");
	}
	catch (const std::exception&){
		cout << "Music not loaded / found" << endl;
	}
}