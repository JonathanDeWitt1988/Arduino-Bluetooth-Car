# Arduino-Bluetooth-Car
This contains an updated Android app and sketch for a 4-wheel drive zero turn Arduino car controlled via Bluetooth.  Note it only works with Android.
The original project can be found here:
https://www.hackster.io/andriy-baranov/smartphone-controlled-arduino-4wd-robot-car-14d239
In the original project the Android app that was in the Google play store can no longer be found.  The Android app in this Github repository closley mimics the functionality of the original Android app.  There are minor differences in the functionality which is why the original project's Arduino sketch needed to be slightly modified.  You will find both the new sketch and new Android app in this github repository.
After installing the app on your Android smart phone (will not work on iPhone) you will need to enable Bluetooth connection in your app settings.
1) Go to Settings
2) Go to Apps
3) Scroll clear down to RCCarControlRev4 and select it
4) Go to Permissions
You need to enable the app to find nearby devices.
Once that is done you can close out of Settings.
Go to your phone's Bluetooth.  You will search for devices to pair with.  You are looking for an HC-05 or HC-06.
Pair with the HC-05 or HC-06 for your car.  When it asks for a password use 0000 or 1234.
Now go into the RCCarControlRev4 app itself.  Click the Bluetooth icon.  A list of Bluetooth devices will come up.  Select the HC-05 or HC-06 you paired your phone with.  It will tell you if you are successfully connected.  The light on your Bluetooth module which was previously blinking should go solid.

You can now drive your car.

Remember, if your Bluetooth module is connected to Arduino pins 0 and 1, you will need to temporarily remote those connections while you are uploading the sketch to your Arduino and then plug the connections back in after upload is complete.
