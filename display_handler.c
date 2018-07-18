#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include "display_handler.h"
#include "usart_opts.h"

extern enum Mode mode;
extern uint8_t press_cnt;
uint8_t defaultScreen[DISPLAY_BUFFER_SIZE] = { 0x21, 0xFE, '-', 'M', 'I', 'T',
		'S', 'U', 'B', 'I', 'S', 'H', 'I', '-', 0xFF, 0xFF, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x9D };
uint8_t displayBuffer[DISPLAY_BUFFER_SIZE];

int greets_counter = 0;
int cnt = 600;
int cnt2 = 0;
void HandleDisplayData() {
	if (CheckChksum(displayBuffer, DISPLAY_BUFFER_SIZE) == ERROR)
		return;



	for (int i = 0; i < DISPLAY_BUFFER_SIZE; i++) {
		if (greets_counter < 30) {

			displayBuffer[i] = defaultScreen[i];
			continue;
		}
		if (i < 2 || i > 13) continue;
		else {
			// for future bluetooth metadata
			// displayBuffer[i] = Translit(displayBuffer[i]);

		}

	}

	if (displayBuffer[0] == ACC_OFF) greets_counter = 0; // ACC OFF byte for dimm display
	else greets_counter++;


	if (mode == Bluetooth)
	{
		if (displayBuffer[6] == 'A' && displayBuffer[7] == 'U' && displayBuffer[8] == 'X')
		{
			displayBuffer[2] = BLUETOOTH_CHAR;
			displayBuffer[3] = ' ';
			displayBuffer[4] = 'B';
			displayBuffer[5] = 'L';
			displayBuffer[6] = 'U';
			displayBuffer[7] = 'E';
			displayBuffer[8] = 'T';
			displayBuffer[9] = 'O';
			displayBuffer[10] = 'O';
			displayBuffer[11] = 'T';
			displayBuffer[12] = 'H';
			displayBuffer[13] = ' ';
		}
	}
//	cnt++;
//	cnt2 = cnt / 5;
//	displayBuffer[2] = cnt2;
//	displayBuffer[3] = cnt2 / 100 + 48;
//	displayBuffer[4] = (cnt2 / 10) % 10 + 48;
//	displayBuffer[5] = cnt2 % 10 + 48;
	SendDisplayData();
}
void SendDisplayData() {
	uint8_t chksum = 0;
	for (int i = 0; i < DISPLAY_BUFFER_SIZE - 1; i++) {
		chksum += displayBuffer[i];
	}
	displayBuffer[DISPLAY_BUFFER_SIZE - 1] = chksum;
	USART2SendDMA();
}

uint8_t Translit(uint8_t ch) {
	if (ch < 192)
		return ch;
	uint8_t out;

	switch (ch - 32) {
	case 192:
		out = 65;
		break;
	case 193:
		out = 66;
		break;
	case 194:
		out = 86;
		break;
	case 195:
		out = 71;
		break;
	case 196:
		out = 68;
		break;
	case 197:
		out = 69;
		break;
	case 198:
		out = 90;
		break;
	case 199:
		out = 90;
		break;
	case 200:
		out = 73;
		break;
	case 201:
		out = 73;
		break;
	case 202:
		out = 75;
		break;
	case 203:
		out = 76;
		break;
	case 204:
		out = 77;
		break;
	case 205:
		out = 78;
		break;
	case 206:
		out = 79;
		break;
	case 207:
		out = 80;
		break;
	case 208:
		out = 82;
		break;
	case 209:
		out = 83;
		break;
	case 210:
		out = 84;
		break;
	case 211:
		out = 85;
		break;
	case 212:
		out = 70;
		break;
	case 213:
		out = 72;
		break;
	case 214:
		out = 67;
		break;
	case 215:
		out = 52;
		break;
	case 216:
		out = 87;
		break;
	case 217:
		out = 87;
		break;
	case 218:
		out = 98;
		break;
	case 219:
		out = 73;
		break;
	case 220:
		out = 98;
		break;
	case 221:
		out = 69;
		break;
	case 222:
		out = 85;
		break;
	case 223:
		out = 65;
		break;

	}
	switch (ch) {
	case 192:
		out = 65;
		break;
	case 193:
		out = 66;
		break;
	case 194:
		out = 86;
		break;
	case 195:
		out = 71;
		break;
	case 196:
		out = 68;
		break;
	case 197:
		out = 69;
		break;
	case 198:
		out = 90;
		break;
	case 199:
		out = 90;
		break;
	case 200:
		out = 73;
		break;
	case 201:
		out = 73;
		break;
	case 202:
		out = 75;
		break;
	case 203:
		out = 76;
		break;
	case 204:
		out = 77;
		break;
	case 205:
		out = 78;
		break;
	case 206:
		out = 79;
		break;
	case 207:
		out = 80;
		break;
	case 208:
		out = 82;
		break;
	case 209:
		out = 83;
		break;
	case 210:
		out = 84;
		break;
	case 211:
		out = 85;
		break;
	case 212:
		out = 70;
		break;
	case 213:
		out = 72;
		break;
	case 214:
		out = 67;
		break;
	case 215:
		out = 52;
		break;
	case 216:
		out = 87;
		break;
	case 217:
		out = 87;
		break;
	case 218:
		out = 98;
		break;
	case 219:
		out = 73;
		break;
	case 220:
		out = 98;
		break;
	case 221:
		out = 69;
		break;
	case 222:
		out = 85;
		break;
	case 223:
		out = 65;
		break;

	}
	return out;

}
