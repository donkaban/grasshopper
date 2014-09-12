#!/bin/bash

android update project --name com.kaban.grasshopper --path . --target "android-19"
ndk-build
ant debug
ant installd

