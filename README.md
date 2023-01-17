# ErrorDetection
This project contains C++ codes of some error detection and correction methods. these methods tested on memory structure data.

* methods:  
parity, combinational parity, 2D-parity  
single checksum, Honeywell checksum, residue checksum  
CRC(Cyclic Redundancy Check), combinational CRC  
Hamming

### Steps 

1. Config desire memory([Header](https://github.com/sadjadasadi/ErrorDetection/blob/main/Header.h)):   
    rows, cols values  
    call create_memory()
2. Set Fault parameters ([Header](https://github.com/sadjadasadi/ErrorDetection/blob/main/Header.h)):  
    Fault_No or Parity_NO ,..
3. Uncommect method and run [ErrorDetection](https://github.com/sadjadasadi/ErrorDetection/blob/main/ErrorDetection.cpp)
