#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "mp_listener.h"
#include "player_utils.h"

#define LOG_TAG "mp_listener"

VideoFrame *gVF;
pthread_mutex_t gVFMutex;

static short *gShortArray;
static int gDataArraySize;

MediaPlayerListener::MediaPlayerListener() {
    gShortArray = NULL;
    gDataArraySize = 0;
	gVF = NULL;
	pthread_mutex_init(&gVFMutex, NULL);
}

MediaPlayerListener::~MediaPlayerListener() {

}

void MediaPlayerListener::postEvent(int msg, int ext1, int ext2) {
	LOGD("post a message: %d", msg);
}

int MediaPlayerListener::audioTrackWrite(void* data, int offset, int data_size) {
	if (data == NULL) {
		return -1;
	}
	int size = data_size / 2;
	if (gShortArray == NULL || gDataArraySize < size) {
		gShortArray = (short*)malloc(size);
		gDataArraySize = size;
	}
	LOGD("write to audio track: %d shorts \n", size);
	return 0;

}

int MediaPlayerListener::drawFrame(VideoFrame *vf) {
	pthread_mutex_lock(&gVFMutex);
	gVF = vf;
	pthread_mutex_unlock(&gVFMutex);

	if (gVF != NULL) {
		free(gVF->yuv_data[0]);
		free(gVF);
		gVF = NULL;
    }
    
    LOGD("draw a frame: %lf \n", vf->pts);
    return 0;
}
