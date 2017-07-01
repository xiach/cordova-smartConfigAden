//
//  BonjourScanner.h
//  OMNIConfig
//
//  Created by Edden on 7/23/15.
//  Copyright (c) 2015 Edden. All rights reserved.
//

#import <Foundation/Foundation.h>
/*!
 *  發出mDNS來搜尋LAN裡的DUT
 */
@interface BonjourScanner : NSObject

/*!
 *  是否偵測機器是因為退回才連上AP (For QA 重覆測試連同一台機器)
 */
@property (assign) BOOL isNeedToDetectReturnBack;

/*!
 *  deprecated.
 *  是否正在執行Smart Config中
 */
@property (assign) BOOL isSmartConfigING;

/*!
 *  是否另外Broadcast mDNS query
 */
@property (assign) BOOL isEnableMultiQuery;

/*!
 *  是否每隔10s重啟一次NetServiceBrowser
 */
@property (assign) BOOL isEnableRestartPeriodically;


/*!
 *  是否要開啟Bonjour
 */
@property (assign) BOOL isEnableBonjour;

/*!
 *  找到DUT後是否要先Ping
 */
@property (assign) BOOL isNeedToPingDUT;

/*!
 *  重置搜尋記錄
 */
- (void)resetScanner;
/*!
 *  開始搜尋 LAN 裡的 DUT
 */
- (void)startScan;
/*!
 *  停止搜尋
 */
- (void)stopScan;

/*!
 *  外部不會用到，這是給DeviceCommander呼叫的Function<br>
 *  主要是在直連模式Apply之後，也需要透過Bonjour來得到Apply的結果
 */
- (void)scanForQueryOmniResult;

/*!
 *  測試用的，建假資料
 */
- (void)createFakeDevices;

@end


/*!
 *  用來註冊消息模式的Key，在Bonjour掃到一個被移除的Device時<br>
 *  會發出這個消息<br><br>
 *
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kRemoveDeviceNotification;

/*!
 *  用來註冊消息模式的Key，在Bonjour掃到一個可加入的Device時<br>
 *  會發出這個消息
 *
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kScanDeviceGotNotification;

/*!
 *  用來註冊消息模式的Key，在直連模式下的DeviceCommander<br>
 *  Apply之後，會一起開Bonjour來搜尋設定結果<br>
 *  會發出這個消息
 *  [sender object] is NetServiceInfo
 */
extern NSString * const kGetOmniResultNotification;
