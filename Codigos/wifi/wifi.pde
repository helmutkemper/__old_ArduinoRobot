/*
 * Web Server: Modified WebServer.pde example. 
 * A simple web server example using the WiShield library and WiBee. 
 */
 
#include <WiShield.h>
 
#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2
 //192.168.1.100
// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {192,168,2,10};	// IP address of Wifi Bee
unsigned char gateway_ip[] = {192,168,2,1};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local Wireless network
const prog_char ssid[] PROGMEM = {"MSHOME"};	// max 32 bytes
 
unsigned char security_type = 0;	// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
 
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"314159265358979314159265358"};	// max 64 characters. The network name.
 
// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = {	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 1
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00,	// Key 2
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00	// Key 3
				};
 
// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
 
unsigned char ssid_len;
unsigned char security_passphrase_len;
//---------------------------------------------------------------------------
 
void setup()
{
	WiFi.init();
}
 
// This is the webpage that is served up by the webserver
const prog_char webpage[] PROGMEM = {"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<center><h1>Hello World!! I am WifiBee.</h1></center>"};
 
void loop()
{
	WiFi.run();
}
