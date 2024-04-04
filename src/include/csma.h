#ifndef CSMA_H
#define CSMA_H

#include <vector>

#define READY_TO_TRANSMIT 0
#define TRANSMIT_COMPLETE 0

struct Node {
    int id;
    int collision_count;
    int backoff;
    int R;
    int ticks_remaining; // Number of ticks remaining for the node to finish transmitting
};

std::vector<Node> nodes;
int packet_length;
std::vector<int> R;
int max_retransmission_attempt;
int total_simulation_time;
int clk;
bool channel_occupied;
int num_packets_received;
int active_node_id; // The id of the node currently transmitting the packet. TODO: rename better

/**
 *  node_id = ID of node
 *  ticks = number of elapsed for loop iterations
 *  R = the R value, aka backoff upper limit value, since backoff is in the range of [0, R)
 * Returns the backoff value of the node, which is the pseudorandom number generator
 * following backoff = mod(node_id + ticks, R)
*/
int generate_backoff(int node_id, int ticks, int R);

/**
 * Called by a node. IF the node is about to start transmitting, is_occupied = true
 * Otherwise if the node is finished transmitting, is_occupied = false.
*/
void set_channel_occupied(bool is_occupied);

/**
 * Returns a list of node IDs that are ready to transmit.
*/
std::vector<int> get_ready_node_ids();

Node& get_node(int node_id);

/**
 * @brief Read the input file and assign the values to the variables.
 * 
 * @param input_file Input file stream.
 */
void assign_values(std::ifstream& input_file);

void initialize_nodes();

void transmit_packet();


#endif // CSMA_H