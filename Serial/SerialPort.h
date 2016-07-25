#pragma once
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include <Windows.h>
#include <iostream>
#include <memory>

using namespace std;

#define ACK 0x06 // 6
#define NAK 0x15 // 21
#define CR 0x0D // 13
#define LF 0x0A // 10

class SerialPort {
public:
	SerialPort(const char *_port, unsigned long _baudRate) : port(_port), baudRate(_baudRate) {}
	virtual ~SerialPort() { disconnect(); }
	bool connect();
	bool disconnect();

	int write(const char *data, int delay = 0);
	int read(char *buffer, int szBuffer = 256);
	void flush();
private:
	HANDLE comPort;
	DCB dcb;
	COMMTIMEOUTS timeouts;
	
	const char *port;
	unsigned long baudRate;
};

#endif