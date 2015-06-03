import serial
import thread
import threading


"""
Escape sequences for this script:
$		Data rcvd on serial enclosed in this will be written to file
\n		Data being sent out must end with the new line character for it to be recognised
		by the device
%		The device is ready to receive the next command

"""

def writeSerial():
	global outfile
	cmd=raw_input("\n Use help if in doubt.\n $>")
	if "help" in cmd:
		print "The available commands are \
						\n 1. record: no arguments. Performs TX and saves RX data. \
						\n 2. pull: give filename as argument. without extension. Saves data to .csv file. \
						\n 3. measure: no arguments. Measures distance on data. \
						\n 4. correlate: no arguments. Performs correlation on existing data. \
						\n 5. setcycles: give cycle setup as argument. First number of cycles per set, then order of sets. Example: setcycles 10 434 => transmit pattern 11110001111, with each digit corresponding to 10 cycles => total duration 110 cycles. Max pattern arg length is 7 \
						\n 6. setcntl: single argument of voltage required for cntl times 10. Eg: setcntl 31 sets to 3.1V \
						\n 7. setclmp: similar to setcntl, but for clmp"
	if "pull" in cmd:
		temp=cmd.split()
		cmd=temp[0]
		outfile=temp[1]+'.csv'
	ser.write(cmd+"\n")

def readSerial():
	a=''
	x=""
	while (a!='\n'):
		a=ser.read(1)
		x+=a
	if "%" in x:
		thread.start_new_thread(writeSerial, ())
	elif "$" in x:
		print "Transferring data to file "+outfile
		f = open(outfile,'w')
		while True:
			a=''
			x=""
			while (a!='\n'):
				a=ser.read(1)
				x+=a
			if "$" in x:
				f.close()
				break
			else:
				f.write(str(x[1:8])+',')
	else:
		print x

print "Connecting to serial port..."
try:
	ser = serial.Serial('/dev/ttyACM0',115200)
except:
	print "SerialException: Could not open port."
	exit(0)
else:
	print "Success!"
	
outfile='data.csv'
ser.flushInput()

while (1):
	readSerial();
