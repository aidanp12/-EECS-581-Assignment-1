#include <iostream>

using namespace std;

// function prototypes
bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);


int main() {
    /*
    main program loop, continue taking inputs from user until user enters "END". case sensitive.
    */ 
    
    // begin awaiting input from user, print message prompting for input
    // -> save user input into a string.
    // -> break loop if input == 'END'
    
    // run the extractIPv4 method using the user's input
    // -> if the method returns success, print: Extracted IPv4 address: A.B.C.D (decimal value: N, port: P) where N is the 32-bit decimal value and P is the port number or the literal text none.
    // -> if failure, print: Invalid input: no valid IPv4 address found


    return 0;
}

// function specifications provided on assignment
// Returns true if a valid address was found, false otherwise.
// On success: outAddress holds the 32-bit value,
// and outPort holds the port number, or -1 if no port was present.
// On failure: outAddress is set to 0 and outPort is set to -1.
bool extractIPv4(const string& str, unsigned long& outAddress, int& outPort) {
    bool addrFound = false;

    // begin creating new logic for extracting IPv4 here
    /*
    NOTES/REQUIREMENTS
    **IMPORTANT**
    The ONLY accepted IPv4 address formats are:
        a.b.c.d OR a.b.c.d:port. 
    where a, b, c, and d are numbers 0-255, and port is a number 0-65535.

    **VALID INPUT RULES**
    - if ANY part of the address is incorrect, whether it is a missing value (such as a.b.c.[blank] or a.b.c.d:[blank]), the address is not complete, and therefore the code should continue checking the string
    - if ANY part of the address is non-numeric, the address is invalid
    - if there's a stray period or colon next to an otherwise-valid address (such as a.b.c.d. or .a.b.c.d or a.b.c.d:), the address is invalid
    - essentially, if it COULD be a real address, then accept it. If not, ignore it.
    - values for a-d or port that have leading zeroes, such as 002 or 01, are to be deemed incorrect.
    - out of range or empty octets are deemed invalid
    - a second colon or a colon not immediately after the fourth octet are invalid
    - reject ANYTHING that doesn't match these rules
    - ONLY 1 address per line. If a valid addr is found, skip the rest of the line

    **LIBRARY RESTRICTIONS**
    the prof said no using existing libraries, so this code has to be all yours. tragic, i know.
    to be specific, you are NOT allowed to use the following:
    - Any string-to-number conversion function: atoi, atol, atoll, strtol, strtoul, strtod, stoi, stol, stoul, sscanf, scanf with numeric conversions.
    - Any address-parsing library function: inet_aton, inet_pton, inet_addr, or equivalents.
    - Any regular-expression facility (std::regex, POSIX regex.h, or similar) — the parsing and validation logic must be your own character-by-character code, not a pattern matched by a library.

    */
    return addrFound;
}