//
//  KBAction.h
//  KBActionWindow
//
//  Created by Mike Kronenberg on 26.11.08.
//  Copyright 2008 Kronenberg Informatik Lösungen. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface KBAction : NSObject {
	IBOutlet id view;
	IBOutlet id theIcon;
	IBOutlet id theTitle;
	IBOutlet id theProgress;
	IBOutlet id theDescription;
	IBOutlet id abort;
@private	
	BOOL isNibLoaded;
	NSInvocation *invocation;
}
- (void) setImage:(NSImage *)image;
- (void) setTitle:(NSString *)string;
- (void) setDescription:(NSString *)string;
- (void) setProgress:(double)value;
- (void) setSelector:(SEL)tSelector forTarget:(id)tTarget;
- (void) setEnded:(id)sender;
- (IBAction) abort:(id)sender;
- (id) view;
@end
