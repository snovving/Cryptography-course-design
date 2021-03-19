import socket
import hmac
import hashlib
import binascii

# a 为发送方，发送密钥和密文

asock = socket.socket(type=socket.SOCK_DGRAM)
# 监听端口 9000
ip_port = (("10.1.11.176", 9000))
# 发送方和接收方共享一个密钥
key = "812638"
byte_key = binascii.unhexlify(key)
success = "[*] 已成功正确接收到数据"
fail = "[!] 消息已被篡改，请重新发送"

while True:
    # 需要签名的原始数据
    msg = input("[+] 请输入要发送给接收方的数据：")
    # 结束通信
    if msg == "exit":
        asock.sendto(msg.encode("utf-8"), ip_port)
        asock.close()
        exit(0)

    temp = msg

    # 生成 hmac sha1 签名
    msg = msg.encode()
    mac = hmac.new(byte_key, msg, hashlib.sha1)
    print(mac.hexdigest())

    # 发送签名和原始数据
    sendmsg = temp + "," + mac.hexdigest()
    sendmsg = sendmsg.encode("utf-8")
    asock.sendto(sendmsg, ip_port)

    msg, addr = asock.recvfrom(1024)
    print(msg)

    # 判断是否信息完整
    msg = msg.decode('utf-8')

    if msg==success.encode("utf-8"):
        asock.close()
        exit(0)

    # 有篡改重新发送直至正确为止
    while msg == fail.encode("utf-8"):
        asock.sendto(sendmsg, ip_port)
        msg, addr = asock.recvfrom(1024)
        if msg == success.encode("utf-8"):
            asock.close()
            exit(0)
