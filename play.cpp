#include "mediaplayer.h"
#include "mp_listener.h"
#include "player_utils.h"

int main(int argc, char* argv[]) {

	if ( argc < 2 ) {
		fprintf(stderr, "no input file!\n");
		return 1;
	}
	char *filename = argv[1];
	
    MediaPlayer* mp = new MediaPlayer();
    
    // create new listener and give it to MediaPlayer
    MediaPlayerListener* listener = new MediaPlayerListener();
    mp->setListener(listener);
    
    mp->open(filename);
    mp->start();
    
    if (mp->wait() != 0) {
		perror("wait for playing failed \n");
		return 2;
	}
    
    return 0;
}