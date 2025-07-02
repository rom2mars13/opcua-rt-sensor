# opcua-rt-sensor

A multithreaded OPC UA server in C++ simulating real-time sensor data updates (soft real-time).

## Purpose

This project was created by **Romain Kusnik** as a technical demonstration for **Schneider Electric**.

This project demonstrates:
- An OPC UA server using [open62541](https://open62541.org/)
- Multithreaded programming in C++
- A **soft real-time** loop that updates simulated sensor values every 10 ms
- An embedded-like environment using Docker

> On a general-purpose system (like a PC or Docker container), real-time behavior is **soft**: the timing is targeted but **not strictly guaranteed**. For **hard real-time**, you would need a real-time OS (RTOS) or a real-time patched Linux kernel (e.g. PREEMPT_RT).

## Technologies

- C++17
- open62541 (OPC UA)
- Docker (dev container)
- CMake

## Build & Run (via Docker)

```bash
docker build -t opcua-sensor .
docker run -it opcua-sensor
