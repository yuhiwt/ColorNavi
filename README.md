# project ColorNavi

## Initialize

iOS向けのGoogleMaps.frameworkが重すぎたため、最初に以下を実行してください。

```
cordova plugin rm plugin.google.maps
cordova plugin rm com.googlemaps.ios
cordova plugin add cordova-plugin-googlemaps --variable API_KEY_FOR_ANDROID="KEY" --variable API_KEY_FOR_IOS="KEY"
```
