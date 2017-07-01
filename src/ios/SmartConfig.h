

#import <Cordova/CDV.h>
#import "libsmartcfg.h"


@interface SmartConfig : CDVPlugin
@property BonjourScanner    * bonjourScanner;
@property DeviceCommander   * commander;
@property SmartConfigApply  * configSender;
@property NSMutableArray    * netServiceInfos;
- (void) start:(CDVInvokedUrlCommand*)command;
- (void) wifiSsid:(CDVInvokedUrlCommand*)command;
- (void) stop:(CDVInvokedUrlCommand*)command;
@end

