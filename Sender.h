#include <string>

using namespace std;

class Sender
{
    public:
        const string readBufferAsBytes(const uint8_t funcCode);
        void send(const string buffer);
};