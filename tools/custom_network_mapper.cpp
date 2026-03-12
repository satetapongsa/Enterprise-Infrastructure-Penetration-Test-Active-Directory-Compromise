/*
 * Custom Network Mapper
 * Description: An internal tool for mapping discovered network segments and hosts
 * using linear lists and chain nodes for efficient memory allocation.
 */

#include <iostream>
#include <string>

using namespace std;

// Define a Node to represent a discovered host on the network
struct HostNode {
    string ipAddress;
    string hostname;
    string os;
    HostNode* next; // Pointer to the next node in the chain
};

// Linked List to manage the discovered hosts dynamically
class NetworkSubnetList {
private:
    HostNode* head;

public:
    NetworkSubnetList() {
        head = nullptr;
    }

    // Allocate memory for a new host node and add to the linear list
    void addHost(string ip, string name, string osType) {
        HostNode* newNode = new HostNode();
        newNode->ipAddress = ip;
        newNode->hostname = name;
        newNode->os = osType;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            HostNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "[+] Host Added via Pointer Allocation: " << ip << " (" << name << ")" << endl;
    }

    // Traverse the chain nodes and display the network map
    void displaySubnet() {
        HostNode* temp = head;
        cout << "\n--- Discovered Subnet Map ---" << endl;
        while (temp != nullptr) {
            cout << "IP: " << temp->ipAddress << " | Host: " << temp->hostname 
                 << " | OS: " << temp->os << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Free memory allocation securely
    ~NetworkSubnetList() {
        HostNode* current = head;
        while (current != nullptr) {
            HostNode* nextNode = current->next;
            delete current; // Prevent memory leaks
            current = nextNode;
        }
    }
};

int main() {
    cout << "Initializing Custom Network Mapper Engine..." << endl;
    NetworkSubnetList vlan20_Account;

    // Simulating hosts discovered during reconnaissance
    vlan20_Account.addHost("10.10.20.15", "ACC-FILESHARE", "Windows Server 2019");
    vlan20_Account.addHost("10.10.20.50", "ACC-ADMIN-PC", "Windows 10 Pro");
    vlan20_Account.addHost("10.10.20.51", "ACC-STAFF-01", "Windows 10");

    vlan20_Account.displaySubnet();

    return 0;
}
