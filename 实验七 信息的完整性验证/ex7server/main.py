import socket
import hmac
import hashlib
import binascii

# b 为接收方，接收原始数据和密钥，并用 hmac 检验原始数据是否有经过篡改
bsock = socket.socket(type=socket.SOCK_DGRAM)
# 监听端口 9000
ip_port = (("10.1.11.176", 9000))
bsock.bind(ip_port)
# 发送方和接收方共享一个密钥
key = "812638"
byte_key = binascii.unhexlify(key)
success = "[*] 已成功正确接收到数据"
fail = "[!] 消息已被篡改，请重新发送"

while True:
    # 接收传过来的密钥和原始数据
    sendmsg, addr = bsock.recvfrom(1024)
    sendmsg = sendmsg.decode('utf-8')
    print(f"[+] 接收到从 a 发过来的原始数据和密钥:{sendmsg}")
    msglist = sendmsg.split(",")
    msg = msglist[0]
    sendmac = msglist[1]

    # 结束通信
    if msg == "exit":
        break

    msg = msg.encode()
    mac = hmac.new(byte_key, msg, hashlib.sha1)
    print(f"[*] 接收方签名：{mac.hexdigest()}")
    if mac.hexdigest() == sendmac:
        print("[*] 通过完整性检测")
        bsock.sendto(success.encode("utf-8"), ip_port)
        break
    else:
        print("消息已被篡改")
        bsock.sendto(fail.encode("utf-8"), ip_port)

bsock.close()  # 关闭套接字
exit(0)