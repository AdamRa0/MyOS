#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port
{
protected:
    uint16_t port_number;
    Port(uint16_t port_number); 
    ~Port();
};

class Port8Bit : public Port
{
public:
    Port8Bit(uint16_t port_number);
    ~Port8Bit();
    void Write(uint8_t data);
    uint8_t Read();
};

class Port8BitSlow : public Port8Bit
{
public:
    Port8BitSlow(uint16_t port_number);
    ~Port8BitSlow();
    void Write(uint8_t data);
};

class Port16Bit : public Port
{
public:
    Port16Bit(uint16_t port_number);
    ~Port16Bit();
    void Write(uint16_t data);
    uint16_t Read();
};

class Port32Bit : public Port
{
public:
    Port32Bit(uint16_t port_number);
    ~Port32Bit();
    void Write(uint32_t data);
    uint32_t Read();
};

#endif