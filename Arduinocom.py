from flask_mysqldb import MySQLdb
import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
db = MySQLdb.connect("localhost", "root", "81GE@Dsa*01", "greenhouse")

cursor = db.cursor()

while 1:
    print("waiting for serial data...")
    print("")
    x = ser.readline()
    print("collecting data...")
    print("")
    time.sleep(1)
    y = ser.readline()
    time.sleep(1)
    z = ser.readline()
    time.sleep(1)
    x = int(x)
    y = int(y)
    z = int(z)
    print("inserting to database...")
    print("")
    time.sleep(1)
    sql = "INSERT INTO systemdata(moisture, temperature, light) VALUES (%d, %d, %d)" %(x,y,z)
    cursor.execute(sql)
    db.commit()
    