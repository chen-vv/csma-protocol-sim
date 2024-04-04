/** 
 * @file csma.h
 * @brief Function prototypes and data structures for CSMA simulation.
 *
 * This contains the function prototypes and any macros, constants,
 * or global variables you will need for simulating the Carrier Sense
 * Multiple Access (CSMA) protocol.
 *
 * @author Vicky Chen (chen-vv)
 * @author Eric Omielan (eomielan)
 * @bug No known bugs.
 */

#ifndef CSMA_H
#define CSMA_H

#include <vector>

/**
 * @brief Macro to determine whether a node is ready to transmit.
 * 
 * This macro is used to check the node's backoff state. When the value
 * of the backoff equals this macro, the node is ready to transmit its 
 * packet.
*/
#define READY_TO_TRANSMIT 0

/**
 * @brief Macro to determine whether a node has completed transmitting.
 * 
 * This macro is used to check whether a node's packet transmission is
 * completed. When the value of the node's ticks_remaining equals this
 * macro, the node has completed transmitting its packet.
*/
#define TRANSMIT_COMPLETE 0

/**
 * @brief Structure to represent a node in the CSMA simulation.
 * 
 * This structure contains the necessary information to represent a node
 * in the CSMA simulation. It includes the node's ID, the number of
 * collisions the node has experienced, the backoff value, the R value,
 * and the number of ticks remaining for the node to finish transmitting.
*/
struct Node {
    int id;                     /**< The unique identifier of the node. */                     
    int collision_count;        /**< The number of collisions experienced. */
    int backoff;                /**< 
                                  * The backoff value of the node.
                                  * This value determines the amount of time the node
                                  * must wait before transmitting its packet. 
                                  */
    int R;                      /**< 
                                  * The R value of the node.  
                                  * This value is used to determine the upper 
                                  * limit of the backoff value.
                                  */
    int packet_ticks_remaining;        /**< 
                                  * The number of ticks remaining for the node
                                  * to finish transmitting its packet.
                                  */
};

// TODO: left off here
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