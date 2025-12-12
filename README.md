# mulle-pq

#### ⛪️ mulle-pq a 'jq' for property lists

If [jq](https://stedolan.github.io/jq/) is installed, you can run an arbitrary
**jq** filter over your property list and get the result back in either JSON
or Plist or XML.




## Usage

```
task 141249 could not launch /home/src/srcO/mulle-objc/MulleObjC/src/protocol/NSCopying.m:45:17: warning: method definition for 'copiedInstance' not found [-Wincomplete-implementation]
   45 | @implementation NSObject ( NSCopying)
      |                 ^
/home/src/srcO/mulle-objc/MulleObjC/src/class/NSObject.h:266:1: note: method 'copiedInstance' declared here
  266 | - (id) copiedInstance;
      | ^
[0;36m[1mRun your executable:[0m
[1m   /home/nat/.mulle/var/mulle-pq-e4020b0ca178/kitchen/Debug/mulle-pq[0m
/home/nat/.mulle/var/mulle-pq-e4020b0ca178/kitchen/Debug/mulle-pq (2:No such file or directory)

```



## Requirements

|   Requirement         | Release Version  | Description
|-----------------------|------------------|---------------
| [MulleFoundation](https://github.com/MulleFoundation/MulleFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/MulleFoundation/MulleFoundation.svg) [![Build Status](https://github.com/MulleFoundation/MulleFoundation/workflows/CI/badge.svg?branch=release)](https://github.com/MulleFoundation/MulleFoundation/actions/workflows/mulle-sde-ci.yml) | 💍 Umbrella library for the MulleFoundation
| [MulleObjCExpatFoundation](https://github.com/MulleFoundation/MulleObjCExpatFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/MulleFoundation/MulleObjCExpatFoundation.svg) [![Build Status](https://github.com/MulleFoundation/MulleObjCExpatFoundation/workflows/CI/badge.svg?branch=release)](https://github.com/MulleFoundation/MulleObjCExpatFoundation/actions/workflows/mulle-sde-ci.yml) | 👴🏼 XML parser based on MulleObjCStandardFoundation and libexpat
| [MulleObjCJSMNFoundation](https://github.com/MulleWeb/MulleObjCJSMNFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/MulleWeb/MulleObjCJSMNFoundation.svg) [![Build Status](https://github.com/MulleWeb/MulleObjCJSMNFoundation/workflows/CI/badge.svg?branch=release)](https://github.com/MulleWeb/MulleObjCJSMNFoundation/actions/workflows/mulle-sde-ci.yml) | 🌼 JSON support for mulle-objc
| [MulleFoundation-startup](https://github.com/MulleFoundation/MulleFoundation-startup) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/MulleFoundation/MulleFoundation-startup.svg) [![Build Status](https://github.com/MulleFoundation/MulleFoundation-startup/workflows/CI/badge.svg?branch=release)](https://github.com/MulleFoundation/MulleFoundation-startup/actions/workflows/mulle-sde-ci.yml) | ▶️  Startup code for the MulleFoundation

### You are here

![Overview](overview.dot.svg)

## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-pq to your project:

``` sh
mulle-sde add github:MulleFoundation/mulle-pq
```


## Install

### Install with mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-pq and all dependencies:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/MulleFoundation/mulle-pq/archive/latest.tar.gz
```

### Manual Installation

Install the requirements:

| Requirements                                 | Description
|----------------------------------------------|-----------------------
| [MulleFoundation](https://github.com/MulleFoundation/MulleFoundation)             | 💍 Umbrella library for the MulleFoundation
| [MulleFoundation-startup](https://github.com/MulleFoundation/MulleFoundation-startup)             | ▶️ Startup library for MulleFoundation
| [MulleObjCExpatFoundation](https://github.com/MulleFoundation/MulleObjCExpatFoundation)             | 👴🏼 XML parser based on MulleObjCStandardFoundation and libexpat
| [MulleObjCJSMNFoundation](https://github.com/MulleWeb/MulleObjCJSMNFoundation)             | 🌼 JSON support for mulle-objc

Install **mulle-pq** into `/usr/local` with [cmake](https://cmake.org):

``` sh
cmake -B build \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_PREFIX_PATH=/usr/local \
      -DCMAKE_BUILD_TYPE=Release &&
cmake --build build --config Release &&
cmake --install build --config Release
```


## Author

[Nat!](https://mulle-kybernetik.com/weblog) for Mulle kybernetiK




