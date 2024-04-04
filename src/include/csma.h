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

std::vector<Node> nodes;        /**< The nodes in the simulation that can send packets. */
int packet_length;              /**< The length of the packet in number of ticks it takes to transmit. */
std::vector<int> R;             /**< The possible backoff windows. */
int max_retransmission_attempt; /**< 
                                  * The maximum number of retransmission attempts before the 
                                  * packet is dropped.
                                  */
int total_simulation_time;      /**< The total number of ticks to simulate. */
int clk;                        /**< The current tick of the simulation. */
bool channel_occupied;          /**< The state of the transmission channel. */
int num_packets_received;       /**< The number of packets successfully transmitted. */
int active_node_id;             /**< The id of the node currently transmitting the packet. */

/**
 * @brief Generate a backoff value for a node, which is the pseudorandom number generator following
 * backoff = mod(node_id + ticks, R)
 * 
 * @param node_id The ID of the node to which the backoff value is assigned.
 * @param ticks The number of ticks that have elapsed in the simulation.
 * @param R The R value of the node, which is the upper limit of the backoff value since the
 * backoff is in the range of [0, R).
 * @return int The backoff value of the node.
 */
int generate_backoff(int node_id, int ticks, int R);

/**
 * @brief Set the transmission channel to occupied or unoccupied.
 * 
 * This function is called by a node that is about to start transmitting a packet in order to block
 * the channel from other nodes. It is also called by a node that has finished transmitting its
 * packet in order to unblock the channel.
 * 
 * @param is_occupied A boolean value indicating whether to set the channel to occupied or not.
 */
void set_channel_occupied(bool is_occupied);

/**
 * @brief Get the nodes that are ready to transmit a packet (ie have a backoff of 0).
 * 
 * @return std::vector<int> A list of node IDs that are ready to transmit.
 */
std::vector<int> get_ready_node_ids();

/**
 * @brief Read the input file and assign the values to the variables.
 * 
 * @param input_file Input file stream.
 */
void assign_values(std::ifstream& input_file);

/**
 * @brief Initialize the nodes in the simulation and their properties.
 */
void initialize_nodes();

/**
 * @brief Transmit a packet from the active node.
 * 
 * @param active_node_id The ID of the node transmitting the packet.
 * @param ticks The current tick of the simulation.
 */
void transmit_packet(int active_node_id, int ticks);


#endif // CSMA_H