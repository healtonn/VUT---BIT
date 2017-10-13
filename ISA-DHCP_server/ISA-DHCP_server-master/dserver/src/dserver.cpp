/*
 *  Jakub Jochlík
 *  ISA - DHCP server
 */

#include "dserver.h"


int main(int argc, char* argv[])
{
  parameter_t parsedParameters;
  if(processParameters(argc, argv, &parsedParameters)){
  	fprintf(stderr, "This is not valid argument! \n");
  	return -1;
  }

  if(parsedParameters.h){
  	printHelp();
  	return 0;
  }

  parsedIP_t networkData;
  setUpIPPool(&networkData, &parsedParameters);

  if(networkData.ipPool.size() < 1){
  	fprintf(stderr, "This is not valid IP Pool! \n");
  	return -1;
  }

  dhcpServer(&networkData);

  return 0;
}

int dhcpServer(parsedIP_t *ipStruct){
	int mySocket;
	struct sockaddr_in dhcpSocket;
	unsigned char buffer[BUFFERSIZE];
	int data;
	socklen_t var;	//must be here for some reason....
	dhcpMessage_t dhcpMessage;

	dhcpSocket.sin_family = AF_INET;
	dhcpSocket.sin_addr.s_addr = htonl(INADDR_ANY);
	dhcpSocket.sin_port = htons(DHCPSERVERPORT);

	if((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		fprintf(stderr, "Error creating socket\n");
		return -1;
		}

	if(bind(mySocket, (struct sockaddr *)&dhcpSocket, sizeof(dhcpSocket)) == -1){
		fprintf(stderr, "Bind failed\n");
		return -1;
	}

	while(1){
		if((data = recvfrom(mySocket, buffer, BUFFERSIZE, 0, (struct sockaddr *)&dhcpSocket, &var)) < 0)
			continue;

		processPacket(&dhcpMessage, buffer);
		checkIfIpCanBeReleased(ipStruct);

		if(dhcpMessage.op == 1){	//BOOTREQUEST
			int messageType = getMessageType(dhcpMessage);

			if(messageType == 1){							//DHCP DISCOVER
				if(isIpAvilableForClient(*ipStruct))
					sendDhcpOffer(mySocket, dhcpMessage, ipStruct);
				else
					sendDhcpNack(mySocket, dhcpMessage, ipStruct);
			}
			else if(messageType == 3){				//DHCP REQUEST
				if(ntohl(dhcpMessage.ciaddr) == 0){	//new ip
					sendDhcpAck(mySocket, dhcpMessage, ipStruct);
				}
				else{																//renewing lease
					bool renew;
					for(unsigned int index = 0; index < ipStruct->dhcpRecords.size(); index++){
						if(htonl(ipStruct->dhcpRecords[index].clientIp) == dhcpMessage.ciaddr){
							renew = true;
							break;
						}
					} //end of for loop
					if(renew){			//lease found ... renewing
						sendDhcpRenewAck(mySocket, dhcpMessage, ipStruct);
					}
					else{				//lease expired, sending nack -> forcing new offer
						sendDhcpNack(mySocket, dhcpMessage, ipStruct);
					}
				}
			}
			else if(messageType == 7){			//DHCP RELEASE
				releaseIp(dhcpMessage, ipStruct);
			}
			else{
				//unknown dhcp message.. ignoring....
				;
			}
		}
		else{		//unknown dhcp message
			//discard packet here?
			;
		}
	}

	return 0;
}


/*********************************************************
 * Part containing DHCP response functions               *
 * DHCP OFFER                                            *
 * DHCP ACK                                              *
 * DHCP RENEW ACK                                        *
 * DHCP NACK                                             *
 *********************************************************
 */
void sendDhcpOffer(int mySocket, dhcpMessage_t clientDiscoverMessage, parsedIP_t *ipStruct){
	size_t len;
	int sendToRet;
	dhcpMessage_t reply;
	struct sockaddr_in client;

	len = sizeof(dhcpMessage_t);

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	client.sin_port = htons(DHCPCLIENTPORT);

	reply.op = BOOTREPLY;
	reply.htype = 1;
	reply.hlen = 6;
	reply.hops = 2;

	reply.xid = ntohl(clientDiscoverMessage.xid);

	reply.secs = htonl(42);
	reply.flags = 0;

	reply.ciaddr = 0;
	reply.yiaddr = assignIpToClient(ipStruct, clientDiscoverMessage);
	reply.siaddr = 0;
	reply.giaddr = 0;

	setMacIntoNewMessage(&clientDiscoverMessage, &reply);

	for(int index = 0; index < SNAMESIZE; index++){
		reply.sname[index] = 0;
	}

	for(int index = 0; index < FILESIZE; index++){
		reply.file[index] = 0;
	}

	for(int index = 0; index < OPTIONSSIZE; index++){
			reply.options[index] = 0;
		}

	//magic cookie
	reply.options[0] = clientDiscoverMessage.options[0];
	reply.options[1] = clientDiscoverMessage.options[1];
	reply.options[2] = clientDiscoverMessage.options[2];
	reply.options[3] = clientDiscoverMessage.options[3];

	reply.options[4] = MESSAGETYPEIDENTIFIER;
	reply.options[5] = MESSAGETYPELENGTH;
	reply.options[6] = DHCPOFFER;

	reply.options[7] = MASKIDENTIFIER;
	reply.options[8] = MASKLENGTH;
	reply.options[9] = htonl(ipStruct->mask);
	reply.options[10] = htonl(ipStruct->mask << 8);
	reply.options[11] = htonl(ipStruct->mask << 16);
	reply.options[12] = htonl(ipStruct->mask << 24);

	reply.options[13] = BROADCASTIDENTIFIER;
	reply.options[14] = BROADCASTLENGTH;
	reply.options[15] = htonl(ipStruct->broadcast);
	reply.options[16] = htonl(ipStruct->broadcast << 8);
	reply.options[17] = htonl(ipStruct->broadcast << 16);
	reply.options[18] = htonl(ipStruct->broadcast << 24);

	reply.options[19] = LEASETIMEIDENTIFIER;
	reply.options[20] = LEASETIMELENGTH;
	reply.options[21] = 0;
	reply.options[22] = 0;
	reply.options[23] = 14;
	reply.options[24] = 16;

	reply.options[25] = SERVERIDENTIFIER;
	reply.options[26] = SERVERIDENTIFIERLENGTH;
	reply.options[27] = ipStruct->serverAddress >> 24;
	reply.options[28] = ipStruct->serverAddress >> 16;
	reply.options[29] = ipStruct->serverAddress >> 8;
	reply.options[30] = ipStruct->serverAddress;

	reply.options[31] = ENDIDENTIFIER;

	struct ifaddrs *ifap, *ifa;
	getifaddrs(&ifap);
	struct sockaddr_in *sa;
	char *netif;

	//get name of interface which is used
	for(ifa = ifap; ifa; ifa = ifa->ifa_next){
		if(ifa->ifa_addr->sa_family==AF_INET) {
      sa = (struct sockaddr_in *) ifa->ifa_addr;
      if(ntohl(sa->sin_addr.s_addr) == ipStruct->serverAddress){
      	netif = ifa->ifa_name;
      }
		}
	}

	int on = 1;

	setsockopt(mySocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	setsockopt(mySocket, SOL_SOCKET, SO_BINDTODEVICE, netif, sizeof(netif));

	if ((sendToRet = sendto(mySocket, &reply, len, 0, (struct sockaddr *) &client, sizeof(client))) < 0) {
		perror("sendto failed");
	}
}

void sendDhcpAck(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct){
	size_t len;
	int sendToRet;
	dhcpMessage_t reply;
	struct sockaddr_in client;

	len = sizeof(dhcpMessage_t);

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	client.sin_port = htons(DHCPCLIENTPORT);

	reply.op = BOOTREPLY;
	reply.htype = 1;
	reply.hlen = 6;
	reply.hops = 2;

	reply.xid = ntohl(clientRequestMessage.xid);

	reply.secs = htonl(42);
	reply.flags = 0;

	reply.ciaddr = 0;
	reply.yiaddr = confirmRequestedIp(clientRequestMessage);
	reply.siaddr = 0;
	reply.giaddr = 0;

	setMacIntoNewMessage(&clientRequestMessage, &reply);

	for(int index = 0; index < SNAMESIZE; index++){
		reply.sname[index] = 0;
	}

	for(int index = 0; index < FILESIZE; index++){
		reply.file[index] = 0;
	}

	for(int index = 0; index < OPTIONSSIZE; index++){
			reply.options[index] = 0;
		}

	//magic cookie
	reply.options[0] = clientRequestMessage.options[0];
	reply.options[1] = clientRequestMessage.options[1];
	reply.options[2] = clientRequestMessage.options[2];
	reply.options[3] = clientRequestMessage.options[3];

	reply.options[4] = MESSAGETYPEIDENTIFIER;
	reply.options[5] = MESSAGETYPELENGTH;
	reply.options[6] = DHCPACK;

	reply.options[7] = MASKIDENTIFIER;
	reply.options[8] = MASKLENGTH;
	reply.options[9] = htonl(ipStruct->mask);
	reply.options[10] = htonl(ipStruct->mask << 8);
	reply.options[11] = htonl(ipStruct->mask << 16);
	reply.options[12] = htonl(ipStruct->mask << 24);

	reply.options[13] = BROADCASTIDENTIFIER;
	reply.options[14] = BROADCASTLENGTH;
	reply.options[15] = htonl(ipStruct->broadcast);
	reply.options[16] = htonl(ipStruct->broadcast << 8);
	reply.options[17] = htonl(ipStruct->broadcast << 16);
	reply.options[18] = htonl(ipStruct->broadcast << 24);

	reply.options[19] = LEASETIMEIDENTIFIER;
	reply.options[20] = LEASETIMELENGTH;
	reply.options[21] = 0;
	reply.options[22] = 0;
	reply.options[23] = 14;
	reply.options[24] = 16;

	reply.options[25] = SERVERIDENTIFIER;
	reply.options[26] = SERVERIDENTIFIERLENGTH;
	reply.options[27] = ipStruct->serverAddress >> 24;
	reply.options[28] = ipStruct->serverAddress >> 16;
	reply.options[29] = ipStruct->serverAddress >> 8;
	reply.options[30] = ipStruct->serverAddress;

	reply.options[31] = ENDIDENTIFIER;


	struct ifaddrs *ifap, *ifa;
	getifaddrs(&ifap);
	struct sockaddr_in *sa;
	char *netif;

	//get name of interface which is used
	for(ifa = ifap; ifa; ifa = ifa->ifa_next){
		if(ifa->ifa_addr->sa_family==AF_INET) {
	     sa = (struct sockaddr_in *) ifa->ifa_addr;
	     if(ntohl(sa->sin_addr.s_addr) == ipStruct->serverAddress){
	     	netif = ifa->ifa_name;
	     }
		}
	}

	int on = 1;

	setsockopt(mySocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	setsockopt(mySocket, SOL_SOCKET, SO_BINDTODEVICE, netif, sizeof(netif));

	if ((sendToRet = sendto(mySocket, &reply, len, 0, (struct sockaddr *) &client, sizeof(client))) < 0) {
		perror("sendto failed");
	}

	char timeBuffer[26];
	static char macAddr[128];
	sprintf(macAddr, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
			reply.chaddr[0], reply.chaddr[1], reply.chaddr[2],
			reply.chaddr[3], reply.chaddr[4], reply.chaddr[5]);

	for(unsigned int index = 0; index < ipStruct->dhcpRecords.size(); index++){
		if(ipStruct->dhcpRecords[index].clientIp == htonl(reply.yiaddr)){
			unsigned char one, two, three, four;
			one = reply.yiaddr & 0xFF;
			two = reply.yiaddr >> 8 & 0xFF;
			three = reply.yiaddr >> 16 & 0xFF;
			four = reply.yiaddr >> 24 & 0xFF;
			cout << macAddr << " ";
			printf("%d.%d.%d.%d ", one, two, three, four);
			strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M", &ipStruct->dhcpRecords[index].leaseTimeStart);
			cout << " " << timeBuffer;
			strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M", &ipStruct->dhcpRecords[index].leaseTimeEnd);
			cout << " " << timeBuffer << endl;
			break;
		}
	}
}

void sendDhcpRenewAck(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct){
	size_t len;
	int sendToRet;
	dhcpMessage_t reply;
	struct sockaddr_in client;

	len = sizeof(dhcpMessage_t);

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(clientRequestMessage.ciaddr);
	client.sin_port = htons(DHCPCLIENTPORT);

	reply.op = BOOTREPLY;
	reply.htype = 1;
	reply.hlen = 6;
	reply.hops = 2;

	reply.xid = ntohl(clientRequestMessage.xid);

	reply.secs = htonl(42);
	reply.flags = 0;

	reply.ciaddr = 0;
	reply.yiaddr = confirmRequestedIp(clientRequestMessage);
	renewLeaseForIp(reply.yiaddr, ipStruct);
	reply.siaddr = 0;
	reply.giaddr = 0;

	setMacIntoNewMessage(&clientRequestMessage, &reply);

	for(int index = 0; index < SNAMESIZE; index++){
		reply.sname[index] = 0;
	}

	for(int index = 0; index < FILESIZE; index++){
		reply.file[index] = 0;
	}

	for(int index = 0; index < OPTIONSSIZE; index++){
			reply.options[index] = 0;
		}

	//magic cookie
	reply.options[0] = clientRequestMessage.options[0];
	reply.options[1] = clientRequestMessage.options[1];
	reply.options[2] = clientRequestMessage.options[2];
	reply.options[3] = clientRequestMessage.options[3];

	reply.options[4] = MESSAGETYPEIDENTIFIER;
	reply.options[5] = MESSAGETYPELENGTH;
	reply.options[6] = DHCPACK;

	reply.options[7] = MASKIDENTIFIER;
	reply.options[8] = MASKLENGTH;
	reply.options[9] = htonl(ipStruct->mask);
	reply.options[10] = htonl(ipStruct->mask << 8);
	reply.options[11] = htonl(ipStruct->mask << 16);
	reply.options[12] = htonl(ipStruct->mask << 24);

	reply.options[13] = BROADCASTIDENTIFIER;
	reply.options[14] = BROADCASTLENGTH;
	reply.options[15] = htonl(ipStruct->broadcast);
	reply.options[16] = htonl(ipStruct->broadcast << 8);
	reply.options[17] = htonl(ipStruct->broadcast << 16);
	reply.options[18] = htonl(ipStruct->broadcast << 24);

	reply.options[19] = LEASETIMEIDENTIFIER;
	reply.options[20] = LEASETIMELENGTH;
	reply.options[21] = 0;
	reply.options[22] = 0;
	reply.options[23] = 14;
	reply.options[24] = 16;

	reply.options[25] = SERVERIDENTIFIER;
	reply.options[26] = SERVERIDENTIFIERLENGTH;
	reply.options[27] = ipStruct->serverAddress >> 24;
	reply.options[28] = ipStruct->serverAddress >> 16;
	reply.options[29] = ipStruct->serverAddress >> 8;
	reply.options[30] = ipStruct->serverAddress;

	reply.options[31] = ENDIDENTIFIER;

	struct ifaddrs *ifap, *ifa;
	getifaddrs(&ifap);
	struct sockaddr_in *sa;
	char *netif;

	//get name of interface which is used
	for(ifa = ifap; ifa; ifa = ifa->ifa_next){
		if(ifa->ifa_addr->sa_family==AF_INET) {
	     sa = (struct sockaddr_in *) ifa->ifa_addr;
	     if(ntohl(sa->sin_addr.s_addr) == ipStruct->serverAddress){
	     	netif = ifa->ifa_name;
	     }
		}
	}

	int on = 1;

	setsockopt(mySocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	setsockopt(mySocket, SOL_SOCKET, SO_BINDTODEVICE, netif, sizeof(netif));

	if ((sendToRet = sendto(mySocket, &reply, len, 0, (struct sockaddr *) &client, sizeof(client))) < 0) {
		perror("sendto failed");
	}

	char timeBuffer[26];
		static char macAddr[128];
		sprintf(macAddr, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
				reply.chaddr[0], reply.chaddr[1], reply.chaddr[2],
				reply.chaddr[3], reply.chaddr[4], reply.chaddr[5]);

		for(unsigned int index = 0; index < ipStruct->dhcpRecords.size(); index++){
			if(ipStruct->dhcpRecords[index].clientIp == htonl(reply.yiaddr)){
				unsigned char one, two, three, four;
				one = reply.yiaddr & 0xFF;
				two = reply.yiaddr >> 8 & 0xFF;
				three = reply.yiaddr >> 16 & 0xFF;
				four = reply.yiaddr >> 24 & 0xFF;
				cout << macAddr << " ";
				printf("%d.%d.%d.%d ", one, two, three, four);
				strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M", &ipStruct->dhcpRecords[index].leaseTimeStart);
				cout << " " << timeBuffer;
				strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M", &ipStruct->dhcpRecords[index].leaseTimeEnd);
				cout << " " << timeBuffer << endl;
				break;
			}
		}
}

void sendDhcpNack(int mySocket, dhcpMessage_t clientRequestMessage, parsedIP_t *ipStruct){
	size_t len;
	int sendToRet;
	dhcpMessage_t reply;
	struct sockaddr_in client;

	len = sizeof(dhcpMessage_t);

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	client.sin_port = htons(DHCPCLIENTPORT);

	reply.op = BOOTREPLY;
	reply.htype = 1;
	reply.hlen = 6;
	reply.hops = 2;

	reply.xid = ntohl(clientRequestMessage.xid);

	reply.secs = htonl(42);
	reply.flags = 0;

	reply.ciaddr = 0;
	reply.yiaddr = 0;
	reply.siaddr = 0;
	reply.giaddr = 0;

	setMacIntoNewMessage(&clientRequestMessage, &reply);

	for(int index = 0; index < SNAMESIZE; index++){
		reply.sname[index] = 0;
	}

	for(int index = 0; index < FILESIZE; index++){
		reply.file[index] = 0;
	}

	for(int index = 0; index < OPTIONSSIZE; index++){
			reply.options[index] = 0;
		}

		//magic cookie
	reply.options[0] = clientRequestMessage.options[0];
	reply.options[1] = clientRequestMessage.options[1];
	reply.options[2] = clientRequestMessage.options[2];
	reply.options[3] = clientRequestMessage.options[3];

	reply.options[4] = MESSAGETYPEIDENTIFIER;		//message type setup
	reply.options[5] = MESSAGETYPELENGTH;
	reply.options[6] = DHCPNACK;

	reply.options[7] = ENDIDENTIFIER;		//end

	struct ifaddrs *ifap, *ifa;
	getifaddrs(&ifap);
	struct sockaddr_in *sa;
	char *netif;

	//get name of interface which is used
	for(ifa = ifap; ifa; ifa = ifa->ifa_next){
		if(ifa->ifa_addr->sa_family==AF_INET) {
	     sa = (struct sockaddr_in *) ifa->ifa_addr;
	     if(ntohl(sa->sin_addr.s_addr) == ipStruct->serverAddress){
	     	netif = ifa->ifa_name;
	     }
		}
	}

	int on = 1;

	setsockopt(mySocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	setsockopt(mySocket, SOL_SOCKET, SO_BINDTODEVICE, netif, sizeof(netif));

	if ((sendToRet = sendto(mySocket, &reply, len, 0, (struct sockaddr *) &client, sizeof(client))) < 0)
		perror("sendto failed");
}


/*********************************************************
 * Part containging data processing and setup operations *
 * SET UP IP POOL                                        *
 * GENERATE IP POOL                                      *
 * SET UP FORBIDDEN IP                                   *
 * PROCESS PACKET                                        *
 * GET MESSAGE TYPE                                      *
 * SET SERVER ADDRESS                                    *
 * SET MAC INTO NEW MESSAGE                              *
 * CHECK IF IP CAN BE RELEASED                           *
 * RENEW LEASE FOR IP                                    *
 * CONFIRM REQUESTED IP                                  *
 * IS IP AVILABLE                                        *
 * ASSIGN IP TO CLIENT                                   *
 * RELEASE IP                                            *
 * PRINT HELP                                            *
 *********************************************************
 */


void setUpIPPool(parsedIP_t *ipStruct, parameter_t *parameters){
	ipStruct->first = parameters->first;
	ipStruct->second = parameters->second;
	ipStruct->third = parameters->third;
	ipStruct->fourth = parameters->fourth;
	ipStruct->mask = ((1 << parameters->mask) - 1) << (32 - parameters->mask);
	ipStruct->constructedIP = parameters->first<<24 | parameters->second<<16 | parameters->third<<8 | parameters->fourth;
	ipStruct->network = ipStruct->constructedIP & ipStruct->mask;
	ipStruct->wildcard = 32 - parameters->mask;

	generateIPPool(ipStruct, parameters);
}

void generateIPPool(parsedIP_t *ipStruct, parameter_t *parameters){
	int ipLimit = (1 << ipStruct->wildcard) - 1;
	bool dontSaveIp = false;
	uint32_t clientIpSuffix = 1;
	uint32_t networkAddres = ipStruct->network;
	uint32_t clientIp;

	if(parameters->e){
		int errcode = setUpForbiddenIp(ipStruct, parameters);
		if(errcode < 0)
			parameters->e = false;
	}

	for(int ipCount = 0; ipCount < ipLimit - 1; ipCount++){
		clientIp = networkAddres | clientIpSuffix;
		for(unsigned int index = 0; index < ipStruct->forbiddenIPs.size(); index++){
			if(clientIp == ipStruct->forbiddenIPs[index]){
				dontSaveIp = true;
				break;
			}
		}
		if(dontSaveIp){
			dontSaveIp = false;
		}
		else{
			ipStruct->ipPool.insert(ipStruct->ipPool.end(), clientIp);
		}
		clientIpSuffix++;
	}
	ipStruct->broadcast = networkAddres | clientIpSuffix;

	if(ipStruct->ipPool.size() < 1)
		return;

	setServerAddress(ipStruct);
}

int setUpForbiddenIp(parsedIP_t *ipStruct, parameter_t *parameters){
	if(parameters->forbiddenIP.empty())
		return -1;

	for(auto forbiddenIp : parameters->forbiddenIP){
		unsigned char ipBuffer[sizeof(struct in6_addr)];
		const char * forbiddenIpAsConstChar = forbiddenIp.c_str();
		unsigned int resultOfConversion;
		uint32_t forbiddenIpTmp;

		resultOfConversion = inet_pton(AF_INET, forbiddenIpAsConstChar, ipBuffer);
		if(resultOfConversion){
			forbiddenIpTmp = ipBuffer[0] << 24 | ipBuffer[1] << 16 | ipBuffer[2] << 8 | ipBuffer[3];
			ipStruct->forbiddenIPs.insert(ipStruct->forbiddenIPs.end(), forbiddenIpTmp);
		}
	}

	return 0;
}

int processPacket(dhcpMessage_t *message, unsigned char* packet){
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	message->op = packet[0];
	message->htype = packet[1];
	message->hlen = packet[2];
	message->hops = packet[3];

	message->xid = packet[4] << 24 | packet[5] << 16 | packet[6] << 8 | packet [7];

	message->secs = packet[8] << 8 | packet[9];
	message->flags = packet[10] << 8 | packet[11];

	message->ciaddr = packet[12] << 24 | packet[13] << 16 | packet[14] << 8 | packet [15];
	message->yiaddr = packet[16] << 24 | packet[17] << 16 | packet[18] << 8 | packet [19];
	message->siaddr = packet[20] << 24 | packet[21] << 16 | packet[22] << 8 | packet [23];
	message->giaddr = packet[24] << 24 | packet[25] << 16 | packet[26] << 8 | packet [27];

	for(; i < CHADDRSIZE; i++){
		message->chaddr[i] = packet[28 + i];
	}

	for(; j < SNAMESIZE; j++){
		message->sname[j] = packet[44 + j];
	}

	for(; k < FILESIZE; k++){
		message->file[k] = packet[108 + k];
	}

	for(; l < OPTIONSSIZE; l++){
		message->options[l] = packet[236 + l];
	}

	return 0;
}

int getMessageType(dhcpMessage_t dhcpMessage){
	for(int index = 0; index < OPTIONSSIZE; index++){
		if(dhcpMessage.options[index] == MESSAGETYPEIDENTIFIER){
			int length = dhcpMessage.options[index + 1];
			return dhcpMessage.options[index + length + 1];
		}
	}
	return 0;
}

void setServerAddress(parsedIP_t *ipStruct){
	ipStruct->serverAddress = ipStruct->ipPool[0];
	ipStruct->ipPool.erase(ipStruct->ipPool.begin());
}

void setMacIntoNewMessage(dhcpMessage_t *requestPacket, dhcpMessage_t *responsePacket){
	for(int index = 0; index < CHADDRSIZE; index++){
		responsePacket->chaddr[index] = requestPacket->chaddr[index];
	}
}

void checkIfIpCanBeReleased(parsedIP_t *ipStruct){
	if(ipStruct->dhcpRecords.size() == 0)
		return;

	time_t timer;
	struct tm timeInfoEnd;
	double resultOfTimeComparing;
	unsigned int index = 0;

	while(index < ipStruct->dhcpRecords.size()){
		time(&timer);
		timeInfoEnd = ipStruct->dhcpRecords[index].leaseTimeEnd;
		resultOfTimeComparing = difftime(mktime(&timeInfoEnd), timer);
		if(resultOfTimeComparing <= 0){
			ipStruct->ipPool.insert(ipStruct->ipPool.begin(), ipStruct->dhcpRecords[index].clientIp);
			ipStruct->dhcpRecords.erase(ipStruct->dhcpRecords.begin() + index);
		}
		else{
			index++;
		}
	}
}

void renewLeaseForIp(uint32_t ipToRenew, parsedIP_t *ipStruct){
	time_t timer;
	struct tm * tmpTime;
	struct tm timeInfoStart;
	struct tm timeInfoEnd;

	for(unsigned int index = 0; index < ipStruct->dhcpRecords.size(); index++){
		if(htonl(ipStruct->dhcpRecords[index].clientIp) == ipToRenew){
			time(&timer);
			tmpTime = localtime(&timer);
			timeInfoStart = *tmpTime;

			timer = timer + 60 * 60;
			tmpTime = localtime(&timer);
			timeInfoEnd = *tmpTime;

			ipStruct->dhcpRecords[index].leaseTimeStart = timeInfoStart;
			ipStruct->dhcpRecords[index].leaseTimeEnd = timeInfoEnd;

			return;
		}
	}
}

uint32_t confirmRequestedIp(dhcpMessage_t clientsMessage){
	uint32_t confirmedIp;

	if(ntohl(clientsMessage.ciaddr) == 0){
		for(int index = 0; index < OPTIONSSIZE; index++){
			if(clientsMessage.options[index] == 50){							//if request ip address is detected
				confirmedIp = clientsMessage.options[index + 2] | clientsMessage.options[index + 3] << 8 | clientsMessage.options[index + 4] << 16 | clientsMessage.options[index + 5] << 24;
				break;
			}
		}
	}
	else{
		confirmedIp = htonl(clientsMessage.ciaddr);
	}

	return confirmedIp;
}

bool isIpAvilableForClient(parsedIP_t ipStruct){
	if(ipStruct.ipPool.size() == 0)
		return false;
	else
		return true;
}

uint32_t assignIpToClient(parsedIP_t *ipStruct, dhcpMessage_t clientsMessage){
	uint32_t assignedIp;
	static dhcpRecord_t dhcpRecord;
	time_t timer;
	struct tm * tmpTime;
	struct tm timeInfoStart;
	struct tm timeInfoEnd;

	assignedIp = ipStruct->ipPool.front();
	ipStruct->ipPool.erase(ipStruct->ipPool.begin());

	dhcpRecord.clientIp = assignedIp;
	dhcpRecord.clientMACAddress[0] = clientsMessage.chaddr[0];
	dhcpRecord.clientMACAddress[1] = clientsMessage.chaddr[1];
	dhcpRecord.clientMACAddress[2] = clientsMessage.chaddr[2];
	dhcpRecord.clientMACAddress[3] = clientsMessage.chaddr[3];
	dhcpRecord.clientMACAddress[4] = clientsMessage.chaddr[4];
	dhcpRecord.clientMACAddress[5] = clientsMessage.chaddr[5];

	time(&timer);
	tmpTime = localtime(&timer);
	timeInfoStart = *tmpTime;

	timer = timer + 60 * 60;
	tmpTime = localtime(&timer);
	timeInfoEnd = *tmpTime;

	dhcpRecord.leaseTimeStart = timeInfoStart;
	dhcpRecord.leaseTimeEnd = timeInfoEnd;

	ipStruct->dhcpRecords.insert(ipStruct->dhcpRecords.end(), dhcpRecord);

	return htonl(assignedIp);
}

void releaseIp(dhcpMessage_t clientReleaseMessage, parsedIP_t *ipStruct){
	uint32_t ipToBeReleased = clientReleaseMessage.ciaddr;

	for(unsigned int index = 0; index < ipStruct->dhcpRecords.size(); index++){
		if(ipStruct->dhcpRecords[index].clientIp == ipToBeReleased){
			ipStruct->ipPool.insert(ipStruct->ipPool.begin(), ipStruct->dhcpRecords[index].clientIp);
			ipStruct->dhcpRecords.erase(ipStruct->dhcpRecords.begin() + index);
			return;
		}
	}
}

void printHelp(){
	cout << "Napoveda programu:" << endl;
	cout << "program lze spustit nasledujicim zpusobem:" << "sudo ./dserver -p 192.168.0.0/24 [-e 192.168.0.1,192.168.0.2]" << endl;
	cout << "Prepinac -p je povinny a urcuje IP pool"  << endl;
	cout << "Prepinac -e je volitelny a specifikuje, ktere IP adresy se nesmi pridelit"  << endl;
	cout << "Prepinac -h zobrazi tuto napovedu" << endl;
}


/*************************************************
 * This part contains debugging output functions *
 * PRINT DHCP MESSAGE                            *
 * PRINT SERVER RECORDS                          *
 * PRINT IP STRUCTURE                            *
 * PRINT BITS                                    *
 *************************************************
 */

void printDhcpMessage(dhcpMessage_t message){
	cout << endl << "Printing out dhcp message... This is debug output" << endl;
	printf("Message type: %x\n", message.op);
	printf("Hardware Type: 0x%.2x\n", message.htype);
	printf("Hardware address length: %i \n", message.hlen);
	printf("Hops: %i\n", message.hops);

	printf("Transaction ID: 0x%x\n", message.xid);
	printf("Seconds elapsed %i\n", message.secs);

	printf("Flags: "); printBits((unsigned int) message.flags); cout << endl;

	printf("Client IP address: %hu.%hu.%hu.%hu\n", message.ciaddr >> 24, message.ciaddr >> 16, message.ciaddr >> 8, message.ciaddr);
	printf("Your client IP address: %hu.%hu.%hu.%hu\n", message.yiaddr >> 24, message.yiaddr >> 16, message.yiaddr >> 8, message.yiaddr);
	printf("Next server IP address: %hu.%hu.%hu.%hu\n", message.siaddr >> 24, message.siaddr >> 16, message.siaddr >> 8, message.siaddr);
	printf("Relay agent IP address: %hu.%hu.%hu.%hu\n", message.giaddr >> 24, message.giaddr >> 16, message.giaddr >> 8, message.giaddr);

	static char str[128];
	sprintf(str, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
			message.chaddr[0], message.chaddr[1], message.chaddr[2],
			message.chaddr[3], message.chaddr[4], message.chaddr[5]);
	cout << "Mac: " <<str << endl;
}

void printServerRecords(parsedIP_t ipStruct){
	if(ipStruct.dhcpRecords.size() == 0){
		cout << "zadne DHCP zaznamy" << endl;
	}
	else{
		cout << "vypis zaznamu: " << endl;
		char timeBuffer[26];

		for(unsigned int index = 0; index < ipStruct.dhcpRecords.size(); index++){
			cout << "client ip addres: ";
			printBits(ipStruct.dhcpRecords[index].clientIp);
			cout << "mac address: ";
			static char str[128];
			sprintf(str, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
					ipStruct.dhcpRecords[index].clientMACAddress[0], ipStruct.dhcpRecords[index].clientMACAddress[1], ipStruct.dhcpRecords[index].clientMACAddress[2],
					ipStruct.dhcpRecords[index].clientMACAddress[3], ipStruct.dhcpRecords[index].clientMACAddress[4], ipStruct.dhcpRecords[index].clientMACAddress[5]);
			cout <<str << endl;
			cout << "lease start: ";
			strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M:%S", &ipStruct.dhcpRecords[index].leaseTimeStart);
			cout << timeBuffer;
			cout << "            lease end: ";
			strftime(timeBuffer, 26, "%Y-%m-%d_%H:%M:%S", &ipStruct.dhcpRecords[index].leaseTimeEnd);
			puts(timeBuffer);
		}
	}
}

void printIPStructure(parsedIP_t ipStructure){
	cout << "this is ip data structure debug output: " << endl;
	cout << "first: " << unsigned(ipStructure.first) << endl;
	cout << "second: " << unsigned(ipStructure.second) << endl;
	cout << "third: " << unsigned(ipStructure.third) << endl;
	cout << "fourth: " << unsigned(ipStructure.fourth) << endl;
	cout << "mask: ";
	printBits(ipStructure.mask);
	cout << endl;
	cout << "constructedIP: ";
	printBits(ipStructure.constructedIP);
	cout << endl;
	cout << "network: ";
	printBits(ipStructure.network);
	cout << endl;
	cout << "wildcard: " << ipStructure.wildcard << endl;
	cout << "Broadcast: ";
	printBits(ipStructure.broadcast);
	cout << endl;
	printf("Server IP: ");
	printBits(ipStructure.serverAddress);
	cout << endl;
}

void printBits(unsigned int num){
    unsigned int size = sizeof(unsigned int);
    unsigned int maxPow = 1<<(size*8-1);
    unsigned int i=0,j;
    for(;i<size;++i){
        for(j=0;j<8;++j){
            // print last bit and shift left.
        	printf("%u ",num&maxPow ? 1 : 0);
        	    num = num<<1;
        }
        printf(".");
    }
}

void printIpPool(parsedIP_t *ipStruct){
	if(ipStruct->ipPool.size() < 1){
		cout << "Ip Pool is empty!" << endl;
		return;
	}

	int index = 1;
	cout << "Printing whole IP Pool: " << endl;;
	for(auto ip : ipStruct->ipPool){
		cout << "Ip num." << index << ": ";
		printBits(ip);
		cout << endl;
		index++;
	}

}
