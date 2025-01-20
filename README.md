# C-Honeypot

# Honeypot Project in C  

## Overview  
This project is a basic **honeypot** implemented in C. Its purpose is to act as a decoy system to detect unauthorized access attempts and log suspicious activities.  

## Features  
- Lightweight honeypot written in pure C  
- Logs connection attempts and suspicious activities  
- Configurable to simulate different responses

## Getting Started  

### Prerequisites  
- A C compiler (e.g., GCC)  
- Basic understanding of networking (if applicable)  

### Building the Project  
Compile the code using:  
```bash
gcc -o honeypot honeypot.c
```
## Configuration
Before running the client.py script, you need to configure the honeypot server IP and port that the client will connect to.

Open the client.py file in a text editor (e.g., VS Code, Sublime Text, or Notepad++).
Locate the following variables:

honeypot_ip = "127.0.0.1"  # Change this to the honeypot server IP
honeypot_port = 8080       # Change this to the honeypot server port
Replace honeypot_ip with the IP address of the honeypot server and honeypot_port with the appropriate port (default is 8080).

## Running the Script

To run the client.py script, follow these steps:

Open a Terminal (or Command Prompt on Windows).

Navigate to the directory where client.py is located.
```
cd path/to/client.py/directory
```
Run the Script: Execute the script with the following command:
```bash
python client.py
```
- The script will attempt to connect to the honeypot server at the configured IP and port.
- If the connection is successful, the script will print a success message.
- If the connection fails (e.g., server not reachable or connection timeout), an error message will be displayed.



