#include "BGMusic.h"

BGMusic::BGMusic(std::string filename){
	song = new GE161::Audio(filename, GE161::Audio::Type::MUSIC);
	attachComponent("Audio", song);
	song->play(-1);
}

void BGMusic::update(){
	if (song)
		song->~Audio();
}

void BGMusic::destroy(){

}