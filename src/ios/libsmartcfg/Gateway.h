//
//  GatewayChecker.h
//  SmartConfig
//
//  Created by Edden on 10/15/15.
//  Copyright © 2015 Edden. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  Delegate for GatewayChecker
 */
@protocol GatewayCheckDelegate <NSObject>
/*!
 *  目前Gateway即是DUT<br>
 *  在自動偵測模式下，會判斷目前App處在直連模式
 *
 *  @param remainingTime DUT剩餘的可設定時間，收到後，應該起個Timer來倒數計時<br>
 *  倒數完後，該DUT就會處於不能設定的狀態，或是退回去連接上次設定的AP
 */
- (void)onConnectedDUTWithTimeout:(NSInteger)remainingTime;
/*!
 *  目前Gateway即是DUT<br>
 *  在自動偵測模式下，會判斷目前App處在直連模式<br>
 *  而且DUT已經是timeout或不可設定的狀態，這時要請使用者重新Trigger DUT
 */
- (void)onConnectedDUTButNotSettable;
/*!
 *  目前Gateway是一般的AP<br>
 *  在自動測偵模式下，會判斷App處於smartconfig模式
 */
- (void)onConnectedNormalAP;
@end

/*!
 *  用來查詢Gateway的IP Address<br>
 *  確認Gateway是DUT(直連)或是一般AP(SmartConfig)
 */
@interface GatewayChecker : NSObject
/*!
 *  是否要先Ping，再發Request確認是不是連到DUT
 */
@property (assign) BOOL isEnablePingFirstToCheck;
/*!
 *  查詢Gateway IP
 */
- (void)lookupGatewayIP;
/*!
 *  查詢Gateway是UT(直連)或是一般AP(SmartConfig)
 */
- (void)checkGatewayMode;
/*!
 *  停止查詢，通常是在timeout或是要APP進Background時呼叫
 */
- (void)stopCheck;

/*!
 *  取得Gateway IP
 */
@property (nonatomic, getter=getGatewayIP) NSString * gatewayIP;
/*!
 *  GatewayCheckDelegate
 */
@property (nonatomic, assign) id<GatewayCheckDelegate> delegate;

/*!
 *  直連模式，查看DUT是不是有support timeout, 目前應該都是有support
 */
@property (nonatomic, getter=isSupportTimeout)  BOOL isSupportTimeout;
/*!
 *  直連模式，查看DUT是不是前次有設定成功過<br>
 *  在配置失敗或timeout時，用來顯示 DUT 會退回去連接上次配置的 AP
 */
@property (nonatomic, getter=isPreviousStation) BOOL isPreviousStation;
@end