#IBM Watson IOT Platform
#pip install wiotp-sdk
import wiotp.sdk.device
import time
import random
myConfig = {
 "identity": {
 "orgId": "qo7yo9",
 "typeId": "nodemcu",
 "deviceId":"123456"
 },
 "auth": {
 "token": "a-qo7yo9-b7czg15vpe"
 }
}
def myCommandCallback(cmd):
 print("Message received from IBM IoT Platform: %s" % cmd.data['command'])
 m=cmd.data['command']
client = wiotp.sdk.device.DeviceClient(config=myConfig, logHandlers=None)
client.connect()
while True:
 temperature=random.randint(0,600)
 Alarm=random.randint(0,125)
 myData={'temperature':temperature, 'humidity':Alarm}
 client.publishEvent(eventId="status", msgFormat="json", data=myData, qos=0, onPublish=None)
 print("Published data Successfully: %s", myData)
 client.commandCallback = myCommandCallback
 time.sleep(2)
client.disconnect()
