//
//  SmartConfigApply.h
//  libsmartcfg
//

#import <Foundation/Foundation.h>

#define SOLUTION_VERSION_1 1
#define SOLUTION_VERSION_2 2

/*!
 *  Smart config 的演算法
 */
typedef NS_ENUM(NSUInteger, SendMode) {
    /*!
     *  1x1的演算法
     */
    SendMode1x1 = 0,
    /*!
     *  2x2的演算法
     */
    SendMode2x2,
    /*!
     *  二種都送
     */
    SendModeBoth,
};

@interface SmartConfigApply : NSObject
/*!
 *  設定使用者填入AP的ssid、密碼、和mode
 *
 *  @param ssid target AP ssid
 *  @param pw   target AP 密碼
 *  @param mode 連線模式 wisp - 3, station - 9
 */
- (void)setSSID:(NSString*)ssid Password:(NSString *)pw Mode:(int)mode;
/*!
 *  smart config 開始設定
 */
- (void)apply;
/*!
 *  停止設定
 */
- (void)stop;

/*!
 *  sleep time for sleep after every SISO packet and MIMO packet
 */
@property (nonatomic, assign) int sendSleepTime;

// only for test
@property (nonatomic, assign) NSUInteger sendtype;
@property (nonatomic, assign) int solutionVer;

@end
