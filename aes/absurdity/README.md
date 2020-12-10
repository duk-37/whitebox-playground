# Absurd white-box AES implementation
Somewhat similar to other whitebox AES implementations in that it uses lookup tables to encode the expanded round key.

# Differences
- 256 megabytes(!!!!) of lookup tables
  - Not practical whatsoever
- An attempt at resistance to DFA through duplication and lossy per-state encoding
  - Each bit of data per state has its own custom whitebox AES state
  - Final state XORs all states together to get output
