import grpc
import argparse
import protobuf_pb2
import protobuf_pb2_grpc
import threading

class Client:
    def __init__(self,hname,p,uname):
        self.hostname = hname
        self.port = p
        self.username = uname
        self.stub = protobuf_pb2_grpc.EchoServiceStub(grpc.insecure_channel(hname+":"+p))

def encrypt(message):
    xored = []
    temp_pass = 'mypass'
    for i in range(len(message)):
        xored_value = ord(message[i%len(message)]) ^ ord(temp_pass[i%len(temp_pass)])
        xored.append(chr(xored_value))
    return ''.join(xored)

def decrypt(message):
    xored = []
    temp_pass = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMflag.txt"
    for i in range(len(message)):
        xored_value = ord(message[i%len(message)]) ^ ord(temp_pass[i%len(temp_pass)])
        xored.append(chr(xored_value))
    return ''.join(xored)

def receiveEcho(client):
    reply = client.stub.ReceiveEcho(protobuf_pb2.ServiceUser(username=client.username))
    print(decrypt(reply.msg))

def echoClient(hostname,port,username):
    client = Client(hostname, port, username)
    reply = client.stub.Login(protobuf_pb2.Request(username=client.username,msg="mypass"))
    reply = client.stub.SendEcho(protobuf_pb2.Request(username=client.username,msg="random"))

    new_thread = threading.Thread(target=receiveEcho,args=(client,))
    new_thread.start()

    reply = client.stub.SendEcho(protobuf_pb2.Request(username=client.username,msg=encrypt("AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMflag.txt")))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Process some arguments")
    parser.add_argument('--host',default='localhost')
    parser.add_argument('-p','--port',default='3010')
    parser.add_argument('-u','--user',default='default')
    args = parser.parse_args()
    echoClient(args.host,args.port,args.user)
