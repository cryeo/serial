#include "SerialPort.h"

bool SerialPort::connect() {
	comPort = CreateFileA(port,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (comPort == INVALID_HANDLE_VALUE) return false;

	GetCommState(comPort, &dcb);
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = baudRate;
	dcb.fBinary = FALSE;
	dcb.ByteSize = 8;
	dcb.fParity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	SetCommState(comPort, &dcb);

	timeouts.ReadIntervalTimeout = 1;
	timeouts.ReadTotalTimeoutMultiplier = 1;
	timeouts.ReadTotalTimeoutConstant = 1;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant = 1;
	SetCommTimeouts(comPort, &timeouts);

	return true;
}

bool SerialPort::disconnect() {
	if (comPort != INVALID_HANDLE_VALUE) {
		CloseHandle(comPort);
	}

	return true;
}

int SerialPort::write(const char *data, int delay) {
	DWORD btWritten;
	int ret = WriteFile(comPort, data, strlen(data), &btWritten, NULL);
	if (!ret) return 0;
	if (delay > 0) Sleep(delay);
	return btWritten;	
}

int SerialPort::read(char *buffer, int szBuffer) {
	DWORD dwErrors;
	COMSTAT ComStat;
	DWORD dwCount;
	DWORD dwRead;

	ClearCommError(comPort, &dwErrors, &ComStat);
	dwCount = ComStat.cbInQue;

	int ret = ReadFile(comPort, buffer, szBuffer, &dwRead, NULL);
	if (!ret) return 0;

	buffer[dwRead] = '\0';

	return dwRead;
}