#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "include/csma.h"

void assign_values(std::ifstream &input_file) {
    std::string line;

    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        char parameter;
        ss >> parameter;

        switch (parameter) {
            case 'N': {
                int N;
                ss >> N;
                nodes.resize(N);
                break;
            }

            case 'L':
                ss >> packet_length;
                break;

            case 'M':
                ss >> max_retransmission_attempt;
                break;

            case 'R': {
                int r_value;
                R.clear();
                while (ss >> r_value) {
                    R.push_back(r_value);
                }
                break;
            }

            case 'T':
                ss >> total_simulation_time;
                break;

            default:
                std::cerr << "Unknown parameter: " << parameter << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfilename>" << std::endl;
        return EXIT_FAILURE;
    }

    // Open the input file
    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    assign_values(input_file);

    input_file.close();

    clk = 0;
    channel_occuiped = false;
    num_packets_received = 0;

    // For each node, initialize its status and other properties
    for (auto& node : nodes) {
        node.collision_count = 0;
        node.backoff = 0;
        node.R = R.empty() ? 0 : R[0];
        node.status = READY_TO_TRANSMIT;
    }

    return EXIT_SUCCESS;
}
