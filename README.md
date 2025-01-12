# RFID Card Payment System

This project involves the development of a full RFID card payment system that automates the payment of dues within a department. The system is divided into two primary sections: the hardware (RFID integration) and the software (website and API).

## Project Structure

- **Hardware Development**:  
  Designed and programmed the RFID card reader system using microcontrollers to process payment transactions. The hardware securely communicates with the system and registers dues payments using RFID cards.

- **Software Development**:  
  Developed a full-stack web application using **Flask** to manage user payments, track dues, and display real-time data in a user dashboard. The system also includes an API for integrating with other systems, ensuring seamless communication between hardware and software.

## Key Features

### Hardware:
- RFID card reader integration with microcontroller.
- Secure transaction processing and validation.
- Real-time data syncing with the backend system.

### Software:
- User-friendly web interface for managing payments.
- Real-time updates on dues and payment status.
- Secure API for backend communication and data management.
- User dashboard to view payment history and track dues.

## Technologies Used
- **Hardware**: RFID, Microcontrollers ( ESP8266 -nodeMcu)
- **Software**: 
  - Frontend: HTML, CSS, JavaScript Bootstrap
  - Backend: Python, Flask
  - API: RESTful API development with Flask

## Setup Instructions

### Hardware:
1. Connect the RFID card reader to the microcontroller (esp8266).
2. Program the microcontroller with the .ino file.

### Software:
1. Clone this repository:
   ```bash
   https://github.com/dracer001/RFID-Card-Payment-System-Hardware-and-Software-.git
