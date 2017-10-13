/*
 * dhcpMessage.h
 *
 *  Created on: 5. 11. 2016
 *      Author: Jakub
 */

#ifndef DHCPMESSAGE_H_
#define DHCPMESSAGE_H_

typedef struct{
    uint8_t op;      // message op code, message type
    uint8_t htype;   // hardware address type
    uint8_t hlen;    // hardware address length
    uint8_t hops;    // incremented by relay agents

    uint32_t xid;    // transaction ID

    uint16_t secs;   // seconds since address acquisition or renewal
    uint16_t flags;  // flags

    uint32_t ciaddr; // client IP address
    uint32_t yiaddr; // 'your' client IP address
    uint32_t siaddr; // IP address of the next server to use in bootstrap
    uint32_t giaddr; // relay agent IP address

    uint8_t chaddr[16]; // client hardware address

    uint8_t sname[64]; // server host name

    uint8_t file[128]; // boot file name

    uint8_t options[312]; // optional parameters field
}dhcpMessage_t;



#endif /* DHCPMESSAGE_H_ */
