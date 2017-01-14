#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "PlayerListener.h"
#include "player_utils.h"

#define LOG_TAG "PlayerListener"

PlayerListener::PlayerListener() {
	mPlayingEnd = 0;
}

PlayerListener::~PlayerListener() {

}

void PlayerListener::postEvent(int msg, int ext1, int ext2) {
	if (msg == 909) {
        mPlayingEnd = 1;
	}
}

int PlayerListener::audioTrackWrite(void* data, int offset, int data_size) {
	if (data == NULL) {
		return -1;
	}
	LOGD("write to audio track: %d bytes\n", data_size);
	// The data buffer will be reused internally. Do not free it here.
	return 0;
}

int PlayerListener::drawFrame(VideoFrame *vf) {
	if (vf == NULL) {
		return -1;
	}
	
	LOGD("draw a frame: %lf\n", vf->pts);
	// Need to free the frame after using it.
	free(vf->yuv_data[0]);
	free(vf);
	return 0;
}
