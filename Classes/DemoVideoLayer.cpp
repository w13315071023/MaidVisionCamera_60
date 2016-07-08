#include "DemoVideoLayer.h"
#include "DataMager.h"

DemoVideoLayer* DemoVideoLayer::create(int Direction)
{
	DemoVideoLayer *pRet = new DemoVideoLayer();
	if (pRet && pRet->init(Direction))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
DemoVideoLayer::~DemoVideoLayer()
{
}
bool DemoVideoLayer::init(int Direction)
{
	if (!CCLayer::init())
	{
		return false;
	}
	printf("³õÊ¼»¯DemoVideoLayer\n");
	videoStream = -1;
	pCodecCtx = NULL;
	pFormatCtx = NULL;
	packet = { NULL };
	filename = new char[64];
	//sprintf(filename,"C:\\Video\\C0004_500fps.MP4");
	sprintf(filename,
		"C:\\Video\\sucai%d-%d-%d.avi",
		DataMager::shareDataMager()->m_curGender,
		DataMager::shareDataMager()->m_curCuetype,
		Direction);
	this->LoadVideo();
	this->ShowDemoVideo();
	CCSprite* beijing2 = CCSprite::create("VideoUI/beijing2.png");
	beijing2->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(beijing2);
	m_pSprite->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(m_pSprite);
	return true;
}
bool DemoVideoLayer::LoadVideo()
{
	av_register_all();

	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)
	{
		CCLog("open");
		return false;
	}
	if (avformat_find_stream_info(pFormatCtx, 0) < 0)
	{
		CCLog("find");
		return false;
	}

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			break;
		}
	if (videoStream == -1)
	{
		CCLog("videoStream");
		return false;
	}
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		CCLog("pCodec");
		return false;
	}
	if (avcodec_open2(pCodecCtx, pCodec, 0) < 0)
	{
		CCLog("pCodecCtx");
		return false;
	}
	pFrame = av_frame_alloc();
	pFrameRGB = av_frame_alloc();

	if ((pFrame == NULL) || (pFrameRGB == NULL))
	{
		CCLog("pFrame||pFrameRGB");
		return false;
	}
	PictureSize = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);

	pSwsCtx = sws_getCachedContext(
		pSwsCtx,
		pCodecCtx->width,
		pCodecCtx->height,
		pCodecCtx->pix_fmt,
		pCodecCtx->width,
		pCodecCtx->height,
		AV_PIX_FMT_BGR24,
		SWS_BICUBIC,
		NULL, NULL, NULL);
	if (!pSwsCtx)
	{
		CCLog("pSwsCtx");
		return false;
	}
	while (av_read_frame(pFormatCtx, &packet) >= 0)
	{
		if (packet.stream_index == videoStream)
		{
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

			if (frameFinished)
			{
				buf = (uint8_t*)av_malloc(PictureSize);

				avpicture_fill((AVPicture *)pFrameRGB, buf, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);
				m_Width = pCodecCtx->width;
				m_Height = pCodecCtx->height;
				unsigned char* pVideoRGB24 = buf;
				m_VideoList.push_back(pVideoRGB24);

				sws_scale(
					pSwsCtx,
					(const uint8_t* const*)pFrame->data,
					pFrame->linesize,
					0,
					pCodecCtx->height,
					pFrameRGB->data,
					pFrameRGB->linesize);
			}
		}
		av_packet_unref(&packet);
	}
	m_VideoIter = m_VideoList.begin();
	Ext_VideoSize = m_VideoList.size();

	sws_freeContext(pSwsCtx);
	av_free(pFrame);
	av_free(pFrameRGB);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return true;
}
