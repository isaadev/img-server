# 🖥️ Multi-threaded Image Processing Server

A concurrent image processing server built in C using POSIX threads and TCP/IP. The server handles client requests for image transformations (rotate, blur, sharpen, edge detection) in FIFO order, with support for bounded queues and detailed request logging.

## Features

- Multi-threaded request processing with POSIX threads  
- FIFO queue with capacity limits to prevent overload  
- Synchronization via semaphores and mutexes  
- Configurable worker threads and queue size  
- Per-request timestamp logging for analysis and debugging  

## Supported Image Operations

- Rotate (90 degrees)  
- Blur  
- Sharpen  
- Edge Detection  

## Build Instructions

Requires `gcc` and a POSIX-compliant OS (Linux/macOS).

```bash
make
```

## Run the Server

```bash
./server -p <port> -w <num_workers> -q <queue_size>
```
### Example 
```bash
./server -p 8080 -w 4 -q 8
```
