//
//  DeviceCommander.h
//  OMNIConfig
//
//  Created by Edden on 10/19/15.
//  Copyright © 2015 Edden. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  直連模式的Request Type
 */
typedef NS_ENUM(NSInteger, RequestTag) {
    /*!
     *  直連模式的Login
     */
    RequestTagLogin,
    /*!
     *  直連模式DUT配置
     */
    RequestTagWiFiSetting,
    /*!
     *  直連模式查詢配置結果
     */
    RequestTagQueryApplyResult,
    /*!
     *  直連模式重啟AP Service
     */
    RequestTagRestartAP
};

/*!
 *  直連模式Request錯誤碼
 */
typedef NS_ENUM(NSInteger, FailedCode) {
    /*!
     *  DUT回復ERR
     */
    FailedCodeServerReturnErr = -1,
};

@class DeviceAuthentication;


/*!
 *  Commander Delegate
 */
@protocol DeviceCommanderDelegate <NSObject>
/*!
 *  送Command成功時呼叫
 *
 *  @param type See RequestTag
 */
- (void)onSuccessWithCommandType:(NSInteger)type;

/*!
 *  送Command失敗時呼叫
 *
 *  @param code See FailedCode, and http status code, "OmniState in libsmartcfg_constant.h"
 *  @param type See RequestTag
 */
- (void)onFailedWithErrCode:(NSInteger)code withCommandType:(NSInteger)type;
@end

/*!
 *  限直連模式<br>
 *  幫忙送出Device相關的Command
 */
@interface DeviceCommander : NSObject

/*!
 *  限直連模式<br>
 *  初始化
 *
 *  @param sIP      DUT的IP
 *  @param delegate callback delegate
 *
 *  @return instance of DeviceCommander
 */
- (instancetype)initWithIP:(NSString*)sIP withDelegate:(id<DeviceCommanderDelegate>)delegate;
/*!
 *  限直連模式<br>
 *  向DUT做Authentication
 *
 *  @param user user
 *  @param pw   password
 */
- (void)doAuthWithUser:(NSString*)user Password:(NSString*)pw;
/*!
 *  限直連模式<br>
 *  請DUT做WiFi設定
 *
 *  @param ssid   target SSID
 *  @param wifiPW target Password
 */
- (void)doWiFiSettingToSSID:(NSString*)ssid
               WiFiPassword:(NSString*)wifiPW;
/*!
 *  限直連模式<br>
 *  向DUT詢問是否配置成功
 */
- (void)queryResultForSettingWiFi;
/*!
 *  限直連模式<br>
 *  停止任何正在執行的動作
 */
- (void)stopAction;
/*!
 *  限直連模式<br>
 *  請DUT重啟Service，在配置成功或失敗後要呼叫
 */
- (void)restartCheetah;

@property (nonatomic, copy) NSString * targetSSID;

/*!
 *  限直連模式<br>
 *  在配置後，這個class內部起的BonjourScanner是否要<br>
 *  支援另外Broadcast mDNS query
 */
@property (assign) BOOL isEnableMultiQuery;

/*!
 *  限直連模式<br>
 *  在配置後，這個class內部起的BonjourScanner是否要<br>
 *  每隔10s重啟一次NetServiceBrowser
 */
@property (assign) BOOL isEnableRestartPeriodically;

@end
