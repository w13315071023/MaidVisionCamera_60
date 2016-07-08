#pragma once
#include "VideoClass.h"
#include "Tools.h"

USING_NS_CC;
class DemoVideoLayer :public VideoClass
{
public:
	char* filename;
	unsigned int videoStream;

	AVCodecContext *pCodecCtx;
	AVFormatContext *pFormatCtx;
	AVCodec *pCodec;
	AVFrame *pFrame, *pFrameRGB;
	struct SwsContext *pSwsCtx = NULL;
	AVPacket packet;
	int frameFinished;
	int PictureSize;
	uint8_t* buf;
public:
	~DemoVideoLayer();
	static DemoVideoLayer* create(int Direction);
	bool init(int Direction);
	bool LoadVideo();
};
