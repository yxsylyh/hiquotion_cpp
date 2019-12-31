#pragma once

class ICameraCallback
{
public:
	ICameraCallback(){};
	~ICameraCallback(){};

	virtual void OnSnapshot(char *buffer, long bufferLength){};
};

