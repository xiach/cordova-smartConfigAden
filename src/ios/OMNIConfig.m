//
//  OMNIConfigTests.m
//  OMNIConfigTests
//
//  Created by YUAN HSIANG TSAI on 2015/6/3.
//  Copyright (c) 2015年 Edden. All rights reserved.
//
@import SystemConfiguration.CaptiveNetwork;
#import <Cordova/CDVPlugin.h>
#import <UIKit/UIKit.h>
#import "SmartConfig.h"


@implementation SmartConfig {
    BOOL bWaitSenderStop;
    NSString *string;
}

-(void)pluginInitialize{
}



//// test Apply Smart Config
- (void)start:(CDVInvokedUrlCommand*)command {
    BOOL wifiOK= FALSE;
    NSDictionary *ifs;
    NSString *ssid;
    if (!wifiOK)
    {
        ifs = [self fetchSSIDInfo];
        ssid = [ifs objectForKey:@"SSID"];
        if (ssid!= nil)
        {
            wifiOK= TRUE;
            //            self.txtSSID.text = ssid;
        }
    }
    string =command.callbackId;
    NSLog(@"wifim名字= %@",ssid);
    if(!wifiOK){
        NSDictionary* info = @{
                               @"code":@"error",
                               @"msg":@"0"
                               };
           [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:info] callbackId:command.callbackId];
        return;
    }
//     添加网络传入的参数
    NSMutableDictionary *args = [command argumentAtIndex:0];


    NSString * ssidStr= [args objectForKey:@"ssid"];
    NSString * pswdStr = [args objectForKey:@"pswd"];
    NSLog(@"ssidStr = %@",ssidStr);
    NSLog(@"pswdStr = %@",pswdStr);
    self.configSender = [[SmartConfigApply alloc] init];
    // 註冊關注消息，在Sender完全停止之後會執行 configStopped 這個 function

    [self.configSender setSSID:ssidStr Password:pswdStr Mode:mode_station_int];


    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onGetNewDevice:) name:kScanDeviceGotNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRemoveDevice:) name:kRemoveDeviceNotification object:nil];

//    int smartConfigVer = (int)[[NSUserDefaults standardUserDefaults] integerForKey:KEY_SMARTCONFIG_VER];
//    self.configSender.solutionVer= smartConfigVer;
    self.configSender.solutionVer = 2;
    [self.configSender apply];

    self.bonjourScanner  = [[BonjourScanner alloc] init];
    self.netServiceInfos = [[NSMutableArray alloc] init];

    [_bonjourScanner startScan];

    NSDate * now = [NSDate date];
    while (([[NSDate date] timeIntervalSinceDate:now] < 60)) { // wait result for 60s
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode
                                 beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
    }

    bWaitSenderStop = YES;
    [self.configSender stop];
    [_bonjourScanner stopScan];
    while (bWaitSenderStop == YES && ([[NSDate date] timeIntervalSinceDate:now] < 5)) { // wait stop for 5s
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode
                                 beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
    }
    NSDictionary* info = @{
                           @"code":@"error",
                           @"msg":@"暂无设备"
                           };
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:info] callbackId:command.callbackId];
}


- (void)wifiSsid:(CDVInvokedUrlCommand*)command {
    BOOL wifiOK= FALSE;
    NSDictionary *ifs;
    NSString *ssid;
    if (!wifiOK)
    {
        ifs = [self fetchSSIDInfo];
        ssid = [ifs objectForKey:@"SSID"];
        if (ssid!= nil)
        {
            wifiOK= TRUE;
            //            self.txtSSID.text = ssid;
        }
    }
    //      [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"{\"code\":\"success\",\"mac\":\"%@\",\"ip\":\"%@\"}",dev.mac,dev.ip]] callbackId:command.callbackId];
    NSLog(@"wifim名字= %@",ssid);
    NSLog(@"xxxxxxxxxxx=%@",command.callbackId);
    if(!wifiOK){

        NSDictionary* info = @{
                               @"code":@"error",
                               @"msg":@"0"
                               };
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:info] callbackId:command.callbackId];
        return;
    }
    NSDictionary* info = @{
                           @"code":@"success",
                           @"ssid":ssid
                           };
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:info] callbackId:command.callbackId];

}

