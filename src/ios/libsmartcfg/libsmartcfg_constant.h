//
//  libsmartcfg_constant.h
//  libsmartcfg
//
//  Created by Edden on 10/27/15.
//  Copyright © 2015 Edden. All rights reserved.
//

#ifndef libsmartcfg_constant_h
#define libsmartcfg_constant_h

#define kConfigSenderStopped (@"ConfigSenderStopped")

#define TIMEOUT_DETECT_GATEWAY                  3
#define TIMEOUT_HTTP_REQUEST                    5
#define TIMEOUT_SCAN_DEVICE                    20
#define TIMEOUT_RESOLVE                        10

#define KEY_DEFAULT_USER      (@"DefaultUser")
#define KEY_DEFAULT_PASSWORD  (@"DefaultPassword")
#define KEY_VENDOR_ID         (@"VendorID")
#define KEY_PRODUCT_ID        (@"ProductID")
#define KEY_VENDOR_PHASE      (@"VendorPhase")
#define KEY_CONFIG_MODE       (@"ConfigMode")

#define VALUE_DEFAULT_USER      (@"admin")
#define VALUE_DEFAULT_PASSWORD  (@"admin")
#define VALUE_VENDOR_ID         (@"")
#define VALUE_PRODUCT_ID        (@"")
#define VALUE_VENDOR_PHASE      (@"MONTAGE")

/*!
 define it for apply mode - station
 */
#define mode_station        @"09"
#define mode_station_int    9
/*!
 define it for apply mode - wisp
 */
#define mode_wisp           @"03"
#define mode_wisp_int       3

#define mode_bridge         @"04"
#define mode_bridge_int     4

/*!
 *  直連模式的配置結果
 */
typedef NS_ENUM(NSInteger, OmniState) {
    /*!
     *  No State
     */
    OmniStateNone = 0,
    /*!
     *  正在連接到Target AP
     */
    OmniStateConnecting,
    /*!
     *  配置成功
     */
    OmniStateConnectSuccess,
    /*!
     *  找不到Target AP
     */
    OmniStateAPNotFound,
    /*!
     *  Target AP的密碼輸入錯誤
     */
    OmniStateIncorrectPassword,
    /*!
     *  無法從Target AP取得正確的IP
     */
    OmniStateCannotGetIP,
    /*!
     *  測試連線失敗
     */
    OmniStateTestConnectivityFailed,
    /*!
     *  配置逾時
     */
    OmniStateConnectTimeout
};

#endif /* libsmartcfg_constant_h */
