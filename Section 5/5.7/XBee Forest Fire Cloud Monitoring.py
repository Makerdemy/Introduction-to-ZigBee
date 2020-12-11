import random  
import time
import serial
import string
import pynmea2
  
from azure.iot.device import IoTHubDeviceClient, Message  
from digi.xbee.devices import XBeeDevice

XBEEPORT = "/dev/ttyUSB0"
BAUD_RATE = 9600
gpsport="/dev/ttyAMA0"


CONNECTION_STRING = "HostName=xbeeiothub.azure-devices.net;DeviceId=xbeedevice;SharedAccessKey=a8wgnR2w1H6f3Ch6QcUV+dJ2sU/ca3XpZ28in2nD1eo="  
device = XBeeDevice(XBEEPORT, BAUD_RATE)
device.open()
while True:
    ser=serial.Serial(gpsport, BAUD_RATE, timeout=0.5)
    dataout = pynmea2.NMEAStreamReader()
    newdata=ser.readline()
    if newdata[0:6] == "$GPRMC":
        newmsg=pynmea2.parse(newdata)
        lat=newmsg.latitude
        lng=newmsg.longitude
        gps = "Latitude=" + str(lat) + "and Longitude=" + str(lng)
    xbee_message = device.read_data()
    remote_device = xbee_message.remote_device
    client = IoTHubDeviceClient.create_from_connection_string(CONNECTION_STRING)
    if xbee_message is not None:
        if remote_device == "XBee B":
            message=xbee_message.data.decode()
            if message>28:
                client.send_message("Forest Fire Detected by XBee B at Coordinates:" + gps)
        if remote_device == "XBee C":
            message=xbee_message.data.decode()
            if message>45:
                client.send_message("Forest Fire Detected by XBee C at Coordinates:" + gps)
        if remote_device == "XBee D":
            message=xbee_message.data.decode()
            if message>45:
                client.send_message("Forest Fire Detected by XBee D at Coordinates:" + gps)
device.close()

