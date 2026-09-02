#include <iostream>
#include <string>

using namespace std;

// function prototypes
bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);


int main() {
    string input;

    // Read and process one line at a time until the sentinel is entered.
    while (true) {
        // > updated input string to match the assignment's exact format
        cout << "Enter a string (or 'END' to quit): ";
        getline(cin, input);

        if (!cin || input == "END") {
            // > didn't include a termination message, added the next line
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address;
        int port;

        if (extractIPv4(input, address, port)) {
            cout << "Extracted IPv4 address: "
                 << ((address >> 24) & 255) << '.'
                 << ((address >> 16) & 255) << '.'
                 << ((address >> 8) & 255) << '.'
                 << (address & 255)
                 << " (decimal value: " << address << ", port: ";

            if (port == -1) {
                cout << "none";
            } else {
                cout << port;
            }

            cout << ')' << endl;
        } else {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
    }


    return 0;
}

// Find the first valid IPv4 address and optionally its port in the input line.
bool extractIPv4(const string& str, unsigned long& outAddress, int& outPort) {
    outAddress = 0;
    outPort = -1;

    // Keep digit handling local so parsing never relies on conversion helpers.
    const auto isDigit = [](char character) {
        return character >= '0' && character <= '9';
    };

    for (size_t start = 0; start < str.size(); ++start) {
        if (!isDigit(str[start])) {
            continue;
        }

        // A match cannot begin in the middle of another number or delimiter.
        if (start > 0 && (isDigit(str[start - 1]) || str[start - 1] == '.' || str[start - 1] == ':')) {
            continue;
        }

        size_t position = start;
        int octets[4];
        bool valid = true;

        // Parse exactly four dot-separated octets.
        for (int octetIndex = 0; octetIndex < 4; ++octetIndex) {
            // > handle finished strings
            if (position >= str.size() || !isDigit(str[position])) {
                valid = false;
                break;
            }

            size_t digitStart = position;
            int value = 0;

            // > found digit in string, begin inspecting for complete octet
            while (position < str.size() && isDigit(str[position])) {
                // > handle digits that exceed octet size (>3 digits)
                if (position - digitStart == 3) {
                    valid = false;
                    break;
                }
                value = value * 10 + (str[position] - '0');
                ++position;
            }

            // > ignore octets greater than numerical max of 255
            if (!valid || (position - digitStart > 1 && str[digitStart] == '0') || value > 255) {
                valid = false;
                break;
            }

            octets[octetIndex] = value;

            // > check if a non-final octet is followed by a '.'
            if (octetIndex < 3) {
                if (position >= str.size() || str[position] != '.') {
                    valid = false;
                    break;
                }
                ++position;
            }
        }

        if (!valid) {
            continue;
        }

        int port = -1;

        // A colon is valid only when followed by one valid port number.
        if (position < str.size() && str[position] == ':') {
            ++position;
            size_t portStart = position;
            int portValue = 0;

            // > next couple lines are similar to octet detection, just for the port parameters
            while (position < str.size() && isDigit(str[position])) {
                if (position - portStart == 5) {
                    valid = false;
                    break;
                }

                portValue = portValue * 10 + (str[position] - '0');
                ++position;
            }
            // > validate port number is correct
            if (!valid || position == portStart ||
                (position - portStart > 1 && str[portStart] == '0') || portValue > 65535) {
                valid = false;
            } else {
                port = portValue;
            }
        }

        // A period or colon immediately after the address is always malformed.
        if (valid && position < str.size() && (str[position] == '.' || str[position] == ':')) {
            valid = false;
        }

        if (!valid) {
            continue;
        }

        // > assign the various indices of the output to the corresponding results from the detected octets
        outAddress = (static_cast<unsigned long>(octets[0]) << 24) |
                     (static_cast<unsigned long>(octets[1]) << 16) |
                     (static_cast<unsigned long>(octets[2]) << 8) |
                     static_cast<unsigned long>(octets[3]);
        outPort = port;
        return true;
    }

    return false;
}