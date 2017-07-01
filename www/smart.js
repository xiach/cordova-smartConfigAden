/*global cordova, module*/
var exec = require('cordova/exec');
module.exports = {
    start: function (paymentInfo, successCallback, errorCallback) {
        exec(successCallback, errorCallback, "smart", "start", [paymentInfo]);
    },
    wifiSsid: function (paymentInfo, successCallback, errorCallback) {
        exec(successCallback, errorCallback, "smart", "wifiSsid", []);
    },
    stop: function (paymentInfo, successCallback, errorCallback) {
        exec(successCallback, errorCallback, "smart", "stop", []);
    }
};
