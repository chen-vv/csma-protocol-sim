#ifndef CSMA_H
#define CSMA_H

#include <vector>

enum NodeStatus {
    READY_TO_TRANSMIT,
    TRANSMIT,
    WAITING
};

struct Node {
    int collision_count;
    int backoff;
    int R;
    NodeStatus status;
};

std::vector<Node> nodes;
int packet_length;
std::vector<int> R;
int max_retransmission_attempt;
int total_simulation_time;
int clk;
bool channel_occuiped;
int num_packets_received;

/**
 * @brief Read the input file and assign the values to the variables.
 * 
 * @param input_file Input file stream.
 */
void assign_values(std::ifstream& input_file);

#endif // CSMA_H