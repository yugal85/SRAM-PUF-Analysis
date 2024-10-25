def hex_to_bin(hex_string):
    """Convert hex string to binary string."""
    return bin(int(hex_string, 16))[2:].zfill(16)

def calculate_bits(hex_data):
    """Calculate the total number of bits, ones, and zeroes in the hex data."""
    total_bits = len(hex_data) * 16  # Each hex string represents 16 bits
    ones_count = sum(bin(int(x, 16)).count('1') for x in hex_data)
    zeros_count = total_bits - ones_count
    return total_bits, ones_count, zeros_count

def read_hex_data(file_path):
    """Read hex data from a file."""
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        data = file.read().split()
    return data

def calculate_bit_difference(hex_data1, hex_data2):
    """Calculate the bit difference between two sets of hex data."""
    assert len(hex_data1) == len(hex_data2), "Data files must be of equal length"
    bit_diff_count = 0
    total_bits = len(hex_data1) * 16  # Each hex string represents 16 bits

    for h1, h2 in zip(hex_data1, hex_data2):
        bin1 = hex_to_bin(h1)
        bin2 = hex_to_bin(h2)
        bit_diff_count += sum(b1 != b2 for b1, b2 in zip(bin1, bin2))

    return bit_diff_count, total_bits

# File paths for power-up states after writing all zeros and all ones
file_path1 = '/Users/yugalsingam/Documents/puf_write0.txt'
file_path2 = '/Users/yugalsingam/Documents/puf_write1.txt'

hex_data1 = read_hex_data(file_path1)
hex_data2 = read_hex_data(file_path2)

# Calculate the total number of bits, ones, and zeroes for the first file
total_bits1, total_ones1, total_zeros1 = calculate_bits(hex_data1)

# Calculate the total number of bits, ones, and zeroes for the second file
total_bits2, total_ones2, total_zeros2 = calculate_bits(hex_data2)

# Ensure both files have the same number of bits
assert total_bits1 == total_bits2, "The total number of bits in both files must be the same"

# Calculate the bit difference between the two power-up states
bit_diff_count, total_bits = calculate_bit_difference(hex_data1, hex_data2)

# Calculate the percentage of bit differences
percentage_diff = (bit_diff_count / total_bits) * 100

print(f"Total number of bits: {total_bits}")
print(f"Total number of '1' bits in power-up state after writing zeros: {total_ones1}")
print(f"Total number of '0' bits in power-up state after writing zeros: {total_zeros1}")
print(f"Total number of '1' bits in power-up state after writing ones: {total_ones2}")
print(f"Total number of '0' bits in power-up state after writing ones: {total_zeros2}")
print(f"Total number of differing bits: {bit_diff_count}")
print(f"Percentage of differing bits: {percentage_diff:.2f}%")
