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

void setup() {
    Serial.begin(115200);

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
        pinMode(dataLinesIDT[i], OUTPUT);
    }

    // Write all zeros to the SRAM
    writeSRAM(0x0000);

    // Write all ones to the SRAM (uncomment for the second run)
    // writeSRAM(0xFFFF);

    // Stop the code execution
    Serial.end(); // Stop the Serial communication
    noInterrupts(); // Disable interrupts
    while (true) {
        // Infinite loop to halt the program
    }
}

void writeSRAM(uint16_t value) {
    uint32_t numWrites = 4194304 / 16; // This equals 262,144 writes

    for (uint32_t address = 0; address < numWrites; address++) {
        // Set the address
        for (int i = 0; i < numAddrLines; i++) {
            digitalWrite(addrLinesIDT[i], (address >> i) & 1);
        }

        // Set the data value
        for (int i = 0; i < numDataLines; i++) {
            digitalWrite(dataLinesIDT[i], (value >> i) & 1);
        }
        digitalWrite(CS, LOW);
        digitalWrite(WE, LOW);
        delayMicroseconds(5); 
        digitalWrite(WE, HIGH);
        digitalWrite(CS, HIGH);
    }
}
void loop() {
}
