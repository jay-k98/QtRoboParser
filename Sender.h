#include <string>
#include <array>
#include "QtRoboEvent.h"
#include "Buffer.h"

using namespace std;

class Sender
{
    public:
        Sender() = delete;
        ~Sender() = default;
        Sender(Sender& orig) = delete;
        Sender& operator=(Sender& orig) = delete;

        static const string readBufferAsBytes(const uint8_t funcCode);
        static void send(const array<uint8_t, 41> buffer);
        static array<uint8_t, 41> parseToSumd(const std::array<uint8_t, 32>& data, const Modes& modes, uint8_t functionCode);
};
