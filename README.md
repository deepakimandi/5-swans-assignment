# 5-swans-assignment

This assignment demonstrates encoding and decoding data using FlatBuffers.

## Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/deepakimandi/5-swans-assignment
   ```

2. **Install FlatBuffers Python package:**
   ```bash
   pip3 install flatbuffers
   ```

3. **Generate FlatBuffers code:**
   ```bash
   flatc --cpp client.fbs
   flatc --python client.fbs
   ```
      
4. **Complie and Execute C++ encoder script:**
   ```bash
   g++ -std=c++11 -o fb_encoder fb_encoder.cpp -lflatbuffers
   ./fb_encoder fb_bytes.bin
   ```

5. **Execute Python decoder script:**
   ```bash
   python3 fb_decoder.py fb_bytes.bin
   ```



