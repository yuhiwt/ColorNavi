/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    //------------------------
    // Scan結果 記録用
    //------------------------
    log: function(str) {
            $("#log").append(str + "<br />");
            $("#log").scrollTop($("#log")[0].scrollHeight);
    },
    //------------------------
    // Scan実行用
    //------------------------
    onScan: function() {
            app.log(">> scan");
            var scanTime=3000;
            ble.startScan([], function(device)
            {
                console.log("scan success")
                app.log("DEVICE: " + JSON.stringify(device));
            }, function(reason)
            {
                console.log("scan failure");
                app.log("ERROR: " + reason);
            });
            setTimeout( function(){
                ble.stopScan(
                    function() { console.log("Scan complete"); },
                    function() { console.log("stopScan failed"); }
                );
                app.log("<< scan");
            }, scanTime);
            ble.showBluetoothSettings(function(e){
                app.log(e);
            }, function(e){
                app.log(e);
            });

    },
    //------------------------
    // connectボタン実行用
    // device_id: UUID or MAC address of the peripheral
    //------------------------
    onConnect: function(device_id){
        ble.connect(device_id, function(device)
        {
            console.log(connect_success);
        }, function(reason){
            console.log(connect_failure);
        });
    },
    onDisconnect: function(device_id){
        ble.disconnect(device_id, function(device)
        {
            console.log(disconnect_success);
        }, function(reason){
            console.log(disconnect_failure);
        });
    },
    sendData: function(){
        var data = new Array();
        data[0] = "220a";
        ble.write(device_id, SERVICE, CHARACTERISTIC, data.buffer, success, failure);

    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicitly call 'app.receivedEvent(...);'
    onDeviceReady: function() {
        app.receivedEvent('deviceready');
        $('#scan').on('click', function()
        {
            app.onScan();
        });
    },
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    }
};
