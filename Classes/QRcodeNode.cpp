#include "QRcodeNode.h"
#include "qrencode.h"
#include <fstream>

using namespace std;


#define OUT_FILE_PIXEL_PRESCALER	8											// Prescaler (number of pixels in bmp file for each QRCode pixel, on each dimension)

#define PIXEL_COLOR_R				0											// Color of bmp pixels
#define PIXEL_COLOR_G				0
#define PIXEL_COLOR_B				0xff

QRcodeNode::QRcodeNode(void)
{
}


QRcodeNode::~QRcodeNode(void)
{
}
bool QRcodeNode::init()
{
	if (!CCNode::init())
	{
		return false;
	}

	CCSize VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	m_QRcodeText = "www.baidu.com";
	m_PicFile = "C:\\CameraRecord\\Test.bmp";

	unsigned int	unWidth, x, y, l, n, unWidthAdjusted, unDataBytes;
	unsigned char*	pRGBData, *pSourceData, *pDestData;
	QRcode*			pQRC;
	FILE*			f;


	if (pQRC = QRcode_encodeString(m_QRcodeText, 0, QR_ECLEVEL_H, QR_MODE_8, 1))
	{
		unWidth = pQRC->width;
		unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3;

		if (unWidthAdjusted % 4)
			unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
		unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;


		if (!(pRGBData = (unsigned char*)malloc(unDataBytes)))
		{
			printf("Out of memory");
			exit(-1);
		}

		memset(pRGBData, 0xff, unDataBytes);

		BITMAPFILEHEADER kFileHeader;
		kFileHeader.bfType = 0x4d42;  // "BM"
		kFileHeader.bfSize = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER) +
			unDataBytes;
		kFileHeader.bfReserved1 = 0;
		kFileHeader.bfReserved2 = 0;
		kFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) +
			sizeof(BITMAPINFOHEADER);

		BITMAPINFOHEADER kInfoHeader;
		kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		kInfoHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;
		kInfoHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER);
		kInfoHeader.biPlanes = 1;
		kInfoHeader.biBitCount = 24;
		kInfoHeader.biCompression = BI_RGB;
		kInfoHeader.biSizeImage = 0;
		kInfoHeader.biXPelsPerMeter = 0;
		kInfoHeader.biYPelsPerMeter = 0;
		kInfoHeader.biClrUsed = 0;
		kInfoHeader.biClrImportant = 0;

		pSourceData = pQRC->data;
		for (y = 0; y < unWidth; y++)
		{
			pDestData = pRGBData + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
			for (x = 0; x < unWidth; x++)
			{
				if (*pSourceData & 1)
				{
					for (l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
					{
						for (n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
						{
							*(pDestData + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_B;
							*(pDestData + 1 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_G;
							*(pDestData + 2 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_R;
						}
					}
				}
				pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
				pSourceData++;
			}
		}

		if (!(fopen_s(&f, m_PicFile, "wb")))
		{
			fwrite(&kFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
			fwrite(&kInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
			fwrite(pRGBData, sizeof(unsigned char), unDataBytes, f);

			fclose(f);
		}
		else
		{
			printf("Unable to open file");
			exit(-1);
		}
		// Free data

		free(pRGBData);
		QRcode_free(pQRC);
	}
	else
	{
		printf("NULL returned");
		exit(-1);
	}


	char outPath[128];

	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;

	ifstream fin("C:\\CameraRecord\\Test.png");

	TCHAR* cmdline = fin ? TEXT("ffmpeg -i C:\\CameraRecord\\Test.bmp C:\\CameraRecord\\Test.png&y") : TEXT("ffmpeg -i C:\\CameraRecord\\Test.bmp C:\\CameraRecord\\Test.png");

	CreateProcess(TEXT("C:\\Users\\Administrator\\Desktop\\ffmpeg\\bin\\ffmpeg.exe"),
		cmdline,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	//不使用的句柄最好关掉
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);

	CCSprite* pSprite = CCSprite::create("C:\\CameraRecord\\Test.png");
	pSprite->setPosition(ccp(VisibleSize.width / 2, VisibleSize.height / 2));
	this->addChild(pSprite, 0);


	return true;
}