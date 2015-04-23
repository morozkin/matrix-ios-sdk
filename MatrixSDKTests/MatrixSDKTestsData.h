/*
 Copyright 2014 OpenMarket Ltd
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>

#import <XCTest/XCTest.h>

#import "MXRestClient.h"
#import "MXSession.h"

// The URL of your test home server
FOUNDATION_EXPORT NSString * const kMXTestsHomeServerURL;

// Alice has a displayname and an avatar
FOUNDATION_EXPORT NSString * const kMXTestsAliceDisplayName;
FOUNDATION_EXPORT NSString * const kMXTestsAliceAvatarURL;

@interface MatrixSDKTestsData : NSObject

+ (id)sharedData;

#pragma mark - mxBob
// Credentials for the user mxBob on the home server located at kMXTestsHomeServerURL
@property (nonatomic, readonly) MXCredentials *bobCredentials;

// Get credentials asynchronously
// The user will be created if needed
- (void)getBobCredentials:(void (^)())success;

// Prepare a test with a MXRestClient for mxBob so that we can make test on it
- (void)doMXRestClientTestWithBob:(XCTestCase*)testCase
                   readyToTest:(void (^)(MXRestClient *bobRestClient, XCTestExpectation *expectation))readyToTest;

// Prepare a test with a a MXRestClient for mxBob so that we can make test on it
- (void)doMXRestClientTestWithBobAndARoom:(XCTestCase*)testCase
                              readyToTest:(void (^)(MXRestClient *bobRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

- (void)doMXRestClientTestWithBobAndAPublicRoom:(XCTestCase*)testCase
                              readyToTest:(void (^)(MXRestClient *bobRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

- (void)doMXRestClientTestWithBobAndThePublicRoom:(XCTestCase*)testCase
                           readyToTest:(void (^)(MXRestClient *bobRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

- (void)doMXRestClientTestInABobRoomAndANewTextMessage:(XCTestCase*)testCase
                                     newTextMessage:(NSString*)newTextMessage
                                      onReadyToTest:(void (^)(MXRestClient *bobRestClient, NSString* roomId, NSString* new_text_message_eventId, XCTestExpectation *expectation))readyToTest;

- (void)doMXRestClientTestWithBobAndARoomWithMessages:(XCTestCase*)testCase
                                       readyToTest:(void (^)(MXRestClient *bobRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

- (void)doMXRestClientTestWihBobAndSeveralRoomsAndMessages:(XCTestCase*)testCase
                                            readyToTest:(void (^)(MXRestClient *bobRestClient, XCTestExpectation *expectation))readyToTest;

- (void)doMXSessionTestWithBob:(XCTestCase*)testCase
                   readyToTest:(void (^)(MXSession *mxSession, XCTestExpectation *expectation))readyToTest;


- (void)doMXSessionTestWithBobAndARoomWithMessages:(XCTestCase*)testCase
                                    readyToTest:(void (^)(MXSession *mxSession, MXRoom *room, XCTestExpectation *expectation))readyToTest;


- (void)doMXSessionTestWithBobAndThePublicRoom:(XCTestCase*)testCase
                                readyToTest:(void (^)(MXSession *mxSession, MXRoom *room, XCTestExpectation *expectation))readyToTest;

#pragma mark - mxAlice
@property (nonatomic, readonly) MXCredentials *aliceCredentials;

- (void)doMXRestClientTestWithAlice:(XCTestCase*)testCase
                   readyToTest:(void (^)(MXRestClient *aliceRestClient, XCTestExpectation *expectation))readyToTest;

#pragma mark - both
- (void)doMXRestClientTestWithBobAndAliceInARoom:(XCTestCase*)testCase
                                     readyToTest:(void (^)(MXRestClient *bobRestClient, MXRestClient *aliceRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

- (void)doMXSessionTestWithBobAndAliceInARoom:(XCTestCase*)testCase
                                  readyToTest:(void (^)(MXSession *bobSession,  MXRestClient *aliceRestClient, NSString* roomId, XCTestExpectation *expectation))readyToTest;

#pragma mark - tools
- (void)for:(MXRestClient *)mxRestClient2 andRoom:(NSString*)roomId sendMessages:(NSUInteger)messagesCount success:(void (^)())success;

// Close the session
// Before closing, it checks if the session must be cleaning.
// Cleaning means making the user leave all private rooms so that requests to the
// home server db require (much) less time
- (void)closeMXSession:(MXSession*)mxSession;

@end