- (void)stop:(CDVInvokedUrlCommand*)command {
        bWaitSenderStop = NO;
    NSDictionary* info = @{
                           @"code":@"success"
                           };
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:info] callbackId:command.callbackId];

}
- (id)fetchSSIDInfo {
        NSArray *ifs = (__bridge_transfer id)CNCopySupportedInterfaces();
        NSLog(@"Supported interfaces: %@", ifs);
        id info = nil;
        for (NSString *ifnam in ifs) {
            info = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)ifnam);
            NSLog(@"%@ => %@", ifnam, info);
            if (info && [info count]) { break; }

        }

    return  info;
}

- (void)onGetNewDevice:(NSNotification *)sender{
//    NSLog(@"1222222222222");
    NetServiceInfo * newDevice = [sender object];
    NSDictionary* info = @{
                           @"code":@"success",
                           @"mac":newDevice.macAddress
                           };
//    [[DebugMessage sharedInstance] writeDebugMessage:[NSString stringWithFormat:@"Add to List -> %@", newDevice.macAddress]
//                                            function:[NSString stringWithFormat:@"%s", __func__]
//                                                line:[NSString stringWithFormat:@"%d", __LINE__]
//                                                mode:DebugMessageBonjour];
//
    [self.netServiceInfos addObject:newDevice];
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:info] callbackId:string];
}

- (void)onRemoveDevice:(NSNotification *)sender {
    NetServiceInfo * device = [sender object];
    [[DebugMessage sharedInstance] writeDebugMessage:[NSString stringWithFormat:@"Remove from List -> %@", device.macAddress]
                                            function:[NSString stringWithFormat:@"%s", __func__]
                                                line:[NSString stringWithFormat:@"%d", __LINE__]
                                                mode:DebugMessageBonjour];
 NSLog(@"orderString = 33333333333333");
    [self.netServiceInfos removeObject:device];
}
- (void)configStopped {
    NSLog(@"configStopped");
    bWaitSenderStop = NO;
}

- (void)onSuccessWithCommandType:(NSInteger)type {
    switch (type) {
        case RequestTagLogin:
            // 直連模式 DUT 帳號密碼認証成功
            NSLog(@"Success to Authentication");
            break;
        case RequestTagWiFiSetting:
            // 直連模式 提交 設定 DUT 連線到 Target AP 成功
            NSLog(@"Success to Configure DUT");
            break;
        case RequestTagQueryApplyResult:
            // 直連模式，拿到DUT配置成功的結果
            NSLog(@"Success to apply DUT");
            break;
        default:
            break;
    }
}

- (void)onFailedWithErrCode:(NSInteger)code withCommandType:(NSInteger)type {
    switch (type) {
        case RequestTagLogin:
            // 直連模式 DUT 帳號密碼認証失敗
            NSLog(@"Failed to Authentication");
            break;
        case RequestTagWiFiSetting:
            // 直連模式 提交 設定 DUT 連線到 Target AP 失敗
            NSLog(@"Failed to commit setting to DUT");
            break;
        case RequestTagQueryApplyResult:
            // 直連模式，拿到DUT配置失敗的結果, code是失敗原因，參考下面說明
            NSLog(@"Failed to apply DUT %d", (int)code);
            //            OmniStateAPNotFound,              // 找不到Target AP
            //            OmniStateIncorrectPassword,       // Target AP的密碼輸入錯誤
            //            OmniStateCannotGetIP,             // 無法從Target AP取得IP
            //            OmniStateTestConnectivityFailed,  // 測試連線失敗
            //            OmniStateConnectTimeout           // 連線到Target AP逾時
            break;
        default:
            break;
    }
}

@end
