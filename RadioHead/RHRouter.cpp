// RHRouter.cpp
//
// Define addressed datagram
//
// Part of the Arduino RH library for operating with HopeRF RH compatible transceivers
// (see http://www.hoperf.com)
// RHDatagram will be received only by the addressed node or all nodes within range if the
// to address is RH_BROADCAST_ADDRESS
//
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2011 Mike McCauley
// $Id: RHRouter.cpp,v 1.9 2019/09/06 04:40:40 mikem Exp mikem $

#include <RHRouter.h>

RHRouter::RoutedMessage RHRouter::_tmpMessage;

////////////////////////////////////////////////////////////////////
// Constructors
RHRouter::RHRouter (RHGenericDriver& driver, uint8_t thisAddress)
	: RHReliableDatagram (driver, thisAddress)
{
	_max_hops = RH_DEFAULT_MAX_HOPS;
	_isa_router = true;
	clearRoutingTable();
}

////////////////////////////////////////////////////////////////////
// Public methods
bool RHRouter::init()
{
	bool ret = RHReliableDatagram::init();
	if (ret)
		_max_hops = RH_DEFAULT_MAX_HOPS;
	return ret;
}

////////////////////////////////////////////////////////////////////
void RHRouter::setMaxHops (uint8_t max_hops)
{
	_max_hops = max_hops;
}

////////////////////////////////////////////////////////////////////
void RHRouter::setIsaRouter (bool isa_router)
{
	_isa_router = isa_router;
}
////////////////////////////////////////////////////////////////////
void RHRouter::addRouteTo (uint8_t dest, uint8_t next_hop, uint8_t state)
{
	uint8_t i;

	// First look for an existing entry we can update
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
	{
		if (_routes[i].dest == dest)
		{
			_routes[i].dest = dest;
			_routes[i].next_hop = next_hop;
			_routes[i].state = state;
			return;
		}
	}

	// Look for an invalid entry we can use
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
	{
		if (_routes[i].state == Invalid)
		{
			_routes[i].dest = dest;
			_routes[i].next_hop = next_hop;
			_routes[i].state = state;
			return;
		}
	}

	// Need to make room for a new one
	retireOldestRoute();
	// Should be an invalid slot now
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
	{
		if (_routes[i].state == Invalid)
		{
			_routes[i].dest = dest;
			_routes[i].next_hop = next_hop;
			_routes[i].state = state;
		}
	}
}

////////////////////////////////////////////////////////////////////
RHRouter::RoutingTableEntry* RHRouter::getRouteTo (uint8_t dest)
{
	uint8_t i;
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
		if (_routes[i].dest == dest && _routes[i].state != Invalid)
			return &_routes[i];
	return NULL;
}

////////////////////////////////////////////////////////////////////
void RHRouter::deleteRoute (uint8_t index)
{
	// Delete a route by copying following routes on top of it
	memcpy (&_routes[index], &_routes[index + 1],
	        sizeof (RoutingTableEntry) * (RH_ROUTING_TABLE_SIZE - index - 1));
	_routes[RH_ROUTING_TABLE_SIZE - 1].state = Invalid;
}

////////////////////////////////////////////////////////////////////
void RHRouter::printRoutingTable()
{
#ifdef RH_HAVE_SERIAL
	printRoutingTable(Serial);
#endif
}

////////////////////////////////////////////////////////////////////
void RHRouter::printRoutingTable(Print &p)
{
	uint8_t i;
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
	{
		p.print (i, DEC);
		p.print (" Dest: ");
		p.print (_routes[i].dest, DEC);
		p.print (" Next Hop: ");
		p.print (_routes[i].next_hop, DEC);
		p.print (" State: ");
		p.println (_routes[i].state, DEC);
	}
}

