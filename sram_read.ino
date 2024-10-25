#define CS   7
#define OE   47
#define WE   8
#define LB   45
#define UB   46

const int numAddrLines = 18;
const int numDataLines = 16;

// Address lines mapping
int addrLinesIDT[] = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 32, 33, 34, 35, 36, 48, 49, 50};

// Data lines mapping
int dataLinesIDT[] = {22, 23, 24, 25, 26, 27, 28, 29, 37, 38, 39, 40, 41, 42, 43, 44};

int countOnes(uint16_t value) {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

void setup() {
    Serial.begin(115200);  // Increase baud rate for faster transmission

    // Initialize control pins
    pinMode(CS, OUTPUT);
    pinMode(OE, OUTPUT);
    pinMode(WE, OUTPUT);
    pinMode(LB, OUTPUT);
    pinMode(UB, OUTPUT);
    digitalWrite(LB, LOW);
    digitalWrite(UB, LOW);
    digitalWrite(CS, HIGH);
    digitalWrite(OE, HIGH);
    digitalWrite(WE, HIGH);  // Ensure WE is HIGH to avoid accidental writes

    // Initialize address and data lines
    for (int i = 0; i < numAddrLines; i++) {
        pinMode(addrLinesIDT[i], OUTPUT);
    }
    for (int i = 0; i < numDataLines; i++) {
        pinMode(dataLinesIDT[i], INPUT);
    }

    // Define the number of reads to achieve 4Mb of data (4,194,304 bits / 16 bits per read)
    uint32_t numReads = 4194304 / 16; // This equals 262,144 reads

    // First pass to count total ones and zeros
    int totalOnes = 0;
    int totalZeros = 0;
    for (uint32_t address = 0; address < numReads; address++) {
        uint16_t data = readSRAM(address);
        totalOnes += countOnes(data);
        totalZeros += (numDataLines - countOnes(data));  
    }

    // Print the totals
    // Serial.print("Total number of 1s: ");
    // Serial.println(totalOnes);
    // Serial.print("Total number of 0s: ");
    // Serial.println(totalZeros);
    // Serial.print("Total number of bits: ");
    // Serial.println(totalOnes + totalZeros);

    // Second pass to print data
    for (uint32_t address = 0; address < numReads; address++) {
        uint16_t data = readSRAM(address);
        char buffer[5]; // Buffer to hold the formatted string
        snprintf(buffer, sizeof(buffer), "%04X", data); 
        Serial.print(buffer);
        Serial.print(" ");
        if ((address + 1) % 1000 == 0) {  // Print a newline after every 1000 values
            Serial.println();
        }
    }

    // Stop the code execution
    Serial.end(); // Stop the Serial communication
    noInterrupts(); // Disable interrupts
    while (true) {
        // Infinite loop to halt the program
    }
}

uint16_t readSRAM(uint32_t address) {
    uint16_t data = 0;

    // Set the address
    for (int i = 0; i < numAddrLines; i++) {
        digitalWrite(addrLinesIDT[i], (address >> i) & 1);
    }

    digitalWrite(CS, LOW);
    digitalWrite(OE, LOW); 

    // Read the data
    for (int i = 0; i < numDataLines; i++) {
        if (digitalRead(dataLinesIDT[i])) {
            data |= (1 << i);
        }
    }
 
    digitalWrite(OE, HIGH);
    digitalWrite(CS, HIGH);

    return data;
}
void loop() {
}
