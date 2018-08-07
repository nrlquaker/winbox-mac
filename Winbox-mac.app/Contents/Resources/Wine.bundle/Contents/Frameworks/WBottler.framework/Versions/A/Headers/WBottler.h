/*
 * WBottler.h
 * of the 'WBottler' target in the 'WineBottler' project
 *
 * Copyright 2009 Mike Kronenberg
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */



#import <Cocoa/Cocoa.h>
#import <KBActionWindow/KBActionWindow.h>
#import <KBActionWindow/KBAction.h>



typedef unsigned BottlerRunMode;
enum {
	BottlerRunModeApp = 0,
	BottlerRunModeWinetricks = 1,
	BottlerRunModePrefix = 2
};


typedef unsigned BottlerExitMode;
enum {
	BottlerExitModeNormal = 0,
	BottlerExitModeAbort = 1,
	BottlerExitModeError = 2
};

@interface WBottler : NSObject {
    BOOL debug;
	BOOL finished;
	id bottlerController;
	SEL callback;
	
	IBOutlet NSPanel *findExePanel;
	IBOutlet NSPopUpButton *exeSelector;
	
	BottlerRunMode runMode;
	BottlerExitMode exitMode;
	
	NSPipe *stdPipe;
	NSPipe *errPipe;
	NSFileHandle *stdHandle;
	NSFileHandle *errHandle;
	NSTask *task;
	KBAction *installAction;
	double percent;
	NSURL *filename;
	NSString *pathtoExecutable;
    NSString *bundleSignature;
	
	NSMutableString *stringBuffer;
	NSMutableString *log;
}
- (void) findWine;
- (id) initWithScript:(NSString *)tScript
			 URL:(NSURL *)tFilename
			 template:(NSString *)tTemplate
		 installerURL:(NSString *)tInstallerURL
	installerIsZipped:(NSString *)tInstallerIsZipped
		installerName:(NSString *)tInstallerName
   installerArguments:(NSString *)tInstallerArguments
               noMono:(BOOL)tNoMono
              noGecko:(BOOL)tNoGecko
              noUsers:(BOOL)tNoUsers
         noInstallers:(BOOL)tNoInstallers
		   winetricks:(NSString *)tWinetricks
			overrides:(NSString *)tOverrides
				  exe:(NSString *)tExe
		 exeArguments:(NSString *)tExeArguments
      bundleCopyright:(NSString *)tBundleCopyright
		bundleVersion:(NSString *)tBundleVersion
     bundleIdentifier:(NSString *)tBundleIdentifier
   bundleCategoryType:(NSString *)tBundleCategoryType
      bundleSignature:(NSString *)tBundleSignature
			   silent:(NSString *)tSilent
		selfcontained:(BOOL)tSelfcontained
			   sender:(id)tSender
			 callback:(SEL)tSelector;
- (IBAction) abort:(id)sender;
- (IBAction) findExe:(id)sender;
- (IBAction) foundExe:(id)sender;
- (IBAction) finish:(id)sender;
- (void) callCallback:(BOOL)success;
- (void) checkATaskStatus:(NSNotification *)aNotification;
@end
