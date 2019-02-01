#ifndef G_BUFFER_H
#define G_BUFFER_H

#include "Header.h"

enum GBUFFER
{
	G_Buffer = 1,
	G_Position = 2,
	G_Normal = 3,
	G_ColorSpec = 4
};

class gBuffer
{
private:
	unsigned int g_buffer;
	unsigned int gPosition;
	unsigned int gNormal;
	unsigned int gColorSpec;
public:
	bool Init(int width, int height);
	unsigned int GetBuffer(GBUFFER select) const;
};
#endif // !G_BUFFER
