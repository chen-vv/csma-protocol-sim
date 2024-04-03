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

int generate_backoff(int node_id, int ticks, int R) {
    int backoff = (node_id + ticks) % R;
    return backoff;
}

bool set_channel_occupied(bool is_occupied) {
    if (is_occupied && channel_occupied) {
        return false;
    }

    channel_occupied = is_occupied;
    return true;
}

Node get_node(int node_id) {
    return nodes[node_id];
}

std::vector<int> get_ready_node_ids() {
    std::vector<int> ready_nodes;

    for (const auto& node : nodes) {
        if (node.status == READY_TO_TRANSMIT) {
            ready_nodes.push_back(node.id);
        }
    }

    return ready_nodes;
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

    channel_occupied = false;
    num_packets_received = 0;

    // For each node, initialize its status and other properties
    for (auto& node : nodes) {
        node.collision_count = 0;
        node.R = R[0];
        node.status = READY_TO_TRANSMIT;
        node.backoff = generate_backoff(node.id, 0, node.R);
    }

    for (int ticks = 0; ticks < total_simulation_time; ticks++) {
        if (channel_occupied) {
            // Freeze node countdowns but decrement active_node's backoff
            Node active_node = get_node(active_node_id);
            active_node.backoff--;
        } else {
            std::vector<int> ready_nodes = get_ready_node_ids();

            if (ready_nodes.empty()) {
                // Decrement backoff of all nodes
                for (auto& node : nodes) {
                    node.backoff--;
                }
            } else {
                if (ready_nodes.size() == 1) {
                    bool transmission_started = set_channel_occupied(true);

                    if (transmission_started) {
                        active_node_id = ready_nodes[0];
                        nodes[active_node_id].status = TRANSMIT;
                    }
                } else {
                    for (auto& node : nodes) {
                        if (node.status == READY_TO_TRANSMIT) {
                            node.collision_count++;

                            if (node.collision_count > max_retransmission_attempt) {
                                // Drop packet and reset node
                                node.R = R[0];
                                node.collision_count = 0;
                                node.backoff = generate_backoff(node.id, ticks, node.R);
                                node.status = WAITING;
                                continue;
                            }

                            // Made a post (#345) asking about this.
                            // For now, assume we just double R  
                            // node.R = R[node.collision_count];
                            node.R = node.R * 2;

                            node.backoff = generate_backoff(node.id, ticks, node.R);
                            node.status = WAITING;
                        }
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