////////////////////////////////////////////////////////////////////
bool RHRouter::deleteRouteTo (uint8_t dest)
{
	uint8_t i;
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
	{
		if (_routes[i].dest == dest)
		{
			deleteRoute (i);
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////
void RHRouter::retireOldestRoute()
{
	// We just obliterate the first in the table and clear the last
	deleteRoute (0);
}

////////////////////////////////////////////////////////////////////
void RHRouter::clearRoutingTable()
{
	uint8_t i;
	for (i = 0; i < RH_ROUTING_TABLE_SIZE; i++)
		_routes[i].state = Invalid;
}


uint8_t RHRouter::sendtoWait (uint8_t* buf, uint8_t len, uint8_t dest, uint8_t flags)
{
	// Serial.print("STW buf:");
	// Serial.println((char*)buf);
	return sendtoFromSourceWait (buf, len, dest, _thisAddress, flags);
}

////////////////////////////////////////////////////////////////////
// Waits for delivery to the next hop (but not for delivery to the final destination)
uint8_t RHRouter::sendtoFromSourceWait (uint8_t* buf, uint8_t len, uint8_t dest, uint8_t source, uint8_t flags)
{
	if ( ( (uint16_t) len + sizeof (RoutedMessageHeader)) > _driver.maxMessageLength())
		return RH_ROUTER_ERROR_INVALID_LENGTH;
	
	// Serial.print("Buf Tx FSW:");
	// Serial.print(int((char*)buf));

	// Serial.println("Byte Array:");
  	// for (int i = 0; i < sizeof(buf); i++) {
	// 	Serial.print("0x");
	// 	if (buf[i] < 0x10) Serial.print("0");  // Add leading zero if necessary
	// 	Serial.print(buf[i], HEX);
	// 	Serial.print(" ");
	// }
	// Serial.print(" ");
	// Serial.print(int((char*)buf[1]));
	// Serial.print(" ");
	// Serial.println(int((char*)buf[2]));

	// Construct a RH RouterMessage message
	_tmpMessage.header.source = source;
	_tmpMessage.header.dest = dest;
	_tmpMessage.header.hops = 0;
	_tmpMessage.header.id = _lastE2ESequenceNumber++;
	_tmpMessage.header.flags = flags;
	memcpy(_tmpMessage.data, buf, len); 
	
	return route (&_tmpMessage, sizeof (RoutedMessageHeader) + len);
}

////////////////////////////////////////////////////////////////////
uint8_t RHRouter::route (RoutedMessage* message, uint8_t messageLen)
{
	// Serial.print("Buf Tx:");
	// Serial.println((char*)message->data);
	// Serial.print(int((char*)message->data[0]));
	// Serial.print(" ");
	// Serial.print(int((char*)message->data[1]));
	// Serial.print(" ");
	// Serial.println(int((char*)message->data[2]));
	// Reliably deliver it if possible. See if we have a route:
	uint8_t next_hop = RH_BROADCAST_ADDRESS;
	if (message->header.dest != RH_BROADCAST_ADDRESS)
	{
		// Serial.println("(1)");
		RoutingTableEntry* route = getRouteTo (message->header.dest);
		if (!route){
			// Serial.println("fail no route");
			return RH_ROUTER_ERROR_NO_ROUTE;
		}
		next_hop = route->next_hop;
	}

	// uint8_t route_buf[messageLen];
	// // route_buf = &message->data;
	// memcpy(route_buf, message->data, messageLen); 
	// // Serial.println((char*)route_buf);
	// // Serial.println("(2)");

	// Serial.println("Byte Array:");
  	// for (int i = 0; i < sizeof(route_buf); i++) {
	// 	Serial.print("0x");
	// 	if (route_buf[i] < 0x10) Serial.print("0");  // Add leading zero if necessary
	// 	Serial.print(route_buf[i], HEX);
	// 	Serial.print(" ");
	// }

	if (!RHReliableDatagram::sendtoWait ( message->data, messageLen, next_hop))
	{
		// Serial.println("(3)");
		return RH_ROUTER_ERROR_UNABLE_TO_DELIVER;
	}
	// Serial.println("(4)");
	return RH_ROUTER_ERROR_NONE;
}

////////////////////////////////////////////////////////////////////
// Subclasses may want to override this to peek at messages going past
void RHRouter::peekAtMessage (RoutedMessage* message, uint8_t messageLen)
{
	// Default does nothing
	(void) message; // Not used
	(void) messageLen; // Not used
}

////////////////////////////////////////////////////////////////////
bool RHRouter::recvfromAck (uint8_t* buf, uint8_t* len, uint8_t* source, uint8_t* dest, uint8_t* id, uint8_t* flags)
{
	uint8_t tmpMessageLen = sizeof (_tmpMessage);
	char route_buf[tmpMessageLen];
	uint8_t _from;
	uint8_t _to;
	uint8_t _id;
	uint8_t _flags;
	if (RHReliableDatagram::recvfromAck ( (uint8_t*) &route_buf, &tmpMessageLen, &_from, &_to, &_id, &_flags))
	{
		// String header = String(route_buf).substring(0,4);
		String data_rx = String(&route_buf[4]);
		// Serial.println(String(route_buf));
		// Serial.print("Temp msg(router) raw: ");
		// Serial.println((char*)route_buf);
		// Serial.print("Temp msg(router) data rx: ");
		// Serial.println(data_rx);
		memcpy(_tmpMessage.data, data_rx.c_str(), data_rx.length());
		// Serial.println((char*)_tmpMessage.data);

		// Serial.println("Router buff : ");
		// Serial.println(header);
		// Serial.println(data_rx);
		// Here we simulate networks with limited visibility between nodes
		// so we can test routing
		// Serial.print("Temp msg(router) dest: ");
		// Serial.println(_from);
		// Serial.print("Temp msg(router) this address: ");
		// Serial.println(_thisAddress);
		// _thisAddress

		_tmpMessage.header.dest  = _to;
		_tmpMessage.header.source= _from;
		_tmpMessage.header.id    = _id;
		_tmpMessage.header.flags = _flags;
#ifdef RH_TEST_NETWORK
		if (
#if RH_TEST_NETWORK==1
		    // This network looks like 1-2-3-4
		    (_thisAddress == 1 && _from == 2)
		    || (_thisAddress == 2 && (_from == 1 || _from == 3))
		    || (_thisAddress == 3 && (_from == 2 || _from == 4))
		    || (_thisAddress == 4 && _from == 3)

#elif RH_TEST_NETWORK==2
		    // This network looks like 1-2-4
		    //                         | | |
		    //                         --3--
		    (_thisAddress == 1 && (_from == 2 || _from == 3))
		    ||  _thisAddress == 2
		    ||  _thisAddress == 3
		    || (_thisAddress == 4 && (_from == 2 || _from == 3))

#elif RH_TEST_NETWORK==3
		    // This network looks like 1-2-4
		    //                         |   |
		    //                         --3--
		    (_thisAddress == 1 && (_from == 2 || _from == 3))
		    || (_thisAddress == 2 && (_from == 1 || _from == 4))
		    || (_thisAddress == 3 && (_from == 1 || _from == 4))
		    || (_thisAddress == 4 && (_from == 2 || _from == 3))

#elif RH_TEST_NETWORK==4
		    // This network looks like 1-2-3
		    //                           |
		    //                           4
		    (_thisAddress == 1 && _from == 2)
		    ||  _thisAddress == 2
		    || (_thisAddress == 3 && _from == 2)
		    || (_thisAddress == 4 && _from == 2)

#endif
		)
		{
			// OK
		}
		else
		{
			return false; // Pretend we got nothing
		}
#endif
		// Serial.print("Temp msg(router): ");
		// Serial.println((char*)_tmpMessage.header.dest);

		// Serial.print(int((char*)_tmpMessage.header.dest));

		// peekAtMessage (&_tmpMessage, tmpMessageLen);
		// See if its for us or has to be routed
		if (_to == _thisAddress || _to == RH_BROADCAST_ADDRESS)
		{
			// Deliver it here
			if (source) *source  = _from;
			if (dest)   *dest    = _to;
			if (id)     *id      = _id;
			if (flags)  *flags   = _flags;
			// uint8_t msgLen = tmpMessageLen - sizeof (RoutedMessageHeader);
			// if (*len > msgLen)
			// 	*len = msgLen;
			memcpy (buf, data_rx.c_str(), data_rx.length());
			// Serial.print("Temp msg(router) final buf : ");
			// Serial.println(int((char*)buf[0]));
			// Serial.println("(router) about to return true");
			return true; // Its for you!
		}
		else if (_tmpMessage.header.dest != RH_BROADCAST_ADDRESS
		         && _tmpMessage.header.hops++ < _max_hops)
		{
			// Maybe it has to be routed to the next hop
			// REVISIT: if it fails due to no route or unable to deliver to the next hop,
			// tell the originator. BUT HOW?

			// If we are forwarding packets, do so. Otherwise, drop.
			if (_isa_router)
				route (&_tmpMessage, tmpMessageLen);
		}
		// Discard it and maybe wait for another
		// Serial.println("(router) about to return false");
	}
	return false;
}

////////////////////////////////////////////////////////////////////
bool RHRouter::recvfromAckTimeout (uint8_t* buf, uint8_t* len, uint16_t timeout, uint8_t* source, uint8_t* dest, uint8_t* id, uint8_t* flags)
{
	unsigned long starttime = millis();
	int32_t timeLeft;
	while ( (timeLeft = timeout - (millis() - starttime)) > 0)
	{
		if (waitAvailableTimeout (timeLeft))
		{
			if (recvfromAck (buf, len, source, dest, id, flags))
				return true;
		}
		YIELD;
	}
	return false;
}
