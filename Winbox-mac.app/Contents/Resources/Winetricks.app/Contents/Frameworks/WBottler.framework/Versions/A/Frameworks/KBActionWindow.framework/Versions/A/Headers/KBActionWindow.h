//
//  KBActionWindow.h
//  KBActionWindow
//
//  Created by Mike Kronenberg on 26.11.08.
//  Copyright 2008 Kronenberg Informatik Lösungen. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface KBActionWindow : NSObject {
	IBOutlet id window;
	IBOutlet id scrollView;
	
	NSMutableArray *actions;
}
+ (KBActionWindow *) sharedKBActionWindow;

- (void) redrawActions;
- (void) setTitle:(NSString *)string;
- (id) addActionWithTitle:(NSString *)tString withDescription:(NSString *)tString withIcon:(NSImage *)tImage withAbortSelector:(SEL)tSelector forTarget:(id)tTarget;
- (void) removeAction:(id)action;

- (NSWindow *) window;
@end
