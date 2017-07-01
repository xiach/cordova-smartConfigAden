package net.yuyun.electric;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.widget.Toast;
import org.apache.cordova.LOG;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import com.montage.omnicfgprivatelib.contants.Constants;
import com.montage.omnicfgprivatelib.contants.OmniSetting;
import com.montage.omnicfgprivatelib.interfaces.IWifiSenderCallback;
import com.montage.omnicfgprivatelib.utils.OmniCfgReceiver;
import com.montage.omnicfgprivatelib.utils.OmniCfgSender;
import android.net.wifi.WifiManager;

import java.util.ArrayList;

public class SmartConfigPlugin extends CordovaPlugin implements IWifiSenderCallback {

    private static String TAG = "SmartConfigPlugin";


    private boolean mIsConncting = false;
    private Activity activity;
    private CallbackContext callbackContext;
    private OmniCfgSender omniCfgSender = null;
    private WifiManager wifiManager;
    //    private WifiManager.MulticastLock lock;
    private boolean boo = false;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        activity = cordova.getActivity();
        omniCfgSender = new OmniCfgSender(activity, this);
        wifiManager = (WifiManager) activity.getSystemService(Context.WIFI_SERVICE);
//        lock = wifiManager.createMulticastLock("test wifi");
    }

    @Override
    public boolean execute(final String action, JSONArray args, CallbackContext callbackContext) {
        try {
            this.callbackContext = callbackContext;
            boo = false;
            if (action.equals("start")) {
//                lock.acquire();
                if (omniCfgSender != null) {
                    omniCfgSender.startUdpServer();
                }
                omniCfgSender.clearNetworkId();
                Constants.Threshold.setTotalApplyTime(6 * 1000);
                OmniSetting.setSelectedSolution(OmniSetting.HYBRID_SOLUTION);
                // notify OmniCfgSender to send probe request for find devices
                JSONObject arguments = args.getJSONObject(0);
                String ssid = arguments.getString("ssid");
                String password = arguments.getString("pswd");
                this.start(ssid, password);
            } else if (action.equals("wifiSsid")) {
                this.getWifiSSID();
            } else if (action.equals("stop")) {
                this.stop();
            }
            /*cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {

                }
            });*/
        } catch (JSONException e) {
            callbackContext.error(this.getJson("params erroe"));
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private void stop() {
        JSONObject json = new JSONObject();
        try {
            json.put("code", "success");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        if (boo) {
            callbackContext.success(json);
            return;
        }
        if (omniCfgSender != null) {
            omniCfgSender.stopUdpServer();
        }
        if (!boo) {
            omniCfgSender.stopProbing(false);
        }
        boo = true;
        callbackContext.success(json);
    }

    private void start(String ssid, String password) {
        LOG.d(TAG, "error==================");
        System.out.println("ssid:=" + ssid + ":::::::::::password:" + password);
        omniCfgSender.oneKeyConfiguration(ssid, password);
        cordova.getThreadPool().execute(new Runnable() {
            @Override
            public void run() {
                try {
                    int i = 60;
                    while (i > 0) {
                        if (boo) {
                            return;
                        }
                        Thread.sleep(1000);
                        i--;
                    }
                    if (boo) {
                        return;
                    }
                    if (omniCfgSender != null) {
                        omniCfgSender.stopUdpServer();
                    }
                    if (!boo) {
                        omniCfgSender.stopProbing(false);
                        callbackContext.error(getJson("暂无设备"));
                        omniCfgSender.clearNetworkId();
                    }
                } catch (Exception e) {

                }
            }
        });
//        try {
//            int i=60;
//            while(i>0){
//                Thread.sleep(1000);
//                i--;
//            }
//            omniCfgSender.stopProbing(false);
//        }catch (Exception e){
//
//        }
    }

    private void getWifiSSID() {
        WifiManager wm = (WifiManager) this.cordova.getActivity().getSystemService(Context.WIFI_SERVICE);
        WifiInfo wi = wm.getConnectionInfo();

        ConnectivityManager connectivityManager = (ConnectivityManager) this.cordova.getActivity().getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo wifiNetworkInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (wifiNetworkInfo.isConnected()) {
            String ssid = wi.getSSID();
            if (ssid != null) {
                if (ssid.length() > 2 && ssid.startsWith("\"") && ssid.endsWith("\"")) {
                    ssid = ssid.substring(1, ssid.length() - 1);
                }
                JSONObject json = new JSONObject();
                try {
                    json.put("code", "success");
                    json.put("ssid", ssid);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callbackContext.success(json);
                return;
            }
        }
        callbackContext.error(this.getJson("wifi error"));
    }

    @Override
    public void onUpdateProbeInfo(ArrayList<OmniCfgReceiver> arrayList) {
        System.out.println(arrayList);
        if (arrayList.size() > 0) {
            onConfigDeviceSuccess(arrayList.get(0));
        }
        // DebugMessage.getInstance().debug("onUpdateProbeInfo()", DebugMessage.DEBUG_NORMAL);
//        onConfigDeviceSuccess(arrayList.get(0));
    }

    @Override
    public void onGetProbeInfoSuccess(ArrayList<OmniCfgReceiver> arrayList) {

    }

    @Override
    public void onGetProbeInfoFailed() {

    }

    @Override
    public void onSetNonceSuccess(int i, boolean b) {

    }

    @Override
    public void onSetDevicePassSuccess() {

    }

    @Override
    public void onAuthDevicePassSuccess() {

    }

    @Override
    public void onAuthDevicePassFailed(boolean b) {

    }

    @Override
    public void onSetChangePassSuccess() {

    }

    @Override
    public void onChangeDevicePassSuccess() {

    }

    @Override
    public void onChangeDevicePassFailed() {

    }

    @Override
    public void onSetWifiInfoSuccess() {

    }

    @Override
    public void onApplyWifiConfigSuccess() {

    }

    @Override
    public void onApplyWifiConfigFailed() {
        LOG.d(TAG, "error==================");
//        System.out.println("error==================");
        callbackContext.error(this.getJson("time out"));
    }

    @Override
    public void onShowApplyFailMessage(int i, String s) {

    }

    @Override
    public void onGetDeviceStatusSuccess(String s) {

    }

    @Override
    public void onGetDeviceStatusFailed() {

    }

    @Override
    public void onGetDeviceAddressSuccess(String s) {

    }

    @Override
    public void onGetDeviceAddressFailed() {

    }

    @Override
    public void onConfigDeviceSuccess(OmniCfgReceiver receiver) {
//        lock.release();
        boo = true;
//        String message = "MAC: " + receiver.getDeviceMac();
//        System.out.println(message);
        JSONObject json = new JSONObject();
        try {
            json.put("code", "success");
            json.put("mac", receiver.getDeviceMac());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        LOG.d(TAG, "{\"code\":\"success\",\"mac\":\"" + receiver.getDeviceMac() + "\"}");
        if (omniCfgSender != null) {
            omniCfgSender.stopUdpServer();
            omniCfgSender.stopProbing(false);
            omniCfgSender.clearNetworkId();
        }
        callbackContext.success(json);
    }

    @Override
    public void onConfigAllDevicesSuccess() {
        boo = true;
    }

    @Override
    public void onConfigAllDevicesFailed(String s) {
        LOG.d(TAG, "error==================onConfigAllDevicesFailed");
        System.out.println("error==================onConfigAllDevicesFailed");
        callbackContext.error(this.getJson("time out"));
    }

    @Override
    public void onConfigInDirectModeSuccess() {

    }

    @Override
    public void onConfigInDirectModeFailed(String s) {

    }

//    @Override
//    public void onCompleted() {
//        this.closeDialog();
//        callbackContext.error(this.getJson("completed"));
//    }
//
//    @Override
//    public void onLinked(SmartLinkedModule arg0) {
//        this.closeDialog();
//        //"{\"code\":\"error\",\"msg\":\"time out\"}"
//        callbackContext.success("{\"code\":\"success\",\"ip\":\"" + arg0.getIp() + "\",\"mac\":\"" + arg0.getMac() + "\"}");
//    }

    /**
     * 获取json对象
     *
     * @param msg
     * @return
     */
    private JSONObject getJson(String msg) {
        JSONObject json = new JSONObject();
        try {
            json.put("code", "error");
            json.put("msg", msg);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return json;
    }

}