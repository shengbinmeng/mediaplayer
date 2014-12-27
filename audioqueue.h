#ifndef __AUDIOQUEUE_H__
#define __AUDIOQUEUE_H__

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

struct AudioData {
    uint32_t data_size;
	uint8_t* pcm_data;
	AudioData *next;
};

class AudioQueue {
public:
	AudioQueue();
	~AudioQueue();

	void flush();
	int put(AudioData *ad);

	/* return < 0 if aborted, 0 if no packet and > 0 if packet.  */
	int get(AudioData **ad, bool block);

	int size();

	void abort();

private:
	AudioData* mFirst;
	AudioData* mLast;
	int mSize;
	bool mAbortRequest;
	pthread_mutex_t mLock;
	pthread_cond_t mCondition;
};

#endif
