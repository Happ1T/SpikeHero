#ifndef TEST1_NETWORK_H
#define TEST1_NETWORK_H
#include "consts.h"

//static const sf::IpAddress LocalHost;
/* using namespace sf;
using namespace std;


IpAddress LocalIPServer;
IpAddress LocalIPClient;

Packet packet;

UdpSocket dataSocketClient;
UdpSocket dataSocketServer;

char clientname[100];
TcpListener listener;

TcpSocket regSocketServer;
TcpSocket regSocketClient;
short regStep=0;

string nameFirstClient;
Uint16 udpPortFirstClient;
Uint16 udpPortServer;


unsigned short dataPortS_s;

struct player{
    float x,y,hp;
};
////////////////////////////////////SERVER//////////////////////////////////////////////////////////////////////////////////////
void init(){
    if (listener.listen(PORT1) == Socket::Status::Done){
        cout << "Port: " << listener.getLocalPort() << " IP:"<< LocalIPServer.getLocalAddress() << endl;
        return ;
    }
    cout << "Failed to connect server into the current port"<< endl;
}
bool acceptIncomingConnection()
{
    if(regStep == 0){
        if(listener.isBlocking())listener.setBlocking(false);

        if(listener.accept(regSocketServer)==Socket::Status::Done)
        {
            cout<<"New connection is accepted" << endl;
            regStep = 1;
            return true;
        }
    }
    return false;
}
bool receiveClientRegData()
{
    Packet packetWithUdp;

    Uint16 tempUdpPort;
    string tempName;
    if (regStep == 1)
    {

        if (regSocketServer.isBlocking()) regSocketServer.setBlocking(false);

        if (regSocketServer.receive(packetWithUdp) == Socket::Status::Done)
        {
            if (packetWithUdp.getDataSize() > 0)
            {

                if (!(packetWithUdp >> tempName))
                {
                    cout << "Failed to read client name from received packet\n";
                    return false;
                }


                if (!(packetWithUdp >>tempUdpPort))
                {
                    cout << "Failed to read client data socket port from received packet\n";
                }

                if (!packetWithUdp.endOfPacket()) {
                    cout << "Client registration data received, but something left, data probably corrupted\n";
                    return false;
                }
            }
            else
            {
                cout << "Error, received packet is empty\n";
                return false;
            }

            cout << "Client registration data received. New client: " << tempName << " UDP Port: " << tempUdpPort<< endl;

            udpPortFirstClient = tempUdpPort;
            LocalIPClient = regSocketServer.getRemoteAddress();
            cout << LocalIPClient << endl;
            regStep = 3;
            packet.clear();
            return true;
        }
    }
}
void sendDedicatedDataPort()
{
    Uint16 UdpPortServer;
    if (regStep == 3)
    {
        if (regSocketServer.isBlocking()) regSocketServer.setBlocking(false);
        UdpPortServer = dataPortS;

        if (packet.getDataSize() == 0)
            packet << static_cast<Uint16>(UdpPortServer);

        if (regSocketServer.send(packet) == Socket::Status::Done)
        {
            cout << "Dedicated data port sent\n";
            regStep = 4;
            packet.clear();
            udpPortServer = UdpPortServer;
            return ;
        }
        else cout <<"Failed to send dedicated data port" << endl;
    }
}
void bindServ(){

    if (dataSocketServer.bind(udpPortServer) != sf::Socket::Done)
    {
        cout<<"Failed you successfully bind to the port"<<endl;
        return;
    }
    cout<<"You successfully bind to the port: "<< udpPortServer <<endl;
}

bool sendToC(Packet &timePacket){
    if(dataSocketServer.isBlocking()) dataSocketServer.setBlocking(false);

   if(dataSocketServer.send(timePacket,LocalIPClient,udpPortFirstClient)==Socket::Done){
      // cout << "Message was sent"<<endl;
       return true;
   }
  // cout<<"Failed to send the message"<<endl;
    return false;
}
bool recieveFromC(Packet &timePacket){


    if(dataSocketServer.isBlocking()) dataSocketServer.setBlocking(false);


    if (dataSocketServer.receive(timePacket,LocalIPClient,udpPortFirstClient) == Socket::Done)
    {
      //  cout << "Message was accepted"<<endl;
        return true;
    }
    //cout << "Failed to accept the message"<<endl;
    return false;
}
///////////////////////////////////////END/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////CLIENT/////////////////////////////////////////////////////////////////////////////////////
bool connect(){
  cin>>LocalIPServer;
    if (regSocketClient.connect(LocalIPServer, PORT1) == Socket::Done){
        cout << "Client send the confirm"<<endl;
        return true;
    }

  //  cout<< "Error sending the confirm"<< endl;
    return false;
}

void sendClientData ()
{
    if (!regSocketClient.isBlocking()) regSocketClient.setBlocking(false);

    Packet tempPacket;
    Uint16 UdpPortClient = dataPortC;
    string LocalIP = LocalIPClient.getLocalAddress().toString();

    tempPacket << LocalIP << static_cast<Uint16>(UdpPortClient);

    if (regSocketClient.send(tempPacket) == Socket::Status::Done)
    {
        cout << "Successfully sent client recipient data (port = "<<UdpPortClient<<")"<<endl;
        udpPortFirstClient = UdpPortClient;
        return;
    }
    else
    {
        cout << "Failed to send client recipient data\n";
    }
}
bool recieveDedicatedDataServerPort()
{
    Uint16 tempUdpPortServer;
    if (!regSocketClient.isBlocking()) regSocketClient.setBlocking(true);

    Packet tempPacket;

    if (regSocketClient.receive(tempPacket) == Socket::Status::Done)
    {
        if (tempPacket.getDataSize() > 0)
        {
            if (tempPacket.getDataSize() == sizeof(Uint16))
            {
                if (tempPacket >> tempUdpPortServer)
                {
                    cout << "Successfully received data client-dedicated port of a server = " << tempUdpPortServer << endl;
                    udpPortServer = tempUdpPortServer;
                    return true;

                }
                else cout << "Failed to read from received packet\n";
            }
            else cout << "Invalid packet size, ensure that server sends only Uint16 var\n";
        }
        else cout << "Received packet is empty\n";
    }
    else cout << "Failed to receive client-dedicated port of a server\n";
    return false;
}


void sendToS(Packet &timePacket ){
    if(dataSocketClient.isBlocking()) dataSocketClient.setBlocking(false);

    if(dataSocketClient.send(timePacket,LocalIPServer, udpPortServer) == Socket::Done){
      //  cout << "Message was sent"<<endl;
        return;
    }
   //cout<<"Failed to send the message"<<endl;

}
void bindClient(){
    if (dataSocketClient.bind(udpPortFirstClient) != sf::Socket::Done)
    {
        cout<<"Bad luck no fartanulo"<<endl;
        return;
    }
    cout<<"You successfully bind to the port: "<< udpPortFirstClient <<endl;
}

bool recieveFromS(Packet &timePacket){

    if(dataSocketClient.isBlocking()) dataSocketClient.setBlocking(false);


    if (dataSocketClient.receive(timePacket,LocalIPServer,udpPortServer) == Socket::Done) {
        //timePacket >> buttonMove >> buttonJump >> buttonShift >> timeS;
       // cout << "Message was accepted"<<endl;
        return true;
    }
  // cout << "Failed to accept the message"<<endl;
    return false;
}
 */
#endif //TEST1_NETWORK_H
