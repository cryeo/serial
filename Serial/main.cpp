#include "SerialPort.h"

int main() {
	SerialPort serial("COM1", 38400);

	serial.connect();

	serial.write("#SET DISP 3\r\n", 1000);

	char *buffer = new char[256];
	cout << serial.read(buffer) << endl;
	cout << buffer << endl;
	delete[] buffer;

	serial.disconnect();

	return 0;
}