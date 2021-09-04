#ifndef __YOU_BOT_H__
#define __YOU_BOT_H__
#include "platform/platform.h"
class YOU_BOT
{
private:
    int _client_id;
public:
    YOU_BOT();
    void init(int client_id);
    PLATFORM platform;
    ~YOU_BOT();
};

YOU_BOT::YOU_BOT()
{
    
}
void YOU_BOT::init(int client_id)
{
    platform.init(client_id);
}

YOU_BOT::~YOU_BOT()
{
}


#endif // __YOU_BOT_H__