# ELEC 331 Programming Assignment 3: Medium Access and Random Backoff Simulator

## Overview

A toy simulator that evaluates the performance of simplified Carrier Sense Multiple Access (CSMA) protocols in a wired network. We evaluate the network utilization when given an input file with configuration parameters.

The following pseudorandom number generator to set the backoff time is used:

```
backoff = mod(nodeID + ticks, R)
```

where:

- `nodeID` and `ticks` both start from 0
- `R` is the backoff window

## Instructions

Run the simulator program using the following command:

```
./csma <inputFileName>
```

## Input File:

- number of nodes N (not just 2),
- the packet length L,
- the minimum value of R (and how it increments),
- the value of M, and
- the total simulation time T.
