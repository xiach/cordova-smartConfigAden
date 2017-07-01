//
//  NetServiceInfo.h
//  OMNIConfig
//
//  Created by YUAN HSIANG TSAI on 2015/6/9.
//  Copyright (c) 2015年 Edden. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  用來註冊消息模式的Key，在Bonjour掃到一個Device時<br>
 *  而且是透過WiFi設定後，才加入的<br>
 *  會發出這個消息
 *
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kGetWifiSettingDevice;
/*!
 *  用來註冊消息模式的Key，在Bonjour掃到一個Device時<br>
 *  會先呼叫StartPing，在Ping成功後<br>
 *  會發出這個消息
 *
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kPingDeviceOK;
/*!
 *  用來註冊消息模式的Key，在Bonjour掃到一個Device時<br>
 *  會先呼叫StartPing，在Ping五次後沒拿到Pong<br>
 *  會發出這個消息
 *
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kPingDeviceFailed;

/*!
 *  是一個用來存放Bonjour收集到的資料的Class
 */
@interface NetServiceInfo : NSObject
/*!
 *  device name from bonjour<br>
 *  (e.g., OMNICFG@003344556601)
 */
@property (nonatomic, copy) NSString * name;
/*!
 *  device type from bonjour<br>
 *  (e.g., _omnicfg._tcp.local)
 */
@property (nonatomic, copy) NSString * type;
/*!
 *  device domain from bonjour<br>
 *  (e.g., router-2.local.:80)
 */
@property (nonatomic, copy) NSString * domain;
/*!
 *  IP address of this device
 */
@property (nonatomic, copy) NSString * address;
/*!
 *  LAN IP Address
 */
@property (nonatomic, copy) NSString * lanIP;
/*!
 *  IPCam, AudioBox, TV, etc.<br>
 *  這是根據vid和pid來決定的，之後會根據客戶的定義來決定種類<br>
 *  目前只是Demo
 */
@property (nonatomic, copy) NSString * typeName;
/*!
 *  MAC Address<br>
 *  主要是從name，把字串Parser出來的
 */
@property (nonatomic, copy) NSString * macAddress;
/*!
 *  vendor id
 */
@property (assign) NSUInteger vid;
/*!
 *  product id
 */
@property (assign) NSUInteger pid;
/*!
 *  因為Bonjour會cache 15秒，所以DUT發出Version來讓App辨認是不是cache data
 */
@property (nonatomic, copy) NSString * sVersion;
/*!
 *  限直連模式<br>
 *  用來查詢配置結果
 */
@property (nonatomic, copy) NSString * omniResult;
/*!
 *  用來確認是不是透過Smart config配置成功的
 */
@property (assign) BOOL isNewAdd;
/*!
 *  這device是否有支援spotify的功能
 */
@property (nonatomic, getter=checkIfSupportSpotify) BOOL isSupportSpotify;

/*!
 *  omnicfg_ver
 */
@property (assign) NSUInteger omnicfg_ver;

/*!
 *  找到重覆的時候，把內容替換
 */
- (void)replaceContent:(NetServiceInfo*)target;

/*!
 *  主要是讓BonjourScanner呼叫的<br>
 *  讓BonjourScanner確認該機器是否真的存在LAN中
 */
- (void)startPing;
/*!
 *  在smartconfig設定後，要確認DUT是因為設定連線成功，還是因為失敗而退回去<br>
 *  這個主要是為了解一個BUG，在DUT第一次設定時，連線到 WiFi_A 成功 <br>
 *  然後重新Trigger DUT，再設定連線到 WiFi_A 但故意輸入錯的密碼<br>
 *  這時，DUT會因為密碼錯誤，而退回去，連接回上次成功設定的 WiFi_A <br>
 *  因為二次設定都是同一台，所以App分不清到底是成功還是失敗 <br>
 *  只好做一個protocol來確認這件事
 */
- (void)checkIfRestoredPreviousMode;
/*!
 *  利用pid和vid來產生對應的typeName
 */
- (void)createTypeName;

/*!
 *  測試用，建立一個假資料
 *
 *  @return random建立的假NetServiceInfo
 */
+ (instancetype)createRandomOne;
/*!
 *  測試用，送出重新trigger的command
 */
- (void)triggerIt;
@end
