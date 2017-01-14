#ifndef __AUDIO_DECODER_H__
#define __AUDIO_DECODER_H__

#include "Decoder.h"
extern "C" {
#include "libswresample/swresample.h"
#include "libavutil/opt.h"
}

typedef void (*AudioDecodingHandler)(void*, int);

class AudioDecoder: public Decoder {
public:
	AudioDecoder(AVStream* stream);
	~AudioDecoder();

	AudioDecodingHandler onDecoded;
	double mAudioClock;
	double mAudioPts;

private:
	SwrContext *mSwrContext;
	void* mSamples;

	int decode(AVPacket *packet);
};

#endif
