#include <unistd.h>
#include "MediaPlayer.h"

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage: %s <input_file>\n", argv[0]);
		exit(1);
	}
	char *filename = argv[1];
	
	MediaPlayer* player = new MediaPlayer();
	
	PlayerListener* listener = new PlayerListener();
	player->setListener(listener);
	
	player->open(filename);
	player->start();
	
	// Wait for the playing end.
	while (!listener->mPlayingEnd) {
		sleep(1);
	}
	
	player->stop();
	player->close();
	
	delete player;
	delete listener;
	
	return 0;
}
