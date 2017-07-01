//
//  DebugMessage.h
//  OMNIConfig
//
//  Created by Edden on 7/8/15.
//  Copyright (c) 2015 Edden. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*! @enum DebugMessageType
 
 */
typedef NS_ENUM(NSUInteger, DebugMsgType) {
    DebugMessageBonjour = 0,
    DebugMessageSmartconfig,
    DebugMessageHttpRequest,
    DebugMessageHttpResponse,
    DebugMessageUIAction,
    DebugMessageOther
};

@interface DebugMessage : NSObject

+ (DebugMessage*)sharedInstance;

/*!
 *  把 Debug message印在 console 上，如果有指定 TextView 則會印在 TextView 上面
 *  e.g, <MODE>:msg @Line-[FunctionName]
 *
 *  @param msg     想要秀出來的Message
 *  @param inFunc  印出Function Name
 *  @param lineNum 印出行數
 *  @param mode    see DebugMsgType
 */
- (void)writeDebugMessage:(NSString*)msg
                 function:(NSString*)inFunc
                     line:(NSString*)lineNum
                     mode:(NSInteger)mode;

/*!
 *  指定 textview 來印出 message
 */
- (void)setDbgView:(UITextView*)dbgMsgView;

@end
