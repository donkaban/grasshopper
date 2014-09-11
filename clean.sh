#!/bin/bash

ant clean
ndk-build clean

rm -rf  ./libs
rm -rf  ./obj
rm -rf  ./build.xml
rm -rf  ./local.properties
rm -rf  ./proguard-project.txt
rm -rf  ./project.properties




