//
//  ViewController.m
//  Porygon-Demo
//
//  Created by DevinShine on 2017/6/12.
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

#import "ViewController.h"
#import "DVSPorygon.h"
@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UISlider *slider;
@property (nonatomic) DVSPorygon *porygon;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _porygon = [[DVSPorygon alloc] init];
    
    _slider.minimumValue = DVS_MIN_VERTEX_COUNT;
    _slider.maximumValue = DVS_MAX_VERTEX_COUNT;
    _slider.value = _porygon.vertexCount;
    _imageView.image = [_porygon lowPolyWithImage:[UIImage imageNamed:@"camera"]];
    
    [_slider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
}

- (IBAction)sliderValueChanged:(UISlider *)sender {
    int count = sender.value;
    _porygon.vertexCount = count;
    _imageView.image = [_porygon lowPolyWithImage:[UIImage imageNamed:@"camera"]];
}

@end
