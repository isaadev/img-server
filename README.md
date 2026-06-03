# Image Processing Server

A TCP image-processing server written in C. The server accepts image requests from a client, stores registered images in memory, processes transformation requests through a bounded FIFO queue, and logs per-request timing data for performance analysis.

This project is a good snapshot of systems-level work: sockets, pthreads, semaphores, memory management, binary image serialization, and CPU-bound image filters.

## Features

- TCP server using POSIX sockets
- Worker-thread request processing with a bounded FIFO queue
- Queue overflow handling with rejected-request responses
- Synchronization with semaphores for queue access and logging
- In-memory image registry with overwrite or copy-on-write request behavior
- Per-request timestamps for receipt, start, and completion
- 24-bit BMP load/save helpers and network image serialization

## Supported Operations

- Register image
- Retrieve image
- Rotate 90 degrees clockwise
- Blur with a 3x3 averaging kernel
- Sharpen with a 3x3 convolution kernel
- Detect vertical edges with a Sobel kernel
- Detect horizontal edges with a Sobel kernel

## Build

```sh
make
```

The server binary is written to:

```sh
build/server_mimg
```

You can also build and run a local image-library smoke test:

```sh
make smoke-test
```

The smoke test writes transformed BMP files into `build/`.

## Run

```sh
./build/server_mimg -q 16 -w 1 -p FIFO 2222
```

Arguments:

- `-q`: maximum number of queued requests
- `-w`: worker count. This implementation currently supports `1`.
- `-p`: queue policy. This implementation currently supports `FIFO`.
- final argument: TCP port

The included `client` binary is a Linux x86-64 executable. On macOS, build and smoke-test the server locally, then run the client in a compatible Linux environment if you want end-to-end client/server testing.

## Log Format

Completed requests are logged in this shape:

```text
T<worker_id> R<request_id>:<client_timestamp>,<operation>,<overwrite>,<client_img_id>,<server_img_id>,<receipt>,<start>,<completion>
```

Rejected requests are logged as:

```text
X<request_id>:<client_timestamp>,<request_length>,<receipt>
```

The queue state is also printed after each processed request:

```text
Q:[R1,R2,R3]
```

## Architecture

The main thread accepts a client connection, registers incoming images immediately, and enqueues transformation/retrieval requests. The worker thread consumes requests from the FIFO queue, applies the requested image operation, sends a response, and optionally sends the transformed image payload back to the client.

Image payloads are serialized over the socket as:

```text
magic bytes "IMG" + width + height + width*height 32-bit RGB pixels
```

## Project Notes

This repository includes course support code for timing, image helpers, and MD5 hashing. My implementation focus is the server-side request lifecycle: queue insertion/removal, worker processing, request rejection, image registration, transformation dispatch, and request logging.

## Future Improvements

- Support multiple workers safely by protecting the shared image registry and serializing socket writes.
- Add a source-built client or integration test harness instead of relying on the included Linux client binary.
- Add stronger request validation for invalid image IDs and malformed socket payloads.
- Add CI to build and smoke-test the project automatically on Linux and macOS.
