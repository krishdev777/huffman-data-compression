# Huffman Lossless Data Compression Engine

An empirical algorithmic study of Information Theory, Greedy Tree Construction, and Priority Queue optimization for prefix-free lossless data compression.

## Benchmark Results
| Metric | Uncompressed (ASCII Baseline) | Huffman Variable-Length Encoded | Performance Gain |
| :--- | :--- | :--- | :--- |
| **Bit Representation** | 8 bits / char | ~4.4 bits / char (Average) | **44.8% Space Saved** |
| **Payload Size (Corpus)** | 6,850 Bytes | 3,780 Bytes | **1.81x Compression Factor** |
| **Pipeline Latency** | Baseline | ~1,250 microseconds | Real-time Throughput |

## Algorithmic Architecture
- **Frequency Analysis**: O(N) linear pass using Hash Map.
- **Greedy Tree Building**: O(K log K) via Min-Heap (`std::priority_queue`).
- **Encoding Generation**: Depth-First Tree Traversal (O(K)).

## How to Compile & Run
```bash
g++ -O3 main.cpp -o huffman
./huffman