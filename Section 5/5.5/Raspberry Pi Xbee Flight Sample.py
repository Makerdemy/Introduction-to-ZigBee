from digi.xbee.devices import XBeeDevice
# TODO: Replace with the serial port where your local module is connected to.
PORT = "/dev/ttyUSB0"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600
DATA_TO_SEND = "Hello XBee!"

def main():
    while True:
        print(" +------------------------------------------------+")
        print(" | XBee Flight Information Display System |")
        print(" +------------------------------------------------+\n")
        Tx_Data = input("Enter the data: ") 
        device = XBeeDevice(PORT, BAUD_RATE)

        try:
            device.open()

            print("Updating Remote Nodes with the  following data: %s" % Tx_Data )

            device.send_data_broadcast(Tx_Data)

            print("Success")

        finally:
            if device is not None and device.is_open():
                device.close()


if __name__ == '__main__':
    main()