# mulle-pq

#### ⛪️ mulle-pq a 'jq' for property lists

If [jq](https://stedolan.github.io/jq/) is installed, you can run an arbitrary
**jq** filter over your property list and get the result back in either JSON
or Plist or XML.




## Usage

```
Usage: mulle-pq [options] ...

   Convert between JSON, Plist, XML format.
   Any arguments after the known options are interpreted to be jq arguments.
   jq will be invoked and given the parsed input. The result of the jq
   command then will undergo output conversion.

Options:
   --in <value>         : input file (stdin)
   --in-format <value>  : input format one of json,xml,plist (auto)
   --no-jq              : don't run input plist through jq
   --no-lf              : don't append a linefeed to the output
   --out <value>        : output file (stdout)
   --out-format <value> : output format one of json,xml,(plist)


```



## Requirements

|   Requirement         | Release Version  | Description
|-----------------------|------------------|---------------
| [MulleFoundation](https://github.com/MulleFoundation/MulleFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag//.svg) [![Build Status](https://github.com///workflows/CI/badge.svg?branch=release)](https://github.com///actions/workflows/mulle-sde-ci.yml) | 💍 Umbrella library for the MulleFoundation
| [MulleObjCExpatFoundation](https://github.com/MulleFoundation/MulleObjCExpatFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag//.svg) [![Build Status](https://github.com///workflows/CI/badge.svg?branch=release)](https://github.com///actions/workflows/mulle-sde-ci.yml) | 👴🏼 XML parser based on MulleObjCStandardFoundation and libexpat
| [MulleObjCJSMNFoundation](https://github.com/MulleWeb/MulleObjCJSMNFoundation) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag//.svg) [![Build Status](https://github.com///workflows/CI/badge.svg?branch=release)](https://github.com///actions/workflows/mulle-sde-ci.yml) | 🌼 JSON support for mulle-objc
| [MulleFoundation-startup](https://github.com/MulleFoundation/MulleFoundation-startup) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag//.svg) [![Build Status](https://github.com///workflows/CI/badge.svg?branch=release)](https://github.com///actions/workflows/mulle-sde-ci.yml) | ▶️  Startup code for the MulleFoundation

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




