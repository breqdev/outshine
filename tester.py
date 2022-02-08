import sys
import serial

ser = serial.Serial(sys.argv[1])


try:
    while True:
        i = input()
        if i == "q":
            break

        result = bytes(bytearray.fromhex(i) + b"\n")

        ser.write(result)

finally:
    ser.close()
