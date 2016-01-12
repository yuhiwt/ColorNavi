# project ColorNavi

## Initialize

* iOS向けのGoogleMaps.frameworkが重すぎたため、最初に以下を実行してください。

```
cordova plugin rm plugin.google.maps
cordova plugin rm com.googlemaps.ios
cordova plugin add cordova-plugin-googlemaps --variable API_KEY_FOR_ANDROID="KEY" --variable API_KEY_FOR_IOS="KEY"
```

## Usage

* このアプリケーションはBLEのエミュレーションができないエミュレータでは、正常に動作しません。
* 特定のBLE端末(ColorNavi本体:Arduino nano+BLE module)のUUIDが指定できない場合、正常に動作しません。
* 実機にインストールすることをおすすめします。
