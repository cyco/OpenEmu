/*
 Copyright (c) 2009, OpenEmu Team
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Cocoa/Cocoa.h>

extern NSString *const OEControlsPreferenceKey;
extern NSString *const OEAdvancedPreferenceKey;

extern NSString *const OESettingValueKey;
extern NSString *const OEHIDEventValueKey;
extern NSString *const OEKeyboardEventValueKey;

@class GameCore, GameDocument, OEHIDEvent;

@interface OEGameCoreController : NSResponder
{
    id              currentPreferenceViewController;
    NSBundle       *bundle;
    NSString       *playerString;
    NSString       *replacePlayerFormat;
    NSArray        *controlNames;
    NSMutableArray *gameDocuments;
    
    BOOL            hasRunningCore;
}

@property(readonly) NSBundle *bundle;
@property(readonly) Class gameCoreClass;
@property(readonly) id currentPreferenceViewController;
@property(readonly) NSString *playerString;
@property(readonly) NSString *replacePlayerFormat;

+ (void)registerPreferenceViewControllerClasses:(NSDictionary *)viewControllerClasses;
- (NSArray *)availablePreferenceViewControllers;

@property(readonly) NSArray    *usedSettingNames;
@property(readonly) NSArray    *genericControlNames;
@property(readonly) NSUInteger  playerCount;
@property(readonly) NSString   *pluginName;

- (NSUInteger)playerNumberInKey:(NSString *)aPlayerKey getKeyIndex:(NSUInteger *)index;
/*
 * The method search for a registered class for the passed-in key and instanciate the controller
 * with the Nib name provided by the controller +preferenceNibName class method.
 * If +preferenceNibName is not overridden by the controller class, the receiver uses the default
 * nib name provided by the key.
 * 
 * For example: if the passed-in key is @"OEControlsPreferenceKey" the default nib name will be
 * @"ControlsPreference" (the two-letter prefix "OE" and three-letter suffix "Key" are removed from
 * the name).
 */
- (id)newPreferenceViewControllerForKey:(NSString *)aKey;
- (GameCore *)newGameCore;
- (GameCore *)newGameCoreWithDocument:(GameDocument *)aDocument;
- (void)unregisterGameCore:(GameCore *)aGameCore;
- (NSString *)keyPathForKey:(NSString *)keyName withValueType:(NSString *)aType;

- (id)registarableValueWithObject:(id)anObject;
- (id)valueForKeyPath:(NSString *)aValue;
- (void)registerValue:(id)aValue forKey:(NSString *)keyName withValueType:(NSString *)aType;

- (void)registerSetting:(id)settingValue forKey:(NSString *)keyName;
- (void)registerEvent:(id)theEvent forKey:(NSString *)keyName;

- (id)settingForKey:(NSString *)keyName;

- (void)forceKeyBindingRecover;
- (id)HIDEventForKey:(NSString *)keyName;
- (id)keyboardEventForKey:(NSString *)keyName;
- (void)removeBindingsToEvent:(id)theEvent withValueType:(NSString *)aType;
- (void)HIDEventWasRemovedForKey:(NSString *)keyName;
- (void)keyboardEventWasRemovedForKey:(NSString *)keyName;

@end

@interface NSViewController (OEGameCoreControllerAddition)
+ (NSString *)preferenceNibName;
@end
