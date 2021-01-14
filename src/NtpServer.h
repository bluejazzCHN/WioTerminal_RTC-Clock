#include "rpcWiFi.h"
#include "SPI.h"
#include "DateTime.h"

class NtpServer
{
private:
    char _ssid[50];
    char _pwd[50];
    unsigned int localPort = 2390;           // local port to listen for UDP packets
    char timeServer[50] = "cn.pool.ntp.org"; // extenral NTP server e.g. time.nist.gov

    const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
    byte packetBuffer[48]; //buffer to hold incoming and outgoing packets

    // declare a time object
    DateTime now;

    // define WiFI client
    WiFiClient client;

    //The udp library class
    WiFiUDP udp;
    void connectToWiFi();
    unsigned long sendNTPpacket(const char *address);

public:
    NtpServer(char *ssid, char *password);
    unsigned long getNTPtime();
};