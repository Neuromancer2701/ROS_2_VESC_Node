/*
    Copyright 2016 - 2019 Benjamin Vedder	benjamin@vedder.se

    This file is part of VESC Tool.

    VESC Tool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    VESC Tool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef PACKET_H
#define PACKET_H


#include "datatypes.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <libserial/SerialPort.h>

using std::vector;
using std::byte;
using std::function;
using std::round;
using LibSerial::SerialPort;

class Packet
{

public:
    Packet();
    Packet(COMM_PACKET_ID  Id);

    Packet(COMM_PACKET_ID  Id, unsigned data);
    Packet(COMM_PACKET_ID  Id, unsigned short data);
    Packet(COMM_PACKET_ID  Id, unsigned  char data);
    Packet(COMM_PACKET_ID  Id, double number, double scale);
    ~Packet();
    vector<uint8_t> createPacket();
    static unsigned short crc16(vector<byte> payload);
    void processData(vector<byte> inputData);


    static void append(vector<byte>& message, unsigned data);
    static void append(vector<byte>& message, unsigned short data);
    static void append(vector<byte>& message, unsigned char data);

    static void append(vector<byte>& message, int data)   {append(message, static_cast<unsigned>(data));}
    static void append(vector<byte>& message, short data) {append(message, static_cast<unsigned short>(data));}
    static void append(vector<byte>& message, char data)  {append(message, static_cast<unsigned char>(data));}

    static void pop(vector<byte>& message, unsigned & data);
    static void pop(vector<byte>& message, unsigned short & data);
    static void pop(vector<byte>& message, unsigned char & data);

    static void pop(vector<byte>& message, int & data);
    static void pop(vector<byte>& message, short & data);
    static void pop(vector<byte>& message, char & data);

    static void appendDouble32(vector<byte>& message, double number, double scale);

    static double popDouble16(vector<byte>& message, double scale);
    static double popDouble32(vector<byte>& message, double scale);

    vector<byte> &getPayload();

    static long getminTotalPacketSize(){ return static_cast<long>(minTotalPacketSize);}

    bool isGoodPacket(){return processState == GoodPacket;}


private:
    vector<byte> rawData;
    vector<byte> payload;
    vector<byte> sendData;

    enum SIZE
    {
     Byte    = 1,
     Word    = 2,
     Integer = 4
    };


    enum States
    {
        DetectLength = 0,
        Length1byte  = 2,
        Length2byte  = 3,
        Length3byte  = 4,
        ReadMessage  = 5,
        CalcCRC      = 6,
        ValidateCRC  = 7,
        GoodPacket   = 8
    };

    enum constants
    {
        minBytes = 2,
        CRCSize  = 2,
        maxPacketLength = 512,
        End = 3,
        minTotalPacketSize = 6
    };

    States processState;


};

#endif // PACKET_H
