import struct
import smbus
import time
sleep = 1

bus = smbus.SMBus(1)

address = 0x08

def get_data():
    return bus.read_i2c_block_data(address, 0);

while True:
    try:
        data = get_data()
        print(f"Mock Data Values From Arduino: {data[0]}")
    except:
        continue
    time.sleep(sleep);
