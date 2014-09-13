#!/bin/bash

android update project --name com.kaban.grasshopper --path . --target "android-19"
ndk-build    || { echo '------------------------ native build failed' ; exit 1; }
ant debug    || { echo '------------------------ apk create failed' ; exit 1; }
ant installd || { echo '------------------------ install failed' ; exit 1; }

