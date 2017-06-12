//
//  Tests.m
//  Tests
//
//  Created by DevinShine on 2017/6/11.
//
//  Copyright (c) 2017 DevinShine <devin.xdw@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import <XCTest/XCTest.h>
#import "DVSPorygon.h"

@interface Tests : XCTestCase
@property (nonatomic) DVSPorygon *porygon;
@end

@implementation Tests

- (void)setUp {
    [super setUp];
    self.porygon = [[DVSPorygon alloc] init];
}

- (void)tearDown {
    self.porygon = nil;
    [super tearDown];
}

- (void)testVertexCountSetter {
    self.porygon.vertexCount = -1;
    XCTAssertEqual(self.porygon.vertexCount, DVS_MIN_VERTEX_COUNT);
    self.porygon.vertexCount = 99;
    XCTAssertEqual(self.porygon.vertexCount, DVS_MIN_VERTEX_COUNT);
    self.porygon.vertexCount = 5001;
    XCTAssertEqual(self.porygon.vertexCount, DVS_MAX_VERTEX_COUNT);
    self.porygon.vertexCount = 100;
    XCTAssertEqual(self.porygon.vertexCount, 100);
    self.porygon.vertexCount = 5000;
    XCTAssertEqual(self.porygon.vertexCount, 5000);
    
}

- (void)testLowPoly {
    [self measureBlock:^{
        UIImage *image = [UIImage imageNamed:@"camera.jpg" inBundle:[NSBundle bundleForClass:[self class]] compatibleWithTraitCollection:nil];
        XCTAssertNotNil(image);
        UIImage *lowPolyImage = [self.porygon lowPolyWithImage:image];
        XCTAssertNotNil(lowPolyImage);
    }];
}

@end
