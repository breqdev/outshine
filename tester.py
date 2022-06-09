import sys
import serial
import time

ser = serial.Serial(sys.argv[1])


try:
    while True:
        transaction = []
        anim = input("Animation number: ")
        anim = int(anim[0]) << 3 | int(anim[1])
        transaction.append(0x40 | anim)

        add_color = "y"
        while add_color == "y":
            color = input("Color (hex): ")
            color = int(color.removeprefix("#"), 16)
            for offset in [18, 12, 6, 0]:
                prefix = 0xC0 if offset == 0 else 0x80
                transaction.append(prefix | (color >> offset) & 0x3F)

            add_color = input("Add color? (y/n): ")

        transaction.append(0x00)

        print([bin(chunk) for chunk in transaction])

        print(bytes(transaction))

        ser.write(bytes(transaction))

        time.sleep(0.2)

        if ser.in_waiting:
            print(ser.read(ser.in_waiting).decode("utf-8"))


finally:
    ser.close()
