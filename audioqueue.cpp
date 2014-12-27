#include "audioqueue.h"
#include "player_utils.h"

#define LOG_TAG "AudioQueue"

AudioQueue::AudioQueue() {
	pthread_mutex_init(&mLock, NULL);
	pthread_cond_init(&mCondition, NULL);
	mFirst = NULL;
	mLast = NULL;
	mSize = 0;
	mAbortRequest = false;
}

AudioQueue::~AudioQueue() {
	flush();
	pthread_mutex_destroy(&mLock);
	pthread_cond_destroy(&mCondition);
}

int AudioQueue::size() {
	pthread_mutex_lock(&mLock);
	int size = mSize;
	pthread_mutex_unlock(&mLock);
	return size;
}

void AudioQueue::flush() {
	pthread_mutex_lock(&mLock);

	AudioData *ad, *ad1;
	for (ad = mFirst; ad != NULL; ad = ad1) {
		ad1 = ad->next;
		free(ad->pcm_data);
		free(ad);
	}

	mLast = NULL;
	mFirst = NULL;
	mSize = 0;

	pthread_mutex_unlock(&mLock);
}

int AudioQueue::put(AudioData *ad) {
	pthread_mutex_lock(&mLock);

	if (mLast == NULL) {
		mFirst = ad;
	} else {
		mLast->next = ad;
	}

	ad->next = NULL;
	mLast = ad;
	mSize++;

	pthread_cond_signal(&mCondition);
	pthread_mutex_unlock(&mLock);
	return 0;
}

// return < 0 if aborted, 0 if got and > 0 if empty
int AudioQueue::get(AudioData **ad, bool block) {
	int ret = 0;

	pthread_mutex_lock(&mLock);

	for (;;) {
		if (mAbortRequest) {
			ret = -1;
			break;
		}

		*ad = mFirst;
		if (*ad) {
			mFirst = (*ad)->next;
			if (mFirst == NULL) {
				//queue empty
				mLast = NULL;
			}
			mSize--;
			ret = 0;
			break;
		} else if (!block) {
			ret = 1;
			break;
		} else {
			pthread_cond_wait(&mCondition, &mLock);
		}
	}

	pthread_mutex_unlock(&mLock);
	return ret;

}

void AudioQueue::abort() {
	pthread_mutex_lock(&mLock);
	mAbortRequest = true;
	pthread_cond_signal(&mCondition);
	pthread_mutex_unlock(&mLock);
}
