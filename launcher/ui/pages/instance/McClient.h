#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include <Exception.h>

#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

// Client for the Minecraft protocol
class McClient : public QObject {
    Q_OBJECT

    QString domain;
    QString ip;
    short port;
    QTcpSocket socket;

public:
    explicit McClient(QObject *parent, QString domain, QString ip, short port);
    QJsonObject getStatusData();
    int getOnlinePlayers();
    void sendRequest();
    void readBytesExactFromSocket(QByteArray &resp, int bytesToRead);
    QJsonObject readResponse();
private:
    void writeVarInt(QByteArray &data, int value);
    int readVarInt(QByteArray &data);
    char readByte(QByteArray &data);
    // write number with specified size in big endian format
    void writeFixedInt(QByteArray &data, int value, int size);
    void writeString(QByteArray &data, const std::string &value);

    void writePacketToSocket(QByteArray &data);
};