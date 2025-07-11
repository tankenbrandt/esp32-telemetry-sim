import serial
import time

#replace when connected to board
port = "/dev/ttyUSB0"
baud_rate = 115200

ser = serial.Serial(port, baud_rate, timeout = 1)
time.sleep (2) #wait for connection to stabilize

print("Ground station is up! Waiting for data...\n")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(f'[RECEIVED] {line}')
except KeyboardInterrupt:
    print("\nGround station shuttin down")
    ser.close()