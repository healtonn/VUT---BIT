/*
 *  Jakub Jochlík
 *  ISA - DHCP server
 */

#include "parameters.h"
#include "dhcpMessage.h"
#include <stdint.h>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <time.h>

using namespace std;

//ports
#define DHCPSERVERPORT 67
#define DHCPCLIENTPORT 68

//size of elements in packet
#define BUFFERSIZE 1024
#define CHADDRSIZE 16
#define SNAMESIZE 64
#define FILESIZE 128
#define OPTIONSSIZE 312

//defines leght in bytes for different dhcp options
#define MASKLENGTH 4
#define BROADCASTLENGTH 4
#define MESSAGETYPELENGTH 1
#define LEASETIMELENGTH 4
#define SERVERIDENTIFIERLENGTH 4

//list of dhcp message identifiers
#define MESSAGETYPEIDENTIFIER 53
#define MASKIDENTIFIER 1
#define BROADCASTIDENTIFIER 28
#define LEASETIMEIDENTIFIER 51
#define SERVERIDENTIFIER 54
#define ENDIDENTIFIER 255

//list of message types
#define BOOTREPLY 2

#define DHCPOFFER 2
#define DHCPACK 5
#define DHCPNACK 6

typedef struct{
	uint32_t clientIp;
	uint8_t clientMACAddress[6];
	struct tm leaseTimeStart;
	struct tm leaseTimeEnd;
}dhcpRecord_t;

typedef struct{
	uint8_t first;
	uint8_t second;
	uint8_t third;
	uint8_t fourth;
	uint32_t constructedIP;
	uint32_t mask;
	uint32_t network;
	uint32_t broadcast;
	uint32_t serverAddress;
	int wildcard;
	vector<uint32_t> ipPool;
	vector<uint32_t> forbiddenIPs;
	vector<dhcpRecord_t> dhcpRecords;
}parsedIP_t;



/**
 * Main program
 */
int dhcpServer(parsedIP_t *ipStruct);


void sendDhcpOffer(int mySocket, dhcpMessage_t clientDiscoverMessage, parsedIP_t *ipStruct);

void sendDhcpAck(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct);

void sendDhcpNack(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct);

void sendDhcpRenewAck(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct);



/**
 * fills up ip structure using data gathered from parameters structure
 */
void setUpIPPool(parsedIP_t *ipStruct, parameter_t *parameters);

/**
 * Generates IP pool based on input arguments
 */
void generateIPPool(parsedIP_t *ipStruct, parameter_t *parameters);

/**
 *  fills up vector with forbidden ips, wich will be used for ip checks
 */
int setUpForbiddenIp(parsedIP_t *ipStruct, parameter_t *parameters);

/**
 * extracts all data from incoming packet and saves them into dhcpMessage_t structure
 */
int processPacket(dhcpMessage_t *message, unsigned char* packet);

/**
 * determinec what kind of response is required / what kind of message was accepted
 */
int getMessageType(dhcpMessage_t dhcpMessage);

void setServerAddress(parsedIP_t *ipStruct);

void setMacIntoNewMessage(dhcpMessage_t *requestPacket, dhcpMessage_t *responsePacket);

/**
 * Function for checking, if lease can be deleted and ip released. Happens after every packet is received
 */
void checkIfIpCanBeReleased(parsedIP_t *ipStruct);

void renewLeaseForIp(uint32_t ipToRenew, parsedIP_t *ipStruct);

uint32_t confirmRequestedIp(dhcpMessage_t clientsMessage);

/**
 * checks if there is any IP left in ip pool
 */
bool isIpAvilableForClient(parsedIP_t ipStruct);

/**
 * goes through ip pool and assigns ip to client while creating DHCP record
 */
uint32_t assignIpToClient(parsedIP_t *ipStruct, dhcpMessage_t clientsMessage);

/**
 * this function is called, when DHCP Release is received
 */
void releaseIp(dhcpMessage_t clientReleaseMessage, parsedIP_t *ipStruct);

void printHelp();


/**
 * debugging oputput
 */
void printDhcpMessage(dhcpMessage_t message);

/*
 * debugging output
 */
void printServerRecords(parsedIP_t ipStruct);

/**
 * shows content of ip data structure
 */
void printIPStructure(parsedIP_t ipStructure);

/**
 * debugging output
 */
void printBits(unsigned int num);

/**
 * debugging output
 */
void printIpPool(parsedIP_t *ipStruct);
