#include "stdafx.h"
#include "CMusicPlayer.h"
#include <Digitalv.h>

CMusicPlayer::CMusicPlayer(void)
{
}


CMusicPlayer::~CMusicPlayer(void)
{
}

void CMusicPlayer::Open(HWND hwnd, CString Strfilepath)
{
	hWnd = hwnd;
	mciSendCommand(Device, MCI_CLOSE, 0, 0);
	mciopenparms.lpstrElementName = Strfilepath;
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciopenparms))
	{

		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256);
		AfxMessageBox(buffer);

	}
	Device = mciopenparms.wDeviceID;
}

DWORD CMusicPlayer::info(DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwItem = item;
	mcistatusparms.dwReturn = 0;
	mciSendCommand(Device, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}

void CMusicPlayer::Play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)hWnd;
	mciplayparms.dwFrom = 0;
	mciSendCommand(Device, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciplayparms);
}

void CMusicPlayer::Pause()
{
	mciSendCommand(Device, MCI_PAUSE, 0, 0);
}
void CMusicPlayer::resume()
{
	mciSendCommand(Device, MCI_RESUME, 0, 0);
}
void CMusicPlayer::Stop()
{
	mciSendCommand(Device, MCI_STOP, 0, 0);
	mciSendCommand(Device, MCI_CLOSE, 0, 0);
}

void CMusicPlayer::SetVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS mcisetvolumn;
	mcisetvolumn.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mcisetvolumn.dwValue = vol;
	mciSendCommand(Device, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)&mcisetvolumn);

}


void CMusicPlayer::SeekTo(DWORD to)
{
	MCI_SEEK_PARMS mciseek;
	mciseek.dwTo = to;
	mciSendCommand(Device, MCI_SEEK, MCI_TO, (DWORD)&mciseek);
}
