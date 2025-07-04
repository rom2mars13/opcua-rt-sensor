# opcua-rt-sensor

A multithreaded OPC UA server in C++ simulating real-time sensor data updates (soft real-time).

## Purpose

This project is a work in progress by **Romain Kusnik** as a technical demonstration for **Schneider Electric**.

Current goals:
- Implement an OPC UA server using [open62541](https://open62541.org/)
- Explore multithreaded programming in C++
- Build a soft real-time loop to update simulated sensor data
- Containerize the environment with Docker for embedded-like testing

> Note: Running on general-purpose systems (PC/Docker), real-time behavior is soft and not guaranteed. For true hard real-time, an RTOS or Linux with PREEMPT_RT is needed.

## Technologies

- C++17
- open62541 (OPC UA)
- Docker (dev container)
- CMake

## Status

- Initial server setup complete
- Basic real-time loop under development
- OPC UA integration ongoing

## Build & Run (via Docker)

```bash
docker build -t opcua-sensor .
docker run -it opcua-sensor
