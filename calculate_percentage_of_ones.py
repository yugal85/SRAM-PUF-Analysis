def hex_to_bin(hex_string):
    """Convert hex string to binary string."""
    return bin(int(hex_string, 16))[2:].zfill(16)

def calculate_percentage_of_ones(hex_data):
    """Calculate the percentage of '1' bits in the hex data."""
    total_bits = len(hex_data) * 16  # Each hex string represents 16 bits
    ones_count = sum(bin(int(x, 16)).count('1') for x in hex_data)
    return (ones_count / total_bits) * 100

def read_hex_data(file_path):
    """Read hex data from a file."""
    with open(file_path, 'r') as file:
        data = file.read().split()
    return data

# Read the hex data from the file
file_path = '/Users/yugalsingam/Documents/newsramdata.txt'
hex_data = read_hex_data(file_path)

# Calculate the percentage of '1' bits
percentage_ones = calculate_percentage_of_ones(hex_data)

print(f"Percentage of '1' bits: {percentage_ones:.2f}%")
