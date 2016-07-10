/**
 * Problem:
 *      MAC Learning
 *
 * Links:
 *      https://www.hackerrank.com/companies/vmware/challenges/mac-learning
 */

#include <iostream>
#include <unordered_map>

using namespace std;

typedef long long MAC;
typedef short port;

/**
 * An Ethernet address, or "MAC address", is a 48-bit (6-byte) number that is canonically represented by six pairs of
 * hex digits delimited by colons. Every NIC should have a globally unique MAC.
 */
bool from_string(const string& address, MAC& mac)
{
    if (address.length() != 17) return false;

    mac = 0;
    for (size_t pos = 0; pos < 17; pos += 3)
    {
        size_t end = 0;
        int b = std::stoi(address.substr(pos, 2), &end, 16);
        if (end != 2) return false;
        mac <<= 8;
        mac |= b;
    }

    return true;
}

/**
 * MAC addresses have a little bit of structure, and in particular the least-significant bit of the first byte of a MAC
 * is 0 if the address represents a single host or 1 if the address is a special "multicast" address that represents
 * multiple hosts. Thus, 00:26:b9:8c:b0:f9 (the Ethernet address for my workstation's NIC) is a unicast address,
 * because 00 has 0 as its least-significant bit, whereas ff:ff:ff:ff:ff:ff is a multicast address (specifically
 * the special "broadcast" address).
 */
bool is_multicast(MAC address)
{
    return (address & ((MAC)1 << 40)) != 0;
}

string /*pout*/ route(port pin, MAC destination, MAC source)
{
    static const size_t CAP = 127;
    typedef unordered_map<MAC, port> mac_dictionary;
    static mac_dictionary mac_dic(CAP);

    // If <source> is a multicast address, terminate the algorithm with output "drop"
    // indicating that the packet should be dropped.
    if (is_multicast(source)) return "drop";

    // Add the mapping <source> -> <pin> to the dictionary. If there is already a mapping from <source> to a different
    // port, update the mapping; if <source> -> <pin> already exists, no change is necessary.
    mac_dic[source] = pin;

    // If <destination> is a multicast address, terminate the algorithm with output "flood"
    // indicating that the packet should be forwarded to all of the switch's ports except for port <pin>.
    if (is_multicast(destination)) return "flood";

    // Search for a mapping for <destination>. If there is no such mapping, terminate the algorithm with output "flood"
    // (the switch doesn't know which port to use, so it outputs it on all the ports).
    // Otherwise, let <pout> be the value found.
    mac_dictionary::const_iterator it = mac_dic.find(destination);
    if (it == mac_dic.end()) return "flood";
    port pout = it->second;

    // If <pin> = <pout>, terminate the algorithm with output "drop" because a switch should not send a packet back
    // out the port it came in on.
    if (pin == pout) return "drop";

    // Terminate the algorithm with output <pout>.
    return std::to_string(pout);
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        port pin;
        string dstr, sstr;
        MAC destination, source;
        cin >> pin >> dstr >> sstr;
        from_string(dstr, destination);
        from_string(sstr, source);
        cout << route(pin, destination, source) << endl;
    }
    return 0;
}
