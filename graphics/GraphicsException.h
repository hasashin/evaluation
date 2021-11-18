#ifndef GRAPHICS_EXCEPTION_H
#define GRAPHICS_EXCEPTION_H

class GraphicsException {
public:
	GraphicsException(const char * pTxt) : pReason(pTxt) {};
	const char * pReason;
};

#endif //GRAPHICS_EXCEPTION_H