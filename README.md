# ErrorDetection
# readme
This project contains C++ codes of some error detection and correction methods. these methods tested on memory structure data.

* methods:  
parity, combinational parity, 2D-parity  
single checksum, Honeywell checksum, residue checksum  
CRC(Cyclic Redundancy Check), combinational CRC  
Hamming

## Steps 

1. Config desire memory([Header]()):   
    rows, cols values  
    call create_memory()
2. Set Fault parameters ([Header]()):  
    Fault_No or Parity_NO ,..
3. Uncommect method and run [ErrorDetection]()
