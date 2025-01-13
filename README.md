# Distributed IoT Communication Infrastructure with SaaS Backend

This repository describes the architecture and functionality of a geographically distributed IoT infrastructure that combines hardware-based communication and SaaS backend capabilities for efficient data exchange and management.

## Overview

The system consists of the following components:
- **IoT Devices:** Geographically distributed devices with dual communication protocols.
- **Frontend:** IoT devices equipped with RADIO-1 and RADIO-2 physical communication protocols.
- **Backend:** SaaS internet platform implementing communication interfaces with IoT devices.

---

## Overall Software Architecture

The overall software architecture of the system is illustrated below using UML2 notation:

![image](https://github.com/user-attachments/assets/707caefc-c08b-40c6-ac70-65e0a33f0694)

### Component Description:

- **RADIO-1:** A hardware interface used for connecting IoT devices to the internet, exchanging geolocation data with the Backend, and receiving connection parameters for neighboring devices.
- **RADIO-2:** A protocol for peer-to-peer data exchange between neighboring IoT devices without requiring a connection.
- **IoT:** The main component of the system that implements geolocation, communication with the Backend, and interaction with neighboring devices.
- **Button, Sensor, Actuator:** Physical interfaces on IoT devices for interaction with the system and external events.
- **Token:** Data propagated between devices.
- **GEO:** Geolocation data.
- **ConnectionParams:** Connection parameters for neighboring devices, provided by the Backend.

For detailed explanations of use cases and component interactions, refer to the following sections.

---

### Key Features of IoT Devices
1. **Geolocation and Network Discovery:**  
   IoT devices autonomously determine their geolocation and locate local internet providers while moving through space.

2. **Communication via RADIO-1:**  
   - RADIO-1 is used for connecting to the internet and interacting with the Backend via a connection-oriented protocol.  
   - Data exchange with the Backend is extremely short compared to idle time between connections.  

3. **Backend Communication Flow (RADIO-1):**  
   A. IoT device sends its geolocation to the Backend.  
   B. Backend responds with a list of up to 10 neighboring IoT device connection parameters visible via RADIO-2.  
   C. IoT device disconnects from the internet (RADIO-1).  

4. **Peer-to-Peer Communication via RADIO-2:**  
   - RADIO-2 enables connectionless communication between IoT neighbors.  
   - Sensor data (Token) is transmitted to neighboring IoT devices' Actuators.

### IoT Device Channels
IoT devices include three physical channels for communication and interaction:
1. **Button:**  
   - Triggers communication via RADIO-1.  
   - Initiates the Backend interaction flow and updates neighbor data.  

2. **Sensor:**  
   - Collects data (Token) for distribution to neighbors via RADIO-2.  
   - Automatically initiates data propagation upon data availability.  

3. **Actuator:**  
   - Receives and processes data (Token) from other IoT devices via RADIO-2.  

---

## System Architecture

1. **Frontend (IoT Devices):**
   - Dual communication protocols:  
     - **RADIO-1:** Internet connectivity and Backend communication.  
     - **RADIO-2:** Peer-to-peer data exchange among IoT devices.  
   - Autonomous geolocation and network discovery capabilities.  

2. **Backend (SaaS Platform):**
   - Handles communication with IoT devices.  
   - Manages geolocation data and neighbor connection parameters.  

---

## Communication Protocols

### RADIO-1 Protocol:
- Connection-oriented protocol for internet communication.  
- Supports fast, intermittent data exchange with the Backend.

### RADIO-2 Protocol:
- Connectionless protocol for peer-to-peer communication.  
- Ensures low-latency data distribution among IoT neighbors.

---

## Use Cases

1. **Dynamic Geolocation Management:**  
   IoT devices adapt to their current location and optimize network connectivity.  

2. **Efficient Data Propagation:**  
   Sensor data is distributed seamlessly to neighboring devices for decentralized processing.  

3. **Scalable IoT Network:**  
   The system supports a growing number of devices with minimal dependency on centralized internet connectivity.  

---

## Contributing

Contributions are welcome! Please submit pull requests or open issues for any bugs, enhancements, or suggestions.

---

## License

This project is licensed under the MIT License.
