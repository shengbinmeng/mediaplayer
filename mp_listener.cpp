#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "mp_listener.h"
#include "player_utils.h"

#define LOG_TAG "mp_listener"

VideoFrame *gVF;
void *gAudioData;
int gAudioDataSize;

MediaPlayerListener::MediaPlayerListener() {
	gAudioData = NULL;
	gAudioDataSize = 0;
	gVF = NULL;
}

MediaPlayerListener::~MediaPlayerListener() {
	if (gVF != NULL) {
		free(gVF->yuv_data[0]);
		free(gVF);
		gVF = NULL;
	}
	if (gAudioData != NULL) {
		free(gAudioData);
		gAudioData = NULL;
	}
}

void MediaPlayerListener::postEvent(int msg, int ext1, int ext2) {
	LOGD("post a message: %d \n", msg);
	if (msg == 909) {
		LOGI("end of playing \n");
	}
}

int MediaPlayerListener::audioTrackWrite(void* data, int offset, int data_size) {
	if (data == NULL) {
		return 1;
	}
	if (data_size > gAudioDataSize) {
		if (gAudioData != NULL) {
			free(gAudioData);
			gAudioData = NULL;
		}
		gAudioData = malloc(data_size);
		gAudioDataSize = data_size;
	}
	memcpy(gAudioData, data, data_size);	
	
	LOGD("write to audio track: %d bytes \n", data_size);
	// TODO: Actually write gAudioData.
	
	return 0;

}

int MediaPlayerListener::drawFrame(VideoFrame *vf) {
	if (vf == NULL) {
		// Post the finish message.
		postEvent(909, 0, 0);
		return 1;
	}
	
	if (gVF != NULL) {
		free(gVF->yuv_data[0]);
		free(gVF);
		gVF = NULL;
	}
	gVF = vf;
	
	LOGD("draw a frame: %lf \n", gVF->pts);
	// TODO: Actually draw gVF.
	
	return 0;
}
