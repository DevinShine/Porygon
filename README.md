<p align="center">
<img src="https://raw.githubusercontent.com/DevinShine/Porygon/master/Art/logo.png" alt="Porygon" title="Porygon" width="557"/>
</p>

<p align="center">
<a href="https://travis-ci.org/DevinShine/Porygon"><img src="https://img.shields.io/travis/DevinShine/Porygon/master.svg"></a>
<a href="https://raw.githubusercontent.com/DevinShine/Porygon/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-green.svg?style=flat"></a>
<a href="https://www.apple.com/nl/ios/"><img src="https://img.shields.io/badge/support-iOS%207%2B%20-blue.svg?style=flat"></a>
</p>

Porygon is a library for generate low-poly style images. It's algorithm is based on this [paper](http://ieeexplore.ieee.org/document/7314186/) and  [Polyvia](https://github.com/Ovilia/Polyvia). The Delaunay algorithm used is this [library](https://github.com/eloraiby/delaunay)

## Effect
![](Art/effect.jpg)

## Requirements

* iOS 6.0+
* Xcode 7.0+

## Useage


### Easy use
``` objc
DVSPorygon *porygon = [[DVSPorygon alloc] init];
UIImage * lowPolyImage = [porygon lowPolyWithImage:[UIImage imageNamed:@"camera"]]; // get low poly image
```

### Configuration parameters

``` objc
DVSPorygon *porygon = [[DVSPorygon alloc] init];
// edge vertex count
porygon.vertexCount = 10000;
// randomly add the number of vertices
porygon.randomCount = 200;
// show wireframe effects
porygon.isWireframe = true;
UIImage * lowPolyImage = [porygon lowPolyWithImage:[UIImage imageNamed:@"camera"]]; // get low poly image
```

## License
Porygon is provided under the MIT license. See LICENSE file for details.

